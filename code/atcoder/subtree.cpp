#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll mod;
  cin >> n >> mod;

  vector<vector<int>> g(n);

  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<int> par(n, -1), order = {0};
  par[0] = 0;

  for (int i = 0; i < n; i++) {
    int v = order[i];

    for (int u : g[v]) {
      if (u == par[v])
        continue;
      par[u] = v;
      order.push_back(u);
    }
  }

  vector<ll> down(n, 1), up(n, 1), ans(n);

  for (int i = n - 1; i >= 0; i--) {
    int v = order[i];

    for (int u : g[v]) {
      if (par[u] == v)
        down[v] = down[v] * (down[u] + 1) % mod;
    }
  }

  for (int v : order) {
    vector<int> ch;

    for (int u : g[v])
      if (par[u] == v)
        ch.push_back(u);

    int m = ch.size();
    vector<ll> pref(m + 1, 1), suf(m + 1, 1);

    for (int i = 0; i < m; i++)
      pref[i + 1] = pref[i] * (down[ch[i]] + 1) % mod;

    for (int i = m - 1; i >= 0; i--)
      suf[i] = suf[i + 1] * (down[ch[i]] + 1) % mod;

    ans[v] = down[v] * up[v] % mod;

    for (int i = 0; i < m; i++) {
      ll other = pref[i] * suf[i + 1] % mod;
      up[ch[i]] = (1 + up[v] * other) % mod;
    }
  }

  for (ll x : ans)
    cout << x << '\n';
}
