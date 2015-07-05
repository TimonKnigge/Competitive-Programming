#include<iostream>
#include<math.h>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

struct point{
	double x, y;
	point() : x(0), y(0) {};
	point(double x, double y) : x(x), y(y) {};
}; 

inline double area2(point a, point b, point c){ // twice the area of the triangle
	return abs(b.x*c.y + a.x*b.y + a.y*c.x - a.x*c.y - a.y*b.x - b.y*c.x);
}

double area(point a, point b, point c){ // triangle area
	return area2(a, b, c) / 2.0;
}

double fourgonarea(point a, point b, point c, point d){ // sorted ccw!
	return area(a, b, c) + area(a, c, d);
}

inline double dist2(point a, point b){ // distance squared
	double dx = a.x - b.x, dy = a.y - b.y;
	return dx * dx + dy * dy;
}

double linedistsq(point a, point l1, point l2){
	double dsq = dist2(l1, l2);
	if (dsq == 0)
		return dist2(l1, a);

	double lambda = (l2.x - l1.x) * (a.x - l1.x) + (l2.y - l1.y) * (a.y - l1.y);
	lambda /= dsq;

	return dist2(a, point((1 - lambda) * l1.x + lambda * l2.x, (1 - lambda) * l1.y + lambda * l2.y));
}

bool ccw(point p, point q, point r){ // counterclockwise ?
	return (0 < (r.x - q.x) * (p.y - q.y) - (r.y - q.y) * (p.x - q.x));
}

void safePrint(double p) { // specific printing requirements ..
	bool h = (p != ((long)p));

	cout << ((long)p);
	if (h)
		cout << ".5";
	cout << endl;
}

// forward declarations
point pivot; // used by both of the functions \/
bool angle_comp(point a, point b);
void GrahamScan(vector<point> polygon, vector<point> * hull);

int main(){

	int cases;
	cin >> cases;

	while (cases-- > 0){
		int n;
		vector<point> polygon, convexhull;
		cin >> n;
		
		polygon.reserve(n);
		
		// read in all points
		for (int _ = 0; _ < n; _++)
		{
			int x, y;
			cin >> x >> y;
			polygon.push_back(point(x, y));
		}

		// find convex hull
		if (polygon.size() > 3)
			GrahamScan(polygon, &convexhull);
		else
			convexhull = polygon;
		int size = convexhull.size();
		
		if (size > 4){
			// find 2 points furthest apart
			int p1 = 0, p2 = size / 2;

			// ?
		}
		else{
			// area of 4/3-gon
			if (size == 4)
				safePrint(fourgonarea(
					convexhull[0],
					convexhull[1],
					convexhull[2],
					convexhull[3]));
			else
				safePrint(area(
					convexhull[0],
					convexhull[1],
					convexhull[2]));
		}
	}

	return 0;
}

// angle sorting function, used by GrahamScan.
bool angle_comp(point a, point b){
	if (area2(pivot, a, b) == 0) // points are colinear
		return (dist2(pivot, a) < dist2(pivot, b));

	double d1x = a.x - pivot.x, d1y = a.y - pivot.y,
		   d2x = b.x - pivot.x, d2y = b.y - pivot.y;
	return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}


void GrahamScan(vector<point> polygon, vector<point> * hull){
	// find the bottom-right point (prioritizing bottom over right)
	int p0 = 0, N = (int)polygon.size();
	for (int i = 1; i < N; i++){
		if (polygon[i].y < polygon[p0].y)
			p0 = i;
		else if (polygon[i].y == polygon[p0].y && polygon[i].x > polygon[p0].x)
			p0 = i;
	}

	// swap p0 and 0:
	point tmp = polygon[0];
	polygon[0] = polygon[p0];
	polygon[p0] = tmp;

	// sort points with respect to p0:
	pivot = polygon[0];
	sort(++polygon.begin(), polygon.end(), angle_comp);

	// ccw testing
	stack<point> stck;
	point prev, cur;
	stck.push(polygon[N - 1]);
	stck.push(polygon[0]);

	int i = 1;
	while (i < N){
		// retrieve 2nd item from stack
		cur = stck.top();
		stck.pop();
		prev = stck.top();
		stck.push(cur);

		// if prev -> cur -> polygon[i] is a left turn, add i.
		if (ccw(prev, cur, polygon[i])){
			stck.push(polygon[i]);
			++i;
		}
		else{ // otherwise remove
			stck.pop();
		}
	}

	// move stack to hull-vector
	while (!stck.empty()){
		(*hull).push_back(stck.top());
		stck.pop();
	}

	// remove top, it's a duplicate of [0]
	(*hull).pop_back();
}