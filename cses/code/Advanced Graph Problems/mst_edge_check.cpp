// cses/Advanced Graph Problems/mst_edge_check.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
  vector<int> p, sz;

  DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }

  int find(int a) { return a == p[a] ? a : p[a] = find(p[a]); }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return;
    if (sz[a] < sz[b])
      swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
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

  vector<Edge> e(m);
  for (int i = 0; i < m; i++) {
    cin >> e[i].a >> e[i].b >> e[i].w;
    e[i].id = i;
  }

  sort(e.begin(), e.end(),
       [](const Edge &x, const Edge &y) { return x.w < y.w; });

  DSU dsu(n);
  vector<bool> ans(m);

  for (int i = 0; i < m;) {
    int j = i;
    while (j < m && e[j].w == e[i].w)
      j++;

    // Check before joining edges of this weight.
    for (int k = i; k < j; k++)
      ans[e[k].id] = dsu.find(e[k].a) != dsu.find(e[k].b);

    for (int k = i; k < j; k++)
      dsu.unite(e[k].a, e[k].b);

    i = j;
  }

  for (bool x : ans)
    cout << (x ? "YES" : "NO") << '\n';
}
