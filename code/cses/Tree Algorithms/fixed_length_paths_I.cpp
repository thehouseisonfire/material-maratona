#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 200005;

int n, k;
vector<int> g[N];

int sz[N], cnt[N];
bool dead[N];

ll ans = 0;

void getSize(int u, int p) {
  sz[u] = 1;

  for (int v : g[u])
    if (v != p && !dead[v]) {
      getSize(v, u);
      sz[u] += sz[v];
    }
}

int getCentroid(int u, int p, int total) {
  for (int v : g[u])
    if (v != p && !dead[v] && sz[v] > total / 2)
      return getCentroid(v, u, total);

  return u;
}

void getDepths(int u, int p, int d, vector<int> &depths) {
  if (d > k)
    return;

  depths.push_back(d);

  for (int v : g[u])
    if (v != p && !dead[v])
      getDepths(v, u, d + 1, depths);
}

void decompose(int start) {
  getSize(start, 0);

  int c = getCentroid(start, 0, sz[start]);
  dead[c] = true;

  // cnt[d] = nodes at distance d from c
  // in previously processed subtrees.
  cnt[0] = 1;

  int maxDepth = 0;
  vector<int> depths;

  for (int v : g[c]) {
    if (dead[v])
      continue;

    depths.clear();
    getDepths(v, c, 1, depths);

    // Count paths whose two endpoints are in
    // different subtrees (or one endpoint is c).
    for (int d : depths)
      ans += cnt[k - d];

    // Add this subtree only after counting it.
    for (int d : depths) {
      cnt[d]++;
      maxDepth = max(maxDepth, d);
    }
  }

  // Restore cnt[] to zero for the next centroid.
  for (int d = 0; d <= maxDepth; d++)
    cnt[d] = 0;

  for (int v : g[c])
    if (!dead[v])
      decompose(v);
}

int main() {
  cin >> n >> k;

  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;

    g[a].push_back(b);
    g[b].push_back(a);
  }

  decompose(1);

  cout << ans << '\n';
}
