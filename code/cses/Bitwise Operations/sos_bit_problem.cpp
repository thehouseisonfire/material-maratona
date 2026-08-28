#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  const int B = 20;
  const int M = 1 << B;

  vector<int> a(n), sub(M), sup(M);

  for (int &x : a) {
    cin >> x;
    sub[x]++;
    sup[x]++;
  }

  // sub[x] = number of y such that y is a submask of x
  //        -> x | y = x
  for (int b = 0; b < B; b++)
    for (int mask = 0; mask < M; mask++)
      if (mask & (1 << b))
        sub[mask] += sub[mask ^ (1 << b)];

  // sup[x] = number of y such that y is a supermask of x
  //        -> x & y = x
  for (int b = 0; b < B; b++)
    for (int mask = 0; mask < M; mask++)
      if (!(mask & (1 << b)))
        sup[mask] += sup[mask ^ (1 << b)];

  int all = M - 1;

  for (int x : a) {
    // x & y == 0 iff y is a submask of ~x.
    int disjoint = sub[all ^ x];

    cout << sub[x] << ' ' << sup[x] << ' ' << n - disjoint << '\n';
  }
}
