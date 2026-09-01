// cses/Additional Problems II/gcd_subsets.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> freq(n + 1);
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    freq[x]++;
  }

  vector<ll> pw2(n + 1, 1);
  for (int i = 1; i <= n; i++)
    pw2[i] = pw2[i - 1] * 2 % MOD;

  vector<ll> ans(n + 1);

  for (int k = n; k >= 1; k--) {
    int cnt = 0;
    for (int j = k; j <= n; j += k)
      cnt += freq[j];

    ans[k] = pw2[cnt] - 1;

    for (int j = 2 * k; j <= n; j += k)
      ans[k] = (ans[k] - ans[j] + MOD) % MOD;
  }

  for (int k = 1; k <= n; k++)
    cout << ans[k] << " \n"[k == n];
}
