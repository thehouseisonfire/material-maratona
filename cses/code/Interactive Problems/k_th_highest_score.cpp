// cses/Interactive Problems/k_th_highest_score.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX / 4;

int n, k;

ll ask(char c, int i) {
  if (i == 0)
    return INF;
  if (i == n + 1)
    return -INF;

  cout << c << " " << i << endl;

  ll x;
  cin >> x;
  return x;
}

int main() {
  cin >> n >> k;

  // x = number of Finnish scores among the top k.
  int l = max(0, k - n);
  int r = min(k, n);

  // Find the largest x such that
  // F[x] > S[k-x+1].
  while (l < r) {
    int x = (l + r + 1) / 2;
    int y = k - x;

    if (ask('F', x) > ask('S', y + 1))
      l = x;
    else
      r = x - 1;
  }

  int x = l;
  int y = k - x;

  // The k-th highest is the smaller of the
  // last selected score from each country.
  ll ans = min(ask('F', x), ask('S', y));

  cout << "! " << ans << endl;
}
