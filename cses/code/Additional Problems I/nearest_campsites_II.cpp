// cses/Additional Problems I/nearest_campsites_II.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
  int n;
  vector<int> bit;

  Fenwick(int n) : n(n), bit(n + 1, INT_MIN) {}

  void update(int i, int x) {
    for (; i <= n; i += i & -i)
      bit[i] = max(bit[i], x);
  }

  int query(int i) {
    int res = INT_MIN;
    for (; i; i -= i & -i)
      res = max(res, bit[i]);
    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> a(n), q(m);
  for (auto &[x, y] : a)
    cin >> x >> y;
  for (auto &[x, y] : q)
    cin >> x >> y;

  vector<int> ans(m, INT_MAX);

  for (int sx : {-1, 1}) {
    for (int sy : {-1, 1}) {
      // {x, type, y, id}; reserved (type 0) before queries on ties
      vector<array<int, 4>> ev;
      vector<int> ys;
      ev.reserve(n + m);
      ys.reserve(n + m);

      for (auto [x, y] : a) {
        x *= sx;
        y *= sy;
        ev.push_back({x, 0, y, -1});
        ys.push_back(y);
      }

      for (int i = 0; i < m; ++i) {
        auto [x, y] = q[i];
        x *= sx;
        y *= sy;
        ev.push_back({x, 1, y, i});
        ys.push_back(y);
      }

      sort(ev.begin(), ev.end());
      sort(ys.begin(), ys.end());
      ys.erase(unique(ys.begin(), ys.end()), ys.end());

      Fenwick fw(ys.size());

      for (auto [x, type, y, id] : ev) {
        int p = lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1;

        if (type == 0) {
          fw.update(p, x + y);
        } else {
          int best = fw.query(p);
          if (best != INT_MIN)
            ans[id] = min(ans[id], x + y - best);
        }
      }
    }
  }

  for (int x : ans)
    cout << x << ' ';
  cout << '\n';
}
