// cses/Bitwise Operations/xor_pyramid_row.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<ll> a(n);
  for (ll &x : a)
    cin >> x;

  int m = n - k;

  for (int d = 1; d <= m; d <<= 1)
    if (m & d)
      for (int i = 0; i + d < n; i++)
        a[i] ^= a[i + d];

  for (int i = 0; i < k; i++)
    cout << a[i] << " \n"[i == k - 1];
}
