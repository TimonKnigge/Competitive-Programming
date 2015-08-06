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
#include <cassert>
#define _USE_MATH_DEFINES
#include <math.h>

const int INF = 2000000000;                     // 9
const long long LLINF = 9000000000000000LL;  // 15
const long double LDINF = 1e300;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

struct T {
	ll val, sum, maxsum, lpre, lsuf;
	T() : val(0), sum(0), maxsum(0), lpre(0), lsuf(0) { }
	T(ll v) : val(v), sum(v), maxsum(v), lpre(v), lsuf(v) { }
	
	void reset() { sum = maxsum = lpre = lsuf = val; }
	void print(string msg) {
		cout << "{" << msg << ": (v="<<val<<",s="<<sum<< ",ms="<<maxsum<<",pr="<<lpre<<",su="<<lsuf<<"}";
	}
	void print() { print(""); }
};

class AVL_Tree {
public:
	struct AVL_Node {
		T val;
		AVL_Node *p, *l, *r;
		int size, height;
		AVL_Node(T& _val, AVL_Node *_p = NULL)
		 : val(_val), p(_p), l(NULL), r(NULL), size(1), height(0) { }
	};
	AVL_Node *root;
	AVL_Tree() : root(NULL) { }
	
	// maximum and predecessor can be written in a similar manner
	AVL_Node *minimum(AVL_Node *n) { // O(lg n)
		if (n != NULL) while (n->l != NULL) n = n->l; return n;
	}
	AVL_Node *minimum() { return minimum(root); } // O(lg n)
	AVL_Node *successor(AVL_Node *n) { // O(lg n)
		if (n->r != NULL) return minimum(n->r);
		AVL_Node *p = n->p;
		while (p != NULL && n == p->r) { n = p; p = n->p; }
		return p;
	}
	AVL_Node *nth(int no) { return nth(root, no); }
	AVL_Node *nth(AVL_Node *n, int no) {
		int lsz = (n == NULL ? 0 : _get_size(n->l));
		if (lsz + 1 == no) return n;
		else if (lsz + 1 > no) return nth(n->l, no);
		else return nth(n->r, no - lsz - 1);
	}
	T query(int L, int R) { return _query(root, L, R); }
	T _query(AVL_Node *n, int L, int R) {
		if (n == NULL) return T(-LLINF);
		int sz = _get_size(n), id = 1 + _get_size(n->l);
		if (R < 1 || sz < L) return T(-LLINF);
		if (L <= 1 && sz <= R) return n->val;
		if (R < id) return _query(n->l, L, R);
		if (L > id) return _query(n->r, L - id, R - id);
		ll v = n->val.val;
		T lq = _query(n->l, L, R), rq = _query(n->r, L - id, R - id);

		T ret(n->val.val); // maxsum sum lpre lsuf
		ret.maxsum = v;
		ret.sum = v;
		ret.lpre = v;
		ret.lsuf = v;
		if (R > id && n->r != NULL) {
			ret.maxsum = max(rq.maxsum, max(ret.maxsum, rq.lpre + v));
			ret.sum += rq.sum;
			ret.lsuf = max(rq.lsuf, rq.sum + v);
		}
		if (L < id && n->l != NULL) {
			ret.maxsum = max(ret.maxsum, max(lq.maxsum, lq.lsuf + v));
			ret.sum += lq.sum;
			ret.lpre = max(lq.lpre, lq.sum + v);
		}
		if (L < id && R > id && n->r != NULL && n->l != NULL) {
			ret.maxsum = max(ret.maxsum, lq.lsuf + v + rq.lpre);
			ret.lpre = max(ret.lpre, lq.sum + v + rq.lpre);
			ret.lsuf = max(ret.lsuf, rq.sum + v + lq.lsuf);
		}
//ret.print();cout<<endl;
		return ret;
	}

