#pragma once
#include "RTObject.h"
#include "RTRay.h"
#include "RTVector.h"
class RTIntersection
{
public:
	
	RTObject  * object ;
	RTVector intersection;
	
	RTIntersection(RTObject * newOBject, RTVector intersection);
	~RTIntersection(void);
};

