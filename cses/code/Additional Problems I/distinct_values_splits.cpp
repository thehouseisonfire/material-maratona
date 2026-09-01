// cses/Additional Problems I/distinct_values_splits.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &x : a)
    cin >> x;

  vector<ll> dp(n + 1), sum(n + 1);
  unordered_map<int, int> last;
  last.reserve(2 * n);

  dp[0] = sum[0] = 1;

  int l = 0;

  for (int i = 0; i < n; i++) {
    if (last.count(a[i]))
      l = max(l, last[a[i]] + 1);

    last[a[i]] = i;

    dp[i + 1] = sum[i];
    if (l > 0)
      dp[i + 1] = (dp[i + 1] - sum[l - 1] + MOD) % MOD;

    sum[i + 1] = (sum[i] + dp[i + 1]) % MOD;
  }

  cout << dp[n] << '\n';
}
