#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
  vector<int> t;

  BIT(int n) : t(n + 1, INT_MIN) {}

  void add(int i, int v) {
    for (; i < (int)t.size(); i += i & -i)
      t[i] = max(t[i], v);
  }

  int get(int i) {
    int res = INT_MIN;
    for (; i; i -= i & -i)
      res = max(res, t[i]);
    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> reserved(n), freec(m);

  for (auto &[x, y] : reserved)
    cin >> x >> y;
  for (auto &[x, y] : freec)
    cin >> x >> y;

  const int INF = 1e9;
  vector<int> best(m, INF);

  for (int sx : {-1, 1}) {
    for (int sy : {-1, 1}) {
      vector<pair<int, int>> p(n);
      vector<array<int, 3>> q(m);
      vector<int> ys;

      for (int i = 0; i < n; ++i) {
        p[i] = {sx * reserved[i].first, sy * reserved[i].second};
        ys.push_back(p[i].second);
      }

      for (int i = 0; i < m; ++i) {
        q[i] = {sx * freec[i].first, sy * freec[i].second, i};
      }

      sort(p.begin(), p.end());
      sort(q.begin(), q.end());

      sort(ys.begin(), ys.end());
      ys.erase(unique(ys.begin(), ys.end()), ys.end());

      BIT bit(ys.size());
      int j = 0;

      for (auto [x, y, id] : q) {
        while (j < n && p[j].first <= x) {
          int pos =
              lower_bound(ys.begin(), ys.end(), p[j].second) - ys.begin() + 1;

          bit.add(pos, p[j].first + p[j].second);
          ++j;
        }

        int pos = upper_bound(ys.begin(), ys.end(), y) - ys.begin();

        int v = bit.get(pos);

        if (v != INT_MIN)
          best[id] = min(best[id], x + y - v);
      }
    }
  }

  cout << *max_element(best.begin(), best.end()) << '\n';
}
