#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> g(n);
  vector<int> in(n);

  while (m--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
    in[b]++;
  }

  queue<int> q;
  for (int i = 0; i < n; i++)
    if (in[i] == 0)
      q.push(i);

  vector<int> dp(n);

  while (!q.empty()) {
    int v = q.front();
    q.pop();

    for (int u : g[v]) {
      dp[u] = max(dp[u], dp[v] + 1);

      if (--in[u] == 0)
        q.push(u);
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << '\n';
}
