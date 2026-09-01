// cses/Interactive Problems/permuted_binary_strings.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int n;
  cin >> n;

  int q = 0;
  while ((1 << q) < n)
    q++;

  vector<int> ans(n);

  for (int bit = 0; bit < q; bit++) {
    string s(n, '0');

    for (int i = 0; i < n; i++)
      if ((i >> bit) & 1)
        s[i] = '1';

    cout << "? " << s << endl;

    string res;
    cin >> res;

    for (int i = 0; i < n; i++)
      if (res[i] == '1')
        ans[i] |= 1 << bit;
  }

  cout << "!";
  for (int x : ans)
    cout << " " << x + 1;
  cout << endl;
}
