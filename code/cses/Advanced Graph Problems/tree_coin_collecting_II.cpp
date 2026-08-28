#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> coin(n);
  int coins = 0;

  for (int &x : coin) {
    cin >> x;
    coins += x;
  }

  vector<vector<int>> g(n);

  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;

    g[a].push_back(b);
    g[b].push_back(a);
  }

  const int LOG = 20;

  vector<int> parent(n, -1), depth(n), order;
  vector<array<int, LOG>> up(n);

  parent[0] = 0;

  vector<int> st = {0};

  while (!st.empty()) {
    int u = st.back();
    st.pop_back();

    order.push_back(u);

    for (int v : g[u]) {
      if (v == parent[u])
        continue;

      parent[v] = u;
      depth[v] = depth[u] + 1;
      st.push_back(v);
    }
  }

  for (int v = 0; v < n; v++)
    up[v][0] = parent[v];

  for (int j = 1; j < LOG; j++) {
    for (int v = 0; v < n; v++) {
      up[v][j] = up[up[v][j - 1]][j - 1];
    }
  }

  auto lca = [&](int a, int b) {
    if (depth[a] < depth[b])
      swap(a, b);

    int d = depth[a] - depth[b];

    for (int j = 0; j < LOG; j++) {
      if (d >> j & 1)
        a = up[a][j];
    }

    if (a == b)
      return a;

    for (int j = LOG - 1; j >= 0; j--) {
      if (up[a][j] != up[b][j]) {
        a = up[a][j];
        b = up[b][j];
      }
    }

    return parent[a];
  };

  auto dist = [&](int a, int b) {
    int c = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[c];
  };

  // Find the minimal subtree containing all coins.
  vector<int> sub = coin;

  for (int i = n - 1; i > 0; i--) {
    int v = order[i];
    sub[parent[v]] += sub[v];
  }

  vector<char> core(n, false);
  ll coreEdges = 0;

  for (int v = 0; v < n; v++) {
    if (coin[v])
      core[v] = true;
  }

  for (int v = 1; v < n; v++) {
    // This edge separates coins on both sides,
    // so it belongs to the coin subtree.
    if (sub[v] > 0 && sub[v] < coins) {
      core[v] = true;
      core[parent[v]] = true;
      coreEdges++;
    }
  }

  // For every node:
  // root[v]   = which core node its branch attaches to
  // toCore[v] = distance to the core
  vector<int> root(n, -1), toCore(n, -1);
  queue<int> qu;

  for (int v = 0; v < n; v++) {
    if (core[v]) {
      root[v] = v;
      toCore[v] = 0;
      qu.push(v);
    }
  }

  while (!qu.empty()) {
    int u = qu.front();
    qu.pop();

    for (int v : g[u]) {
      if (toCore[v] != -1)
        continue;

      root[v] = root[u];
      toCore[v] = toCore[u] + 1;
      qu.push(v);
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    --a, --b;

    ll ans;

    if (root[a] == root[b]) {
      // Their branches meet before entering the coin subtree.
      ans = 2 * coreEdges + toCore[a] + toCore[b];
    } else {
      // Both branches are added independently.
      ll requiredEdges = coreEdges + toCore[a] + toCore[b];

      ans = 2 * requiredEdges - dist(a, b);
    }

    cout << ans << '\n';
  }
}
