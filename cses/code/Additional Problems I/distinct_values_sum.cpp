// cses/Additional Problems I/distinct_values_sum.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  unordered_map<int, int> last;
  last.reserve(2 * n);

  ll cur = 0, ans = 0;

  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;

    cur += i - last[x];
    last[x] = i;

    ans += cur;
  }

  cout << ans << '\n';
}
