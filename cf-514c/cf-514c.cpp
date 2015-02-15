#include <iostream>
#include <string>
#include <math.h>

using namespace std;

string ins;
string::iterator it;

class Node
{
public:
	void Insert() {
		if (it == ins.end()) {
			isEnd = true;
			return;
		}
		int cnt = (*it) - 'a';
		it++;
		if (ch[cnt] == nullptr) {
			ch[cnt] = new Node();
		}
		ch[cnt]->Insert();
	}
	void Delete() {
		if (ch[0] != nullptr) {
			ch[0]->Delete();
			delete ch[0];
		}
		if (ch[1] != nullptr) {
			ch[1]->Delete();
			delete ch[1];
		}
		if (ch[2] != nullptr) {
			ch[2]->Delete();
			delete ch[2];
		}
	}

	bool Query(string::iterator p, bool canDiff) {
		if (p == ins.end()) {
			return isEnd && !canDiff;
		}
		bool v = false;
		for (int i = 0; i < 3; ++i) {
			if (((*p) - 'a') == i || canDiff) {
				if (ch[i] != nullptr)
					v = v || (ch[i]->Query(p + 1, canDiff && ((*p) - 'a') == i));
			}
		}
		return v;
	}

	bool isEnd = false;
	Node* ch[3];
	Node() {
		ch[0] = ch[1] = ch[2] = nullptr;
	}
};


int main() {

	Node root;

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		cin >> ins;
		it = ins.begin();
		root.Insert();
	}

	for (int i = 0; i < m; ++i) {
		cin >> ins;
		if (root.Query(ins.begin(), true)) {
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	}

	root.Delete();
	return 0;
}