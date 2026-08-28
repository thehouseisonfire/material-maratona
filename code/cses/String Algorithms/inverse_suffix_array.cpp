#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> sa(n), rank(n);

  for (int &x : sa) {
    cin >> x;
    --x;
  }

  for (int i = 0; i < n; i++)
    rank[sa[i]] = i;

  string s(n, 'a');
  int c = 0;

  for (int i = 1; i < n; i++) {
    int a = sa[i - 1];
    int b = sa[i];

    // Rank of the suffix after removing the first character.
    // The empty suffix is smaller than every nonempty suffix.
    int ra = (a + 1 == n ? -1 : rank[a + 1]);
    int rb = (b + 1 == n ? -1 : rank[b + 1]);

    // Same first character would give the wrong order.
    if (ra > rb)
      c++;

    if (c >= 26) {
      cout << -1 << '\n';
      return 0;
    }

    s[b] = 'a' + c;
  }

  cout << s << '\n';
}
