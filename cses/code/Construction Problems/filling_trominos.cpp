// cses/Construction Problems/filling_trominos.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    int n = N, m = M;
    bool transposed = false;

    // Make n divisible by 3.
    if (n % 3 != 0) {
      swap(n, m);
      transposed = true;
    }

    if (n % 3 != 0 || n == 1 || m == 1) {
      cout << "NO\n";
      continue;
    }

    // Odd 3 x odd is impossible.
    if (n % 2 && m % 2 && (n == 3 || m == 3)) {
      cout << "NO\n";
      continue;
    }

    vector<vector<int>> a(n, vector<int>(m, -1));
    int ids = 0;

    // Fill a 3 x 2 block.
    auto tile32 = [&](int r, int c) {
      int x = ids++;
      a[r][c] = a[r][c + 1] = a[r + 1][c] = x;

      x = ids++;
      a[r + 1][c + 1] = a[r + 2][c] = a[r + 2][c + 1] = x;
    };

    // Fill a 2 x 3 block.
    auto tile23 = [&](int r, int c) {
      int x = ids++;
      a[r][c] = a[r][c + 1] = a[r + 1][c] = x;

      x = ids++;
      a[r][c + 2] = a[r + 1][c + 1] = a[r + 1][c + 2] = x;
    };

    if (m % 2 == 0) {
      // Entire grid = 3 x 2 blocks.
      for (int i = 0; i < n; i += 3)
        for (int j = 0; j < m; j += 2)
          tile32(i, j);

    } else if (n % 2 == 0) {
      // First 3 columns = 2 x 3 blocks.
      for (int i = 0; i < n; i += 2)
        tile23(i, 0);

      // Rest = 3 x 2 blocks.
      for (int i = 0; i < n; i += 3)
        for (int j = 3; j < m; j += 2)
          tile32(i, j);

    } else {
      // Both dimensions are odd.
      // Use one fixed 9 x 5 solution.
      const vector<string> p = {
          "AACAA", "AECCA", "GEEGG", "GGBAG", "DBBAA",
          "DDIIG", "AAIGG", "ADFFD", "DDFDD",
      };

      bool vis[9][5] = {};

      for (int si = 0; si < 9; si++) {
        for (int sj = 0; sj < 5; sj++) {
          if (vis[si][sj])
            continue;

          int x = ids++;
          char ch = p[si][sj];

          queue<pair<int, int>> q;
          q.push({si, sj});
          vis[si][sj] = true;

          while (!q.empty()) {
            auto [i, j] = q.front();
            q.pop();

            a[i][j] = x;

            const int di[] = {1, -1, 0, 0};
            const int dj[] = {0, 0, 1, -1};

            for (int d = 0; d < 4; d++) {
              int ni = i + di[d];
              int nj = j + dj[d];

              if (ni < 0 || ni >= 9 || nj < 0 || nj >= 5)
                continue;
              if (vis[ni][nj] || p[ni][nj] != ch)
                continue;

              vis[ni][nj] = true;
              q.push({ni, nj});
            }
          }
        }
      }

      // Remaining bottom-left rectangle: (n-9) x 5.
      for (int i = 9; i < n; i += 2)
        tile23(i, 0);

      for (int i = 9; i < n; i += 3)
        tile32(i, 3);

      // Remaining right rectangle: n x (m-5).
      for (int i = 0; i < n; i += 3)
        for (int j = 5; j < m; j += 2)
          tile32(i, j);
    }

    // Build adjacency graph between trominos.
    vector<vector<int>> adj(ids);

    auto add_edge = [&](int x, int y) {
      if (x != y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
      }
    };

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++) {
        if (i + 1 < n)
          add_edge(a[i][j], a[i + 1][j]);
        if (j + 1 < m)
          add_edge(a[i][j], a[i][j + 1]);
      }

    // Give adjacent trominos different letters.
    vector<char> color(ids);

    for (int x = 0; x < ids; x++) {
      bool used[26] = {};

      for (int y : adj[x])
        if (y < x)
          used[color[y] - 'A'] = true;

      for (int c = 0; c < 26; c++)
        if (!used[c]) {
          color[x] = 'A' + c;
          break;
        }
    }

    cout << "YES\n";

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int x = transposed ? a[j][i] : a[i][j];
        cout << color[x];
      }
      cout << '\n';
    }
  }
}
