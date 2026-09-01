// atcoder/candies.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &x : a)
    cin >> x;

  vector<ll> dp(k + 1), ndp(k + 1), pref(k + 1);
  dp[0] = 1;

  for (int x : a) {
    pref[0] = dp[0];

    for (int j = 1; j <= k; j++)
      pref[j] = (pref[j - 1] + dp[j]) % MOD;

    for (int j = 0; j <= k; j++) {
      ndp[j] = pref[j];

      if (j - x - 1 >= 0)
        ndp[j] = (ndp[j] - pref[j - x - 1] + MOD) % MOD;
    }

    dp.swap(ndp);
  }

  cout << dp[k] << '\n';
}
