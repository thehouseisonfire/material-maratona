// cses/Additional Problems II/knight_moves_queries.cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll solve(ll x, ll y) {
  x--;
  y--;

  if (x < y)
    swap(x, y);

  if (x == 1 && y == 1)
    return 4;
  if (x == 1 && y == 0)
    return 3;
  if (x == 2 && y == 2)
    return 4;

  ll d = max((x + 1) / 2, (x + y + 2) / 3);

  if ((d + x + y) % 2)
    d++;
  return d;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  while (n--) {
    ll x, y;
    cin >> x >> y;
    cout << solve(x, y) << '\n';
  }
}
