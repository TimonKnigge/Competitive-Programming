#include <iostream>
#include <random>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;

struct line {
	ll A, B, C;
	line() : A(0), B(0), C(0) { }
	line(ll _A, ll _B, ll _C) : A(_A), B(_B), C(_C) { }
}

inline bool intersects(int i, int j, vector<line> &ls) {
	if (ls[i].A * ls[j].B - ls[j].A * ls[i].B == 0) return (i == j);
	return true;
}
inline bool three_intersects(int i, int j, int k, vector<line> &ls) {
	if (ls[i].A == 0) {
		// ls[i] = horizontal
		ll yt = ls[i].C, yn = ls[i].B;
		
	}

	ld a1 = ls[i].A, b1 = ls[i].B, c1 = ls[i].C,
	   a2 = ls[j].A, b2 = ls[j].B, c2 = ls[j].C,
	   a3 = ls[k].A, b3 = ls[k].B, c3 = ls[k].C;
	
	
	r += 
}

int main() {
	int n, k;
	cin >> n >> k;
	if (n == 1) { cout << "Yes\n" << 1 << ' ' << -1 << endl; }

	vector<line> ls;
	for (int i = 0; i < n; ++i) {
		ll A, B, C;
		cin >> A>> B>>C;
		ls.push_back(line(A, B, C));
	}

	const int rep = 300;
	vector<pair<int, int>> res;
	while (rep-- > 0) {
		for (int i = 0; i < k; ++i) {
			int l = rand() % n, r = rand() % n;
			while (r != l) r = rand() % n;
			if (intersects(l, r, ls))
				rep.push_back({l + 1, r + 1});
			else
				rep.push_back({l + 1, -1});
		}
		
	}
}
