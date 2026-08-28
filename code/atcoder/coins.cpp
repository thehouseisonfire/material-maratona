#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<double> dp(n + 1);
  dp[0] = 1;

  for (int i = 0; i < n; i++) {
    double p;
    cin >> p;

    for (int j = i + 1; j >= 0; j--) {
      dp[j] *= 1 - p;

      if (j)
        dp[j] += dp[j - 1] * p;
    }
  }

  double ans = 0;

  for (int heads = n / 2 + 1; heads <= n; heads++)
    ans += dp[heads];

  cout << fixed << setprecision(10) << ans << '\n';
}
