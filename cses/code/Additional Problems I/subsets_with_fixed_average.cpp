// cses/Additional Problems I/subsets_with_fixed_average.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, a;
  cin >> n >> a;

  vector<int> v(n);

  int pos = 0, neg = 0;

  for (int &x : v) {
    cin >> x;
    x -= a;

    if (x > 0)
      pos += x;
    else
      neg -= x;
  }

  sort(v.rbegin(), v.rend());

  int m = min(pos, neg);

  vector<int> dp(m + 1);
  dp[0] = 1;

  for (int x : v) {
    if (x > 0) {
      if (x > m)
        continue;

      for (int s = m; s >= x; --s) {
        dp[s] += dp[s - x];
        if (dp[s] >= MOD)
          dp[s] -= MOD;
      }
    } else if (x == 0) {
      for (int s = 0; s <= m; ++s) {
        dp[s] = 2LL * dp[s] % MOD;
      }
    } else {
      int d = -x;

      if (d > m)
        continue;

      for (int s = 0; s + d <= m; ++s) {
        dp[s] += dp[s + d];
        if (dp[s] >= MOD)
          dp[s] -= MOD;
      }
    }
  }

  cout << (dp[0] - 1 + MOD) % MOD << '\n';
}
