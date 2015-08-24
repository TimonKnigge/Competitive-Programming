#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef vector<int> vi;

void compute_prefix_function(string &word, vi &pi) {
	pi.assign(word.length(), 0);
	int k = pi[0] = -1;
	
	for (int i = 1; i < word.length(); ++i) {
		while (k >= 0 && word[k + 1] != word[i])
			k = pi[k];
		if (word[k + 1] == word[i]) k++;
		pi[i] = k;
	}
	for (int i : pi) cout << i << ' ';cout<<endl;
}

void knuth_morris_pratt(string &sentence, string &word) {
	int q = -1; vi pi;
	compute_prefix_function(word, pi);
	for (int i = 0; i < sentence.length(); ++i) {
		while (q >= 0 && word[q + 1] != sentence[i])
			q = pi[q];
		if (word[q + 1] == sentence[i]) q++;
		if (q + 1== word.length()) {
			cout << (i - int(word.length()) + 1) << ' ';
			q = pi[q];
		}
	}
}

int main() {
	string p, s;
	while (getline(cin, p)) {
		getline(cin, s);
		knuth_morris_pratt(s, p);
		cout << '\n';
	}
	return 0;
}
