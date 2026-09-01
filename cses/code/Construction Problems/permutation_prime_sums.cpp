// cses/Construction Problems/permutation_prime_sums.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int m = 2 * n + 5;

  vector<bool> prime(m, true);
  prime[0] = prime[1] = false;

  for (int i = 2; i * i < m; i++)
    if (prime[i])
      for (int j = i * i; j < m; j += i)
        prime[j] = false;

  // nextPrime[x] = smallest prime >= x
  vector<int> nextPrime(m);
  int nxt = -1;

  for (int i = m - 1; i >= 0; i--) {
    if (prime[i])
      nxt = i;
    nextPrime[i] = nxt;
  }

  vector<int> b(n + 1);

  int r = n;

  while (r > 0) {
    int p = nextPrime[r + 1];
    int l = p - r;

    for (int i = l; i <= r; i++)
      b[i] = p - i;

    r = l - 1;
  }

  for (int i = 1; i <= n; i++)
    cout << i << " \n"[i == n];

  for (int i = 1; i <= n; i++)
    cout << b[i] << " \n"[i == n];
}
