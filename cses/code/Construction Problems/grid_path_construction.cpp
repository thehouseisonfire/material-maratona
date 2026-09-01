// cses/Construction Problems/grid_path_construction.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int dy[4] = {1, 0, -1, 0};
const int dx[4] = {0, 1, 0, -1};
const char dc[4] = {'D', 'R', 'U', 'L'};

int id(char c) {
  if (c == 'D')
    return 0;
  if (c == 'R')
    return 1;
  if (c == 'U')
    return 2;
  return 3;
}

bool possible(int n, int m, int sy, int sx, int ty, int tx) {
  if (sy == ty && sx == tx)
    return n * m == 1;

  if (n > m) {
    swap(n, m);
    swap(sy, sx);
    swap(ty, tx);
  }

  if (sx > tx) {
    swap(sx, tx);
    swap(sy, ty);
  }

  if (n == 1)
    return sx == 0 && tx == m - 1;

  if (n == 2) {
    if (sx == tx)
      return sx == 0 || sx == m - 1;

    return (sx + sy) % 2 != (tx + ty) % 2;
  }

  if (n * m % 2)
    return (sx + sy) % 2 == 0 && (tx + ty) % 2 == 0;

  if (n == 3) {
    if ((sx + sy) % 2 == (tx + ty) % 2)
      return false;

    if ((sx + sy) % 2 == 1 && (sx < tx - 1 || (sy == 1 && sx < tx)))
      return false;

    if ((tx + ty) % 2 == 1 && (tx < sx - 1 || (ty == 1 && tx < sx)))
      return false;

    return true;
  }

  return (sx + sy) % 2 != (tx + ty) % 2;
}

// Exact solver only for rectangles up to 4 x 5.
string small_path(int n, int m, int sy, int sx, int ty, int tx) {
  int N = n * m;
  int S = sy * m + sx;
  int T = ty * m + tx;

  vector<char> vis(N);
  vector<int> path;
  vis[S] = true;

  auto inside = [&](int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < m;
  };

  function<bool(int, int)> dfs = [&](int v, int used) {
    if (used == N)
      return v == T;

    int y = v / m;
    int x = v % m;

    vector<pair<int, int>> cand;

    for (int d = 0; d < 4; d++) {
      int ny = y + dy[d];
      int nx = x + dx[d];

      if (!inside(ny, nx))
        continue;

      int u = ny * m + nx;

      if (vis[u])
        continue;

      if (u == T && used + 1 < N)
        continue;

      int deg = 0;

      for (int e = 0; e < 4; e++) {
        int yy = ny + dy[e];
        int xx = nx + dx[e];

        if (inside(yy, xx) && !vis[yy * m + xx])
          deg++;
      }

      cand.push_back({deg, d});
    }

    sort(cand.begin(), cand.end());

    for (auto [_, d] : cand) {
      int ny = y + dy[d];
      int nx = x + dx[d];
      int u = ny * m + nx;

      vis[u] = true;
      path.push_back(d);

      bool connected = true;

      if (used + 1 < N) {
        vector<char> seen(N);
        queue<int> q;

        q.push(u);
        seen[u] = true;

        int cnt = 1;

        while (!q.empty()) {
          int a = q.front();
          q.pop();

          int ay = a / m;
          int ax = a % m;

          for (int e = 0; e < 4; e++) {
            int by = ay + dy[e];
            int bx = ax + dx[e];

            if (!inside(by, bx))
              continue;

            int b = by * m + bx;

            if (seen[b] || (vis[b] && b != u))
              continue;

            seen[b] = true;
            q.push(b);
            cnt++;
          }
        }

        connected = (cnt == N - used);
      }

      if (connected && dfs(u, used + 1))
        return true;

      path.pop_back();
      vis[u] = false;
    }

    return false;
  };

  dfs(S, 1);

  string res;
  for (int d : path)
    res += dc[d];

  return res;
}

