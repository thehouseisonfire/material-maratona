// atcoder/intervals.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegTree {
  int n;
  vector<ll> st, lazy;

  SegTree(int n) : n(n), st(4 * n), lazy(4 * n) {}

  void push(int p) {
    if (!lazy[p])
      return;

    for (int q : {p * 2, p * 2 + 1}) {
      st[q] += lazy[p];
      lazy[q] += lazy[p];
    }

    lazy[p] = 0;
  }

  void add(int p, int l, int r, int ql, int qr, ll x) {
    if (qr < l || r < ql)
      return;

    if (ql <= l && r <= qr) {
      st[p] += x;
      lazy[p] += x;
      return;
    }

    push(p);

    int m = (l + r) / 2;
    add(p * 2, l, m, ql, qr, x);
    add(p * 2 + 1, m + 1, r, ql, qr, x);

    st[p] = max(st[p * 2], st[p * 2 + 1]);
  }

  void setval(int p, int l, int r, int pos, ll x) {
    if (l == r) {
      st[p] = x;
      lazy[p] = 0;
      return;
    }

    push(p);

    int m = (l + r) / 2;

    if (pos <= m)
      setval(p * 2, l, m, pos, x);
    else
      setval(p * 2 + 1, m + 1, r, pos, x);

    st[p] = max(st[p * 2], st[p * 2 + 1]);
  }

  void add(int l, int r, ll x) { add(1, 0, n - 1, l, r, x); }

  void setval(int pos, ll x) { setval(1, 0, n - 1, pos, x); }

  ll best() { return st[1]; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, ll>>> ending(n + 1);

  while (m--) {
    int l, r;
    ll a;
    cin >> l >> r >> a;
    ending[r].push_back({l, a});
  }

  SegTree seg(n + 1);

  for (int r = 1; r <= n; r++) {
    seg.setval(r, seg.best());

    for (auto [l, a] : ending[r])
      seg.add(l, r, a);
  }

  cout << seg.best() << '\n';
}