	// Modification
//	AVL_Node *insert(T& nval) { // O(lg n)
//		AVL_Node *p = NULL, *c = root;
//		while (c != NULL) { 
//			p = c;
//			c = (c->val < nval ? c->r : c->l);
//		}
//		AVL_Node *r = new AVL_Node(nval, p);
//		(p == NULL ? root : (
//			nval < p->val ? p->l : p->r) = r;
//		_fixup(r);
//		return r;
//	}
	AVL_Node *insert_at(T nval, int pos) { // pos = number of predecessors
		AVL_Node *p = NULL, *c = root; bool mleft = true;
		while (c != NULL) {
			p = c;
			int lsz = _get_size(c->l);
			if (lsz >= pos) {
				c = c->l;
				mleft = true;
			} else {
				pos -= lsz + 1;
				c = c->r;
				mleft = false;
			}
		}
		AVL_Node *r = new AVL_Node(nval, p);
		(p == NULL ? root : (mleft?p->l:p->r)) = r;
		_fixup(r);
		return r;
	}
	void modify(AVL_Node *n, T nval) {
		assert(n != NULL);
		n->val = nval;
		while (n != NULL) {
			_augmentation(n);
			n = n->p;
		}
	}
	void remove(AVL_Node *n, bool del = true) { // O(lg n)
		if (n == NULL) return;
		if (n->l != NULL && n->r != NULL) {
			AVL_Node *y = successor(n), *z = y->p;
			if (z != n) {
				_transplant(y, y->r);
				y->r = n->r;
				y->r->p = y;
			}
			_transplant(n, y);
			y->l = n->l;
			y->l->p = y;
			_fixup(z->r == NULL ? z : z->r);
			if (del) delete n;
			return;
		} else if (n->l != NULL) {
			_pchild(n) = n->l;
			n->l->p = n->p;
		} else if (n->r != NULL) {
			_pchild(n) = n->r;
			n->r->p = n->p;
		} else _pchild(n) = NULL;
		_fixup(n->p);
		if (del) delete n;
	}
	void cleanup() { _cleanup(root); }
	
private:
	// Helpers
	void _transplant(AVL_Node *u, AVL_Node *v) {
		_pchild(u) = v;
		if (v != NULL) v->p = u->p;
	}
	AVL_Node *&_pchild(AVL_Node *n) {
		return (n == NULL ? root : (n->p == NULL ? root :
			(n->p->l == n ? n->p->l : n->p->r)));
	}
	void _augmentation(AVL_Node *n) {
		if (n == NULL) return;
		n->height = 1 + max(_get_height(n->l), _get_height(n->r));
		n->size = 1 + _get_size(n->l) + _get_size(n->r);
		
		// val sum maxsum lpre lsuf
		if (n->l != NULL && n->r != NULL) {
			ll v = n->val.val;
			T &lT = n->l->val, &rT = n->r->val;
			n->val.sum = lT.sum + n->val.val + rT.sum;
			n->val.maxsum = max(v, max(lT.maxsum, max(rT.maxsum, max(lT.lsuf + v, max(rT.lpre + v, lT.lsuf + v + rT.lpre)))));
			n->val.lpre = max(lT.lpre, max(lT.sum + v, lT.sum + v + rT.lpre));
			n->val.lsuf = max(rT.lsuf, max(rT.sum + v, rT.sum + v + lT.lsuf));
		} else if (n->r != NULL) {
			T &rT = n->r->val;
			n->val.sum = n->val.val + rT.sum;
			n->val.maxsum = max(n->val.val, max(rT.maxsum, n->val.val + rT.lpre));
			n->val.lpre = max(n->val.val, n->val.val + rT.lpre);
			n->val.lsuf = max(rT.lsuf, n->val.val + rT.sum);
		} else if (n->l != NULL) {
			T &lT = n->l->val;
			n->val.sum = n->val.val + lT.sum;
			n->val.maxsum = max(n->val.val, max(lT.maxsum, n->val.val + lT.lsuf));
			n->val.lpre = max(lT.lpre, n->val.val + lT.sum);
			n->val.lsuf = max(n->val.val, n->val.val + lT.lsuf);
		} else {
			n->val.reset();
		}
	}
	int _get_height(AVL_Node *n) { return (n == NULL ? 0 : n->height); }
	int _get_size(AVL_Node *n) { return (n == NULL ? 0 : n->size); }
	bool _balanced(AVL_Node *n) { return (abs(_get_height(n->l) - _get_height(n->r)) <= 1); }
	bool _leans_left(AVL_Node *n) { return _get_height(n->l) > _get_height(n->r); }
	bool _leans_right(AVL_Node *n) { return _get_height(n->r) > _get_height(n->l); }
#define ROTATE(L, R) \
	AVL_Node *o = n->R; \
	n->R = o->L; \
	if (o->L != NULL) o->L->p = n; \
	o->p = n->p; \
	_pchild(n) = o; \
	o->L = n; \
	n->p = o; \
	_augmentation(n); \
	_augmentation(o);
	void _left_rotate(AVL_Node *n) { ROTATE(l, r); }
	void _right_rotate(AVL_Node *n) { ROTATE(r, l); }
	void _fixup(AVL_Node *n) {
		while (n != NULL) {
			_augmentation(n);
			if (!_balanced(n)) {
				if (_leans_left(n) && _leans_right(n->l)) _left_rotate(n->l);
				else if (_leans_right(n) && _leans_left(n->r)) _right_rotate(n->r);
				if (_leans_left(n)) _right_rotate(n);
				if (_leans_right(n)) _left_rotate(n);
			}
			n = n->p;
		}
	}
	void _cleanup(AVL_Node *n) {
		if (n->l != NULL) _cleanup(n->l);
		if (n->r != NULL) _cleanup(n->r);
	}
public:
	void print() { print(root); }
	void print(AVL_Node *n) {
		if (n == NULL) return;
		cout << '(';
		print(n->l);
		cout << ' ' << n->val.val <<' ';
		print(n->r);
		cout << ')';
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N; cin >> N;
	AVL_Tree avltree;
	for (int i = 0; i < N; ++i) {
		int ai; cin >> ai;
		avltree.insert_at(T(ai), i);
	}

	int Q; cin >> Q;
	for (int q = 0; q < Q; ++q) {
//		cout << "Tree: "; avltree.print(); cout << endl;
		string c; cin >> c;
		if (c == "I"){
			int x, y;
			cin >> x >> y;
			avltree.insert_at(T(y), x - 1);
		} else if (c == "D") {
			int x;
			cin >> x;
			avltree.remove(avltree.nth(x));
		} else if (c == "R") {
			int x, y;
			cin >> x >> y;
			avltree.modify(avltree.nth(x), T(y));
		} else {
			int x, y;
			cin >> x >> y;
			cout << avltree.query(x, y).maxsum << '\n';
		}
	}
	
	return 0;
}
