#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
  int n;
  vector<ll> bit;

  Fenwick(int n) : n(n), bit(n + 1) {}

  void update(int i, ll x) {
    for (; i <= n; i += i & -i)
      bit[i] = max(bit[i], x);
  }

  ll query(int i) {
    ll res = 0;

    for (; i > 0; i -= i & -i)
      res = max(res, bit[i]);

    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<int> h(n);
  vector<ll> a(n);

  for (int &x : h)
    cin >> x;
  for (ll &x : a)
    cin >> x;

  Fenwick fw(n);

  for (int i = 0; i < n; i++) {
    ll cur = fw.query(h[i] - 1) + a[i];
    fw.update(h[i], cur);
  }

  cout << fw.query(n) << '\n';
}
