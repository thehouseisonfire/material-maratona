// segment-tree.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 9;

// CURRENT CONFIGURATION:
// Query: MAX
// Update: RANGE ADD
//
// Valid ADD queries: SUM, SUM MOD, MAX, MIN
// Valid SET queries: SUM, SUM MOD, MAX, MIN, GCD, XOR, MULT

struct SegTree {
  int n;
  vector<ll> tree, lazy;

  // Needed for RANGE SET lazy:
  // vector<char> hasLazy;

  SegTree(const vector<ll> &a) {
    n = a.size();
    tree.resize(4 * n);
    lazy.assign(4 * n, 0);

    // RANGE SET:
    // hasLazy.assign(4 * n, false);

    if (n)
      build(1, 0, n - 1, a);
  }

  // Identity value for queries outside the range.
  ll neutral() {
    // SUM:
    // return 0;

    // MAX:
    return LLONG_MIN;

    // MIN:
    // return LLONG_MAX;

    // GCD:
    // return 0;

    // XOR:
    // return 0;

    // MULT:
    // return 1;
  }

  // Merge two children.
  ll mergeVal(ll a, ll b) {
    // SUM:
    // return a + b;

    // SUM MOD:
    // return (a + b) % MOD;

    // MAX:
    return max(a, b);

    // MIN:
    // return min(a, b);

    // GCD:
    // return gcd(a, b);

    // XOR:
    // return a ^ b;

    // MULT:
    // return a * b % MOD;
  }

  // Modular exponentiation -- used by MULT.
  ll power(ll a, int e) {
    a %= MOD;
    if (a < 0)
      a += MOD;

    ll res = 1;

    while (e) {
      if (e & 1)
        res = res * a % MOD;

      a = a * a % MOD;
      e >>= 1;
    }

    return res;
  }

  void build(int p, int l, int r, const vector<ll> &a) {
    if (l == r) {
      // SUM / MAX / MIN / XOR:
      tree[p] = a[l];

      // SUM MOD:
      // tree[p] = (a[l] % MOD + MOD) % MOD;

      // GCD:
      // tree[p] = abs(a[l]);

      // MULT:
      // tree[p] = (a[l] % MOD + MOD) % MOD;

      return;
    }

    int m = (l + r) / 2;

    build(p * 2, l, m, a);
    build(p * 2 + 1, m + 1, r, a);

    tree[p] = mergeVal(tree[p * 2], tree[p * 2 + 1]);
  }

  // Apply lazy update to every element in [l, r].
  void apply(int p, int l, int r, ll x) {
    int len = r - l + 1;

    ///////////////////////////////////////////////////////////////
    // RANGE ADD -- COMMENT THIS WHOLE BLOCK WHEN USING RANGE SET
    ///////////////////////////////////////////////////////////////

    // SUM + ADD:
    // tree[p] += x * len;

    // SUM MOD + ADD:
    // tree[p] = (tree[p] + (x % MOD + MOD) % MOD * len) % MOD;

    // MAX + ADD:
    tree[p] += x;

    // MIN + ADD:
    // tree[p] += x;

    // Lazy composition for ADD:
    lazy[p] += x;

    ///////////////////////////////////////////////////////////////
    // RANGE SET -- COMMENT THIS WHOLE BLOCK WHEN USING RANGE ADD
    ///////////////////////////////////////////////////////////////

    // SUM + SET:
    // tree[p] = x * len;

    // SUM MOD + SET:
    // tree[p] = (x % MOD + MOD) % MOD * len % MOD;

    // MAX + SET:
    // tree[p] = x;

    // MIN + SET:
    // tree[p] = x;

    // GCD + SET:
    // tree[p] = abs(x);

    // XOR + SET:
    // tree[p] = (len & 1) ? x : 0;

    // MULT + SET:
    // tree[p] = power(x, len);

    // Lazy composition for SET:
    // lazy[p] = x;
    // hasLazy[p] = true;
  }

  void push(int p, int l, int r) {
    if (l == r)
      return;

    ////////////////////////////////////////////////////////////////
    // RANGE ADD
    ////////////////////////////////////////////////////////////////

    if (lazy[p] == 0)
      return;

    int m = (l + r) / 2;

    apply(p * 2, l, m, lazy[p]);
    apply(p * 2 + 1, m + 1, r, lazy[p]);

    lazy[p] = 0;

    ////////////////////////////////////////////////////////////////
    // RANGE SET
    ////////////////////////////////////////////////////////////////

    /*
    if (!hasLazy[p])
      return;

    int m = (l + r) / 2;

    apply(p * 2, l, m, lazy[p]);
    apply(p * 2 + 1, m + 1, r, lazy[p]);

    hasLazy[p] = false;
    */
  }

  // Apply update x to every a[i] in [ql, qr].
  void update(int p, int l, int r, int ql, int qr, ll x) {
    if (qr < l || r < ql)
      return;

    if (ql <= l && r <= qr) {
      apply(p, l, r, x);
      return;
    }

    push(p, l, r);

    int m = (l + r) / 2;

    update(p * 2, l, m, ql, qr, x);
    update(p * 2 + 1, m + 1, r, ql, qr, x);

    tree[p] = mergeVal(tree[p * 2], tree[p * 2 + 1]);
  }

  ll query(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql)
      return neutral();

    if (ql <= l && r <= qr)
      return tree[p];

    push(p, l, r);

    int m = (l + r) / 2;

    return mergeVal(query(p * 2, l, m, ql, qr),
                    query(p * 2 + 1, m + 1, r, ql, qr));
  }

  void update(int l, int r, ll x) {
    if (n)
      update(1, 0, n - 1, l, r, x);
  }

  ll query(int l, int r) {
    if (!n)
      return neutral();

    return query(1, 0, n - 1, l, r);
  }
};

int main() {
  vector<ll> a = {1, 2, 3, 4, 5};
  SegTree st(a);

  cout << st.query(1, 3) << '\n'; // 4

  // a[1..3] += 10
  st.update(1, 3, 10);

  cout << st.query(1, 3) << '\n'; // 14
}
