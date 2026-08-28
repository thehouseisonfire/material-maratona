#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  vector<ll> h(n), dp(n, 1e18);
  for (ll &x : h)
    cin >> x;

  dp[0] = 0;

  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= k && i - j >= 0; j++) {
      dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
    }
  }

  cout << dp[n - 1] << '\n';
}
