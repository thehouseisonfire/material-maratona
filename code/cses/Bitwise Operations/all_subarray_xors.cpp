#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fwht(vector<ll> &a) {
  int n = a.size();

  for (int len = 1; len < n; len <<= 1)
    for (int i = 0; i < n; i += 2 * len)
      for (int j = 0; j < len; j++) {
        ll x = a[i + j];
        ll y = a[i + j + len];

        a[i + j] = x + y;
        a[i + j + len] = x - y;
      }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  const int M = 1 << 20;
  vector<ll> f(M);

  int pref = 0;
  f[0]++;

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;

    pref ^= x;
    f[pref]++;
  }

  // XOR convolution f * f.
  fwht(f);

  for (ll &x : f)
    x *= x;

  fwht(f);

  for (ll &x : f)
    x /= M;

  vector<int> ans;

  for (int x = 0; x < M; x++) {
    if (x == 0) {
      // f[0] also counts pairing every prefix with itself.
      if (f[x] > n + 1)
        ans.push_back(x);
    } else if (f[x] > 0) {
      ans.push_back(x);
    }
  }

  cout << ans.size() << '\n';

  for (int x : ans)
    cout << x << ' ';

  cout << '\n';
}
