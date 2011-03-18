#pragma once
#include "RTAppearance.h"
#include "RTVector.h"
#include "RTRay.h"

class RTObject
{
public:
	
	RTObject(void);
	~RTObject(void);
	RTAppearance getAppearance(RTVector pt);
	bool intersects(RTRay ray, double & t);
	RTVector getIntersection(double t );
	RTVector getCenter( );

	//get's the normal vector at a point define in the local coordinate system
	//TODO Implement this method, if it seems important
	RTVector GetNormal( RTVector point);

};

