#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, ll>>> adj(n + 1);

  while (m--) {
    int l, r;
    ll s;
    cin >> l >> r >> s;
    --l;

    adj[l].push_back({r, s});
    adj[r].push_back({l, -s});
  }

  vector<ll> p(n + 1);
  vector<bool> vis(n + 1);

  for (int st = 0; st <= n; ++st) {
    if (vis[st])
      continue;

    queue<int> q;
    q.push(st);
    vis[st] = true;

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (auto [v, w] : adj[u]) {
        ll want = p[u] + w;

        if (!vis[v]) {
          vis[v] = true;
          p[v] = want;
          q.push(v);
        } else if (p[v] != want) {
          cout << "NO\n";
          return 0;
        }
      }
    }
  }

  cout << "YES\n";
  for (int i = 1; i <= n; ++i)
    cout << p[i] - p[i - 1] << " \n"[i == n];
}
