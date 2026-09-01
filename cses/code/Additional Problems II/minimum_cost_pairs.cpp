// cses/Additional Problems II/minimum_cost_pairs.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> x(n);
  for (ll &v : x)
    cin >> v;
  sort(x.begin(), x.end());

  const ll INF = (1LL << 62);

  // Edge i joins x[i-1] and x[i], for 1 <= i < n.
  // Edges 0 and n are infinite sentinels.
  vector<ll> w(n + 1, INF);
  vector<int> prv(n + 1), nxt(n + 1);
  vector<char> alive(n + 1, true);

  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;

  for (int i = 1; i < n; ++i) {
    w[i] = x[i] - x[i - 1];
    pq.push({w[i], i});
  }

  for (int i = 0; i <= n; ++i) {
    prv[i] = i - 1;
    nxt[i] = i + 1;
  }
  prv[0] = -1;
  nxt[n] = -1;

  ll ans = 0;

  for (int k = 1; k <= n / 2; ++k) {
    ll cost;
    int i;

    while (true) {
      tie(cost, i) = pq.top();
      pq.pop();

      if (alive[i] && cost == w[i])
        break;
    }

    ans += cost;
    cout << ans << (k == n / 2 ? '\n' : ' ');

    int l = prv[i];
    int r = nxt[i];

    // Regret choosing i:
    // replace it by choosing both neighboring edges.
    ll nw = INF;
    if (w[l] < INF / 2 && w[r] < INF / 2)
      nw = w[l] + w[r] - w[i];

    alive[l] = false;
    alive[r] = false;

    int ll = prv[l];
    int rr = nxt[r];

    prv[i] = ll;
    nxt[i] = rr;

    if (ll != -1)
      nxt[ll] = i;
    if (rr != -1)
      prv[rr] = i;

    w[i] = nw;
    if (nw < INF / 2)
      pq.push({nw, i});
  }
}
