// numero de substrings num intervalo de tamanho n = (n * (n+1))/2
// problema:
// https://codeforces.com/contest/84/problem/B (nome: Magical Array)
// solução:

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll n;
  cin >> n;
  vector<ll> a(n);
  for (auto &i : a)
    cin >> i;
  // formula = (x * (x+1)) / 2
  ll asw = 0;
  ll aux = 1e12;
  ll seq = 0;
  for (int i = 0; i < n;) {
    if (a[i] != aux) {
      aux = a[i];
      seq = 0;
    }
    while (i < n && a[i] == aux) {
      seq++;
      i++;
    }
    asw += (seq * (seq + 1)) / 2;
  }
  cout << asw << endl;
}
