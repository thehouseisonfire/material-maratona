// atcoder/knapsack1.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, W;
  cin >> n >> W;

  vector<ll> dp(W + 1);

  for (int i = 0; i < n; i++) {
    int w, v;
    cin >> w >> v;

    for (int j = W; j >= w; j--)
      dp[j] = max(dp[j], dp[j - w] + v);
  }

  cout << dp[W] << '\n';
}
