#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	

	while (true) {
		int n; 
		char colon;
		cin >> n;
		if (n == 0) break;
		cin >> colon;
	
		int a[10005];
		bitset<10005> bs;
		bs.reset();
		
		bool aa = true;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			if (!aa) continue;
			bs.set(a[i], true);
			for (int j = 0, v; aa && j < i; ++j) {
				if ((v = a[i] + a[i] - a[j]) >= 0 
					&& v < n && !bs.test(v)) {
					aa = false;
					break;
				}
			}
		}
		cout << (aa ? "yes\n" : "no\n");
	}
	cout << flush;
	
	
	return 0;
}

