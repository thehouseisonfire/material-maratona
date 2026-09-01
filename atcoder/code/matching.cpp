// atcoder/matching.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<vector<int>> a(n, vector<int>(n));

  for (auto &row : a)
    for (int &x : row)
      cin >> x;

  vector<ll> dp(1 << n);
  dp[0] = 1;

  for (int mask = 0; mask < (1 << n); mask++) {
    int i = __builtin_popcount(mask);

    if (i == n)
      continue;

    for (int j = 0; j < n; j++) {
      if (a[i][j] && !(mask >> j & 1)) {
        int nxt = mask | (1 << j);
        dp[nxt] = (dp[nxt] + dp[mask]) % MOD;
      }
    }
  }

  cout << dp[(1 << n) - 1] << '\n';
}
