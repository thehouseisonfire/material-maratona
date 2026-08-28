#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  auto ask = [&](int l, int r) {
    cout << l << " " << r << endl;

    ll x;
    cin >> x;

    if (x < 0)
      exit(0);

    return x;
  };

  vector<ll> pref(n + 1);

  // Reverse everything once so we learn the inversion count
  // of the permutation we will reconstruct.
  ll base = ask(1, n);

  if (base == 0)
    return 0;

  pref[1] = 0;
  pref[n] = base;

  // Recover inversion count of every prefix.
  for (int k = 2; k < n; k++) {
    ll after = ask(1, k);

    if (after == 0)
      return 0;

    ll pairs = 1LL * k * (k - 1) / 2;

    // after - base = pairs - 2 * pref[k]
    pref[k] = (pairs - (after - base)) / 2;

    // Restore the permutation.
    base = ask(1, k);

    if (base == 0)
      return 0;
  }

  // e[i] = number of previous elements greater than a[i].
  // This is an inversion sequence, so reconstruct the permutation.
  vector<int> remaining(n);
  iota(remaining.begin(), remaining.end(), 1);

  vector<int> a(n + 1);

  for (int i = n; i >= 1; i--) {
    int e = pref[i] - pref[i - 1];
    int rank = i - e; // rank of a[i] among remaining values

    a[i] = remaining[rank - 1];
    remaining.erase(remaining.begin() + rank - 1);
  }

  // Now we know the permutation. Put i into position i.
  for (int i = 1; i <= n; i++) {
    if (a[i] == i)
      continue;

    int j = i;
    while (a[j] != i)
      j++;

    ll inv = ask(i, j);

    if (inv == 0)
      return 0;

    reverse(a.begin() + i, a.begin() + j + 1);
  }
}
