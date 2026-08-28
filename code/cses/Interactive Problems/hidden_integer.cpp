#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll l = 1, r = 1e9;

  while (l < r) {
    ll mid = (l + r) / 2;

    cout << "? " << mid << endl; // endl flushes output

    string s;
    cin >> s;

    if (s == "YES")
      l = mid + 1;
    else
      r = mid;
  }

  cout << "! " << l << endl;
}
