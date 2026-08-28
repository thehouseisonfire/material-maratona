#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> dp(n + 1);
  dp[1] = 1;

  for (int i = 2; i <= n; i++) {
    for (int k = i; k >= 1; k--) {
      dp[k] = (k * dp[k] + (i - k + 1LL) * dp[k - 1]) % MOD;
    }
  }

  for (int k = 1; k <= n; k++)
    cout << dp[k] << '\n';
}
