#include<iostream>
#include<vector>
#include<algorithm>

#define DEBUG false

using namespace std;


// Vector and vector operations
typedef pair<int, int> vec;
vec operator-(vec l, vec r){
	return vec(l.first - r.first, l.second - r.second);
}
int operator*(vec l, vec r){ // dot product
	return l.first * r.first + l.second * r.second;
}
float len(vec v){
	return sqrt(v*v);
}
int cross(vec l, vec r){
	return l.first * r.second - l.second * r.first;
}

// Points are guaranteed not to be colinear
bool angleCompare(vec l, vec r){
	vec  diff1 = l,
		diff2 = r;
	return (atan2(diff1.second, diff1.first) - atan2(diff2.second, diff2.first) < 0);
}

int main(){

	int T;
	cin >> T;

	while(T-- > 0){
		
		// Collect points, move origin to (x1, y1), and sort to be counter-clockwise.
		vector<vec> points(4);
		int cx, cy;
		cin >> cx >> cy;
		points[0] = vec(0, 0);
		for (int i = 1; i < 4; i++){
			int x, y;
			cin >> x >> y;
			points[i] = vec(x - cx, y - cy);
		}		
		sort(++points.begin(), points.end(), angleCompare);

#ifdef DEBUG
		for (int i = 0; i < 4; i++){
			cout << i << ": " << points[i].first << ", " << points[i].second << endl;
		}
#endif

		// Gather information about the quadrilateral
		vector<float> lengths(4);
		bool rightAngled = true;
		for (int i = 0; i < 4; i++){
			// Two sides are right-angled if their inproduct is zero.
			int dot = (points[(i + 1) % 4] - points[i])
				    * (points[(i + 1) % 4] - points[(i + 2) % 4]);
			rightAngled = rightAngled && (dot == 0);
			lengths[i] = len(points[i] - points[(i + 1) % 4]);
		}
		// Two sides are parallel if their cross product is zero.
		bool firstParallel = (cross(points[0] - points[1], points[2] - points[3]) == 0),
			secondParallel = (cross(points[1] - points[2], points[3] - points[0]) == 0);

		// Make a decision.
		if (rightAngled){ // Cube or rectangle
			if (lengths[0] == lengths[1])
				cout << "Case 1: Square" << endl;
			else
				cout << "Case 2: Rectangle" << endl;
		}
		else if (firstParallel && secondParallel){ // Rhombus or Parallelogram
			if (lengths[2] == lengths[3])
				cout << "Case 3: Rhombus" << endl;
			else
				cout << "Case 4: Parallelogram" << endl;
		}
		else{ // Trapezium or ordinary quadrilateral
			if (firstParallel || secondParallel)
				cout << "Case 5: Trapezium" << endl;
			else
				cout << "Case 6: Ordinary Quadrilateral" << endl;
		}
	}

	return 0;
}