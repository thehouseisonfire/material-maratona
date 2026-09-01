// cses/Counting Problems/raab_game_II.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

ll pw(ll a, ll b) {
  ll r = 1;
  while (b) {
    if (b & 1)
      r = r * a % MOD;
    a = a * a % MOD;
    b >>= 1;
  }
  return r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  vector<array<int, 3>> q(t);
  int N = 0;

  for (auto &[n, a, b] : q) {
    cin >> n >> a >> b;
    N = max(N, n);
  }

  vector<ll> fact(N + 1, 1), invfact(N + 1, 1);
  for (int i = 1; i <= N; i++)
    fact[i] = fact[i - 1] * i % MOD;

  invfact[N] = pw(fact[N], MOD - 2);
  for (int i = N; i; i--)
    invfact[i - 1] = invfact[i] * i % MOD;

  // Need dp[a][b] only for queried pairs.
  vector<vector<int>> ask(N + 1);
  vector<ll> ways(t);

  for (int i = 0; i < t; i++) {
    auto [n, a, b] = q[i];
    if (a + b <= n)
      ask[a].push_back(i);
  }

  // dp[a][b]:
  // derangements of a+b elements with
  // a positions p[i] < i and b positions p[i] > i.
  vector<ll> prv(N + 1), cur(N + 1);

  for (int a = 0; a <= N; a++) {
    fill(cur.begin(), cur.end(), 0);

    if (a == 0)
      cur[0] = 1;

    for (int b = 0; a + b <= N; b++) {
      if (a == 0 && b == 0)
        continue;

      ll x = 0;

      if (b)
        x += (ll)a * cur[b - 1];

      if (a)
        x += (ll)b * prv[b];

      if (a && b)
        x += (ll)(a + b - 1) * prv[b - 1];

      cur[b] = x % MOD;
    }

    for (int id : ask[a])
      ways[id] = cur[q[id][2]];

    swap(prv, cur);
  }

  for (int i = 0; i < t; i++) {
    auto [n, a, b] = q[i];

    if (a + b > n) {
      cout << 0 << '\n';
      continue;
    }

    int m = a + b;

    ll choose = fact[n] * invfact[m] % MOD * invfact[n - m] % MOD;

    ll ans = fact[n] * choose % MOD * ways[i] % MOD;
    cout << ans << '\n';
  }
}
