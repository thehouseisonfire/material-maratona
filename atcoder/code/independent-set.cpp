// atcoder/independent-set.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

vector<vector<int>> g;

pair<ll, ll> dfs(int v, int p) {
  ll white = 1, black = 1;

  for (int u : g[v]) {
    if (u == p)
      continue;

    auto [w, b] = dfs(u, v);

    white = white * (w + b) % MOD;
    black = black * w % MOD;
  }

  return {white, black};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  g.resize(n);

  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;

    g[a].push_back(b);
    g[b].push_back(a);
  }

  auto [white, black] = dfs(0, -1);

  cout << (white + black) % MOD << '\n';
}
