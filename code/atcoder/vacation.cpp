#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  ll a, b, c;
  cin >> a >> b >> c;

  ll x = a, y = b, z = c;

  for (int i = 1; i < n; i++) {
    cin >> a >> b >> c;

    ll nx = a + max(y, z);
    ll ny = b + max(x, z);
    ll nz = c + max(x, y);

    x = nx;
    y = ny;
    z = nz;
  }

  cout << max({x, y, z}) << '\n';
}
