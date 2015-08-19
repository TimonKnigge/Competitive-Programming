#include <iostream>
#include <iomanip>
#include <vector>	       
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <algorithm>
#include <functional>
#include <string>
#include <string.h>  // Include for memset!
#include <complex>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>
#include <cstdio>

const long long LLINF = 9000000000000000000LL;  // 18
const long double LDINF = 1e300;

using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long double ld;

void readcor(ll &x, ll &y) {
	char c;
	scanf(" %c", &c);
	assert(c == '(');
	scanf("%lld %lld", &x, &y);
	scanf("%c", &c);
	assert(c == ')');
//	printf("Read %lld %lld", x, y);
}

// COMPUTATIONAL GEOMETRY
inline ld polygon_size(vii &p) {
	ld sum = 0.0;
	ll s = p.size();
	for (int i = 0; i < s; ++i)
		sum += p[i].first * p[(i+1)%s].second - p[i].second * p[(i+1)%s].first;
	return abs(sum) / 2.0;
}

inline ll idet(ll x1, ll y1, ll x2, ll y2) {
	return x1 * y2 - x2 * y1;
}
inline ll idet(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
	return idet(x2 - x1, y2 - y1, x3 - x1, y3 - y1);
}

inline ll winding_number(vii &p, ll x, ll y) {
	ll wn = 0, s = p.size();
	for (int i = 0; i < s; ++i) {
		if (p[i].second - y < 0 && p[(i+1)%s].second - y >= 0) {
			// Upward
			if (idet(p[i].first - x, p[i].second - y,
				 p[(i+1)%s].first - x, p[(i+1)%s].second - y,
				 0, 0) > 0) wn++;
		} else
		if (p[i].second - y >= 0 && p[(i+1)%s].second - y < 0) {
			// Downward
			if (idet(p[i].first - x, p[i].second - y,
				 p[(i+1)%s].first - x, p[(i+1)%s].second - y,
				 0, 0) < 0) wn--;
		}
	}
	return wn;
}
inline ld dsq(ld x1, ld y1, ld x2, ld y2) { return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1); }
inline ll dot(ll x1, ll y1, ll x2, ll y2) { return x1 * x2 + y1 * y2; }

ld polydistance(vii &p1, vii &p2);

inline bool canjump(vii &p1, vii &p2, ld d) {
	ll minx1 = LLINF, maxx1 = -LLINF, miny1 = LLINF, 
	   maxy1 = -LLINF, minx2 = LLINF, maxx2 = -LLINF, 
	   miny2 = LLINF, maxy2 = -LLINF;
	for (ii v : p1) {
		minx1 = min(minx1, v.first);
		miny1 = min(miny1, v.second);
		maxx1 = max(maxx1, v.first);
		maxy1 = max(maxy1, v.second);
	}
	for (ii v : p2) {
		minx2 = min(minx2, v.first);
		miny2 = min(miny2, v.second);
		maxx2 = max(maxx2, v.first);
		maxy2 = max(maxy2, v.second);
	}
	ll lld = ll(d) + 2;
	minx1 -= lld; maxx1 += lld; miny1 -= lld; maxy1 += lld;
	minx2 -= lld; maxx2 += lld; miny2 -= lld; maxy2 += lld;
	if (minx1 > maxx2 || minx2 > maxx1 || miny1 > maxy2
		|| miny2 > maxy1) return false;
	else return (polydistance(p1, p2) <= d * d + 1e-6);
}

inline ld _polydistance(vii &p1, vii &p2) {
	ld ans = LDINF;
	for (int i = 0; i < p1.size(); ++i) {
		ll s = p2.size();
		ii p = p1[i];
		for (int j = 0; j < s; ++j) {
			ii l1 = p2[j], l2 = p2[(j+1)%s];
			// Distance of p to [l1, l2]
			ld lambda = dot(p.first - l1.first, p.second - l1.second, l2.first - l1.first, l2.second - l1.second) / ld(dot(l2.first - l1.first, l2.second - l1.second, l2.first - l1.first, l2.second - l1.second));
			lambda = max(ld(0.0), min(ld(1.0), lambda));
			ld cx = l1.first + (l2.first - l1.first) * lambda;
			ld cy = l1.second + (l2.second - l1.second) * lambda;
			ans = min(ans, dsq(cx, cy, ld(p.first), ld(p.second)));
		}
	}
	return ans;
}
ld polydistance(vii &p1, vii &p2) {
	return min(_polydistance(p1, p2), _polydistance(p2, p1));
}
// -COMPUTATIONAL GEOMETRY
// UNION FIND
class UnionFind {
private:
	vi par, rank, size;
	int c;
public:
	UnionFind(int n) : par(n, 0), rank(n, 0), size(n, 1), c(n) {
		for (int i = 0; i < n; ++i) par[i] = i;
	}
	int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
	bool same(int i, int j) { return find(i) == find(j); }
	void union_set(int i, int j) {
		if ((i = find(i)) == (j = find(j))) return;
		c--;
		if (rank[i] > rank[j]) swap(i, j);
		par[i] = j; size[j] += size[i];
		if (rank[i] == rank[j]) rank[j]++;
	}
};
// -UNION FIND

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	scanf("%d", &T);
	for (ll t = 1; t <= T; ++t) {
		ll f; ld d; double _d;
		scanf("%lld %lf", &f, &_d);
		d = ld(_d);
		ll s1x, s1y, s2x, s2y;
		int s1id = -1, s2id = -1;
		readcor(s1x, s1y);
		readcor(s2x, s2y);
		vvii polygons(f, vii());
		vector<ld> polysize(f, 0.0);
		vector<vb> adj(f, vb(f, false));
		for (int i = 0; i < f; ++i) {
			ll s;
			scanf("%lld", &s);
			for (int j = 0; j < s; ++j) {
				ll _x, _y;
				readcor(_x, _y);
				polygons[i].push_back({_x, _y});
			}
			polysize[i] = polygon_size(polygons[i]);
//			cerr << "Polygon " << i << " has size " << polysize[i] << endl;
			if (winding_number(polygons[i], s1x, s1y) != 0) s1id = i;
			if (winding_number(polygons[i], s2x, s2y) != 0) s2id = i;
			
			for (ll j = 0; j < i; ++j) {
				adj[i][j] = adj[j][i] = canjump(polygons[i], polygons[j], d);
			}
		}
		
		if (s1id == -1 || s2id == -1) {
			printf("Scientists cannot meet\n");
			continue;
		}
		if (s1id == s2id) {
			printf("%.7lf \n", double(polysize[s1id]));
			continue;
		}
		
//		cerr << "Scntsts: " << s1id << ' ' << s2id << endl;
//		for(int i=0;i<f;++i){
//		for(int j=0;j<f;++j){
//			cout<<adj[i][j];
//		}cout<<endl;}
		
		UnionFind uf(f);
		priority_queue<pair<ld, ii> > pq;
		for (int i = 0; i < f; ++i) {
			for (int j = i + 1; j < f; ++j) {
				if (!adj[i][j]) continue;
				ld wght = min(polysize[i], polysize[j]);
				pq.push({wght, {i, j}});
			}
		}
		bool success = false;
		while (!pq.empty()) {
			auto it = pq.top(); pq.pop();
//			cerr << "Handling " << it.first << " between " << it.second.first << " & " << it.second.second << endl;
			uf.union_set(it.second.first, it.second.second);
			if (uf.same(s1id, s2id)) {
				printf("%.7lf \n", double(it.first));
				success = true;
				break;
			}
		}
		if (!success)
			printf("Scientists cannot meet\n");
	}

	
	return 0;
}
