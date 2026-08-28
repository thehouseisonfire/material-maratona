#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  ll k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &x : a)
    cin >> x;

  int r = min<ll>(n - 1, k);

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  for (int i = 0; i <= r; i++)
    pq.push({a[i], i});

  int nxt = r + 1;

  for (int i = 0; i < n; i++) {
    auto [x, id] = pq.top();
    pq.pop();

    cout << x << " \n"[i == n - 1];

    if (nxt < n) {
      pq.push({a[nxt], nxt});
      nxt++;
    }
  }
}
