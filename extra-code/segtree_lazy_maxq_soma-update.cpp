// segtree_lazy_maxq_soma-update.cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define MAX 100010

ll v[MAX];
ll seg[4 * MAX];
ll lazy[4 * MAX]; // armazena multiplicações pendentes

ll build(int p, int l, int r) {
  lazy[p] = 0; // neutro da soma
  if (l == r)
    return seg[p] = v[l];
  int m = (l + r) / 2;
  return seg[p] = max(build(2 * p, l, m), build(2 * p + 1, m + 1, r));
}

// Propaga o valor pendente do nó atual para seus filhos
void push(int p, int l, int r) {
  if (lazy[p] != 0) {

    seg[2 * p] += lazy[p];
    seg[2 * p + 1] += lazy[p];

    lazy[2 * p] += lazy[p];
    lazy[2 * p + 1] += lazy[p];

    lazy[p] = 0;
  }
}

// Atualiza o intervalo [a, b] somando x a todos os elementos
void update(int a, int b, ll x, int p, int l, int r) {
  push(p, l, r);
  if (b < l || r < a)
    return;
  if (a <= l && r <= b) {
    seg[p] += x;
    lazy[p] += x;
    return;
  }

  push(p, l, r);

  int m = (l + r) / 2;
  update(a, b, x, 2 * p, l, m);
  update(a, b, x, 2 * p + 1, m + 1, r);
  seg[p] = max(seg[2 * p], seg[2 * p + 1]);
}

// Consulta a soma no intervalo [a, b]
ll query(int a, int b, int p, int l, int r) {
  push(p, l, r);
  if (b < l || r < a)
    return 0; // neutro da soma
  if (a <= l && r <= b)
    return seg[p];
  int m = (l + r) / 2;
  return max(query(a, b, 2 * p, l, m), query(a, b, 2 * p + 1, m + 1, r));
}

int main(int argc, char *argv[]) {
  cin.tie(0)->sync_with_stdio(0);

  int tt = 1;
  // cin >> tt;

  while (tt--) {
    int n, q;
    cin >> n >> q;

    memset(v, 0, sizeof(v));
    memset(seg, 0, sizeof(seg));
    memset(lazy, 0, sizeof(lazy));

    build(1, 0, n - 1);

    while (q--) {
      int o;
      cin >> o;
      if (o == 1) {
        int p, q;
        ll val;
        cin >> p >> q >> val;
        p--;
        q--;
        update(p, q, val, 1, 0, n - 1);
      } else {
        int p, r;
        cin >> p >> r;
        p--;
        r--;
        ll res = query(p, r, 1, 0, n - 1);
        cout << res << endl;
      }
    }
  }

  return 0;
}
