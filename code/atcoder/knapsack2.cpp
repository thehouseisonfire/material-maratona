#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll W;
  cin >> n >> W;

  vector<pair<ll, int>> a(n);
  int sum = 0;

  for (auto &[w, v] : a) {
    cin >> w >> v;
    sum += v;
  }

  const ll INF = 4e18;
  vector<ll> dp(sum + 1, INF);
  dp[0] = 0;

  for (auto [w, v] : a) {
    for (int j = sum; j >= v; j--)
      dp[j] = min(dp[j], dp[j - v] + w);
  }

  int ans = 0;
  for (int v = 0; v <= sum; v++)
    if (dp[v] <= W)
      ans = v;

  cout << ans << '\n';
}
