// cses/Bitwise Operations/and_subset_count.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int m = 1;
  while (m <= n)
    m <<= 1;

  vector<int> cnt(m);

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }

  // cnt[mask] = number of elements containing all bits of mask
  for (int bit = 1; bit < m; bit <<= 1)
    for (int mask = 0; mask < m; mask++)
      if (!(mask & bit))
        cnt[mask] += cnt[mask | bit];

  vector<ll> pow2(n + 1, 1);
  for (int i = 1; i <= n; i++)
    pow2[i] = 2 * pow2[i - 1] % MOD;

  // ans[mask] = subsets whose AND contains mask
  vector<ll> ans(m);
  for (int mask = 0; mask < m; mask++)
    ans[mask] = (pow2[cnt[mask]] - 1 + MOD) % MOD;

  // Möbius inversion: containing mask -> exactly mask
  for (int bit = 1; bit < m; bit <<= 1)
    for (int mask = 0; mask < m; mask++)
      if (!(mask & bit)) {
        ans[mask] -= ans[mask | bit];
        if (ans[mask] < 0)
          ans[mask] += MOD;
      }

  for (int k = 0; k <= n; k++)
    cout << ans[k] << " \n"[k == n];
}
