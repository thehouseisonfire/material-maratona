// cses/Counting Problems/all_letter_subgrid_count_II.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 500;

struct OrQueue {
  int val[N], in_or[N], out_or[N];
  int in = 0, out = 0;

  void clear() { in = out = 0; }

  void push(int x) {
    val[in] = x;
    in_or[in] = x | (in ? in_or[in - 1] : 0);
    ++in;
  }

  void pop() {
    if (!out) {
      while (in) {
        int x = val[--in];
        out_or[out] = x | (out ? out_or[out - 1] : 0);
        ++out;
      }
    }
    --out;
  }

  int get() const {
    return (in ? in_or[in - 1] : 0) | (out ? out_or[out - 1] : 0);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<string> g(n);
  for (auto &s : g)
    cin >> s;

  int full = (1 << k) - 1;
  int col[N];
  OrQueue q;

  ll ans = 0;

  for (int top = 0; top < n; ++top) {
    fill(col, col + n, 0);

    for (int bottom = top; bottom < n; ++bottom) {
      int all = 0;

      for (int c = 0; c < n; ++c) {
        col[c] |= 1 << (g[bottom][c] - 'A');
        all |= col[c];
      }

      if (all != full)
        continue;

      q.clear();

      for (int right = 0; right < n; ++right) {
        q.push(col[right]);

        while (q.get() == full) {
          ans += n - right;
          q.pop();
        }
      }
    }
  }

  cout << ans << '\n';
}
