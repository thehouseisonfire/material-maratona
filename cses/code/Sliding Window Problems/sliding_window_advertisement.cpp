// cses/Sliding Window Problems/sliding_window_advertisement.cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct LiChao {
  struct Line {
    ll m = 0, b = 0;

    ll get(ll x) const { return m * x + b; }
  };

  int n;
  vector<Line> tree;

  LiChao(int n) : n(n), tree(4 * n) {}

  void add_line(Line nw, int p, int l, int r) {
    int mid = (l + r) / 2;

    bool lef = nw.get(l) > tree[p].get(l);
    bool mid_better = nw.get(mid) > tree[p].get(mid);

    if (mid_better)
      swap(nw, tree[p]);

    if (l == r)
      return;

    if (lef != mid_better)
      add_line(nw, 2 * p, l, mid);
    else
      add_line(nw, 2 * p + 1, mid + 1, r);
  }

  void add_segment(Line nw, int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql)
      return;

    if (ql <= l && r <= qr) {
      add_line(nw, p, l, r);
      return;
    }

    int mid = (l + r) / 2;
    add_segment(nw, ql, qr, 2 * p, l, mid);
    add_segment(nw, ql, qr, 2 * p + 1, mid + 1, r);
  }

  void add_segment(Line nw, int l, int r) {
    l = max(l, 0);
    r = min(r, n - 1);

    if (l <= r)
      add_segment(nw, l, r, 1, 0, n - 1);
  }

  ll query(int x, int p, int l, int r) {
    ll ans = tree[p].get(x);

    if (l == r)
      return ans;

    int mid = (l + r) / 2;

    if (x <= mid)
      return max(ans, query(x, 2 * p, l, mid));
    else
      return max(ans, query(x, 2 * p + 1, mid + 1, r));
  }

  ll query(int x) { return query(x, 1, 0, n - 1); }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<ll> a(n);
  for (ll &x : a)
    cin >> x;

  // Maximal interval [prv[i] + 1, nxt[i] - 1]
  // where a[i] can be the minimum.
  vector<int> prv(n), nxt(n), st;

  for (int i = 0; i < n; i++) {
    while (!st.empty() && a[st.back()] >= a[i])
      st.pop_back();

    prv[i] = st.empty() ? -1 : st.back();
    st.push_back(i);
  }

  st.clear();

  for (int i = n - 1; i >= 0; i--) {
    while (!st.empty() && a[st.back()] >= a[i])
      st.pop_back();

    nxt[i] = st.empty() ? n : st.back();
    st.push_back(i);
  }

  int windows = n - k + 1;
  LiChao cht(windows);

  for (int i = 0; i < n; i++) {
    int l = prv[i] + 1;
    int r = nxt[i] - 1;
    int len = r - l + 1;
    ll h = a[i];

    if (len >= k) {
      // Increasing part.
      cht.add_segment({h, h * (k - l)}, l - k + 1, l);

      // Whole window fits.
      cht.add_segment({0, h * k}, l, r - k + 1);

      // Decreasing part.
      cht.add_segment({-h, h * (r + 1)}, r - k + 1, r);
    } else {
      // Window enters [l, r].
      cht.add_segment({h, h * (k - l)}, l - k + 1, r - k + 1);

      // Window completely covers [l, r].
      cht.add_segment({0, h * len}, r - k + 1, l);

      // Window leaves [l, r].
      cht.add_segment({-h, h * (r + 1)}, l, r);
    }
  }

  for (int i = 0; i < windows; i++)
    cout << cht.query(i) << " \n"[i + 1 == windows];
}
