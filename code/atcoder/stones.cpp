#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &x : a)
    cin >> x;

  vector<bool> win(k + 1);

  for (int stones = 1; stones <= k; stones++) {
    for (int x : a) {
      if (x > stones)
        break;

      if (!win[stones - x]) {
        win[stones] = true;
        break;
      }
    }
  }

  cout << (win[k] ? "First" : "Second") << '\n';
}
