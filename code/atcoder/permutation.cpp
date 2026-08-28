#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  string s;
  cin >> n >> s;

  vector<ll> dp(n), ndp(n), pref(n + 1);
  dp[0] = 1;

  for (int i = 1; i < n; i++) {
    pref[0] = 0;

    for (int j = 0; j < i; j++)
      pref[j + 1] = (pref[j] + dp[j]) % MOD;

    fill(ndp.begin(), ndp.end(), 0);

    for (int j = 0; j <= i; j++) {
      if (s[i - 1] == '<') {
        ndp[j] = pref[j];
      } else {
        ndp[j] = (pref[i] - pref[j] + MOD) % MOD;
      }
    }

    dp.swap(ndp);
  }

  ll ans = 0;

  for (int j = 0; j < n; j++)
    ans = (ans + dp[j]) % MOD;

  cout << ans << '\n';
}
