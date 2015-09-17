#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		int N;
		scanf("%d", &N);
		
		vector<int> P(N, 0);
		for (int i = 0; i < N; ++i) scanf("%d", &P[i]);
		
		int nimsum = 0;
		for (int i = 0; i < N; ++i) {
			int K;
			scanf("%d", &K);
			nimsum ^= (P[i] % (K + 1));
		}
		
		if (nimsum == 0) printf("Mishra\n");
		else printf("Amit\n");
	}
	
	return 0;
}
