#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> p(n - 2), deg(n + 1, 1);

  for (int &x : p) {
    cin >> x;
    deg[x]++;
  }

  priority_queue<int, vector<int>, greater<int>> leaves;

  for (int i = 1; i <= n; i++)
    if (deg[i] == 1)
      leaves.push(i);

  for (int x : p) {
    int u = leaves.top();
    leaves.pop();

    cout << u << ' ' << x << '\n';

    if (--deg[x] == 1)
      leaves.push(x);
  }

  int a = leaves.top();
  leaves.pop();
  int b = leaves.top();

  cout << a << ' ' << b << '\n';
}
