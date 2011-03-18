#include "RTVector.h"


RTVector::RTVector(void)
{
}

RTVector::RTVector(double newX, double newY, double newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}
RTVector::~RTVector(void)
{
}


RTVector  RTVector::add(RTVector other)
{
	return RTVector(x+other.x, y + other.y, z+other.z);
	
}

RTVector  RTVector::sub(RTVector other )
{
	return RTVector(x-other.x, y -other.y , z-other.z);
}






RTVector RTVector::scale(double scalar)
{
	return RTVector(scalar*x,scalar*y,scalar* z);
}

double RTVector::dot(RTVector other)
{
	return x *other.x +
		   y *other.y +
		   z *other.z;
}

double RTVector::magnitude()
{
	return sqrt(x*x+y*y+z*z);
}
RTVector RTVector::normal()
{
	RTVector toNormalize = *this;
	return RTVector(toNormalize.scale(1/toNormalize.magnitude()));
}
RTVector RTVector::normalize()
{
	scale(1/ magnitude());
	return *this;
}


RTVector RTVector::operator-(RTVector rhs)
{
	return sub(rhs);
}
RTVector RTVector::operator+(RTVector rhs)
{
	return add(rhs);
}
double RTVector::operator*(RTVector rhs)
{
	return dot(rhs);
}

RTVector  RTVector::operator*(double rhs)
{
	return scale(rhs);
}