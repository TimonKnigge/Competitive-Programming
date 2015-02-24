#include<iostream>
#include<string>

using namespace std;

class node{
public:
	node *l, *r;
	char v;

	node(char v) : v(v){};
};

// Reconstructs the message given by the LL.
void reconstruct(node * l, node * r, bool rev, int dInc, int sz, bool del = false){
	node *cur = (rev ? r : l), *tmp;
	while (sz-- > 0){
		char v = cur->v;

		// Shift digits if necessary.
		if ('0' <= v && v <= '9'){
			v = (v - '0' + 10 + dInc) % 10 + '0';
		}
		cout << v;

		tmp = cur;
		cur = (rev ? cur->l : cur->r);

		if (del)
			delete tmp;
	}
}

int main(){

	int N;
	cin >> N;
	while (N-- > 0){

		string messengers, message;
		cin >> messengers >> message;

		int sz = message.length();
		node *l = nullptr,
			 *m = nullptr, 
			 *r = nullptr, 
			 *last = nullptr;
		
		// Put the message in a linked list, and maintain left, right and middle nodes.
		for (int i = 0; i < sz; i++){
			node *tmp = new node(message[i]);
			tmp->l = last;

			if (last != nullptr)
				last->r = tmp;
			else
				l = tmp;
			last = tmp;

			// Save the middle node.
			if (i == (sz - 1) / 2)
				m = last;
		}
		r = last;
		// Connect both ends to turn the list into a cycle.
		r->r = l;
		l->l = r;

		// process messengers right to left
		bool rev = false;
		int dInc = 0;
		int msz = messengers.length();
		for (int i = msz - 1; i >= 0; i--){

			// For messengers C and J, move the l, r and m nodes forward or backwards,
			// depending on the messenger and current reversal state.
			if (messengers[i] == (rev ? 'C' : 'J')){
				node *t1, *t2, *t3;
				t1 = l->l;
				t2 = m->l;
				t3 = r->l;
				l = t1; m = t2; r = t3;
			}
			else if (messengers[i] == (rev ? 'J' : 'C')){
				node *t1, *t2, *t3;
				t1 = l->r;
				t2 = m->r;
				t3 = r->r;
				l = t1; m = t2; r = t3;
			}
			else if (messengers[i] == 'E'){
				
				// If there is no middle to be left in place,
				// we simply swap l <-> mr and m <-> r.
				if (sz % 2 == 0){
					node * tr = r, *mr = m->r;

					r = m; 
					m = tr;
					l = mr;
				}
				// If there is a middle, we do the same, but we
				// take m out of the list and place it between l and r.
				else{
					node *ml = m->l, *mr = m->r;
					mr->l = ml; ml->r = mr;

					m->l = r; m->r = l;
					l->l = m; r->r = m;

					l = mr; r = ml;
				}
			}
			// Rest is trivial.
			else if (messengers[i] == 'A'){
				rev = !rev;
			}
			else if (messengers[i] == 'P'){
				dInc -= 1;
			}
			else if (messengers[i] == 'M'){
				dInc += 1;
			}
		}

		// Output solution, delete dynamic memory.
		reconstruct(l, r, rev, dInc, sz, true);

		cout << endl;
	}
}