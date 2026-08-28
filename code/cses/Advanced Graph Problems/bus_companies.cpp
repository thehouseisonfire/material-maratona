#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<ll> cost(m);
  for (auto &x : cost)
    cin >> x;

  vector<vector<int>> companies(m);
  vector<vector<int>> at(n);

  for (int j = 0; j < m; j++) {
    int k;
    cin >> k;

    companies[j].resize(k);
    for (int &v : companies[j]) {
      cin >> v;
      --v;
      at[v].push_back(j);
    }
  }

  const ll INF = 4e18;
  vector<ll> distCity(n, INF), distCompany(m, INF);

  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;

  distCity[0] = 0;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [d, id] = pq.top();
    pq.pop();

    if (id < n) {
      int v = id;
      if (d != distCity[v])
        continue;

      for (int j : at[v]) {
        ll nd = d + cost[j];
        if (nd < distCompany[j]) {
          distCompany[j] = nd;
          pq.push({nd, n + j});
        }
      }
    } else {
      int j = id - n;
      if (d != distCompany[j])
        continue;

      for (int v : companies[j]) {
        if (d < distCity[v]) {
          distCity[v] = d;
          pq.push({d, v});
        }
      }
    }
  }

  for (int i = 0; i < n; i++)
    cout << distCity[i] << " \n"[i == n - 1];
}
