#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int ans[8][8];

int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};

bool valid(int x, int y) {
  return x >= 0 && x < 8 && y >= 0 && y < 8 && ans[y][x] == 0;
}

// Number of moves available after entering (x, y).
int degree(int x, int y) {
  int cnt = 0;

  for (int k = 0; k < 8; k++)
    if (valid(x + dx[k], y + dy[k]))
      cnt++;

  return cnt;
}

bool dfs(int x, int y, int step) {
  ans[y][x] = step;

  if (step == 64)
    return true;

  // {degree, x, y}
  vector<tuple<int, int, int>> moves;

  for (int k = 0; k < 8; k++) {
    int nx = x + dx[k];
    int ny = y + dy[k];

    if (valid(nx, ny))
      moves.push_back({degree(nx, ny), nx, ny});
  }

  // Warnsdorff: visit the most constrained square first.
  sort(moves.begin(), moves.end());

  for (auto [d, nx, ny] : moves)
    if (dfs(nx, ny, step + 1))
      return true;

  ans[y][x] = 0;
  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int x, y;
  cin >> x >> y;
  x--, y--;

  dfs(x, y, 1);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++)
      cout << ans[i][j] << ' ';
    cout << '\n';
  }
}
