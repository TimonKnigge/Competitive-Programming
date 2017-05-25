#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n;
	cin >> n;
	
	vector<pair<ii, int>> l(n, {{0, 0}, 0}), r(n, {{0, 0}, 0});
	for (int i = 0; i < n; ++i)
		cin >> l[i].first.first >> l[i].first.second,
		l[i].second = i;
	for (int i = 0; i < n; ++i)
		cin >> r[i].first.first >> r[i].first.second,
		r[i].second = i;
	sort(l.begin(), l.end()); sort(r.begin(), r.end());
	
	vi match(n, -1);
	bool error = false;
	map<ll, int> active;
	size_t j = 0;
	for (size_t i = 0; i < l.size() && !error; ++i) {
		while (!error && j < r.size()
				&& r[j].first.first < l[i].first.first) {
			pair<ii, int> v = r[j++];
			auto it = active.upper_bound(v.first.second);
			while (it != active.begin()
				&& (it == active.end() ||
					it->first > v.first.second))
				--it;
			if (it == active.end() || it->first > v.first.second) {
				error = true;
				break;
			} else {
				match[it->second] = v.second;
				active.erase(it);
			}
		}
		if (error) break;
		
		pair<ii, int> v = l[i];
		active.insert({v.first.second, v.second});
	}
	while (!error && j < r.size()) {
		pair<ii, int> v = r[j++];
		auto it = active.upper_bound(v.first.second);
		while (it != active.begin()
			&& (it == active.end() ||
				it->first > v.first.second))
			--it;
		if (it == active.end() || it->first > v.first.second) {
			error = true;
		} else {
			match[it->second] = v.second;
			active.erase(it);
		}
	}
	
	if (error) {
		cout << "syntax error" << endl;
		return 0;
	}
	
	sort(l.begin(), l.end(), [](const pair<ii, int>& lv,
				const pair<ii, int>& rv) {
		return lv.second < rv.second; });
	sort(r.begin(), r.end(), [](const pair<ii, int>& lv,
				const pair<ii, int>& rv) {
		return lv.second < rv.second; });
	
	vector<pair<ii, ii>> squares;
	for (int i = 0; i < n; ++i) {
		ll x1 = l[i].first.first, x2 = r[match[i]].first.first;
		ll y1 = l[i].first.second, y2 = r[match[i]].first.second;
		if (x1 + 1LL >= x2 || y1 + 1LL >= y2)
			squares.push_back({{x1, x2}, {y1, y2}});
		else {
			squares.push_back({{x1, x1}, {y1, y2}});
			squares.push_back({{x2, x2}, {y1, y2}});
			squares.push_back({{x1+1, x2-1}, {y1, y1}});
			squares.push_back({{x1+1, x2-1}, {y2, y2}});
		}
	}
	sort(squares.begin(), squares.end());
	
	map<ll, ll> inuse;
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>,
		greater<pair<ll, ll>>> pq;
	for (pair<ii, ii> sq : squares) {
		ll x1 = sq.first.first, x2 = sq.first.second;
		ll y1 = sq.second.first, y2 = sq.second.second;
		
		while (!pq.empty() && pq.top().first < x1)
			inuse.erase(inuse.find(pq.top().second)),
			pq.pop();

		auto it = inuse.lower_bound(y1);
		if (it != inuse.end() && it->first <= y2) {
			error = true; break;
		}
		if (it != inuse.begin()) {
			--it;
			if (it->second >= y1) {
				error = true; break;
			}
		}
		
		inuse.insert({y1, y2});
		pq.push({x2, y1});
	}
	
	if (error)
		cout << "syntax error" << endl;
	else	for (int i = 0; i < n; ++i)
		cout << (match[i]+1) << '\n';
	
	return 0;
}
