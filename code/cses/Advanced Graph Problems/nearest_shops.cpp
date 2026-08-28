#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> shops(k);
  vector<bool> isShop(n + 1);

  for (int &x : shops) {
    cin >> x;
    isShop[x] = true;
  }

  vector<vector<int>> g(n + 1);
  vector<pair<int, int>> edges;

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
    edges.push_back({a, b});
  }

  // Multi-source BFS: owner[u] is the nearest shop to u.
  vector<int> dist(n + 1, -1), owner(n + 1, -1);
  queue<int> q;

  for (int s : shops) {
    dist[s] = 0;
    owner[s] = s;
    q.push(s);
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : g[u]) {
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        owner[v] = owner[u];
        q.push(v);
      }
    }
  }

  // When two BFS regions touch, we get a path between their shops.
  const int INF = 1e9;
  vector<int> other(n + 1, INF);

  for (auto [u, v] : edges) {
    if (owner[u] != -1 && owner[v] != -1 && owner[u] != owner[v]) {
      int d = dist[u] + 1 + dist[v];
      other[owner[u]] = min(other[owner[u]], d);
      other[owner[v]] = min(other[owner[v]], d);
    }
  }

  for (int i = 1; i <= n; i++) {
    if (isShop[i]) {
      cout << (other[i] == INF ? -1 : other[i]);
    } else {
      cout << dist[i];
    }

    cout << (i == n ? '\n' : ' ');
  }
}
