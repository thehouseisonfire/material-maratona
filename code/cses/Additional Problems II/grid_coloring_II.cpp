#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  int N = n * m;
  vector<int> a(N);

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++)
      a[i * m + j] = s[j] - 'A';
  }

  int V = 2 * N;

  vector<int> head(V, -1), rhead(V, -1);
  vector<int> to, nxt, rto, rnxt;

  to.reserve(8 * N);
  nxt.reserve(8 * N);
  rto.reserve(8 * N);
  rnxt.reserve(8 * N);

  auto add_edge = [&](int u, int v) {
    to.push_back(v);
    nxt.push_back(head[u]);
    head[u] = (int)to.size() - 1;

    rto.push_back(u);
    rnxt.push_back(rhead[v]);
    rhead[v] = (int)rto.size() - 1;
  };

  auto add_adj = [&](int u, int v) {
    for (int c = 0; c < 3; c++) {
      if (c == a[u] || c == a[v])
        continue;

      int cu = (c == (a[u] + 1) % 3 ? 0 : 1);
      int cv = (c == (a[v] + 1) % 3 ? 0 : 1);

      int x = 2 * u + cu;
      int y = 2 * v + cv;

      // not (x and y)
      add_edge(x, y ^ 1);
      add_edge(y, x ^ 1);
    }
  };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int u = i * m + j;
      if (i + 1 < n)
        add_adj(u, u + m);
      if (j + 1 < m)
        add_adj(u, u + 1);
    }
  }

  // Kosaraju, first pass
  vector<char> vis(V);
  vector<int> ptr = head, order, st;
  order.reserve(V);
  st.reserve(V);

  for (int s = 0; s < V; s++) {
    if (vis[s])
      continue;

    vis[s] = 1;
    st.push_back(s);

    while (!st.empty()) {
      int v = st.back();
      int &e = ptr[v];

      while (e != -1 && vis[to[e]])
        e = nxt[e];

      if (e == -1) {
        order.push_back(v);
        st.pop_back();
      } else {
        int u = to[e];
        e = nxt[e];
        vis[u] = 1;
        st.push_back(u);
      }
    }
  }

  // Kosaraju, second pass
  vector<int> comp(V, -1);
  int cid = 0;

  for (int k = V - 1; k >= 0; k--) {
    int s = order[k];
    if (comp[s] != -1)
      continue;

    comp[s] = cid;
    st.push_back(s);

    while (!st.empty()) {
      int v = st.back();
      st.pop_back();

      for (int e = rhead[v]; e != -1; e = rnxt[e]) {
        int u = rto[e];
        if (comp[u] == -1) {
          comp[u] = cid;
          st.push_back(u);
        }
      }
    }

    cid++;
  }

  for (int i = 0; i < N; i++) {
    if (comp[2 * i] == comp[2 * i + 1]) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int v = i * m + j;
      int choice = comp[2 * v] > comp[2 * v + 1] ? 0 : 1;
      int color = (a[v] + 1 + choice) % 3;
      cout << char('A' + color);
    }
    cout << '\n';
  }
}
