#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF = (1LL << 62);

struct Seg {
  ll x1, y1, x2, y2;
};

vector<Seg> seg;
vector<char> dir;
vector<ll> len;

// Checks intersections between parallel segments.
bool parallel_intersection(int m, bool vertical) {
  vector<array<ll, 3>> v;

  for (int i = 0; i < m; i++) {
    auto s = seg[i];

    if (vertical && s.x1 == s.x2)
      v.push_back({s.x1, min(s.y1, s.y2), max(s.y1, s.y2)});

    if (!vertical && s.y1 == s.y2)
      v.push_back({s.y1, min(s.x1, s.x2), max(s.x1, s.x2)});
  }

  sort(v.begin(), v.end());

  for (int i = 1; i < (int)v.size(); i++)
    if (v[i][0] == v[i - 1][0] && v[i][1] <= v[i - 1][2])
      return true;

  return false;
}

// Checks horizontal/vertical intersections with a sweep line.
bool perpendicular_intersection(int m) {
  // {x, type, y1, y2}
  // type: 0 = add horizontal
  //       1 = query vertical
  //       2 = remove horizontal
  vector<array<ll, 4>> ev;

  for (int i = 0; i < m; i++) {
    auto s = seg[i];

    if (s.y1 == s.y2) {
      ll l = min(s.x1, s.x2);
      ll r = max(s.x1, s.x2);

      ev.push_back({l, 0, s.y1, 0});
      ev.push_back({r, 2, s.y1, 0});
    } else {
      ev.push_back({s.x1, 1, min(s.y1, s.y2), max(s.y1, s.y2)});
    }
  }

  sort(ev.begin(), ev.end());

  multiset<ll> active;

  for (auto [x, type, a, b] : ev) {
    if (type == 0) {
      active.insert(a);
    } else if (type == 2) {
      active.erase(active.find(a));
    } else {
      auto it = active.lower_bound(a);

      if (it != active.end() && *it <= b)
        return true;
    }
  }

  return false;
}

bool has_intersection(int m) {
  return parallel_intersection(m, true) || parallel_intersection(m, false) ||
         perpendicular_intersection(m);
}

// Distance from a.x1,a.y1 to the first intersection with b.
ll intersection_dist(const Seg &a, const Seg &b) {
  bool ah = (a.y1 == a.y2);
  bool bh = (b.y1 == b.y2);

  // horizontal-horizontal
  if (ah && bh) {
    if (a.y1 != b.y1)
      return INF;

    ll l = max(min(a.x1, a.x2), min(b.x1, b.x2));

    ll r = min(max(a.x1, a.x2), max(b.x1, b.x2));

    if (l > r)
      return INF;

    if (a.x2 >= a.x1)
      return l - a.x1;

    return a.x1 - r;
  }

  // vertical-vertical
  if (!ah && !bh) {
    if (a.x1 != b.x1)
      return INF;

    ll l = max(min(a.y1, a.y2), min(b.y1, b.y2));

    ll r = min(max(a.y1, a.y2), max(b.y1, b.y2));

    if (l > r)
      return INF;

    if (a.y2 >= a.y1)
      return l - a.y1;

    return a.y1 - r;
  }

  // a horizontal, b vertical
  if (ah) {
    ll x = b.x1;
    ll y = a.y1;

    if (x < min(a.x1, a.x2) || x > max(a.x1, a.x2) || y < min(b.y1, b.y2) ||
        y > max(b.y1, b.y2))
      return INF;

    return abs(x - a.x1);
  }

  // a vertical, b horizontal
  ll x = a.x1;
  ll y = b.y1;

  if (x < min(b.x1, b.x2) || x > max(b.x1, b.x2) || y < min(a.y1, a.y2) ||
      y > max(a.y1, a.y2))
    return INF;

  return abs(y - a.y1);
}

bool opposite(char a, char b) {
  return (a == 'U' && b == 'D') || (a == 'D' && b == 'U') ||
         (a == 'L' && b == 'R') || (a == 'R' && b == 'L');
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  seg.resize(n);
  dir.resize(n);
  len.resize(n);

  ll x = 0, y = 0;

  for (int i = 0; i < n; i++) {
    char d;
    ll z;
    cin >> d >> z;

    ll dx = (d == 'R') - (d == 'L');
    ll dy = (d == 'U') - (d == 'D');

    // For i > 0, exclude the point where the
    // previous command ended.
    seg[i] = {x + (i > 0) * dx, y + (i > 0) * dy, x + z * dx, y + z * dy};

    x += z * dx;
    y += z * dy;

    dir[i] = d;
    len[i] = z;
  }

  // First command that creates an intersection.
  int lo = 0, hi = n;

  while (lo < hi) {
    int mid = (lo + hi) / 2;

    if (has_intersection(mid + 1))
      hi = mid;
    else
      lo = mid + 1;
  }

  int bad = lo;

  ll ans = 0;

  for (int i = 0; i < bad; i++)
    ans += len[i];

  if (bad == n) {
    cout << ans << '\n';
    return 0;
  }

  ll d = INF;

  for (int i = 0; i < bad; i++)
    d = min(d, intersection_dist(seg[bad], seg[i]));

  // seg[bad] begins one unit after the real command start.
  ans += 1 + d;

  // Reversing direction overlaps the previous segment immediately.
  if (opposite(dir[bad], dir[bad - 1]))
    ans--;

  cout << ans << '\n';
}
