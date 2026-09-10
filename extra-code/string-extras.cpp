// COUNT UNIQUE PERMUTATIONS OF STRINGS

ll factorial(const ll n) {
  if (n < 3)
    return n;
  vector<ll> results(n + 1);
  results[2] = 2;
  for (ll i = 3; i <= n; i++)
    results[i] = i * results[i - 1];
  return results[n];
}

ll formula(const string &str) {
  ll alphabet[26] = {0};
  for (const char c : str) {
    alphabet[c - 'A']++;
  }
  ll result = factorial(str.length()) % MOD;
  cout << result << endl;
  ll divide = 1;
  for (ll i = 0; i < 26; i++) {
    if (alphabet[i] > 1)
      divide *= factorial(alphabet[i]) % MOD;
  }
  return result / divide;
}

void count_unique() {
  string str;
  str.reserve(69);
  cin >> str;
  ll ammount = formula(str);
  cout << ammount << endl;
  return 0;
}
