#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void dfs1(int v, const vector<vector<int>> &g, vector<bool> &vis,
          vector<int> &order) {
  vis[v] = true;
  for (int u : g[v])
    if (!vis[u])
      dfs1(u, g, vis, order);
  order.push_back(v);
}

void dfs2(int v, const vector<vector<int>> &rg, vector<bool> &vis) {
  vis[v] = true;
  for (int u : rg[v])
    if (!vis[u])
      dfs2(u, rg, vis);
}

int kosaraju(const vector<vector<int>> &g, const vector<vector<int>> &rg) {
  int n = (int)g.size() - 1;

  vector<bool> vis(n + 1);
  vector<int> order;
  order.reserve(n);

  for (int v = 1; v <= n; v++)
    if (!vis[v])
      dfs1(v, g, vis, order);

  fill(vis.begin(), vis.end(), false);

  int scc = 0;
  reverse(order.begin(), order.end());

  for (int v : order) {
    if (vis[v])
      continue;
    dfs2(v, rg, vis);
    scc++;
  }

  return scc;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;

  while (cin >> n >> m && (n || m)) {
    vector<vector<int>> g(n + 1), rg(n + 1);

    for (int i = 0; i < m; i++) {
      int x, y, z;
      cin >> x >> y >> z;

      g[x].push_back(y);
      rg[y].push_back(x);

      if (z == 2) {
        g[y].push_back(x);
        rg[x].push_back(y);
      }
    }

    cout << (kosaraju(g, rg) == 1) << '\n';
  }
}
