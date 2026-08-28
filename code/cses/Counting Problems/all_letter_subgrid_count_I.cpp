#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static unsigned short dp[2][3001][26];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  const int INF = 6000;

  for (int t = 0; t < 2; t++)
    for (int j = 0; j <= n; j++)
      for (int c = 0; c < k; c++)
        dp[t][j][c] = INF;

  ll ans = 0;

  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;

    int cur = i & 1;
    int pre = cur ^ 1;

    for (int c = 0; c < k; c++)
      dp[cur][0][c] = INF;

    for (int j = 1; j <= n; j++) {
      int here = s[j - 1] - 'A';
      int need = 1;

      for (int c = 0; c < here; c++) {
        int x = min({dp[pre][j][c], dp[cur][j - 1][c], dp[pre][j - 1][c]}) + 1;

        dp[cur][j][c] = x;
        need = max(need, x);
      }

      dp[cur][j][here] = 1;

      for (int c = here + 1; c < k; c++) {
        int x = min({dp[pre][j][c], dp[cur][j - 1][c], dp[pre][j - 1][c]}) + 1;

        dp[cur][j][c] = x;
        need = max(need, x);
      }

      ans += max(0, min(i, j) - need + 1);
    }
  }

  cout << ans << '\n';
}
