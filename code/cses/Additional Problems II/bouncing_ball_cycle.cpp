#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    ll n, m;
    cin >> n >> m;

    ll a = n - 1;
    ll b = m - 1;
    ll g = gcd(a, b);

    ll A = a / g;
    ll B = b / g;
    ll l = A * b; // lcm(a, b)

    ll steps = 2 * l;
    ll cells = l - (A - 1) * (B - 1) / 2 + 1;

    cout << steps << ' ' << cells << '\n';
  }
}
