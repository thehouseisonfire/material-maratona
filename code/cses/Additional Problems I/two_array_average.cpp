#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> a(n + 1), b(n + 1);

  for (int i = 1; i <= n; i++) {
    ll x;
    cin >> x;
    a[i] = a[i - 1] + x;
  }

  for (int i = 1; i <= n; i++) {
    ll x;
    cin >> x;
    b[i] = b[i - 1] + x;
  }

  long double lo = 0, hi = 1e9;

  for (int it = 0; it < 60; it++) {
    long double mid = (lo + hi) / 2;

    long double bestA = -1e30L;
    long double bestB = -1e30L;

    for (int i = 1; i <= n; i++) {
      bestA = max(bestA, (long double)a[i] - mid * i);
      bestB = max(bestB, (long double)b[i] - mid * i);
    }

    if (bestA + bestB >= 0)
      lo = mid;
    else
      hi = mid;
  }

  int x = 1, y = 1;
  long double bestA = -1e30L;
  long double bestB = -1e30L;

  for (int i = 1; i <= n; i++) {
    long double cur = (long double)a[i] - lo * i;
    if (cur > bestA) {
      bestA = cur;
      x = i;
    }
  }

  for (int i = 1; i <= n; i++) {
    long double cur = (long double)b[i] - lo * i;
    if (cur > bestB) {
      bestB = cur;
      y = i;
    }
  }

  cout << x << ' ' << y << '\n';
}
