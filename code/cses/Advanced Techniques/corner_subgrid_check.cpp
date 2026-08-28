#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<vector<vector<int>>> pos(n, vector<vector<int>>(k));

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;

    for (int j = 0; j < n; j++)
      pos[i][s[j] - 'A'].push_back(j);
  }

  // seen[a * n + b] = letter for which pair (a, b) was seen.
  vector<unsigned char> seen(n * n);

  ll maxPairs = 1LL * n * (n - 1) / 2;

  for (int c = 0; c < k; c++) {
    ll pairs = 0;

    for (int i = 0; i < n; i++) {
      ll sz = pos[i][c].size();
      pairs += sz * (sz - 1) / 2;
    }

    // More occurrences of column-pairs than distinct column-pairs:
    // some pair must appear in two rows.
    if (pairs > maxPairs) {
      cout << "YES\n";
      continue;
    }

    bool ok = false;
    unsigned char mark = c + 1;

    for (int i = 0; i < n && !ok; i++) {
      auto &v = pos[i][c];

      for (int a = 0; a < (int)v.size() && !ok; a++)
        for (int b = a + 1; b < (int)v.size(); b++) {
          int id = v[a] * n + v[b];

          if (seen[id] == mark) {
            ok = true;
            break;
          }

          seen[id] = mark;
        }
    }

    cout << (ok ? "YES\n" : "NO\n");
  }
}
