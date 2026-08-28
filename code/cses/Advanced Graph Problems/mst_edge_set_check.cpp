#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
  vector<int> p, sz;
  vector<pair<int, int>> hist;

  DSU(int n) : p(n + 1), sz(n + 1, 1) { iota(p.begin(), p.end(), 0); }

  int find(int x) {
    while (x != p[x])
      x = p[x];
    return x;
  }

  bool unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
      return false;

    if (sz[a] < sz[b])
      swap(a, b);

    hist.push_back({b, sz[a]});

    p[b] = a;
    sz[a] += sz[b];

    return true;
  }

  int snapshot() { return hist.size(); }

  void rollback(int snap) {
    while ((int)hist.size() > snap) {
      auto [b, oldSize] = hist.back();
      hist.pop_back();

      int a = p[b];

      p[b] = b;
      sz[a] = oldSize;
    }
  }
};

struct Edge {
  int u, v;
  ll w;
};

struct Event {
  ll w;
  int q, u, v;

  bool operator<(const Event &other) const {
    if (w != other.w)
      return w < other.w;
    return q < other.q;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  vector<Edge> edges(m);

  for (auto &[u, v, w] : edges)
    cin >> u >> v >> w;

  vector<Event> events;
  events.reserve(m);

  vector<char> ok(q, true);

  for (int qi = 0; qi < q; qi++) {
    int k;
    cin >> k;

    while (k--) {
      int id;
      cin >> id;
      --id;

      auto [u, v, w] = edges[id];
      events.push_back({w, qi, u, v});
    }
  }

  vector<int> ord(m);
  iota(ord.begin(), ord.end(), 0);

  sort(ord.begin(), ord.end(),
       [&](int a, int b) { return edges[a].w < edges[b].w; });

  sort(events.begin(), events.end());

  DSU dsu(n);
  int ptr = 0;

  for (int i = 0; i < (int)events.size();) {
    ll w = events[i].w;

    // Permanently add all strictly lighter edges.
    while (ptr < m && edges[ord[ptr]].w < w) {
      auto [u, v, _] = edges[ord[ptr++]];
      dsu.unite(u, v);
    }

    int j = i;

    // Test each query separately for this weight.
    while (j < (int)events.size() && events[j].w == w) {
      int qi = events[j].q;
      int snap = dsu.snapshot();

      int k = j;

      while (k < (int)events.size() && events[k].w == w && events[k].q == qi) {
        if (ok[qi] && !dsu.unite(events[k].u, events[k].v))
          ok[qi] = false;

        k++;
      }

      dsu.rollback(snap);
      j = k;
    }

    i = j;
  }

  for (bool x : ok)
    cout << (x ? "YES\n" : "NO\n");
}
