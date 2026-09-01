// cses/Range Queries/visible_buildings_queries.cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  int n, q;
  cin >> n >> q;

  vector<ll> h(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> h[i];

  const int LOG = 18;
  vector<vector<int>> up(LOG, vector<int>(n + 2, n + 1));

  // Next strictly greater element to the right
  stack<int> st;

  for (int i = n; i >= 1; i--) {
    while (!st.empty() && h[st.top()] <= h[i])
      st.pop();

    if (!st.empty())
      up[0][i] = st.top();

    st.push(i);
  }

  // Binary lifting
  for (int k = 1; k < LOG; k++)
    for (int i = 1; i <= n; i++)
      up[k][i] = up[k - 1][up[k - 1][i]];

  while (q--) {
    int a, b;
    cin >> a >> b;

    int cur = a;
    int ans = 1; // building a is always visible

    for (int k = LOG - 1; k >= 0; k--) {
      if (up[k][cur] <= b) {
        cur = up[k][cur];
        ans += 1 << k;
      }
    }

    cout << ans << '\n';
  }
}
