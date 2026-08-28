#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> x(n);
  for (ll &v : x)
    cin >> v;

  int m = n / 2;

  auto gen = [&](int l, int r) {
    int k = r - l, N = 1 << k;
    vector<pair<ll, int>> v(N);

    for (int mask = 1; mask < N; ++mask) {
      int b = __builtin_ctz(mask);
      int pm = mask ^ (1 << b);
      v[mask] = {v[pm].first + x[l + b], mask};
    }

    sort(v.begin(), v.end());
    return v;
  };

  auto A = gen(0, m);
  auto B = gen(m, n);

  vector<ll> sa(A.size()), sb(B.size());

  for (int i = 0; i < (int)A.size(); ++i)
    sa[i] = A[i].first;
  for (int i = 0; i < (int)B.size(); ++i)
    sb[i] = B[i].first;

  // Number of non-empty subsets with sum <= s.
  auto count_le = [&](ll s) {
    ll cnt = 0;
    int j = (int)sb.size() - 1;

    for (ll a : sa) {
      while (j >= 0 && a + sb[j] > s)
        --j;

      if (j < 0)
        break;
      cnt += j + 1;
    }

    return cnt - 1; // remove empty subset
  };

  // Find adjacent lo, hi such that
  // count_le(lo) <= lo and count_le(hi) > hi.
  ll lo = 0;
  ll hi = accumulate(x.begin(), x.end(), 0LL);

  while (hi - lo > 1) {
    ll mid = (lo + hi) / 2;

    if (count_le(mid) > mid)
      hi = mid;
    else
      lo = mid;
  }

  // At least two subsets have sum exactly hi.
  ll target = hi;

  ull p = 0, q = 0;
  bool have = false, found = false;

  int i = 0;
  int j = (int)B.size() - 1;

  while (i < (int)A.size() && j >= 0) {
    ll s = A[i].first + B[j].first;

    if (s < target) {
      ++i;
    } else if (s > target) {
      --j;
    } else {
      ll a = A[i].first;
      ll b = B[j].first;

      int ni = i + 1;
      int nj = j - 1;

      while (ni < (int)A.size() && A[ni].first == a)
        ++ni;
      while (nj >= 0 && B[nj].first == b)
        --nj;

      auto mask = [&](int u, int v) {
        return (ull)A[u].second | ((ull)B[v].second << m);
      };

      ull cur = mask(i, j);

      if (!have) {
        p = cur;
        have = true;

        if (ni - i >= 2) {
          q = mask(i + 1, j);
          found = true;
          break;
        }

        if (j - nj >= 2) {
          q = mask(i, j - 1);
          found = true;
          break;
        }
      } else {
        q = cur;
        found = true;
        break;
      }

      i = ni;
      j = nj;
    }
  }

  if (!found) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  // Cancel their intersection.
  ull common = p & q;
  p ^= common;
  q ^= common;

  auto print = [&](ull mask) {
    cout << __builtin_popcountll(mask) << '\n';

    for (int i = 0; i < n; ++i)
      if (mask >> i & 1ULL)
        cout << x[i] << ' ';

    cout << '\n';
  };

  print(p);
  print(q);
}
