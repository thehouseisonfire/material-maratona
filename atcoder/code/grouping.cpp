// atcoder/grouping.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<vector<ll>> a(n, vector<ll>(n));

  for (auto &row : a)
    for (ll &x : row)
      cin >> x;

  int N = 1 << n;

  vector<ll> score(N);

  for (int mask = 1; mask < N; mask++) {
    int i = __builtin_ctz(mask);
    int rest = mask ^ (1 << i);

    score[mask] = score[rest];

    for (int j = 0; j < n; j++)
      if (rest >> j & 1)
        score[mask] += a[i][j];
  }

  vector<ll> dp(N);
  dp[0] = 0;

  for (int mask = 1; mask < N; mask++) {
    int bit = mask & -mask;
    dp[mask] = score[mask];

    for (int sub = mask; sub; sub = (sub - 1) & mask) {
      if (!(sub & bit))
        continue;

      dp[mask] = max(dp[mask], score[sub] + dp[mask ^ sub]);
    }
  }

  cout << dp[N - 1] << '\n';
}
