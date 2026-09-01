// cses/Counting Problems/tournament_graph_distribution.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1'000'000'007;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  static ll C[501][501];
  static ll dp[501][501];

  vector<ll> all(n + 1), strong(n + 1);

  // Binomial coefficients
  for (int i = 0; i <= n; i++) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; j++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
  }

  // all[i] = number of tournaments on i vertices
  //        = 2^(i choose 2)
  all[0] = 1;
  ll p2 = 1;
  for (int i = 1; i <= n; i++) {
    all[i] = all[i - 1] * p2 % MOD;
    p2 = p2 * 2 % MOD;
  }

  // strong[i] = number of strongly connected tournaments on i vertices.
  // Pick the first SCC; all its edges point towards the remaining vertices.
  for (int i = 1; i <= n; i++) {
    strong[i] = all[i];

    for (int s = 1; s < i; s++) {
      ll ways = C[i][s] * strong[s] % MOD * all[i - s] % MOD;
      strong[i] -= ways;
      if (strong[i] < 0)
        strong[i] += MOD;
    }
  }

  // dp[i][k] = tournaments on i vertices with exactly k SCCs.
  dp[0][0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int s = 1; s <= i; s++) {
      ll ways = C[i][s] * strong[s] % MOD;

      for (int k = 1; k <= i - s + 1; k++) {
        dp[i][k] += ways * dp[i - s][k - 1] % MOD;
        if (dp[i][k] >= MOD)
          dp[i][k] -= MOD;
      }
    }
  }

  for (int k = 1; k <= n; k++)
    cout << dp[n][k] << '\n';
}
