#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> pos(n + 1);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    pos[x] = i;
  }

  vector<int> val, p;
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    if (x <= n) {
      val.push_back(x);
      p.push_back(pos[x]);
    }
  }

  int k = p.size();
  vector<int> tail, tail_idx, par(k, -1);

  for (int i = 0; i < k; i++) {
    int j = lower_bound(tail.begin(), tail.end(), p[i]) - tail.begin();

    if (j > 0)
      par[i] = tail_idx[j - 1];

    if (j == (int)tail.size()) {
      tail.push_back(p[i]);
      tail_idx.push_back(i);
    } else {
      tail[j] = p[i];
      tail_idx[j] = i;
    }
  }

  vector<int> ans;
  if (!tail.empty()) {
    int cur = tail_idx.back();
    while (cur != -1) {
      ans.push_back(val[cur]);
      cur = par[cur];
    }
    reverse(ans.begin(), ans.end());
  }

  cout << ans.size() << '\n';
  for (int x : ans)
    cout << x << ' ';
  cout << '\n';
}
