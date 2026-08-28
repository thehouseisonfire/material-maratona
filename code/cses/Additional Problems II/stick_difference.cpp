#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<ll> a(n);
  for (ll &x : a)
    cin >> x;

  // hi[k] = best possible maximum piece after k cuts.
  // lo[k] = minimum piece in the greedy construction for hi[k].
  vector<ll> hi(m + 1), lo(m + 1), diff(m + 1);
  vector<int> cnt(n, 1);

  priority_queue<pair<ll, int>> pq;
  for (int i = 0; i < n; ++i)
    pq.push({a[i], i});

  hi[0] = pq.top().first;
  lo[0] = *min_element(a.begin(), a.end());
  diff[0] = hi[0] - lo[0];

  for (int k = 1; k <= m; ++k) {
    int i = pq.top().second;
    pq.pop();

    ++cnt[i];

    ll mx = (a[i] + cnt[i] - 1) / cnt[i];
    ll mn = a[i] / cnt[i];

    pq.push({mx, i});

    hi[k] = pq.top().first;
    lo[k] = min(lo[k - 1], mn);
    diff[k] = hi[k] - lo[k];
  }

  // best_min = largest possible minimum piece after k cuts.
  fill(cnt.begin(), cnt.end(), 1);

  priority_queue<pair<ll, int>> next_min;
  for (int i = 0; i < n; ++i)
    next_min.push({a[i] / 2, i});

  ll best_min = lo[0];

  // p = last j with lo[j] >= best_min.
  // q maintains min(diff[j]) for j in (p, k].
  int p = 0;
  deque<int> q;

  for (int k = 1; k <= m; ++k) {
    auto [mn, i] = next_min.top();
    next_min.pop();

    best_min = min(best_min, mn);

    ++cnt[i];
    next_min.push({a[i] / (cnt[i] + 1), i});

    while (!q.empty() && diff[q.back()] >= diff[k])
      q.pop_back();
    q.push_back(k);

    while (p < k && lo[p + 1] >= best_min)
      ++p;

    while (!q.empty() && q.front() <= p)
      q.pop_front();

    ll ans = hi[p] - best_min;

    if (!q.empty())
      ans = min(ans, diff[q.front()]);

    cout << ans << (k == m ? '\n' : ' ');
  }
}
