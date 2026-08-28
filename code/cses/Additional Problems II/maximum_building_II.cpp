#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<string> g(n);
  for (auto &s : g)
    cin >> s;

  vector<vector<ll>> A(n + 2, vector<ll>(m + 2));
  vector<vector<ll>> B(n + 2, vector<ll>(m + 2));

  auto add = [&](int h, int l, int r, ll a, ll b) {
    if (h == 0 || l > r)
      return;

    A[1][l] += a;
    A[1][r + 1] -= a;
    A[h + 1][l] -= a;
    A[h + 1][r + 1] += a;

    B[1][l] += b;
    B[1][r + 1] -= b;
    B[h + 1][l] -= b;
    B[h + 1][r + 1] += b;
  };

  vector<int> h(m), prv(m), nxt(m), st;

  for (int row = 0; row < n; row++) {
    for (int j = 0; j < m; j++) {
      if (g[row][j] == '.')
        h[j]++;
      else
        h[j] = 0;
    }

    st.clear();
    for (int i = 0; i < m; i++) {
      while (!st.empty() && h[st.back()] >= h[i])
        st.pop_back();
      prv[i] = st.empty() ? -1 : st.back();
      st.push_back(i);
    }

    st.clear();
    for (int i = m - 1; i >= 0; i--) {
      while (!st.empty() && h[st.back()] > h[i])
        st.pop_back();
      nxt[i] = st.empty() ? m : st.back();
      st.push_back(i);
    }

    for (int i = 0; i < m; i++) {
      if (h[i] == 0)
        continue;

      int L = i - prv[i];
      int R = nxt[i] - i;

      int x = min(L, R);
      int y = max(L, R);
      int s = L + R;

      // Number of intervals of width w containing i:
      //
      // w                    for 1 <= w <= x
      // x                    for x < w <= y
      // L + R - w            for y < w <= L+R-1

      add(h[i], 1, x, 1, 0);
      add(h[i], x + 1, y, 0, x);
      add(h[i], y + 1, s - 1, -1, s);
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      A[i][j] += A[i - 1][j] + A[i][j - 1] - A[i - 1][j - 1];
      B[i][j] += B[i - 1][j] + B[i][j - 1] - B[i - 1][j - 1];

      cout << A[i][j] * j + B[i][j] << (j == m ? '\n' : ' ');
    }
  }
}
