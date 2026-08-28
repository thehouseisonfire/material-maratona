#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<ll> a(n);
  for (ll &x : a)
    cin >> x;
  sort(a.begin(), a.end());

  ll base = 0;
  for (int i = 0; i < m; i++)
    base += a[i];

  // (sum, p, x, y)
  // p = leftmost position differing from [0,1,...,m-1]
  // x = selected index at position p
  // y = selected index at position p+1, or n
  using T = tuple<ll, int, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;

  cout << base;
  int done = 1;

  if (m < n) {
    pq.push({base + a[m] - a[m - 1], m - 1, m, n});
  }

  while (done < k) {
    auto [sum, p, x, y] = pq.top();
    pq.pop();

    cout << ' ' << sum;
    done++;

    // Move the current changed index one step right.
    if (x + 1 < y) {
      pq.push({sum + a[x + 1] - a[x], p, x + 1, y});
    }

    // Make position p-1 the new leftmost changed position.
    if (p > 0) {
      pq.push({sum + a[p] - a[p - 1], p - 1, p, x});
    }
  }

  cout << '\n';
}
