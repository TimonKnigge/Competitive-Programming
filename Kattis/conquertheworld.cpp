#include <bits/stdc++.h>

using namespace std;
using ll  = long long;
using ull = unsigned long long;
using ld  = long double;
using ii  = pair<ll,ll>;
using vi  = vector<ll>;
using vii = vector<ii>;
using vb  = vector<bool>;
using vvi = vector<vi>;
using vvii = vector<vii>;

constexpr int  INF = 1e9+1;
constexpr ll LLINF = 1e18+1;

using ValueSet = pair<map<ll, ll>, ll>;
void absorb(ValueSet &large, const ValueSet &small) {
  for (pair<ll, ll> pr : small.first) {
    large.first[pr.first + small.second - large.second] += pr.second;
  }
}

ll dfs(int u, int p, const vvii &E, const vi &x, const vi &y,
       vector<ValueSet> &credit, vector<ValueSet> &debit,
       vector<ValueSet> &residual) {
  // Put the x/y values into our own ValueSets.
  credit[u].first.clear();
  debit[u].first.clear();
  residual[u].first.clear();
  credit[u].second = debit[u].second = residual[u].second = 0LL;
  if (x[u] > 0LL)
    credit[u].first[0] = x[u];
  if (y[u] > 0LL)
    debit[u].first[0] = y[u];

  // Visit all children first, and retain the largest child set for reusage.
  ll cost = 0LL;
  for (auto &vw : E[u]) {
    int v = vw.first;
    ll w = vw.second;
    if (v != p) {
      cost += dfs(v, u, E, x, y, credit, debit, residual);
      credit[v].second += w;
      debit[v].second += w;
      residual[v].second += w;
      if (credit[v].first.size() > credit[u].first.size())
        credit[u].swap(credit[v]);
      if (debit[v].first.size() > debit[u].first.size())
        debit[u].swap(debit[v]);
      if (residual[v].first.size() > residual[u].first.size())
        residual[u].swap(residual[v]);
    }
  }

  // Merge all children into u.
  for (auto &vw : E[u]) {
    int v = vw.first;
    if (v != p) {
      absorb(credit[u], credit[v]);
      absorb(debit[u], debit[v]);
      absorb(residual[u], residual[v]);
    }
  }

  // Cancel out paths that meet each other. First take any credit/debit pairs
  // since those we are always required to take.
  while (!credit[u].first.empty() && !debit[u].first.empty()) {
    // Find how many armies we can match and how much it will cost.
    auto cit = credit[u].first.begin();
    auto dit = debit[u].first.begin();
    ll budget = min(cit->second, dit->second),
       creditcost = cit->first + credit[u].second,
       debitcost = dit->first + debit[u].second;

    // Match as many as possible.
    cost += budget * (debitcost + creditcost);
    cit->second -= budget;
    if (cit->second == 0LL)
      credit[u].first.erase(cit);
    dit->second -= budget;
    if (dit->second == 0LL)
      debit[u].first.erase(dit);

    // Add a residual path for each match, with cost equal to -creditcost.
    residual[u].first[-(creditcost + residual[u].second)] += budget;
  }

  // Now, while possible, match credit and residual paths.
  while (!credit[u].first.empty() && !residual[u].first.empty()) {
    // Again, find how many armies we can match and how much it will cost.
    auto cit = credit[u].first.begin();
    auto rit = residual[u].first.begin();
    ll budget = min(cit->second, rit->second),
       creditcost = cit->first + credit[u].second,
       residualcost = rit->first + residual[u].second;

    // Now, since this match is optional we only do it if it reduces cost.
    if (creditcost + residualcost >= 0LL)
      break;

    // Match as many as possible.
    cost += budget * (residualcost + creditcost);
    cit->second -= budget;
    if (cit->second == 0LL)
      credit[u].first.erase(cit);
    rit->second -= budget;
    if (rit->second == 0LL)
      residual[u].first.erase(rit);

    // Add a residual path for each match, with cost equal to -creditcost.
    residual[u].first[-(creditcost + residual[u].second)] += budget;

    // Also readd the old credit path.
    credit[u].first[-(residualcost + credit[u].second)] += budget;
  }

  return cost;
}

int main() {
  int n;
  cin >> n;
  vvii E(n);
  for (int i = 1, u, v, c; i < n; ++i)
    cin >> u >> v >> c, --u, --v,
    E[u].push_back({v, c}),
    E[v].push_back({u, c});

  vi x(n), y(n);
  for (int i = 0; i < n; ++i)
    cin >> x[i] >> y[i];

  vector<ValueSet> credit(n), debit(n), residual(n);
  cout << dfs(0, -1, E, x, y, credit, debit, residual) << endl;

  return 0;
}
