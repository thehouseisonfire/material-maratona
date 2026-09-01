// atcoder/slimes.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<ll> a(n), pref(n + 1);

  for (int i = 0; i < n; i++) {
    cin >> a[i];
    pref[i + 1] = pref[i] + a[i];
  }

  const ll INF = 4e18;
  vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));

  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len <= n; l++) {
      int r = l + len;
      dp[l][r] = INF;

      for (int m = l + 1; m < r; m++)
        dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r] + pref[r] - pref[l]);
    }
  }

  cout << dp[0][n] << '\n';
}
