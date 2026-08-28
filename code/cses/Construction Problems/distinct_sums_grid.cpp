#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  if (n <= 3) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  if (n == 4) {
    cout << "3 4 4 3\n";
    cout << "2 3 4 4\n";
    cout << "1 2 2 3\n";
    cout << "1 1 1 2\n";
    return 0;
  }

  vector<vector<int>> a(n, vector<int>(n));

  for (int i = 0; i < n; i++) {
    a[i][0] = n;

    for (int j = 1; j < n; j++)
      a[i][j] = (j > i ? i + 1 : i);
  }

  map<ll, int> row;

  for (int i = 0; i < n; i++) {
    ll sum = 0;
    for (int x : a[i])
      sum += x;
    row[sum] = i;
  }

  for (int j = 0; j < n; j++) {
    ll sum = 0;
    for (int i = 0; i < n; i++)
      sum += a[i][j];

    if (!row.count(sum))
      continue;

    int i = row[sum];

    swap(a[1][0], a[1][j]);
    swap(a[i + 1][n - 1], a[i + 2][n - 1]);
    break;
  }

  for (auto &row : a) {
    for (int x : row)
      cout << x << ' ';
    cout << '\n';
  }
}
