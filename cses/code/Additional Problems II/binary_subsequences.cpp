// cses/Additional Problems II/binary_subsequences.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int steps(int a, int b) {
  int ans = -1;

  while (b) {
    ans += a / b;
    a %= b;
    swap(a, b);
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  int sum = n + 2;

  int best_len = INT_MAX;
  int best_a = 1, best_b = sum - 1;

  // (a,b) and (b,a) are symmetric.
  for (int a = 1; a * 2 <= sum; ++a) {
    int b = sum - a;

    if (gcd(a, b) != 1)
      continue;

    int len = steps(a, b);

    if (len < best_len) {
      best_len = len;
      best_a = a;
      best_b = b;
    }
  }

  int a = best_a, b = best_b;
  string ans;

  // Trace the subtractive Euclidean algorithm.
  while (a != b) {
    if (a > b) {
      int cnt = (a - 1) / b;
      ans.append(cnt, '1');
      a -= cnt * b;
    } else {
      int cnt = (b - 1) / a;
      ans.append(cnt, '0');
      b -= cnt * a;
    }
  }

  cout << ans << '\n';
}
