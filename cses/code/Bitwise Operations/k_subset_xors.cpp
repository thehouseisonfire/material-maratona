// cses/Bitwise Operations/k_subset_xors.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  const int B = 30;
  ll basis[B] = {};

  // Build xor basis, pivot = highest set bit.
  for (int t = 0; t < n; t++) {
    ll x;
    cin >> x;

    for (int i = B - 1; i >= 0; i--) {
      if (!(x >> i & 1))
        continue;

      if (basis[i])
        x ^= basis[i];
      else {
        basis[i] = x;
        break;
      }
    }
  }

  // Reduced basis:
  // basis[j] must not contain the pivot bit of basis[i], i < j.
  //
  // After this, masks 0,1,2,... produce xor values
  // directly in increasing order.
  for (int i = 0; i < B; i++)
    if (basis[i])
      for (int j = i + 1; j < B; j++)
        if (basis[j] >> i & 1)
          basis[j] ^= basis[i];

  vector<ll> b;
  for (int i = 0; i < B; i++)
    if (basis[i])
      b.push_back(basis[i]);

  int rank = b.size();

  // Every distinct xor appears 2^(n-rank) times.
  ll copies = 1;
  for (int i = 0; i < n - rank && copies < k; i++)
    copies = min<ll>(k, copies * 2);

  int need = (k + copies - 1) / copies;

  int printed = 0;

  for (int mask = 0; mask < need; mask++) {
    ll x = 0;

    for (int i = 0; i < rank; i++)
      if (mask >> i & 1)
        x ^= b[i];

    for (ll rep = 0; rep < copies && printed < k; rep++) {
      if (printed++)
        cout << ' ';
      cout << x;
    }
  }

  cout << '\n';
}
