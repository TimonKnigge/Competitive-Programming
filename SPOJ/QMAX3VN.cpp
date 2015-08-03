#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <stdio.h>
using namespace std;

typedef long long ll;

const int INF = 2000000000;

struct info_package {
public:
	int x, xmax;
	info_package() { }
};

struct AVL_Node { 
	info_package val; 
	AVL_Node *par, *lef, *rig;
	int size, height; 
	AVL_Node(info_package& _val, AVL_Node *_par = NULL)
	 : val(_val), par(_par), lef(NULL), rig(NULL), size(1), height(0) { } 
};
class AVL_Tree {
public:
	AVL_Node *root;
	AVL_Tree() : root(NULL) { }

	// Querying
//	AVL_Node *find(info_package& key) {
//		AVL_Node *c = root;
//		while (c != NULL && c->val != key) {
//			if (c->val < key) c = c->rig;
//			else c = c->lef;
//		}
//		return c;
//	}
	AVL_Node *minimum(AVL_Node *n) {
		if (n != NULL) while (n->lef != NULL) n = n->lef; return n;
	}
	AVL_Node *maximum(AVL_Node *n) {
		if (n != NULL) while (n->rig != NULL) n = n->rig; return n;
	}
	AVL_Node *minimum() { return minimum(root); }
	AVL_Node *maximum() { return maximum(root); }
	AVL_Node *predecessor(AVL_Node *n) { 
		if (n->lef != NULL) return maximum(n->lef);
		AVL_Node *p = n->par;
		while (p != NULL && n == p->lef) { n = p; p = n->par; }
		return p;
	}
	AVL_Node *successor(AVL_Node *n) {
		if (n->rig != NULL) return minimum(n->rig);
		AVL_Node *p = n->par;
		while (p != NULL && n == p->rig) { n = p; p = n->par; }
		return p;
	}
	int get_height(AVL_Node *n) { return (n == NULL ? 0 : n->height); }
	int get_size(AVL_Node *n) { return (n == NULL ? 0 : n->size); }
	int rank(AVL_Node *n) {
		int r = get_size(n->lef); 
		AVL_Node *p = n->par;
		while (p != NULL) {
			if (n == p->rig) r += 1 + get_size(p->lef);
			n = p; p = p->par; 
		}
		return r + 1;
	}
	AVL_Node *nth(int n) {
		AVL_Node *r = root;
		while (r != NULL) {
			int sz = 1 + get_size(r->lef);
			if (sz < n) { r = r->rig; n -= sz; }
			else if (sz > n) { r = r->lef; }
			else break;
		}
		return r;
	}
	int query(int L, int R) { return _query(root, L, R); }
	int _query(AVL_Node *n, int L, int R) {
		if (n == NULL) return -INF;
		int sz = get_size(n); // we have the interval [1..sz]
		if (L > sz || R < 1 || L > R) return -INF;
		if (L <= 1 && R >= sz) return n->val.xmax;
		int mx = -INF, lsz = 1 + get_size(n->lef);
		if (L <= lsz && R >= lsz) mx = max(mx, n->val.x);
		mx = max(mx, _query(n->lef, L, R));
		mx = max(mx, _query(n->rig, L - lsz, R - lsz));
		return mx;
	}

	// Modification
//	AVL_Node *insert(info_package& nval) {
//		AVL_Node *p = NULL, *c = root;
//		while (c != NULL) {
//			p = c;
//			if (c->val < nval) c = c->rig;
//			else c = c->lef;
//		}
//		AVL_Node *r = new AVL_Node(nval, p);
//		(p == NULL ? root :
//			nval < p->val ? p->lef : p->rig)
//			 = r;
//		_fixup(r); return r;
//	}
	AVL_Node *insert_at(info_package& nval, int n) { // 0-based
//		cerr << "began insert" << endl;
		AVL_Node *p = NULL, *c = root; bool leftinsert = true;
		while (c != NULL) {
			p = c;
			int sz = get_size(c->lef);
			if (sz >= n) {
				c = c->lef;
				leftinsert = true;
			} else {
				n -= 1 + get_size(c->lef);
				c = c->rig;
				leftinsert = false;
			}
		}
//		cerr << "found location"<<endl;
		AVL_Node *r = new AVL_Node(nval, p);	
		(p == NULL ? root :
			leftinsert ? p->lef : p->rig) = r;
		_fixup(r);
//		cerr << "finished insert"<<endl;
		return r;
	}
	void remove(AVL_Node *n, bool del = true) {
		if (n == NULL) return;
		if (n->lef == NULL && n->rig == NULL) 
			_pchild(n) = NULL;
		else if (n->lef != NULL && n->rig == NULL) {
			_pchild(n) = n->lef;
			n->lef->par = n->par;
		} else if (n->rig != NULL && n->lef == NULL) {
			_pchild(n) = n->rig;
			n->rig->par = n->par;
		} else {
			AVL_Node *y = successor(n), *z = y->par;
			if (z != n) {
				_transplant(y, y->rig);
				y->rig = n->rig;
				y->rig->par = y;
			}
			_transplant(n, y);
			y->lef = n->lef;
			y->lef->par = y;
			_fixup(z->rig == NULL ? z : z->rig);
			if (del) delete n;
			return;
		}
		_fixup(n->par);
		if (del) delete n;
	}
	void cleanup() { _cleanup(root); }

