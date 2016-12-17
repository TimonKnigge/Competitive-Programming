// O(N^3 lg N), but too slow
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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
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

ll det(ll x1, ll y1, ll x2, ll y2) {
	return x1*y2-x2*y1;
}
ll det(ii c, ii p1, ii p2) {
	return det(p1.first-c.first, p1.second-c.second,
		p2.first-c.first, p2.second-c.second);
}
ll con(ii p, ii t1, ii t2, ii t3) {
	ll v1 = det(t1, t2, p) > 0 ? 1 : -1;
	ll v2 = det(t2, t3, p) > 0 ? 1 : -1;
	ll v3 = det(t3, t1, p) > 0 ? 1 : -1;
	return v1 * v2 > 0 && v1 * v3 > 0 && v2 * v3 > 0;
}

template<class TIn, class TOut>
using order_tree = tree<
	TIn, TOut, less<TIn>, // key, value types. TOut can be null_type
	rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(int r) (0-based)
// order_of_key(TIn v)
// use key pair<Tin,int> {value, counter} for multiset/multimap

void count(ii p1, ii p2, vii &pts, vi &ans) {
	// For each point p3 \in pts we have
	// det(p1, p2, p3) > 0
	
//	cerr << "Considering " << p1.first << ',' << p1.second << " and ";
//	cerr << p2.first << ',' << p2.second << endl;
	
	// Sort the points clockwise by angle compared to p1
	sort(pts.begin(), pts.end(), [p1](const ii &l, const ii &r) {
		return det(p1, l, r) < 0LL;
	});
	
//	cerr << "Sorted points: ";
//	for (ii v : pts) cerr << v.first << ',' << v.second << ' ';
//	cerr << endl;
	
	// Duplicate the points and sort by angle wrt p2
	vi pts2(pts.size(), 0LL);
	iota(pts2.begin(), pts2.end(), 0LL);
	sort(pts2.begin(), pts2.end(), [p2, &pts](const ll &l, const ll &r) {
		return det(p2, pts[l], pts[r]) < 0LL;
	});
	
	// Invert pts2.
	vi pts2i(pts2.size(), 0LL);
	order_tree<ll, ll> ot;
	for (size_t i = 0; i < pts2.size(); ++i) {
		pts2i[pts2[i]] = i;
		ot.insert({i, i});
	}
//	cerr << "Inverse indices: ";
//	for (size_t i = 0; i < pts2i.size(); ++i)
//		cerr << i << ':' << pts2i[i] << ' ';
//	cerr << endl;
	
	// Loop through the points.
	for (size_t i = 0; i < pts.size(); ++i) {
		// Consider the triangle with points p1, p2, pts[i].
		// We know that pts is sorted wrt angle to p1, so points 0..i-1
		// are outside this triangle (and have been removed from the tree).
		// Also, points in pts2 are sorted wrt p2 (clockwise), so the
		// points in the triangle are to the left of pts[i] in pts2.
		ot.erase(ot.find(pts2i[i]));
//		cerr << "Found something containing " << ot.order_of_key(pts2i[i]) << " with point " << pts[i].first << ' ' << pts[i].second << endl;
		ans[ot.order_of_key(pts2i[i])]++;
	}
}

int main() {
	
	ifstream fin("triangles.in");
	int N;
	fin >> N;
	vii pts(N, {0LL, 0LL});
	for (ii &pt : pts) fin >> pt.first >> pt.second;
	fin.close();
	
	vi ans(N - 2, 0LL);
	for (size_t i = 0; i < pts.size(); ++i)
		for (size_t j = i + 1; j < pts.size(); ++j) {
			// Consider points [j+1 .. N)
			// Separate into two groups, above and below the line i,j
			vii a, b;
			for (size_t k = 0; k < pts.size(); ++k)
				if (k == i || k == j) continue; else
				if (det(pts[i], pts[j], pts[k]) > 0)
					a.push_back(pts[k]);
				else	b.push_back(pts[k]);
			// Treat each group separately
			count(pts[i], pts[j], a, ans);
			count(pts[j], pts[i], b, ans);
		}
		
	
	ofstream fout("triangles.out");
	for (ll v : ans) fout << v/3LL << '\n';
	fout.close();
	
	return 0;
}
