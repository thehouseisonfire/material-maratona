// knapsack-valor-recupecao.cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Result {
  ll best;
  vector<int> ans;
};

///////////////////////////////////////
// -- KNAPSACK 0/1 + RECUPERAÇÃO  -- //
///////////////////////////////////////

Result knapsack01(int n, int W, const vector<int> &w, const vector<ll> &val) {
  // dp[p] = maior valor usando peso <= p

  vector<ll> dp(W + 1);
  vector<vector<char>> take(n + 1, vector<char>(W + 1));

  for (int i = 1; i <= n; i++)
    for (int p = W; p >= w[i]; p--)
      if (dp[p - w[i]] + val[i] > dp[p]) {
        dp[p] = dp[p - w[i]] + val[i];
        take[i][p] = 1;
      }

  ll best = dp[W]; // resposta

  // Recupera itens
  vector<int> ans;
  int p = W;

  for (int i = n; i >= 1; i--)
    if (take[i][p]) {
      ans.push_back(i);
      p -= w[i];
    }

  reverse(ans.begin(), ans.end());

  return {best, ans};
}

/////////////////////////////////////////////////////////////////
// -- KNAPSACK COMPLETO (PODE REPETIR ITEM) + RECUPERAÇÃO  -- //
/////////////////////////////////////////////////////////////////

Result knapsackComplete(int n, int W, const vector<int> &w,
                        const vector<ll> &val) {
  // dp[p] = maior valor usando peso <= p

  vector<ll> dp(W + 1);
  vector<vector<char>> take(n + 1, vector<char>(W + 1));

  for (int i = 1; i <= n; i++)
    for (int p = w[i]; p <= W; p++)
      if (dp[p - w[i]] + val[i] > dp[p]) {
        dp[p] = dp[p - w[i]] + val[i];
        take[i][p] = 1;
      }

  ll best = dp[W]; // resposta

  // Recupera itens
  vector<int> ans;
  int i = n, p = W;

  while (i >= 1) {
    if (take[i][p]) {
      ans.push_back(i);
      p -= w[i]; // continua no mesmo i
    } else {
      i--; // item i não foi usado aqui
    }
  }

  reverse(ans.begin(), ans.end());

  return {best, ans};
}

//////////////////////////////////////////////////////////////////////
// -- KNAPSACK COMPLETO (PODE REPETIR ITEM) VALOR + RECUPERAÇÃO  -- //
//////////////////////////////////////////////////////////////////////

Result knapsackCompleteValue(int n, int W, const vector<int> &w,
                             const vector<ll> &val) {
  // dp[v] = menor peso para obter valor exatamente v

  // Limite superior seguro para a resposta
  int soma_valores = 0;

  for (int i = 1; i <= n; i++)
    soma_valores = max(soma_valores, (int)((__int128)W * val[i] / w[i]));

  const ll INF = LLONG_MAX / 4;

  vector<ll> dp(soma_valores + 1, INF);
  vector<int> par(soma_valores + 1, -1);

  dp[0] = 0;

  for (int i = 1; i <= n; i++)
    for (int v = val[i]; v <= soma_valores; v++)
      if (dp[v - val[i]] != INF && dp[v - val[i]] + w[i] < dp[v]) {
        dp[v] = dp[v - val[i]] + w[i];
        par[v] = i;
      }

  int best = soma_valores;
  while (dp[best] > W)
    best--;

  // Recupera itens
  vector<int> ans;
  int v = best;

  while (v > 0) {
    int i = par[v];
    ans.push_back(i);
    v -= val[i];
  }

  reverse(ans.begin(), ans.end());

  return {best, ans};
}

/////////////////////////////////////////////
// -- KNAPSACK 0/1 VALOR + RECUPERAÇÃO  -- //
/////////////////////////////////////////////

Result knapsack01Value(int n, int W, const vector<int> &w,
                       const vector<ll> &val) {
  // dp[v] = menor peso para obter valor exatamente v

  int soma_valores = accumulate(val.begin() + 1, val.end(), 0LL);

  const ll INF = LLONG_MAX / 4;

  vector<ll> dp(soma_valores + 1, INF);
  vector<vector<char>> take(n + 1, vector<char>(soma_valores + 1));

  dp[0] = 0;

  for (int i = 1; i <= n; i++)
    for (int v = soma_valores; v >= val[i]; v--)
      if (dp[v - val[i]] != INF && dp[v - val[i]] + w[i] < dp[v]) {
        dp[v] = dp[v - val[i]] + w[i];
        take[i][v] = 1;
      }

  int best = soma_valores;
  while (dp[best] > W)
    best--;

  // Recupera itens
  vector<int> ans;
  int v = best;

  for (int i = n; i >= 1; i--)
    if (take[i][v]) {
      ans.push_back(i);
      v -= val[i];
    }

  reverse(ans.begin(), ans.end());

  return {best, ans};
}

////////////////////////
// -- DRIVER BÁSICO -- //
////////////////////////

void printResult(const string &name, const Result &r) {
  cout << name << '\n';
  cout << "best = " << r.best << '\n';

  cout << "items:";
  for (int i : r.ans)
    cout << ' ' << i;

  cout << "\n\n";
}

int main() {
  int n = 3;
  int W = 7;

  // 1-indexado: posição 0 não é usada
  vector<int> w = {0, 3, 4, 2};
  vector<ll> val = {0, 4, 5, 3};

  printResult("0/1 por peso", knapsack01(n, W, w, val));

  printResult("Completo por peso", knapsackComplete(n, W, w, val));

  printResult("Completo por valor", knapsackCompleteValue(n, W, w, val));

  printResult("0/1 por valor", knapsack01Value(n, W, w, val));
}
