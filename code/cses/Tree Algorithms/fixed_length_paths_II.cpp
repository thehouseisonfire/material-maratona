#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 200005;

int n, k1, k2;
vector<int> g[N];

int sz[N], par[N];
bool dead[N];

int suf[N], cur[N];
ll ans = 0;

// Reused buffers to avoid lots of allocations.
vector<int> order_, st_;
vector<array<int, 3>> walk_;

int get_centroid(int start) {
  order_.clear();
  st_.clear();

  st_.push_back(start);
  par[start] = 0;

  // Get all nodes in this component.
  while (!st_.empty()) {
    int u = st_.back();
    st_.pop_back();

    order_.push_back(u);

    for (int v : g[u])
      if (v != par[u] && !dead[v]) {
        par[v] = u;
        st_.push_back(v);
      }
  }

  // Subtree sizes.
  for (int i = (int)order_.size() - 1; i >= 0; i--) {
    int u = order_[i];
    sz[u] = 1;

    for (int v : g[u])
      if (!dead[v] && par[v] == u)
        sz[u] += sz[v];
  }

  int total = sz[start];

  // Find a node whose largest remaining component
  // has size <= total / 2.
  for (int u : order_) {
    int largest = total - sz[u];

    for (int v : g[u])
      if (!dead[v] && par[v] == u)
        largest = max(largest, sz[v]);

    if (largest <= total / 2)
      return u;
  }

  return start;
}

// Process one child subtree of the centroid.
//
// suf[d] = number of already processed nodes
//          whose depth from the centroid is >= d.
int process_subtree(int root, int centroid) {
  walk_.clear();
  walk_.push_back({root, centroid, 1});

  int mx = 0;

  while (!walk_.empty()) {
    auto [u, p, d] = walk_.back();
    walk_.pop_back();

    if (d > k2)
      continue;

    // Need another node at depth x such that:
    // k1 <= d + x <= k2.
    int lo = max(0, k1 - d);
    int hi = k2 - d;

    ans += suf[lo] - suf[hi + 1];

    cur[d]++;
    mx = max(mx, d);

    for (int v : g[u])
      if (v != p && !dead[v])
        walk_.push_back({v, u, d + 1});
  }

  // Add this subtree to suf.
  int sum = 0;

  for (int d = mx; d >= 0; d--) {
    sum += cur[d];
    suf[d] += sum;
    cur[d] = 0;
  }

  return mx;
}

void decompose(int start) {
  int c = get_centroid(start);
  dead[c] = true;

  // Centroid itself has depth 0.
  suf[0] = 1;

  int max_depth = 0;

  for (int v : g[c])
    if (!dead[v])
      max_depth = max(max_depth, process_subtree(v, c));

  // Clear suffix counts for the next centroid.
  for (int d = 0; d <= max_depth; d++)
    suf[d] = 0;

  for (int v : g[c])
    if (!dead[v])
      decompose(v);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k1 >> k2;

  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;

    g[a].push_back(b);
    g[b].push_back(a);
  }

  decompose(1);

  cout << ans << '\n';
}
