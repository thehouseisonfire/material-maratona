// atcoder/grid1.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int h, w;
  cin >> h >> w;

  vector<string> a(h);
  for (string &s : a)
    cin >> s;

  vector<int> dp(w);
  dp[0] = 1;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (a[i][j] == '#') {
        dp[j] = 0;
        continue;
      }

      if (j)
        dp[j] = (dp[j] + dp[j - 1]) % MOD;
    }
  }

  cout << dp[w - 1] << '\n';
}
