#include<iostream>
#include<string>

using namespace std;

// Grid status identifiers
const int BOMB = 0, NEARBOMB = 1, NOBOMBS = 2, NEARBOMB_VISITED = 3, NOBOMBS_VISITED = 4;
// note: visited(x) <=> (x >= 3)

// forward decs
void updateStatus(int i, int j, int N, short* s);
void visit(int i, int j, int N, short* s);

int main(){

	int T;
	cin >> T;

	for(int t = 1; t <= T; t++){
		int N;
		cin >> N;

		short* s = new short[N * N];

		// Read in the board
		for (int i = 0; i < N; i++){
			string in;
			cin >> in;
			for (int j = 0; j < N; j++){
				s[i*N + j] = (in[j] == '*' ? BOMB : NOBOMBS);

				// Update positions in the board whose full surroundings are now known
				if (i * j > 0)
					updateStatus(i - 1, j - 1, N, s);
				if (j == N - 1 && i > 0)
					updateStatus(i - 1, j, N, s);
				if (j > 0 && i == N - 1)
					updateStatus(i, j - 1, N, s);
			}
			updateStatus(N - 1, N - 1, N, s);
		}

		int clickCount = 0;

		// Visit each cel
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){

				// Skip if it is already visited or is a bomb
				if (s[i*N + j] == BOMB || (s[i*N + j] >= 3))
					continue;

				// If there are no bombs, click, and recursively unfold
				if (s[i*N + j] == NOBOMBS){
					clickCount++;
					s[i*N + j] = NOBOMBS_VISITED;
					visit(i, j, N, s);
				}
				else if(s[i*N + j] == NEARBOMB)
				{
					int l = (i - 1 >= 0) ? i - 1 : 0,
						r = (i + 1 <  N) ? i + 1 : N - 1,
						t = (j - 1 >= 0) ? j - 1 : 0,
						b = (j + 1 <  N) ? j + 1 : N - 1;
					bool noBombLocFound = false;

					// Try to find an adjacent square with no adjacent bombs.
					// If one is found, click it and recursively unfold.
					for (int x = l; x <= r; x++){
						for (int y = t; y <= b; y++){
							if (x == i && y == j) continue;

							if (s[x*N + y] == NOBOMBS){
								noBombLocFound = true;
								clickCount++;
								s[x*N + y] = NOBOMBS_VISITED;
								visit(x, y, N, s);
								break;
							}
						}
					}

					// If no adjacent 'nobombs' were found, click this square.
					if (!noBombLocFound){
						s[i*N + j] = NEARBOMB_VISITED;
						clickCount++;
					}
				}
			}
		}

		delete[] s;

		cout << "Case #" << t << ": " << clickCount << endl;
	}

	return 0;
}

// Updates grid cels to reflect their surroundings
void updateStatus(int i, int j, int N, short* s){
	if (s[i*N + j] == BOMB) return;

	int l = (i - 1 >= 0) ? i - 1 : 0,
		r = (i + 1 <  N) ? i + 1 : N - 1,
		t = (j - 1 >= 0) ? j - 1 : 0,
		b = (j + 1 <  N) ? j + 1 : N - 1;

	int status = NOBOMBS;

	for (int x = l; x <= r; x++){
		for (int y = t; y <= b; y++){
			if (x == i && y == j) continue;
			if (s[x*N + y] == BOMB)
				status = NEARBOMB;
		}
	}

	s[i*N + j] = status;
}

// Recursively visits surrounding cels (flood fill)
void visit(int i, int j, int N, short* s){
	int l = (i - 1 >= 0) ? i - 1 : 0,
		r = (i + 1 <  N) ? i + 1 : N - 1,
		t = (j - 1 >= 0) ? j - 1 : 0,
		b = (j + 1 <  N) ? j + 1 : N - 1;

	for (int x = l; x <= r; x++){
		for (int y = t; y <= b; y++){
			if (x == i && y == j) continue;

			switch (s[x*N + y]){
			case NEARBOMB:
				s[x*N + y] = NEARBOMB_VISITED;
				break;
			case NOBOMBS:
				s[x*N + y] = NOBOMBS_VISITED;
				visit(x, y, N, s);
			}
		}
	}
}