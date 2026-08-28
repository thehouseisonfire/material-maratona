#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> adj(n);

  while (m--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    adj[a] |= 1 << b;
    adj[b] |= 1 << a;
  }

  int N = 1 << n;

  // independent[mask] = whether mask is an independent set
  vector<char> independent(N, false);
  independent[0] = true;

  for (int mask = 1; mask < N; ++mask) {
    int v = __builtin_ctz(mask);
    int rest = mask ^ (1 << v);

    independent[mask] = independent[rest] && !(adj[v] & rest);
  }

  // dp[mask] = minimum colors needed for vertices in mask
  vector<int> dp(N, n + 1), take(N);
  dp[0] = 0;

  for (int mask = 1; mask < N; ++mask) {
    int bit = mask & -mask;
    int rest = mask ^ bit;

    // The color class containing 'bit' can be any
    // independent subset containing it.
    for (int sub = rest;; sub = (sub - 1) & rest) {
      int group = sub | bit;

      if (independent[group] && dp[mask ^ group] + 1 < dp[mask]) {
        dp[mask] = dp[mask ^ group] + 1;
        take[mask] = group;
      }

      if (sub == 0)
        break;
    }
  }

  vector<int> color(n);
  int mask = N - 1;
  int c = 1;

  while (mask) {
    int group = take[mask];

    for (int v = 0; v < n; ++v)
      if (group & (1 << v))
        color[v] = c;

    mask ^= group;
    ++c;
  }

  cout << dp[N - 1] << '\n';

  for (int v = 0; v < n; ++v)
    cout << color[v] << " \n"[v == n - 1];
}
