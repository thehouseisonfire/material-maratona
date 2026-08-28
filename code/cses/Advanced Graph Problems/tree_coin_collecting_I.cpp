#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int LOG = 20;
const int INF = 1e9;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> coin(n);
  for (int &x : coin)
    cin >> x;

  vector<vector<int>> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  // Distance from every node to the nearest coin.
  vector<int> dist(n, INF);
  queue<int> qu;

  for (int i = 0; i < n; i++) {
    if (coin[i]) {
      dist[i] = 0;
      qu.push(i);
    }
  }

  while (!qu.empty()) {
    int v = qu.front();
    qu.pop();

    for (int u : adj[v]) {
      if (dist[u] > dist[v] + 1) {
        dist[u] = dist[v] + 1;
        qu.push(u);
      }
    }
  }

  vector<int> depth(n);
  vector<array<int, LOG>> up(n);
  vector<array<int, LOG>> mn(n);

  // Root the tree at 0.
  vector<int> par(n, -1);
  par[0] = 0;
  qu.push(0);

  while (!qu.empty()) {
    int v = qu.front();
    qu.pop();

    for (int u : adj[v]) {
      if (u == par[v])
        continue;

      par[u] = v;
      depth[u] = depth[v] + 1;
      qu.push(u);
    }
  }

  for (int v = 0; v < n; v++) {
    up[v][0] = par[v];
    mn[v][0] = min(dist[v], dist[par[v]]);
  }

  for (int j = 1; j < LOG; j++) {
    for (int v = 0; v < n; v++) {
      up[v][j] = up[up[v][j - 1]][j - 1];
      mn[v][j] = min(mn[v][j - 1], mn[up[v][j - 1]][j - 1]);
    }
  }

  auto lca = [&](int a, int b) {
    if (depth[a] < depth[b])
      swap(a, b);

    int d = depth[a] - depth[b];
    for (int j = 0; j < LOG; j++)
      if (d >> j & 1)
        a = up[a][j];

    if (a == b)
      return a;

    for (int j = LOG - 1; j >= 0; j--) {
      if (up[a][j] != up[b][j]) {
        a = up[a][j];
        b = up[b][j];
      }
    }

    return up[a][0];
  };

  auto pathMinToAncestor = [&](int v, int anc) {
    int ans = dist[v];
    int d = depth[v] - depth[anc];

    for (int j = 0; j < LOG; j++) {
      if (d >> j & 1) {
        ans = min(ans, mn[v][j]);
        v = up[v][j];
      }
    }

    return min(ans, dist[anc]);
  };

  while (q--) {
    int a, b;
    cin >> a >> b;
    --a, --b;

    int c = lca(a, b);

    int pathDist = depth[a] + depth[b] - 2 * depth[c];
    int best = min(pathMinToAncestor(a, c), pathMinToAncestor(b, c));

    cout << pathDist + 2 * best << '\n';
  }
}
