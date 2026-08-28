#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  while (n--) {
    ll a, b, x;
    cin >> a >> b >> x;

    cout << (x <= a && x % gcd(a, b) == 0 ? "YES\n" : "NO\n");
  }
}
