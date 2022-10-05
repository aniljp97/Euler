#define _USE_MATH_DEFINES

#include "euler.h"
#include <iostream>
#include <cmath>

// https://projecteuler.net/problem=118

struct Coord {
	double x;
	double y;

	Coord(double x, double y) {
		this->x = x;
		this->y = y;
	}

	bool operator!=(const Coord& rhs)
	{
		double x_difference = x - rhs.x;
		double y_difference = y - rhs.y;

		return !(0.000001 > x_difference && x_difference > -0.000001 && 0.000001 > y_difference && y_difference > -0.000001);
	}

	string toStr() {
		return "(" + to_string(x) + "," + to_string(y) + ")";
	}
};

double getTangentLine(Coord point) {
	return -4.0 * point.x / point.y;
}

double getSlope(Coord p1, Coord p2) {
	return (p2.y - p1.y) / (p2.x - p1.x);
}

double getReflectionSlope(double line_slope, double tangent_line_slope) {
	double tangent_perpendicular_line_slope = -1.0 / tangent_line_slope;

	// acute angle between two lines formula, multiply by 2
	double angle_line_should_be_rotated = atan((line_slope - tangent_perpendicular_line_slope) / (1 + line_slope * tangent_perpendicular_line_slope)) * 2;

	double new_slope = tan(atan(line_slope) - angle_line_should_be_rotated);

	return new_slope;
}

Coord getOtherIntersectPoint(Coord point, double line_slope) {
	// get y-intercept of the line, represented in y = mx + b as b
	double y_intercept = point.y - point.x * line_slope;

	// plug in equation find the 2 different possible coordinates
	// we can get the x of each coordinate with the quadratic formula with a = slope^2 + 4, b = 2*slope*y-intercept, c = 2*y-intercept - 100
	double a = pow(line_slope, 2) + 4;
	double b = 2 * line_slope * y_intercept;
	double c = pow(y_intercept,2) - 100;
	// get the quadratic formula parts
	double numerator1 = b * -1;
	double numerator2 = sqrt(pow(b, 2) - 4 * a * c);
	double denomiator = 2 * a;
	// the 2 solutions
	double x1 = (numerator1 + numerator2) / denomiator;
	double x2 = (numerator1 - numerator2) / denomiator;
	// x's plugged into the line formula to get corresponding y
	double y1 = x1 * line_slope + y_intercept;
	double y2 = x2 * line_slope + y_intercept;
	
	// get the point that is not similar to the parameter point (may need some room for precision loss)
	if (point != Coord(x1, y1)) {
		return Coord(x1, y1);
	}
	else {
		return Coord(x2,y2);
	}
}

Coord getNextImpactPoint(const Coord start_point, const Coord end_point) {
	double tangent_line_slope = getTangentLine(end_point);
	double start_laser_line_slope = getSlope(start_point, end_point);
	double next_line_slope = getReflectionSlope(start_laser_line_slope, tangent_line_slope);
	return getOtherIntersectPoint(end_point, next_line_slope);
}

int p144() {
	Coord entry_point(0, 10.1);

	Coord start_point = entry_point;
	Coord next_impact_point(1.4, -9.6);

	int total_reflections = 0;
	while (true) {
		total_reflections++;
		cout << "Hit " << next_impact_point.toStr() << "Hits: " << total_reflections << endl;
		Coord next_point = getNextImpactPoint(start_point, next_impact_point);
		start_point = next_impact_point;
		next_impact_point = next_point;

		// get next point as long as we dont hit the missing top section
		if (next_impact_point.y > 0 && next_impact_point.x >= -0.01 && next_impact_point.x <= 0.01) {
			cout << "Exiting at: " << next_impact_point.toStr() << endl;
			break;
		}
	}

	return total_reflections;
}