#include <iostream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n; cin >> n;
	unordered_map<string, int> k, d;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		if (k.find(s) == k.end()) k[s] = 1;
		else k[s]++;
	}
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		if (d.find(s) == d.end()) d[s] = 1;
		else d[s]++;
	}

	int t = 0;
	for (auto kv : k) {
		if (d.find(kv.first) != d.end())
		t += min(kv.second, d[kv.first]);
	}

	cout << t << endl;

	return 0;
}