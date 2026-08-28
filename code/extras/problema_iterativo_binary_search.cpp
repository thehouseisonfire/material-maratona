// regra numero 1:
//
// COLOCA BOUND EXATO. SE O T VAI DE 0 ATE 100, L = 0 E R = 100
//
//
// regra numero 2:
//
// VE SE A STRING TA CERTA ANTES DE MANDAR, PQ VCS VAO DIMINUIR ELA PRA TESTAR E
// SE FERRAR
//
//
// regra numero 3:
//
// 'WRONG ANSWER' EH A MESMA COISA QUE 'TIME LIMIT EXCEED' NESSES PROBLEMAS

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ll l = 1, r = 1000000000;
  // ll l = 1, r = 100;
  string s;

  while (l < r) {
    ll mid = (l + r) / 2;
    cout << "? " << mid << endl;
    cin >> s;

    if (s == "QUENTE")
      l = mid + 1;
    else
      r = mid;
  }
  cout << "! " << r << endl;
}
