// atcoder/digit-sum.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string k;
  int d;
  cin >> k >> d;

  vector<vector<int>> dp(d, vector<int>(2));
  dp[0][0] = 1;

  for (char c : k) {
    int lim = c - '0';
    vector<vector<int>> ndp(d, vector<int>(2));

    for (int r = 0; r < d; r++) {
      for (int less = 0; less < 2; less++) {
        int hi = less ? 9 : lim;

        for (int x = 0; x <= hi; x++) {
          int nr = (r + x) % d;
          int nl = less || x < lim;

          ndp[nr][nl] += dp[r][less];
          if (ndp[nr][nl] >= MOD)
            ndp[nr][nl] -= MOD;
        }
      }
    }

    dp.swap(ndp);
  }

  int ans = (dp[0][0] + dp[0][1] - 1 + MOD) % MOD;

  cout << ans << '\n';
}
