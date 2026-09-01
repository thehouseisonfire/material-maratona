// atcoder/sushi.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
double dp[301][301][301];

double solve(int a, int b, int c) {
  if (a + b + c == 0)
    return 0;

  double &res = dp[a][b][c];
  if (res != 0)
    return res;

  res = n;

  if (a)
    res += a * solve(a - 1, b, c);

  if (b)
    res += b * solve(a + 1, b - 1, c);

  if (c)
    res += c * solve(a, b + 1, c - 1);

  return res /= a + b + c;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n;

  int cnt[4] = {};

  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cnt[x]++;
  }

  cout << fixed << setprecision(15) << solve(cnt[1], cnt[2], cnt[3]) << '\n';
}
