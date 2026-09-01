// cses/Advanced Graph Problems/mst_edge_cost.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
  vector<int> p, sz;

  DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }

  int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
      return false;

    if (sz[a] < sz[b])
      swap(a, b);

    p[b] = a;
    sz[a] += sz[b];
    return true;
  }
};

struct Edge {
  int a, b, id;
  ll w;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<Edge> edges(m);
  for (int i = 0; i < m; i++) {
    cin >> edges[i].a >> edges[i].b >> edges[i].w;
    edges[i].id = i;
  }

  vector<Edge> ord = edges;
  sort(ord.begin(), ord.end(),
       [](const Edge &a, const Edge &b) { return a.w < b.w; });

  DSU dsu(n);
  vector<vector<pair<int, ll>>> g(n + 1);
  ll mst = 0;

  for (auto [a, b, id, w] : ord) {
    if (dsu.unite(a, b)) {
      mst += w;
      g[a].push_back({b, w});
      g[b].push_back({a, w});
    }
  }

  int LOG = 1;
  while ((1 << LOG) <= n)
    LOG++;

  vector<int> depth(n + 1);
  vector<vector<int>> up(LOG, vector<int>(n + 1));
  vector<vector<ll>> mx(LOG, vector<ll>(n + 1));

  auto dfs = [&](auto &&self, int u, int p) -> void {
    for (auto [v, w] : g[u]) {
      if (v == p)
        continue;

      depth[v] = depth[u] + 1;
      up[0][v] = u;
      mx[0][v] = w;
      self(self, v, u);
    }
  };

  dfs(dfs, 1, 0);

  for (int j = 1; j < LOG; j++) {
    for (int v = 1; v <= n; v++) {
      up[j][v] = up[j - 1][up[j - 1][v]];
      mx[j][v] = max(mx[j - 1][v], mx[j - 1][up[j - 1][v]]);
    }
  }

  auto pathMax = [&](int a, int b) {
    ll ans = 0;

    if (depth[a] < depth[b])
      swap(a, b);

    int diff = depth[a] - depth[b];

    for (int j = LOG - 1; j >= 0; j--) {
      if (diff & (1 << j)) {
        ans = max(ans, mx[j][a]);
        a = up[j][a];
      }
    }

    if (a == b)
      return ans;

    for (int j = LOG - 1; j >= 0; j--) {
      if (up[j][a] != up[j][b]) {
        ans = max({ans, mx[j][a], mx[j][b]});
        a = up[j][a];
        b = up[j][b];
      }
    }

    ans = max({ans, mx[0][a], mx[0][b]});
    return ans;
  };

  for (auto [a, b, id, w] : edges)
    cout << mst + w - pathMax(a, b) << '\n';
}
