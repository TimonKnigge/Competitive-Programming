#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 2000000000;
const ll LLINF = 9000000000000000000;
double dp[513][513], d[513][513];
int N;

double dp_step(int i, int j)
{
	if(dp[i][j] != -1)
		return dp[i][j];

	if(i > j+1)
		return (dp_step(i,j+1) + d[j][j+1]);
	if(j > i+1)
		return (dp_step(i+1, j) + d[i][i+1]);
	if(i == j+1)
	{
		double MIN = INF;
		for(int k = i+1; k <= N; k++)
			MIN = min(MIN, dp_step(i,k) + d[j][k]);
		return MIN;
	}	 
	if(j == i+1)
	{
		double MIN = INF;
		for(int k = j+1; k <= N; k++)
			MIN = min(MIN, dp_step(k, j) + d[i][k]);
		return MIN;
	}
	return -100;

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T; 
	cin >> T;
	while(T-- > 0)
	{ 
		cin >> N;
		vii p(N+1, make_pair(-1,-1));
		for(int i = 1; i <= N; i++)
		{
			cin >> p[i].first >> p[i].second;
		}

		for(int i = 0; i <= N; i++)
			for(int j = 0; j <= N; j++)
				d[i][j] = sqrt((p[i].first - p[j].first)*(p[i].first - p[j].first) + (p[i].second - p[j].second)*(p[i].second - p[j].second));

		for(int i = 0; i <= N; i++)
			for(int j = 0; j <= N; j++)
				dp[i][j] = -1;

		dp[N][N-1] = d[N][N-1];
		dp[N-1][N] = d[N-1][N];

		double ans = INF; 
		for(int i = 2; i <= N; i++)
			ans = min(ans, dp_step(1,i)+ d[i][1]);

		printf("%.7lf\n", ans);
	
	}	
	
	
	return 0;
}
