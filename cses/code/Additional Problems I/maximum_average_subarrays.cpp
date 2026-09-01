// cses/Additional Problems I/maximum_average_subarrays.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> s(n + 1);
  for (int i = 1; i <= n; i++) {
    ll x;
    cin >> x;
    s[i] = s[i - 1] + x;
  }

  auto cross = [&](int a, int b, int c) {
    return 1LL * (b - a) * (s[c] - s[a]) - 1LL * (c - a) * (s[b] - s[a]);
  };

  vector<int> hull;
  hull.push_back(0);

  for (int i = 1; i <= n; i++) {
    int l = 0, r = (int)hull.size() - 1;

    while (l < r) {
      int m = (l + r) / 2;

      // slope(hull[m], i) >= slope(hull[m+1], i)
      if (cross(hull[m], hull[m + 1], i) <= 0)
        r = m;
      else
        l = m + 1;
    }

    cout << i - hull[l] << " \n"[i == n];

    while (hull.size() >= 2 &&
           cross(hull[hull.size() - 2], hull.back(), i) <= 0) {
      hull.pop_back();
    }

    hull.push_back(i);
  }
}
