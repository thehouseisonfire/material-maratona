#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
  vector<int> p, sz, xr;
  vector<set<int>> rights;

  DSU(int n) : p(n), sz(n, 1), xr(n), rights(n) { iota(p.begin(), p.end(), 0); }

  pair<int, int> find(int x) {
    if (p[x] == x)
      return {x, 0};
    auto q = find(p[x]);
    xr[x] ^= q.second;
    p[x] = q.first;
    return {p[x], xr[x]};
  }

  // Enforce color[a] != color[b].
  bool unite(int a, int b) {
    auto A = find(a);
    auto B = find(b);

    if (A.first == B.first)
      return (A.second ^ B.second) == 1;

    if (sz[A.first] < sz[B.first])
      swap(A, B);

    int ra = A.first, rb = B.first;
    p[rb] = ra;
    xr[rb] = A.second ^ B.second ^ 1;
    sz[ra] += sz[rb];

    if (rights[ra].size() < rights[rb].size())
      rights[ra].swap(rights[rb]);

    rights[ra].insert(rights[rb].begin(), rights[rb].end());
    rights[rb].clear();

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n), pos(n), seen(n);
  vector<int> L(n), R(n);

  for (int &x : a) {
    cin >> x;
    --x;
  }

  // Build intervals with distinct endpoints.
  vector<pair<int, int>> event(2 * n); // {index, 0=open / 1=close}

  int timer = 0, need = 0;

  for (int i = 0; i < n; ++i) {
    pos[a[i]] = i;
    seen[a[i]] = 1;

    L[i] = timer;
    event[timer++] = {i, 0};

    while (need < n && seen[need]) {
      int j = pos[need++];
      R[j] = timer;
      event[timer++] = {j, 1};
    }
  }

  DSU dsu(n);

  for (int i = 0; i < n; ++i)
    dsu.rights[i].insert(R[i]);

  // One active representative per DSU component.
  set<pair<int, int>> active; // {right endpoint, interval index}

  for (int t = 0; t < 2 * n; ++t) {
    int i = event[t].first;
    int type = event[t].second;

    if (type == 0) {
      int bestR = R[i];
      int bestI = i;

      // These intervals cross interval i.
      while (!active.empty() && active.begin()->first < R[i]) {
        auto cur = *active.begin();
        active.erase(active.begin());

        if (cur.first < bestR) {
          bestR = cur.first;
          bestI = cur.second;
        }

        if (!dsu.unite(i, cur.second)) {
          cout << "IMPOSSIBLE\n";
          return 0;
        }
      }

      active.insert({bestR, bestI});
    } else {
      auto it = active.find({R[i], i});

      // i may not currently be its component's representative.
      if (it == active.end())
        continue;

      active.erase(it);

      int root = dsu.find(i).first;
      auto nxt = dsu.rights[root].upper_bound(R[i]);

      if (nxt != dsu.rights[root].end()) {
        int r = *nxt;
        int j = event[r].first;
        active.insert({r, j});
      }
    }
  }

  vector<int> color(n);

  for (int i = 0; i < n; ++i)
    color[i] = dsu.find(i).second;

  // Verify by greedily popping whenever possible.
  stack<int> st[2];
  need = 0;

  for (int i = 0; i < n; ++i) {
    st[color[i]].push(a[i]);

    while (true) {
      if (!st[0].empty() && st[0].top() == need) {
        st[0].pop();
        ++need;
      } else if (!st[1].empty() && st[1].top() == need) {
        st[1].pop();
        ++need;
      } else {
        break;
      }
    }
  }

  if (need != n) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  for (int i = 0; i < n; ++i)
    cout << color[i] + 1 << " \n"[i + 1 == n];
}