	void print() { _print(root); cerr << endl; }
	void _print(AVL_Node *n) {
		if (n == NULL) return;
		cerr << '(';
		_print(n->lef);
		cerr << ' ' << n->val.x << ':' << n->val.xmax << ' ';
		_print(n->rig);
		cerr << ')';
	}

private:
	// Helpers
	void _transplant(AVL_Node *u, AVL_Node *v) {
		_pchild(u) = v;
		if (v != NULL) v->par = u->par;
	}
	AVL_Node *&_pchild(AVL_Node *n) {
		return (n == NULL ? root :
			(n->par == NULL ? root :
			(n->par->lef == n ? n->par->lef : n->par->rig)));
	}
	void _augmentation(AVL_Node *n) {
		if (n == NULL) return;
		n->height = 1 + max(get_height(n->lef), get_height(n->rig));
		n->size = 1 + get_size(n->lef) + get_size(n->rig);
		
		n->val.xmax = n->val.x;
		if (n->lef != NULL) n->val.xmax = max(n->val.xmax, n->lef->val.xmax);
		if (n->rig != NULL) n->val.xmax = max(n->val.xmax, n->rig->val.xmax);
	}
	bool balanced(AVL_Node *n) { return (abs(get_height(n->lef) - get_height(n->rig)) <= 1); }
	bool leans_left(AVL_Node *n) { return get_height(n->lef) > get_height(n->rig); }
	bool leans_right(AVL_Node *n) { return get_height(n->rig) > get_height(n->lef); }
#define ROTATE(L, R) \
		AVL_Node *o = n->R; \
		n->R = o->L; \
		if (o->L != NULL) o->L->par = n; \
		o->par = n->par; \
		_pchild(n) = o; \
		o->L = n; \
		n->par = o; \
		_augmentation(n); _augmentation(o);
	void _left_rotate(AVL_Node *n) { ROTATE(lef, rig); }
	void _right_rotate(AVL_Node *n) { ROTATE(rig, lef); }
	void _fixup(AVL_Node *n) {
		while (n != NULL) {
			_augmentation(n);
			if (!balanced(n)) {
				if (leans_left(n) && leans_right(n->lef)) _left_rotate(n->lef);
				else if (leans_right(n) && leans_left(n->rig)) _right_rotate(n->rig);
				if (leans_left(n)) _right_rotate(n);
				if (leans_right(n)) _left_rotate(n);
			}
			n = n->par;
		}
	}
	void _cleanup(AVL_Node *n) {
		if (n->lef != NULL) _cleanup(n->lef);
		if (n->rig != NULL) _cleanup(n->rig);
		delete n;
	}
};

// l, r, cl, cr, A, B, O

int main() {
	AVL_Tree avl_tree;
	int n;
	scanf("%d", &n);

	char c; int x, y;
	for (int i = 0; i < n; ++i) {
		scanf(" %c %d %d", &c, &x, &y);
//		cerr << "got " << c <<' '<<x<<' '<<y <<endl;
		if (c == 'A') {
			info_package ip;
			ip.x = ip.xmax = x;
			avl_tree.insert_at(ip, y-1);
//			avl_tree.print();
		} else if (c == 'Q') {
			printf("%d\n", avl_tree.query(x, y));
		}
	}
//	avl_tree.cleanup();
	
	return 0;
}
