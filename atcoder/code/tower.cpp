// atcoder/tower.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Block {
  int w, s;
  ll v;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<Block> a(n);
  int maxw = 0;

  for (auto &[w, s, v] : a) {
    cin >> w >> s >> v;
    maxw = max(maxw, w + s);
  }

  sort(a.begin(), a.end(),
       [](const Block &a, const Block &b) { return a.w + a.s < b.w + b.s; });

  vector<ll> dp(maxw + 1, -1);
  dp[0] = 0;

  for (auto [w, s, v] : a) {
    for (int cur = s; cur >= 0; cur--) {
      if (dp[cur] == -1)
        continue;

      dp[cur + w] = max(dp[cur + w], dp[cur] + v);
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << '\n';
}
