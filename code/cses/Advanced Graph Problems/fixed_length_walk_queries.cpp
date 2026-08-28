#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Query {
  int b, id;
  ll x;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<int>> g(n);

  while (m--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<vector<Query>> queries(n);
  vector<char> ans(q);

  for (int i = 0; i < q; i++) {
    int a, b;
    ll x;
    cin >> a >> b >> x;
    --a, --b;
    queries[a].push_back({b, i, x});
  }

  for (int s = 0; s < n; s++) {
    if (queries[s].empty())
      continue;

    // state = 2 * node + parity
    vector<int> dist(2 * n, -1);
    queue<int> qu;

    dist[2 * s] = 0;
    qu.push(2 * s);

    while (!qu.empty()) {
      int state = qu.front();
      qu.pop();

      int u = state / 2;
      int p = state % 2;

      for (int v : g[u]) {
        int nxt = 2 * v + (p ^ 1);

        if (dist[nxt] == -1) {
          dist[nxt] = dist[state] + 1;
          qu.push(nxt);
        }
      }
    }

    for (auto [b, id, x] : queries[s]) {
      int d = dist[2 * b + (x & 1)];
      ans[id] = (d != -1 && d <= x);
    }
  }

  for (char ok : ans)
    cout << (ok ? "YES\n" : "NO\n");
}
