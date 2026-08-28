#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int LOG = 20;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<pair<int, int>>> g(n);

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back({b, i});
    g[b].push_back({a, i});
  }

  vector<int> tin(n, -1), tout(n), low(n), depth(n);
  vector<array<int, LOG>> up(n);

  int timer = 0;

  auto dfs = [&](auto &&self, int v, int p, int pe) -> void {
    tin[v] = low[v] = timer++;

    up[v][0] = p;
    for (int k = 1; k < LOG; k++)
      up[v][k] = up[up[v][k - 1]][k - 1];

    for (auto [to, id] : g[v]) {
      if (id == pe)
        continue;

      if (tin[to] != -1) {
        low[v] = min(low[v], tin[to]);
      } else {
        depth[to] = depth[v] + 1;
        self(self, to, v, id);
        low[v] = min(low[v], low[to]);
      }
    }

    tout[v] = timer - 1;
  };

  dfs(dfs, 0, 0, -1);

  auto ancestor = [&](int a, int b) {
    return tin[a] <= tin[b] && tin[b] <= tout[a];
  };

  auto jump = [&](int v, int d) {
    for (int k = 0; k < LOG; k++)
      if (d & (1 << k))
        v = up[v][k];
    return v;
  };

  // Component containing x after removing c.
  // -1 means the component on the parent side of c.
  auto side = [&](int c, int x) {
    if (!ancestor(c, x))
      return -1;

    int child = jump(x, depth[x] - depth[c] - 1);

    if (low[child] >= tin[c])
      return child;

    return -1;
  };

  while (q--) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b, --c;

    if (a == c || b == c) {
      cout << "NO\n";
      continue;
    }

    cout << (side(c, a) == side(c, b) ? "YES\n" : "NO\n");
  }
}
