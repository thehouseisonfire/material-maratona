// cses/Interactive Problems/hidden_permutation.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool ask(int i, int j) {
  cout << "? " << i << ' ' << j << endl;

  string s;
  cin >> s;
  return s == "YES";
}

void merge_sort(vector<int> &v, int l, int r) {
  if (r - l <= 1)
    return;

  int m = (l + r) / 2;
  merge_sort(v, l, m);
  merge_sort(v, m, r);

  vector<int> tmp;
  int i = l, j = m;

  while (i < m && j < r) {
    if (ask(v[i], v[j]))
      tmp.push_back(v[i++]);
    else
      tmp.push_back(v[j++]);
  }

  while (i < m)
    tmp.push_back(v[i++]);
  while (j < r)
    tmp.push_back(v[j++]);

  for (int k = 0; k < (int)tmp.size(); k++)
    v[l + k] = tmp[k];
}

int main() {
  int n;
  cin >> n;

  vector<int> p(n);
  iota(p.begin(), p.end(), 1);

  merge_sort(p, 0, n);

  vector<int> ans(n);

  for (int i = 0; i < n; i++)
    ans[p[i] - 1] = i + 1;

  cout << "!";
  for (int x : ans)
    cout << ' ' << x;
  cout << endl;
}
