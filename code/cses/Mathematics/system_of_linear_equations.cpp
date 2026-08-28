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
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<ll>> a(n, vector<ll>(m + 1));

  for (auto &row : a)
    for (ll &x : row)
      cin >> x;

  vector<int> where(m, -1);
  int row = 0;

  // Gaussian elimination.
  for (int col = 0; col < m && row < n; col++) {
    int sel = row;

    while (sel < n && a[sel][col] == 0)
      sel++;

    if (sel == n)
      continue;

    swap(a[sel], a[row]);
    where[col] = row;

    ll inv = modpow(a[row][col], MOD - 2);

    for (int j = col; j <= m; j++)
      a[row][j] = a[row][j] * inv % MOD;

    for (int i = row + 1; i < n; i++) {
      if (a[i][col] == 0)
        continue;

      ll f = a[i][col];

      for (int j = col; j <= m; j++) {
        a[i][j] -= f * a[row][j] % MOD;
        if (a[i][j] < 0)
          a[i][j] += MOD;
      }
    }

    row++;
  }

  // Check for 0 = nonzero.
  for (int i = row; i < n; i++) {
    bool zero = true;

    for (int j = 0; j < m; j++)
      if (a[i][j] != 0)
        zero = false;

    if (zero && a[i][m] != 0) {
      cout << -1 << '\n';
      return 0;
    }
  }

  // Free variables stay 0.
  vector<ll> x(m);

  // Back substitution.
  for (int col = m - 1; col >= 0; col--) {
    if (where[col] == -1)
      continue;

    int r = where[col];
    x[col] = a[r][m];

    for (int j = col + 1; j < m; j++) {
      x[col] -= a[r][j] * x[j] % MOD;
      if (x[col] < 0)
        x[col] += MOD;
    }
  }

  for (int i = 0; i < m; i++)
    cout << x[i] << " \n"[i == m - 1];
}
