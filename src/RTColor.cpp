#include "RTColor.h"
#include <math.h>

RTColor::RTColor(double newR, double newG, double newB)
{
	r = newR;
	g = newG;
	b = newB;
}

RTColor::RTColor(void){

}

RTColor::~RTColor(void)
{
}


RTColor  RTColor::add(RTColor other)
{
	return RTColor(r+other.r, g + other.g, g+other.g);
	
}

RTColor  RTColor::sub(RTColor other )
{
	return RTColor(r-other.r, g -other.g, b-other.b);
}




RTColor RTColor::scale(double scalar)
{
	return RTColor(scalar*r,scalar*g,scalar* b);
}

double RTColor::magnitude()
{
	return sqrt(r*r+g*g+b*b);
}

RTColor RTColor::normal()
{
	RTColor toNormalize = *this;
	return RTColor(toNormalize.scale(1/toNormalize.magnitude()));
}