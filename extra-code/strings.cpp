// https://codeforces.com/contest/271/problem/D

#include <cmath>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const ld PI = acos(-1.0);

template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
  return is >> p.first >> p.second;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  return os << p.first << " " << p.second;
}

template <typename T> istream &operator>>(istream &is, vector<T> &v) {
  for (auto &x : v)
    is >> x;
  return is;
}
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v) {
  for (int i = 0; i < v.size(); ++i)
    os << (i > 0 ? " " : "") << v[i];
  return os;
}

#define dbg(x) cerr << #x << " = " << (x) << endl
#define all(x) (x).begin(), (x).end()

// single hash
// const int p1 = 31;
// const ll m1 = 1'000'000'009;

// double hash (pra não ser fudido por collision)
const int p1 = 31;
const int p2 = 37;
const ll m1 = 1'000'000'007;
const ll m2 = 1'000'000'009;

// paranoia contra collision (pode dar TLE, usar unordened_set)
// #include <chrono>
// #include <random>
//
// mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//
// const ll m1 = 1'000'000'007;
// const ll m2 = 1'000'000'009;
// const int p1 = uniform_int_distribution<int>(256, m1 - 1)(rng);
// const int p2 = uniform_int_distribution<int>(256, m2 - 1)(rng);

ll val(char c) { return c - 'a' + 1; }

// substring s[l..r], `r` inclusive
ll get_hash(vector<ll> &prefix, vector<ll> &power, ll l, ll r, ll m) {
  return (prefix[r + 1] - prefix[l] * power[r - l + 1] % m + m) % m;
}

// substring s[l..r), `r` exclusive
ll get_hash_exclusive(vector<ll> &prefix, vector<ll> &power, ll l, ll r, ll m) {
  return (prefix[r] - prefix[l] * power[r - l] % m + m) % m;
}

// https://codeforces.com/contest/271/problem/D
// Some letters of the lower english alphabet are 'bad'. Print all substrings
// from a given string that have at most `k` bad letters (instances, repeated
// ones count).
void solve_good_string() {
  string s, good_in;
  ll k;
  cin >> s >> good_in >> k;
  ll n = s.size();

  // prefix[0] = hash("") = 0
  vector<ll> prefix1(n + 1);
  vector<ll> power1(n + 1, 1);

  // comment these two for single hash
  vector<ll> prefix2(n + 1);
  vector<ll> power2(n + 1, 1);

  bool good[26];
  for (ll i = 0; i < 26; i++)
    good[i] = good_in[i] - '0';

  for (ll i = 0; i < n; i++) {
    prefix1[i + 1] = (prefix1[i] * p1 + val(s[i])) % m1;
    power1[i + 1] = power1[i] * p1 % m1;

    // comment these for single hash
    prefix2[i + 1] = (prefix2[i] * p2 + val(s[i])) % m2;
    power2[i + 1] = power2[i] * p2 % m2;
  }

  // single hash
  // set<ll> seen;

  // double hash
  set<pair<ll, ll>> seen;

  for (ll l = 0; l < n; l++) {
    ll bad = 0;

    for (ll r = l; r < n; r++) {
      bad += !good[s[r] - 'a'];

      if (bad > k)
        break;

      ll h1 = get_hash(prefix1, power1, l, r, m1);

      // single hash
      // seen.insert(h1);

      // double hash
      ll h2 = get_hash(prefix2, power2, l, r, m2);
      seen.insert({h1, h2});
    }
  }

  cout << seen.size() << endl;
}

// https://codeforces.com/contest/271/problem/D
// Solução melhor, sem prefixo
void solve_good_string_sliding_window() {
  string s, good_in;
  ll k;
  cin >> s >> good_in >> k;
  bool good[26];
  for (ll i = 0; i < 26; i++)
    good[i] = good_in[i] - '0';

  set<ll> seen;
  for (ll l = 0; l < s.size(); l++) {
    ll h = 0;
    ll bad = 0;
    for (ll r = l; r < s.size(); r++) {
      bad += !good[s[r] - 'a'];
      if (bad > k)
        break;
      h = (h * p1 + val(s[r])) % m1;
      seen.insert(h);
    }
  }
  cout << seen.size() << endl;
}

// https://www.spoj.com/problems/NHAY/
// finds all occurrences of a pattern of length `k` in a given input
// string (and print the starting index or each occurrence)
void solve_needle_in_haystack() {
  ll n, k;
  string pat, s;
  while (cin >> k >> pat >> s) {

    n = s.size();
    if (n < k) {
      cout << endl;
      continue;
    }
    ll pat_hash = 0, str_hash = 0;
    for (char &c : pat)
      pat_hash = (pat_hash * p1 + val(c)) % m1;

    for (ll i = 0; i < k && i < n; i++)
      str_hash = (str_hash * p1 + val(s[i])) % m1;

    // power(p,k) pré-computado, como é sliding window, é sempre o mesmo que
    // queremos
    ll power_k = 1;
    for (ll i = 0; i < k; i++)
      power_k = power_k * p1 % m1;

    if (pat_hash == str_hash)
      cout << 0 << endl;

    if (n == k) {
      cout << endl;
      continue;
    }

    for (ll l = 1, r = k; r < n; l++, r++) {
      str_hash = (str_hash * p1 + val(s[r])) % m1;
      // somamos `m` pois senão o hash pode ficar negativo (por causa
      // do módulo baixar o acumulado)
      // não, não tem jeito de escapar
      str_hash = (str_hash - ((val(s[l - 1]) * power_k) % m1) + m1) % m1;
      if (str_hash == pat_hash) {
        cout << l << endl;
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t = 1;
  // cin >> t;
  while (t--) {
    solve_good_string();
  }
  return 0;
}
