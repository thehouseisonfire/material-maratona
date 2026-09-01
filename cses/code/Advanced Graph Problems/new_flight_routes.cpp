// cses/Advanced Graph Problems/new_flight_routes.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> g, rg;
vector<int> order, comp;
vector<char> vis;

void dfs1(int u) {
  vis[u] = true;
  for (int v : g[u])
    if (!vis[v])
      dfs1(v);
  order.push_back(u);
}

void dfs2(int u, int c) {
  comp[u] = c;
  for (int v : rg[u])
    if (comp[v] == -1)
      dfs2(v, c);
}

struct Info {
  vector<int> src, sink;
  int comps;
};

Info getInfo(int n) {
  fill(vis.begin(), vis.end(), 0);
  fill(comp.begin(), comp.end(), -1);
  order.clear();

  for (int i = 0; i < n; ++i)
    if (!vis[i])
      dfs1(i);

  reverse(order.begin(), order.end());

  vector<int> rep;
  int cc = 0;

  for (int u : order) {
    if (comp[u] != -1)
      continue;

    rep.push_back(u);
    dfs2(u, cc++);
  }

  vector<char> in(cc), out(cc);

  for (int u = 0; u < n; ++u) {
    for (int v : g[u]) {
      if (comp[u] != comp[v]) {
        out[comp[u]] = true;
        in[comp[v]] = true;
      }
    }
  }

  Info res;
  res.comps = cc;

  for (int c = 0; c < cc; ++c) {
    if (!in[c])
      res.src.push_back(rep[c]);
    if (!out[c])
      res.sink.push_back(rep[c]);
  }

  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  g.resize(n);
  rg.resize(n);
  vis.resize(n);
  comp.resize(n);
  order.reserve(n);

  while (m--) {
    int a, b;
    cin >> a >> b;
    --a, --b;

    g[a].push_back(b);
    rg[b].push_back(a);
  }

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  vector<pair<int, int>> ans;
  Info cur = getInfo(n);

  while (cur.comps > 1 && cur.src.size() > 1 && cur.sink.size() > 1) {

    int k = min(cur.src.size(), cur.sink.size()) / 2;

    auto src = cur.src;
    auto sink = cur.sink;

    shuffle(src.begin(), src.end(), rng);
    shuffle(sink.begin(), sink.end(), rng);

    vector<pair<int, int>> add;

    for (int i = 0; i < k; ++i) {
      int u = sink[i];
      int v = src[i];

      g[u].push_back(v);
      rg[v].push_back(u);
      add.push_back({u, v});
    }

    Info nxt = getInfo(n);

    if ((int)nxt.src.size() != (int)cur.src.size() - k ||
        (int)nxt.sink.size() != (int)cur.sink.size() - k) {

      for (auto [u, v] : add) {
        g[u].pop_back();
        rg[v].pop_back();
      }
    } else {
      ans.insert(ans.end(), add.begin(), add.end());
      cur = std::move(nxt); // needs to use `std::` here.
    }
  }

  if (cur.comps > 1) {
    if (cur.src.size() == 1) {
      for (int t : cur.sink)
        ans.push_back({t, cur.src[0]});
    } else {
      for (int s : cur.src)
        ans.push_back({cur.sink[0], s});
    }
  }

  cout << ans.size() << '\n';
  for (auto [u, v] : ans)
    cout << u + 1 << ' ' << v + 1 << '\n';
}
