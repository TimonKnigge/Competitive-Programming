#include <iostream> 
#include <fstream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

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

inline void fadd(map<ll, ll> &m, ii pr) {
	auto it = m.find(pr.first);
	if (it == m.end())
		m.insert(pr);
	else	it->second += pr.second;
}

int main() {
	ifstream fin("roboherd.in");
	
	int N, K;
	fin >> N >> K;
	vvi mcs(N, vi());
	for (vi& mc : mcs) {
		int Mi;
		fin >> Mi;
		mc.assign(Mi, 0LL);
		for (ll& v : mc) fin >> v;
		sort(mc.begin(), mc.end());
	}
	fin.close();
	
	ll base = 0LL;
	for (vi &mc : mcs) base += mc[0];
	
	vi ids(N, 0LL);
	iota(ids.begin(), ids.end(), 0LL);
	sort(ids.begin(), ids.end(), [&mcs](const int &l, const int &r) {
		for (size_t i = 2; i < min(mcs[l].size(),mcs[r].size()); ++i) {
			if (mcs[l][i] != mcs[r][i])
				return mcs[l][i] < mcs[r][i];
		}
		if (mcs[l].size() > 1 && mcs[r].size() > 1)
			if (mcs[l][1] != mcs[r][1])
				return mcs[l][1] < mcs[r][1];
		return mcs[l].size() < mcs[r].size();
	});
	
	map<ll, ll> answers;
	answers.insert({0LL, 1LL});
	ll total = 1LL;
	for (ll i : ids) {
		map<ll, ll> toadd;
		for (size_t j = 1; j < mcs[i].size(); ++j) {
			// combine v with any earlier diffs
			ll v = mcs[i][j] - mcs[i][0];
			auto it = answers.begin();
			while (it != answers.end()) {
				ll nv = it->first + v;
				ll rem = it->second;
				// add nv? If there is space, always
				// add.
				if (total < K) {
					ll t = min(K - total, rem);
					rem -= t;
					total += t;
					fadd(toadd, {nv, t});
				}
				bool br = false;
				while (rem > 0) {
					// Otherwise, it needs to be smaller
					// than end or addend
					auto ite = answers.end(); --ite;
					ll endv = ite->first;
					ll addendv = -1LL;
					if (toadd.size() > 0) {
						ite = toadd.end(); --ite;
						addendv = ite->first;
					}
					if (nv >= max(addendv, endv)) {
						br = true;
						break;
					}
					if (addendv > endv) {
						ite = toadd.end(); --ite;
						ll t = min(rem, ite->second);
						rem -= t;
						if (t == ite->second)
							toadd.erase(ite);
						else	ite->second -= t;
						fadd(toadd, {nv, t});
					} else {
						ite = answers.end(); --ite;
						ll t = min(rem, ite->second);
						rem -= t;
						if (t == ite->second)
							answers.erase(ite);
						else	ite->second -= t;
						fadd(toadd, {nv, t});
					}
				}
				if (br) break;
				++it;
			}
		}
		for (ii pr : toadd) fadd(answers, pr);
	}
	
	ll ans = 0LL;
	for (ii pr : answers) {
		ans += (base + pr.first) * pr.second;
	}
	
	ofstream fout("roboherd.out");
	fout << ans << endl;
	fout.close();
	
	return 0;
}
