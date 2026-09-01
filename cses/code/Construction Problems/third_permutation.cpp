// cses/Construction Problems/third_permutation.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &x : a)
    cin >> x;
  for (int &x : b)
    cin >> x;

  if (n == 2) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  // p[i] = position in a containing value b[i].
  vector<int> pos(n + 1);
  for (int i = 0; i < n; i++)
    pos[a[i]] = i;

  vector<int> p(n);
  for (int i = 0; i < n; i++)
    p[i] = pos[b[i]];

  // Concatenate the cycles of p.
  vector<int> order;
  vector<bool> vis(n);

  for (int i = 0; i < n; i++) {
    if (vis[i])
      continue;

    int u = i;
    while (!vis[u]) {
      vis[u] = true;
      order.push_back(u);
      u = p[u];
    }
  }

  // Shift by two positions in the concatenated cycle order.
  vector<int> c(n);

  for (int i = 0; i < n; i++)
    c[order[i]] = a[order[(i + 2) % n]];

  for (int x : c)
    cout << x << ' ';
  cout << '\n';
}
