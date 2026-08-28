#include <bits/stdc++.h>
using namespace std;
using ll = long long;

unordered_map<ll, pair<ll, ll>> memo[10];

// mx = largest digit in the prefix outside n
// returns {number of steps, remainder after n is reduced to <= 0}
pair<ll, ll> solve(int mx, ll n) {
  if (n == 0)
    return {0, 0};
  if (n < 10)
    return {1, n - max<ll>(mx, n)};

  auto it = memo[mx].find(n);
  if (it != memo[mx].end())
    return it->second;

  ll p = 1;
  while (p <= n / 10)
    p *= 10;

  pair<ll, ll> ans;

  if (n % p == 0) {
    // Empty suffix: perform one greedy step directly.
    int d = max(mx, int(n / p));
    auto cur = solve(mx, n - d);
    ans = {cur.first + 1, cur.second};
  } else {
    int first = n / p;

    // Process the suffix while the leading digit stays unchanged.
    auto low = solve(max(mx, first), n % p);

    // The suffix may borrow from the prefix.
    auto high = solve(mx, n / p * p + low.second);

    ans = {low.first + high.first, high.second};
  }

  return memo[mx][n] = ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  cin >> n;

  cout << solve(0, n).first << '\n';
}
