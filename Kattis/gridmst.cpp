#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <random>
#include <cstring>

using namespace std;

#define M 1000000
#define SM 1000
bool mark[M];
int dist[M];

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

int main() {
	int N, C;
	scanf("%d", &N);
	C = N;
	
	fill(mark, mark + M, false);
	fill(dist, dist + M, 2 * M);
	
	int p = rand() % N, sx = 0, sy = 0;
	for (int i = 0; i < N; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		mark[x + SM * y] = true;
		if (i == p) { sx = x; sy = y; }
	}
	
	priority_queue<iii, vector<iii>, greater<iii> > pq;
	pq.push({0, {sx, sy}});
	dist[sx + SM * sy] = 0;
	int ans = 0;
	
	while (!pq.empty() && C > 0) {
		int d = pq.top().first, x = pq.top().second.first,
			y = pq.top().second.second, id = x + SM * y;
		pq.pop();
		if (d > dist[x + SM * y]) continue;
		
		if (mark[id]) {
			mark[id] = false;
			ans += dist[id];
			d = dist[id] = 0;
			C--;
		}
		if (x > 0 && dist[x - 1 + SM * y] > d + 1) {
			dist[x - 1 + SM * y] = d + 1;
			pq.push({d + 1, {x - 1, y}}); }
		if (y > 0 && dist[x + SM * (y - 1)] > d + 1) {
			dist[x + SM * (y - 1)] = d + 1;
			pq.push({d + 1, {x, y - 1}}); }
		if (x < SM - 1 && dist[x + 1 + SM * y] > d + 1) {
			dist[x + 1 + SM * y] = d + 1;
			pq.push({d + 1, {x + 1, y}}); }
		if (y < SM - 1 && dist[x + SM * (y + 1)] > d + 1) {
			dist[x + SM * (y + 1)] = d + 1;
			pq.push({d + 1, {x, y + 1}}); }
	}
	
	printf("%d\n", ans);
	
	return 0;
}
