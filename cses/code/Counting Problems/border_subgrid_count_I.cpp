// cses/Counting Problems/border_subgrid_count_I.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct FastPrefix {
  int blocks;
  vector<int> bit;
  vector<unsigned long long> mask;

  FastPrefix(int n) : blocks((n + 63) / 64), bit(blocks + 1), mask(blocks) {}

  void clear() {
    fill(bit.begin(), bit.end(), 0);
    fill(mask.begin(), mask.end(), 0);
  }

  void add(int x) {
    int b = x / 64;
    mask[b] |= 1ULL << (x % 64);

    for (int i = b + 1; i <= blocks; i += i & -i)
      ++bit[i];
  }

  // number of added positions in [0, x)
  int sum(int x) {
    int b = x / 64, res = 0;

    for (int i = b; i > 0; i -= i & -i)
      res += bit[i];

    if (b < blocks && x % 64)
      res += __builtin_popcountll(mask[b] & ((1ULL << (x % 64)) - 1));

    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<string> g(n);
  for (auto &row : g)
    cin >> row;

  int sz = n * n;

  // reach1: min(same-letter run right, down)
  // reach2: min(same-letter run left, up)
  vector<unsigned short> reach1(sz), reach2(sz);
  vector<int> vert(n);

  for (int i = n - 1; i >= 0; --i) {
    int right = 0;

    for (int j = n - 1; j >= 0; --j) {
      right = (j + 1 < n && g[i][j] == g[i][j + 1]) ? right + 1 : 1;

      vert[j] = (i + 1 < n && g[i][j] == g[i + 1][j]) ? vert[j] + 1 : 1;

      reach1[i * n + j] = min(right, vert[j]);
    }
  }

  fill(vert.begin(), vert.end(), 0);

  for (int i = 0; i < n; ++i) {
    int left = 0;

    for (int j = 0; j < n; ++j) {
      left = (j > 0 && g[i][j] == g[i][j - 1]) ? left + 1 : 1;

      vert[j] = (i > 0 && g[i][j] == g[i - 1][j]) ? vert[j] + 1 : 1;

      reach2[i * n + j] = min(left, vert[j]);
    }
  }

  vector<ll> ans(k);

  vector<unsigned short> start_reach(n), end_reach(n);
  vector<unsigned char> color(n);

  vector<int> head(n + 1), nxt(n);
  FastPrefix dead_pos(n);

  for (int d = -n + 1; d < n; ++d) {
    int i0 = max(0, -d);
    int j0 = max(0, d);
    int len = n - abs(d);

    // Copy the diagonal contiguously for better cache behavior.
    for (int t = 0; t < len; ++t) {
      int i = i0 + t;
      int j = j0 + t;
      int p = i * n + j;

      start_reach[t] = reach1[p];
      end_reach[t] = reach2[p];
      color[t] = g[i][j] - 'A';
    }

    fill(head.begin(), head.begin() + len + 1, -1);
    dead_pos.clear();

    int dead = 0;

    for (int t = 0; t < len; ++t) {
      // Top-left corners that can no longer reach t.
      for (int p = head[t]; p != -1; p = nxt[p]) {
        dead_pos.add(p);
        ++dead;
      }

      // Corner t remains usable through t + start_reach[t] - 1.
      int expire = t + start_reach[t];
      nxt[t] = head[expire];
      head[expire] = t;

      // Bottom-right corner t can pair only with
      // positions [left, t].
      int left = t + 1 - end_reach[t];

      int dead_here = dead - dead_pos.sum(left);
      ans[color[t]] += end_reach[t] - dead_here;
    }
  }

  for (ll x : ans)
    cout << x << '\n';
}
