#include<iostream>
#include<iomanip>
#include<math.h>

using namespace std;

typedef long double ld;

// forward declarations
ld plusint(ld x1, ld y1, ld x2, ld y2);
ld minint(ld x1, ld y1, ld x2, ld y2);
inline ld triangle_area(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3);
inline ld n1dot(ld x1, ld y1, ld x2, ld y2);

int main()
{
	int cases;
	cin >> cases;

	// set precision
	cout << fixed;
	cout << setprecision(6);

	while (cases-- > 0){
		int corners;
		ld x1, x2, y1, y2;
		cin >> corners;
		cin >> x1 >> y1 >> x2 >> y2;

		ld originx = ((ld)(x1 + x2)) / 2,
			originy = ((ld)(y1 + y2)) / 2,
			totalarea = 0.0f,
			visiblearea = 0.0f;

		// Determine the rotation matrix
		ld m11, m12, m21, m22;
		m11 = m22 = n1dot(x2 - originx, y2 - originy, 1, 0);
		m12 = -sqrt(1 - m11 * m11);
		m21 = -m12;

		// transform original coordinates
		// transform
		x1 -= originx; y1 -= originy;
		x2 -= originx; y2 -= originy;

		// rotate
		ld t = x1;
		t = m11 * x1 + m12 * y1;
		y1 = m21 * x1 + m22 * y1;
		x1 = t;
		t = m11 * x2 + m12 * y2;
		y2 = m21 * x2 + m22 * y2;
		x2 = t;

		// Status: -1 : right of viewing cone, 0 in viewing cone, 1 left of viewing cone
		int prev_status = -1, cur_status = -1;
		ld lx, ly, x = x2, y = y2;
		while (corners-- > 1)
		{
			lx = x; 
			ly = y;
			prev_status = cur_status;

			// read and transform new coordinates
			if (corners > 1)
			{
				cin >> x >> y;
				x -= originx;
				y -= originy;
				ld t = m11 * x + m12 * y;
				y = m21 * x + m22 * y;
				x = t;
			}
			else{
				x = x1; y = y1;
			}

			if (x > y)
				cur_status = -1;
			else if (-x > y)
				cur_status = 1;
			else cur_status = 0;

			if (cur_status == prev_status){
				if (cur_status == 0){
					visiblearea += triangle_area(0, 0, lx, ly, x, y);
				}
			}
			else if (cur_status == 1 && prev_status == -1){
				ld l1 = plusint(lx, ly, x, y),
					   l2 = minint(lx, ly, x, y);
				visiblearea += triangle_area(0, 0, l1, l1, l2, -l2);
			}
			else if (cur_status == 0 && prev_status == -1){
				ld l1 = plusint(lx, ly, x, y);
				visiblearea += triangle_area(0, 0, l1, l1, x, y);
			}
			else if (cur_status == 1 && prev_status == 0){
				ld l2 = minint(lx, ly, x, y);
				visiblearea += triangle_area(0, 0, lx, ly, l2, -l2);
			}

			// total area
			if (corners > 1)
				totalarea += triangle_area(x1, y1, lx, ly, x, y);
		}

		cout << (visiblearea / totalarea) << endl;
	}

	return 0;
}

// Finds the intersection with x = y, assumes given line is not parallel
ld plusint(ld x1, ld y1, ld x2, ld y2){
	x2 -= x1;
	y2 -= y1;

	ld lambda = (y1 - x1) / (x2 - y2);

	return x1 + lambda * x2;
}

// Same as above, for y = -x
ld minint(ld x1, ld y1, ld x2, ld y2){
	x2 -= x1;
	y2 -= y1;

	ld lambda = - (y1 + x1) / (x2 + y2);

	return x1 + lambda * x2;
}

// Coordinates in lds since some intersections have non-integer values.
inline ld triangle_area(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3)
{
	ld det = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
	return det > 0.0f ? det/2 : -det/2;
}

// normalizes the first vector, returns the dot product
inline ld n1dot(ld x1, ld y1, ld x2, ld y2)
{
	ld len = sqrt(x1 * x1 + y1 * y1);
	ld val = (x1 * x2 + y1 * y2) / len;

	return (x1*y2 - x2*y1 > 0) ? -val : val;
}