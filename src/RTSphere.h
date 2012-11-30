#pragma once
#include "RTObject.h"
#include "RTVector.h"
#include "RTtexture.h"
class RTSphere :
	public RTObject
{
public:
	RTSphere(RTVector newCenter, double radius, RTtexture newTexture);
	~RTSphere(void);
	RTSphere(void);
	RTtexture texture;
	RTVector center;
	double radius;
	bool intersects(RTRay ray, double & t);
	RTAppearance getAppearance(RTVector pt);
	RTVector getIntersection(double t);
	RTVector getCenter( );
	RTVector getNormal(RTVector point);

};

