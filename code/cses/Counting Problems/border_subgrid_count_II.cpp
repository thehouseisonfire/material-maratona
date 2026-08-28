#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<string> g(n);
  for (auto &s : g)
    cin >> s;

  // down[i][j] = number of equal letters starting at (i,j) going down
  vector<vector<int>> down(n, vector<int>(n, 1));

  for (int i = n - 2; i >= 0; --i)
    for (int j = 0; j < n; ++j)
      if (g[i][j] == g[i + 1][j])
        down[i][j] = down[i + 1][j] + 1;

  vector<ll> ans(k);

  for (int top = 0; top < n; ++top) {
    for (int bot = top; bot < n; ++bot) {
      int h = bot - top + 1;
      char cur = 0;
      ll cnt = 0;

      for (int col = 0; col < n; ++col) {
        if (g[top][col] != g[bot][col]) {
          cur = 0;
          cnt = 0;
          continue;
        }

        char c = g[top][col];

        // Start of a new horizontal run.
        if (c != cur) {
          cur = c;
          cnt = 0;
        }

        // This column can be the right border.
        if (down[top][col] >= h) {
          ++cnt;
          ans[c - 'A'] += cnt;
        }
      }
    }
  }

  for (ll x : ans)
    cout << x << '\n';
}
