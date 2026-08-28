#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll position(ll len, ll k) {
  ll d = len - 1;
  ll x = k % (2 * d);
  if (x > d)
    x = 2 * d - x;
  return x + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    ll n, m, k;
    cin >> n >> m >> k;

    ll a = n - 1;
    ll b = m - 1;

    ll g = gcd(a, b);
    ll lcm = a / g * b;

    ll changes = k / a + k / b - k / lcm;

    cout << position(n, k) << ' ' << position(m, k) << ' ' << changes << '\n';
  }
}
