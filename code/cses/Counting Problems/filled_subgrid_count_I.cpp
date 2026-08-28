#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<ll> ans(k);
  vector<int> prev(n), cur(n);

  string last, row;

  for (int i = 0; i < n; i++) {
    cin >> row;

    for (int j = 0; j < n; j++) {
      cur[j] = 1;

      if (i > 0 && j > 0 && row[j] == last[j] && row[j] == row[j - 1] &&
          row[j] == last[j - 1]) {
        cur[j] = 1 + min({prev[j], cur[j - 1], prev[j - 1]});
      }

      ans[row[j] - 'A'] += cur[j];
    }

    swap(prev, cur);
    last = row;
  }

  for (ll x : ans)
    cout << x << '\n';
}
