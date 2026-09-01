// cses/Additional Problems I/water_containers_moves.cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a, b, x;
  cin >> a >> b >> x;

  if (x > a || x % gcd(a, b) != 0) {
    cout << -1 << '\n';
    return 0;
  }

  int W = b + 1;
  int N = (a + 1) * (b + 1);

  auto id = [&](int A, int B) { return A * W + B; };

  const ll INF = (1LL << 60);

  vector<ll> dist(N, INF);
  vector<int> par(N, -1);
  vector<char> how(N, -1);

  const string name[] = {"FILL A",  "FILL B",   "EMPTY A",
                         "EMPTY B", "MOVE A B", "MOVE B A"};

  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;

  int start = id(0, 0);
  dist[start] = 0;
  pq.push({0, start});

  int target = -1;

  while (!pq.empty()) {
    auto cur = pq.top();
    pq.pop();

    ll d = cur.first;
    int v = cur.second;

    if (d != dist[v])
      continue;

    int A = v / W;
    int B = v % W;

    if (A == x) {
      target = v;
      break;
    }

    auto relax = [&](int nA, int nB, int cost, int op) {
      if (cost == 0)
        return;

      int u = id(nA, nB);
      if (d + cost < dist[u]) {
        dist[u] = d + cost;
        par[u] = v;
        how[u] = op;
        pq.push({dist[u], u});
      }
    };

    relax(a, B, a - A, 0);
    relax(A, b, b - B, 1);
    relax(0, B, A, 2);
    relax(A, 0, B, 3);

    int t = min(A, b - B);
    relax(A - t, B + t, t, 4);

    t = min(B, a - A);
    relax(A + t, B - t, t, 5);
  }

  if (target == -1) {
    cout << -1 << '\n';
    return 0;
  }

  vector<int> ops;

  for (int v = target; v != start; v = par[v])
    ops.push_back(how[v]);

  reverse(ops.begin(), ops.end());

  cout << ops.size() << ' ' << dist[target] << '\n';

  for (int op : ops)
    cout << name[op] << '\n';
}
