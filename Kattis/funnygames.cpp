#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long double ld;
struct iv { // Represents (l, r]
	ld l, r;
	iv() : l(0.0), r(0.0) { }
	iv(ld _l, ld _r) : l(_l), r(_r) { }
	bool operator<(const iv &o) const { return (l != o.l ? l < o.l : r > o.r); }
};

void pis(string msg, vector<iv> &v) {
	cerr << msg << ": ";
	for (iv i : v) cerr << "(" << i.l << ", " << i.r << "], ";
	cerr << endl;
}

ld MAX = 10020.0;

void union_self(vector<iv> &v) {
	vector<iv> u(v);
	v.clear();
	sort(u.begin(), u.end());
	if (u.size() == 0) return;
	ld l = u[0].l, r = u[0].r;
	for (int i = 1; i < u.size(); ++i) {
		if (u[i].l > MAX) continue;
		if (u[i].l > r) {
			v.push_back(iv(l, r));
			l = u[i].l; r = u[i].r;
		}
		r = min(MAX, max(r, u[i].r));
	}
	if (l < MAX)
		v.push_back(iv(l, r));
}
void complement(vector<iv> &v) { // [0, MAX]
	vector<iv> c(v);
	v.clear();
	ld l = 0.0;
	for (int i = 0; i < c.size(); ++i) {
		if (l < c[i].l) v.push_back(iv(l, c[i].l));
		l = c[i].r;
	}
	if (l < MAX) v.push_back(iv(l, MAX));
}

int main() {
	int N;
	cin >> N;
	for (int t = 1; t <= N; ++t) {
		int K;
		ld X;
		cin >> X >> K;
		vector<ld> F(K, 0.0);
		bool c = true;
		ld M = 0.0;
		for (int i = 0; i < K; ++i) {
			cin >> F[i];
			if (F[i] < 1e-8) {
				if (c)
					cout << "Nils" << endl;
				c = false;
			} else F[i] = 1.0 / F[i];
			if (F[i] > M) M = F[i];
		}
		if (!c) continue;
		if (X <= M) {
			cout << "Nils" << endl;
			continue;
		}
		
		vector<iv> win, lose;
		win.push_back(iv(0.0, M));
		bool pa = false;
		int IT = 250;
		while (IT > 0) {
			IT--;
			pa = !pa;
			if (pa) {
				// Calculate losing intervals
				vector<iv> sf, temp;
				for (int i = 0; i < K; ++i) {
					temp.clear();
					for (int j = 0; j < win.size(); ++j) {
						temp.push_back(iv(F[i]*win[j].l, F[i]*win[j].r));
					}
					union_self(temp);
					complement(temp);
					for (iv intv : temp)
						sf.push_back(intv);
				}
				for (iv intv : win)
					sf.push_back(intv);
				union_self(sf);
				complement(sf);
				for (iv intv : sf)
					lose.push_back(intv);
				union_self(lose);
				for (iv intv : lose)
					if (intv.l < X && intv.r >= X) {
						IT = -12;
						cout << (pa ? "Mikael" : "Nils") << endl;
						break;
					}
			} else {
				// Calculate winning intervals
				for (int i = 0; i < K; ++i)
					for (iv intv : lose)
						win.push_back(iv(F[i]*intv.l, F[i]*intv.r));
				union_self(win);
				for (iv intv : win)
					if (intv.l < X && intv.r >= X) {
						IT = -5;
						cout << (pa ? "Mikael" : "Nils") << endl;
						break;
					}
			}
		}
		if (IT == 0) cout << " Nils" << endl;
	}
	
	return 0;
}
