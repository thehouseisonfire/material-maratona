// Subset sum com uma determinada quantidade de elementos

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &x : a)
    cin >> x;

  const int K = 4;

  vector<unordered_map<int, ll>> dp(K + 1);
  dp[0][0] = 1;

  for (int x : a)
    for (int k = K - 1; k >= 0; k--)
      for (auto [sum, cnt] : dp[k])
        dp[k + 1][sum + x] += cnt;

  int target;
  cin >> target;

  cout << dp[K][target] << '\n';
}
