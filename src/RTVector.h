#pragma once
#include <math.h>
class RTVector
{
public:
    double x;
    double y;
	double z;
	double r;
	double theta;
	double rho;
	RTVector(void);
	RTVector(double x, double y, double z);
	~RTVector(void);
	RTVector  add(RTVector other);
	RTVector  sub(RTVector other);
	double  dot(RTVector other);
	
	RTVector scale(double scalar);
	RTVector normal();
	RTVector normalize();

	RTVector operator-(RTVector rhs);
	RTVector operator+(RTVector rhs);
	double   operator*(RTVector rhs);
	RTVector  operator*(double rhs);
	/**
	* returns the magnitude
	*/ 
	double magnitude();
};

