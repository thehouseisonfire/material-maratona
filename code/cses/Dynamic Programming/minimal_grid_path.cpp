#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  int n;
  cin >> n;

  vector<string> grid(n);
  for (auto &s : grid)
    cin >> s;

  string ans;
  ans += grid[0][0];

  // Current cells are represented only by their row.
  // On diagonal d, column = d - row.
  vector<int> cur = {0}, nxt;
  vector<int> seen(n, -1);

  for (int d = 0; d < 2 * n - 2; d++) {
    char best = '{'; // one after 'Z'
    nxt.clear();

    auto add = [&](int r, int c) {
      char ch = grid[r][c];

      if (ch < best) {
        best = ch;
        nxt.clear();
      }

      if (ch == best && seen[r] != d) {
        seen[r] = d;
        nxt.push_back(r);
      }
    };

    for (int r : cur) {
      int c = d - r;

      if (c + 1 < n)
        add(r, c + 1);

      if (r + 1 < n)
        add(r + 1, c);
    }

    ans += best;
    cur.swap(nxt);
  }

  cout << ans << '\n';
}
