// cses/Advanced Graph Problems/split_into_two_paths.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> g(n), rg(n);
  vector<int> deg(n);

  while (m--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    g[a].push_back(b);
    rg[b].push_back(a);
    deg[b]++;
  }

  // Topological order.
  queue<int> q;
  for (int i = 0; i < n; ++i)
    if (!deg[i])
      q.push(i);

  vector<int> ord;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    ord.push_back(u);

    for (int v : g[u])
      if (--deg[v] == 0)
        q.push(v);
  }

  vector<int> pos(n);
  for (int i = 0; i < n; ++i)
    pos[ord[i]] = i;

  // At step i, ord[i] is the end of one path.
  // active[y] means the other path may end at ord[y].
  vector<int> active(n), prv(n, -2);

  int version = 1;
  bool empty = true;

  for (int i = 0; i + 1 < n; ++i) {
    int v = ord[i + 1];

    bool straight = false;
    bool canSwitch = empty;
    int from = empty ? -1 : -2;

    for (int u : rg[v]) {
      int j = pos[u];

      if (j == i)
        straight = true;
      else if (j < i && active[j] == version && !canSwitch) {
        canSwitch = true;
        from = j;
      }
    }

    // Switch paths: ord[i+1] is appended to the other path,
    // so ord[i] becomes the new "other endpoint".
    if (canSwitch) {
      active[i] = version;
      prv[i] = from;
    }

    // Without ord[i] -> ord[i+1], all old states disappear.
    if (!straight) {
      if (!canSwitch) {
        cout << "NO\n";
        return 0;
      }

      ++version;
      empty = false;
      active[i] = version;
    }
  }

  int state = -1;

  if (!empty) {
    state = -2;
    for (int i = n - 1; i >= 0; --i)
      if (active[i] == version) {
        state = i;
        break;
      }

    if (state == -2) {
      cout << "NO\n";
      return 0;
    }
  }

  // Reconstruct which path each topological position belongs to.
  vector<int> side(n);
  int cur = 0;

  for (int i = n - 1; i > 0; --i) {
    side[i] = cur;

    if (state == i - 1) {
      state = prv[i - 1];
      cur ^= 1;
    }
  }

  side[0] = cur;

  vector<int> path[2];

  for (int i = 0; i < n; ++i)
    path[side[i]].push_back(ord[i]);

  cout << "YES\n";

  for (int t = 0; t < 2; ++t) {
    cout << path[t].size();
    for (int u : path[t])
      cout << ' ' << u + 1;
    cout << '\n';
  }
}
