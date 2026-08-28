#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;

  auto ask = [&](int i) {
    cout << "? " << i << endl;
    char c;
    cin >> c;
    return c;
  };

  int l = 1, r = n;
  char cl = ask(l);
  char cr = ask(r);

  // Since n is odd, chairs n and 1 are adjacent.
  if (cl == cr) {
    cout << "! " << n << endl;
    return 0;
  }

  while (r - l > 1) {
    int m = (l + r) / 2;
    char cm = ask(m);

    // With perfect alternation:
    // even distance -> same color
    // odd distance  -> different colors
    bool left_bad = (cl == cm) != ((m - l) % 2 == 0);

    if (left_bad) {
      r = m;
      cr = cm;
    } else {
      l = m;
      cl = cm;
    }
  }

  cout << "! " << l << endl;
}
