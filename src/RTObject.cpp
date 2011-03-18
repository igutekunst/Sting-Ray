#include "RTObject.h"
#include "RTAppearance.h"

RTObject::RTObject(void)
{
}


RTObject::~RTObject(void)
{
}

 RTAppearance  RTObject::getAppearance(RTVector pt){
	return RTAppearance();
}

RTVector RTObject::getIntersection(double t){
	return RTVector();
}

RTVector RTObject::getCenter( )
{
	return RTVector();
}


bool RTObject::intersects(RTRay newRay, double & t)
{

	return true;

}


 RTVector RTObject::GetNormal( RTVector point)
{

	return RTVector();

}
