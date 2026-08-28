// https://cses.fi/problemset/result/14125885/
// CSES - Graphs - Labyrinth

#include <bits/stdc++.h>

using namespace std;

const char WALL = '#';
const char START = 'A';
const char END = 'B';
const int MAX = 1005;

using pi = pair<int, int>;

int n, m;

pi start, End;

char mtx[MAX][MAX];
bool visited[MAX][MAX];
pi parent[MAX][MAX];

int counter = 0;

string traceback() {
  string res;
  auto prev = End;
  while (prev != start) {
    counter++;
    const auto [px, py] = prev;
    const auto [x, y] = parent[px][py];
    if (x + 1 == px && y == py)
      res.push_back('D');
    if (x - 1 == px && y == py)
      res.push_back('U');
    if (x == px && y + 1 == py)
      res.push_back('R');
    if (x == px && y - 1 == py)
      res.push_back('L');
    prev = {x, y};
  }
  return res;
}

bool valid(int x, int y) {
  return !(x < 0 || y < 0 || x == n || y == m || mtx[x][y] == WALL);
}

bool bfs() {
  queue<pi> q;
  q.push(start);
  visited[start.first][start.second] = true;
  while (!q.empty()) {
    const auto curr = q.front();
    q.pop();
    const auto [x, y] = curr;
    if (curr == End)
      return true;
    pi options[4] = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
    for (const auto &[nx, ny] : options) {
      if (valid(nx, ny) && !visited[nx][ny]) {
        visited[nx][ny] = true;
        parent[nx][ny] = {x, y};
        q.push({nx, ny});
      }
    }
  }
  return false;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> n >> m;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      char aux;
      cin >> aux;
      mtx[i][j] = aux;
      if (aux == START)
        start = {i, j};
      if (aux == END)
        End = {i, j};
    }
  }

  bool found = bfs();
  if (!found) {
    cout << "NO" << endl;
    return 0;
  }
  cout << "YES" << endl;
  string res = traceback();
  cout << counter << endl;
  reverse(res.begin(), res.end());
  cout << res << endl;

  return 0;
}
