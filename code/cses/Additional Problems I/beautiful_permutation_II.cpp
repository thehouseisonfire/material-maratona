#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  if (n == 2 || n == 3) {
    cout << "NO SOLUTION\n";
    return 0;
  }

  set<int> rem;
  for (int i = 1; i <= n; i++)
    rem.insert(i);

  vector<int> ans;

  // Greedily construct the prefix.
  // Leave 5 elements so completion is always possible.
  while ((int)rem.size() > 5) {
    auto it = rem.begin();

    while (!ans.empty() && abs(*it - ans.back()) == 1)
      ++it;

    ans.push_back(*it);
    rem.erase(it);
  }

  // Brute force the last at most 5 elements.
  vector<int> tail(rem.begin(), rem.end());

  do {
    bool ok = ans.empty() || abs(ans.back() - tail[0]) != 1;

    for (int i = 1; i < (int)tail.size(); i++)
      if (abs(tail[i] - tail[i - 1]) == 1)
        ok = false;

    if (ok) {
      ans.insert(ans.end(), tail.begin(), tail.end());
      break;
    }
  } while (next_permutation(tail.begin(), tail.end()));

  for (int i = 0; i < n; i++)
    cout << ans[i] << " \n"[i + 1 == n];
}
