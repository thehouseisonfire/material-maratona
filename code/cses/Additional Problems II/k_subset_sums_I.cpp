#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<ll> a(n);
  ll base = 0;

  for (ll &x : a) {
    cin >> x;
    if (x < 0)
      base += x;
    x = abs(x);
  }

  sort(a.begin(), a.end());

  // (subset sum, largest index used)
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;

  cout << base;

  if (k == 1) {
    cout << '\n';
    return 0;
  }

  pq.push({a[0], 0});

  for (int cnt = 1; cnt < k; cnt++) {
    auto [sum, i] = pq.top();
    pq.pop();

    cout << ' ' << base + sum;

    if (i + 1 < n) {
      // Keep a[i], also add a[i+1].
      pq.push({sum + a[i + 1], i + 1});

      // Replace a[i] by a[i+1].
      pq.push({sum - a[i] + a[i + 1], i + 1});
    }
  }

  cout << '\n';
}
