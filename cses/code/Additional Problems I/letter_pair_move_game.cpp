// cses/Additional Problems I/letter_pair_move_game.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

map<string, string> build_bfs(const vector<string> &roots) {
  map<string, string> par;
  queue<string> q;

  for (auto s : roots) {
    if (!par.count(s)) {
      par[s] = "";
      q.push(s);
    }
  }

  int m = roots[0].size();

  while (!q.empty()) {
    string s = q.front();
    q.pop();

    int h = s.find("..");

    for (int i = 0; i + 1 < m; ++i) {
      if (s[i] == '.' || s[i + 1] == '.')
        continue;

      string t = s;
      swap(t[i], t[h]);
      swap(t[i + 1], t[h + 1]);

      if (!par.count(t)) {
        par[t] = s;
        q.push(t);
      }
    }
  }

  return par;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  string s;
  cin >> n >> s;

  vector<string> ans;

  auto move_pair = [&](int i, int j) {
    swap(s[i], s[j]);
    swap(s[i + 1], s[j + 1]);
    ans.push_back(s);
  };

  // Small cases: exact BFS.
  if (n <= 3) {
    string base(n - 1, 'A');
    base += string(n - 1, 'B');

    vector<string> roots;

    for (int h = 0; h < 2 * n - 1; ++h) {
      string t = base;
      t.insert(h, "..");
      roots.push_back(t);
    }

    auto par = build_bfs(roots);

    if (!par.count(s)) {
      cout << -1 << '\n';
      return 0;
    }

    while (!par[s].empty()) {
      s = par[s];
      ans.push_back(s);
    }
  } else {
    int m = 2 * n;

    // Move the empty pair to positions 0,1.
    int h = s.find("..");

    if (h > 1) {
      move_pair(h, 0);
    } else if (h == 1) {
      move_pair(1, 3);
      move_pair(3, 0);
    }

    // All 448 possible 8-cell states are reachable from one
    // of these sorted states.
    vector<string> roots;

    for (int a = 0; a <= 6; ++a)
      roots.push_back(".." + string(a, 'A') + string(6 - a, 'B'));

    auto par = build_bfs(roots);

    auto sort8 = [&](int l) {
      string cur = s.substr(l, 8);

      while (!par[cur].empty()) {
        cur = par[cur];
        s.replace(l, 8, cur);
        ans.push_back(s);
      }
    };

    int p = 0; // current position of ".."

    while (p + 8 < m) {
      // Fix two A's permanently.
      if (s[p + 2] == 'A' && s[p + 3] == 'A') {
        move_pair(p, p + 2);
        p += 2;
        continue;
      }

      // There is a B among the first two letters after "..".
      int b = (int)s.find('B', p + 2);
      size_t pos = s.find('A', b + 2);

      // The remaining disorder is inside the next 8 cells.
      if (pos == string::npos) {
        sort8(p);
        break;
      }

      int a = (int)pos;
      bool last = (a == m - 1);

      // If the last A is at the final position, use the BA pair.
      if (last)
        --a;

      // Swap the pair starting at b with the pair starting at a,
      // using ".." as temporary storage.
      move_pair(p, b);
      move_pair(b, a);
      move_pair(a, p);

      if (last)
        sort8(p);
    }

    sort8(p);
  }

  cout << ans.size() << '\n';
  for (auto &t : ans)
    cout << t << '\n';
}
