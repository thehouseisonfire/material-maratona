// cses/Additional Problems II/replace_with_difference.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXS = 500001;

bitset<MAXS> dp[1001];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  int sum = 0;

  for (int &x : a) {
    cin >> x;
    sum += x;
  }

  if (sum % 2) {
    cout << -1 << '\n';
    return 0;
  }

  int target = sum / 2;

  dp[0][0] = 1;

  for (int i = 0; i < n; i++)
    dp[i + 1] = dp[i] | (dp[i] << a[i]);

  if (!dp[n][target]) {
    cout << -1 << '\n';
    return 0;
  }

  vector<int> A, B;

  int s = target;

  for (int i = n; i >= 1; i--) {
    if (dp[i - 1][s]) {
      B.push_back(a[i - 1]);
    } else {
      A.push_back(a[i - 1]);
      s -= a[i - 1];
    }
  }

  int i = 0, j = 0;
  int x = A[0], y = B[0];
  int zeros = 0;

  while (i < (int)A.size() && j < (int)B.size()) {
    cout << x << ' ' << y << '\n';

    if (x > y) {
      x -= y;
      j++;
      if (j < (int)B.size())
        y = B[j];
    } else if (y > x) {
      y -= x;
      i++;
      if (i < (int)A.size())
        x = A[i];
    } else {
      zeros++;
      i++;
      j++;

      if (i < (int)A.size())
        x = A[i];
      if (j < (int)B.size())
        y = B[j];
    }
  }

  for (int k = 1; k < zeros; k++)
    cout << "0 0\n";
}
