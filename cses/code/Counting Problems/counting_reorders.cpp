// cses/Counting Problems/counting_reorders.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

ll modpow(ll a, ll b) {
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

  string s;
  cin >> s;
  int n = s.size();

  vector<int> cnt(26);
  for (char c : s)
    cnt[c - 'a']++;

  vector<ll> fact(n + 1), ifact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; i++)
    fact[i] = fact[i - 1] * i % MOD;

  ifact[n] = modpow(fact[n], MOD - 2);
  for (int i = n; i; i--)
    ifact[i - 1] = ifact[i] * i % MOD;

  // dp[j] = coefficient for selecting j forced equal-adjacency bonds
  vector<ll> dp(n + 1);
  dp[0] = 1;

  int deg = 0;

  for (int c : cnt) {
    if (!c)
      continue;

    vector<ll> ndp(n + 1);

    for (int j = 0; j < c; j++) {
      // C(c-1, j) / (c-j)!
      ll ways = fact[c - 1] * ifact[j] % MOD * ifact[c - 1 - j] % MOD *
                ifact[c - j] % MOD;

      for (int k = 0; k <= deg; k++) {
        ndp[k + j] = (ndp[k + j] + dp[k] * ways) % MOD;
      }
    }

    deg += c - 1;
    dp.swap(ndp);
  }

  ll ans = 0;

  for (int j = 0; j <= deg; j++) {
    ll cur = dp[j] * fact[n - j] % MOD;

    if (j & 1)
      ans = (ans - cur + MOD) % MOD;
    else
      ans = (ans + cur) % MOD;
  }

  cout << ans << '\n';
}
