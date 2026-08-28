#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<ll> ans(k);
  vector<int> h(n);
  string prev(n, '?');

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;

    for (int j = 0; j < n; j++) {
      if (i && s[j] == prev[j])
        h[j]++;
      else
        h[j] = 1;
    }

    vector<pair<int, int>> st;
    ll sum = 0;

    for (int j = 0; j < n; j++) {
      if (j && s[j] != s[j - 1]) {
        st.clear();
        sum = 0;
      }

      int cnt = 1;

      while (!st.empty() && st.back().first >= h[j]) {
        auto [x, c] = st.back();
        st.pop_back();

        sum -= 1LL * x * c;
        cnt += c;
      }

      st.push_back({h[j], cnt});
      sum += 1LL * h[j] * cnt;

      ans[s[j] - 'A'] += sum;
    }

    prev = s;
  }

  for (ll x : ans)
    cout << x << '\n';
}
