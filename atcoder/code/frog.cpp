// atcoder/frog.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<ll> h(n), dp(n, 1e18);
  for (ll &x : h)
    cin >> x;

  dp[0] = 0;

  for (int i = 1; i < n; i++) {
    dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]);

    if (i >= 2)
      dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
  }

  cout << dp[n - 1] << '\n';
}
