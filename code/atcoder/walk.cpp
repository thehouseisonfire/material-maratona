#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

using Matrix = vector<vector<ll>>;

Matrix mul(const Matrix &a, const Matrix &b) {
  int n = a.size();
  Matrix c(n, vector<ll>(n));

  for (int i = 0; i < n; i++)
    for (int k = 0; k < n; k++)
      if (a[i][k])
        for (int j = 0; j < n; j++)
          c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;

  return c;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll k;
  cin >> n >> k;

  Matrix a(n, vector<ll>(n));
  Matrix res(n, vector<ll>(n));

  for (auto &row : a)
    for (ll &x : row)
      cin >> x;

  for (int i = 0; i < n; i++)
    res[i][i] = 1;

  while (k) {
    if (k & 1)
      res = mul(res, a);

    a = mul(a, a);
    k >>= 1;
  }

  ll ans = 0;

  for (auto &row : res)
    for (ll x : row)
      ans = (ans + x) % MOD;

  cout << ans << '\n';
}