string build(int n, int m, int sy, int sx, int ty, int tx) {
  // Rotate until n <= m.
  if (n > m) {
    string res = build(m, n, m - 1 - sx, sy, m - 1 - tx, ty);

    for (char &c : res) {
      if (c == 'D')
        c = 'L';
      else if (c == 'R')
        c = 'D';
      else if (c == 'U')
        c = 'R';
      else
        c = 'U';
    }

    return res;
  }

  // Reflect until sx <= tx.
  if (sx > tx) {
    string res = build(n, m, sy, m - 1 - sx, ty, m - 1 - tx);

    for (char &c : res) {
      if (c == 'L')
        c = 'R';
      else if (c == 'R')
        c = 'L';
    }

    return res;
  }

  // Reflect until sy <= ty.
  if (sy > ty) {
    string res = build(n, m, n - 1 - sy, sx, n - 1 - ty, tx);

    for (char &c : res) {
      if (c == 'U')
        c = 'D';
      else if (c == 'D')
        c = 'U';
    }

    return res;
  }

  if (n == 1)
    return string(m - 1, 'R');

  // Adjacent endpoints in a 2-row grid.
  if (n == 2 && sy == ty && sx + 1 == tx) {
    string res;

    res += string(sx, 'L');
    res += sy == 0 ? 'D' : 'U';
    res += string(m - 1, 'R');
    res += sy == 0 ? 'U' : 'D';
    res += string(m - 1 - tx, 'L');

    return res;
  }

  if (n <= 4 && m <= 5)
    return small_path(n, m, sy, sx, ty, tx);

  // Strip two columns from the left.
  if (sx >= 2 && possible(n, m - 2, sy, sx - 2, ty, tx - 2)) {
    string res = build(n, m - 2, sy, sx - 2, ty, tx - 2);

    int y = sy;
    int x = sx - 2;

    for (int i = 0; i < (int)res.size(); i++) {
      int d = id(res[i]);

      int ny = y + dy[d];
      int nx = x + dx[d];

      if (x == 0 && nx == 0) {
        return res.substr(0, i) + "L" + build(n, 2, y, 1, ny, 1) + "R" +
               res.substr(i + 1);
      }

      y = ny;
      x = nx;
    }
  }

  // Strip two columns from the right.
  if (tx <= m - 3 && possible(n, m - 2, sy, sx, ty, tx)) {
    string res = build(n, m - 2, sy, sx, ty, tx);

    int y = sy;
    int x = sx;

    for (int i = 0; i < (int)res.size(); i++) {
      int d = id(res[i]);

      int ny = y + dy[d];
      int nx = x + dx[d];

      if (x == m - 3 && nx == m - 3) {
        return res.substr(0, i) + "R" + build(n, 2, y, 0, ny, 0) + "L" +
               res.substr(i + 1);
      }

      y = ny;
      x = nx;
    }
  }

  // Horizontal split.
  for (int r = sy; r < ty; r++) {
    for (int c = 0; c < m; c++) {
      if (possible(r + 1, m, sy, sx, r, c) &&
          possible(n - r - 1, m, 0, c, ty - r - 1, tx)) {
        return build(r + 1, m, sy, sx, r, c) + "D" +
               build(n - r - 1, m, 0, c, ty - r - 1, tx);
      }
    }
  }

  // Vertical split.
  for (int c = sx; c < tx; c++) {
    for (int r = 0; r < n; r++) {
      if (possible(n, c + 1, sy, sx, r, c) &&
          possible(n, m - c - 1, r, 0, ty, tx - c - 1)) {
        return build(n, c + 1, sy, sx, r, c) + "R" +
               build(n, m - c - 1, r, 0, ty, tx - c - 1);
      }
    }
  }

  return "";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    int n, m, y1, x1, y2, x2;
    cin >> n >> m >> y1 >> x1 >> y2 >> x2;

    --y1;
    --x1;
    --y2;
    --x2;

    if (!possible(n, m, y1, x1, y2, x2)) {
      cout << "NO\n";
      continue;
    }

    cout << "YES\n";
    cout << build(n, m, y1, x1, y2, x2) << '\n';
  }
}
