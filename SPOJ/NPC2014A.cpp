#include <iostream>
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	
	for (int t = 1; t <= T; ++t) {
		int N;
		scanf("%d", &N);
		
		int nimsum = 0;
		for (int i = 0; i < N; ++i) {
			int X, k = 0;
			scanf("%d", &X);
			
			if (X > 0)
				while ((X&1) == 0) k++, X >>= 1;
			
			nimsum ^= k;
		}
		
		if (nimsum != 0) printf("Puguh is the bestest player in teh wurld\n");
		else printf("Joke is the bestest player in teh wurld\n");
	}
	
	return 0;
}
