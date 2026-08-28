#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<ll> a(n), dp(n);

  for (ll &x : a)
    cin >> x;

  dp = a;

  for (int len = 2; len <= n; len++) {
    for (int l = 0; l + len <= n; l++) {
      int r = l + len - 1;

      dp[l] = max(a[l] - dp[l + 1], a[r] - dp[l]);
    }
  }

  cout << dp[0] << '\n';
}
