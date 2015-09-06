#include <iostream>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cout << "2000\n";
	int N = 1000;
	for (int i = 1; i <= N; ++i)
		cout << i << " 1 " << i << " 2\n";
	for (int i = N; i >= 1; --i)
		cout << i << " 1 " << i << " 2\n";
	cout << flush;
	
	return 0;
}
