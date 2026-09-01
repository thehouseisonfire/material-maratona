// atcoder/frog3.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
  ll m, b;

  ll get(ll x) { return m * x + b; }
};

bool bad(Line a, Line b, Line c) {
  return (__int128)(b.b - a.b) * (b.m - c.m) >=
         (__int128)(c.b - b.b) * (a.m - b.m);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll C;
  cin >> n >> C;

  vector<ll> h(n), dp(n);
  for (ll &x : h)
    cin >> x;

  deque<Line> hull;

  hull.push_back({-2 * h[0], h[0] * h[0]});

  for (int i = 1; i < n; i++) {
    ll x = h[i];

    while (hull.size() >= 2 && hull[0].get(x) >= hull[1].get(x))
      hull.pop_front();

    dp[i] = x * x + C + hull[0].get(x);

    Line cur = {-2 * x, dp[i] + x * x};

    while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull.back(), cur))
      hull.pop_back();

    hull.push_back(cur);
  }

  cout << dp[n - 1] << '\n';
}
