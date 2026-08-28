#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

ll modpow(ll a, ll e) {
  ll r = 1;

  while (e) {
    if (e & 1)
      r = r * a % MOD;
    a = a * a % MOD;
    e >>= 1;
  }

  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int h, w, n;
  cin >> h >> w >> n;

  vector<pair<int, int>> p(n);

  for (auto &[r, c] : p)
    cin >> r >> c;

  p.push_back({h, w});
  sort(p.begin(), p.end());

  int mx = h + w;
  vector<ll> fact(mx + 1), invfact(mx + 1);

  fact[0] = 1;
  for (int i = 1; i <= mx; i++)
    fact[i] = fact[i - 1] * i % MOD;

  invfact[mx] = modpow(fact[mx], MOD - 2);

  for (int i = mx; i >= 1; i--)
    invfact[i - 1] = invfact[i] * i % MOD;

  auto C = [&](int n, int k) -> ll {
    if (k < 0 || k > n)
      return 0;
    return fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
  };

  vector<ll> dp(n + 1);

  for (int i = 0; i <= n; i++) {
    auto [r, c] = p[i];

    dp[i] = C(r + c - 2, r - 1);

    for (int j = 0; j < i; j++) {
      auto [pr, pc] = p[j];

      if (pc > c)
        continue;

      int dr = r - pr;
      int dc = c - pc;

      dp[i] = (dp[i] - dp[j] * C(dr + dc, dr)) % MOD;
    }

    if (dp[i] < 0)
      dp[i] += MOD;
  }

  cout << dp[n] << '\n';
}
