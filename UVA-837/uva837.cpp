#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<iomanip>

using namespace std;

typedef pair<double, double> dd;
typedef pair<dd, double> ddd;
typedef vector<ddd> vddd;

const int INF = 2000000000;

// Custom compare function for the sort function
bool compare(ddd l, ddd r){
	return l.first.first < r.first.first;
}

// Custom compare class for the priority queue
class Compare{
public:
	bool operator() (ddd l, ddd r){
		// lt because we want a min-heap.
		return l.first.second > r.first.second;
	}
};

int main(){
	cout << setprecision(3) << fixed;

	int T;
	cin >> T;
	while (T-- > 0){
		int NL;
		cin >> NL;

		// read in segments
		vddd segments(NL), output;
		for (int i = 0; i < NL; i++){
			double x1, y1, x2, y2, r;
			cin >> x1 >> y1 >> x2 >> y2 >> r;

			// segment should be left-to-right
			if (x1 > x2){
				double t = x1;
				x1 = x2;
				x2 = t;
			}

			segments[i] = ddd(dd(x1, x2), r);
		}

		// sort on first coordinate
		sort(segments.begin(), segments.end(), compare);

		double active = 1.0, lastSince = -INF;
		priority_queue<ddd, vddd, Compare> pq;
		for (int i = 0; i < NL; i++){
			// Introduce segment i
			output.push_back(ddd(dd(lastSince, segments[i].first.first), active));
			
			active *= segments[i].second;
			lastSince = segments[i].first.first;

			pq.push(segments[i]);

			if (pq.size() == 0)
				continue;
			
			// Keep removing segments until a new one has to be added.
			while ((i + 1 < NL) ? (pq.top().first.second < segments[i + 1].first.first) : true){
				ddd rm = pq.top();
				pq.pop();

				output.push_back(ddd(dd(lastSince, rm.first.second), active));

				active /= rm.second;
				lastSince = rm.first.second;

				if (pq.size() == 0)
					break;
			}
		}
		output.push_back(ddd(dd(lastSince, INF), active));

		// Assemble output.
		int sz = output.size();
		cout << sz << endl;
		for (int i = 0; i < sz; i++){
			double d1 = output[i].first.first,
				d2 = output[i].first.second;

			if (d1 == -INF)
				cout << "-inf ";
			else
				cout << d1 << " ";
			
			if (d2 == INF)
				cout << "+inf ";
			else
				cout << d2 << " ";

			cout << output[i].second << endl;
		}
	}

	return 0;
}