#include "RTSphere.h"
#include <math.h>
#include "RTMatrix.h"
#include "RTTransformation.h"
#include "RTtexture.h"
RTVector xAxis = RTVector(1,0,0);
RTVector yAxis = RTVector(0,1,0);
RTVector zAxis = RTVector(0,0,1);

RTSphere::RTSphere(void)
{
}

 RTSphere::RTSphere(RTVector newCenter, double newRadius, RTtexture newTexture)

{
	texture = newTexture;
	center = newCenter;
	radius = newRadius;
}


RTSphere::~RTSphere(void)
{
}

 RTAppearance  RTSphere::getAppearance(RTVector pt){
	RTVector fromCenter = center - pt;
	fromCenter = fromCenter.normal();

	RTVector yAxis = RTVector(0,1,0);
	double theta = fromCenter * xAxis;

	
	
	return texture.getAppearance(theta,.5);
}

RTVector RTSphere::getIntersection(double t){
	return RTVector();
}

RTVector RTSphere::getCenter( )
{
	return center;
}

 RTVector RTSphere::getNormal(RTVector point)
 {
	 //vector from center to point, then normalized
	 return (point-center).normal();
 }
bool RTSphere::intersects(RTRay newRay, double & t)
{
	
	RTVector dist =   center - newRay.point; 
    double B = newRay.dir * dist;
    double D = B*B - dist * dist + radius*radius;
    if (D < 0.0L) 
        return false; 
    double t0 = B - sqrt(D); 
    double t1 = B + sqrt(D);
    bool retvalue = false;  
    if ((t0 > 0.1f) && (t0 < t)) 
    {
        t = t0;
        retvalue = true; 
    } 
    if ((t1 > 0.1f) && (t1 < t)) 
    {
        t = t1; 
        retvalue = true; 
    }
    return retvalue; 
	/*
	//transform the ray into local coords
 	RTMatrix transform = RTMatrix(xAxis, yAxis,  zAxis, center);
	RTMatrix inverse = transform.inverse();

	RTTransformation transformation = RTTransformation(inverse,transform);
	RTRay ray = transformation.transformRay(newRay);

	 //Compute A, B and C coefficients
    double a = ray.dir.dot(ray.dir);
    
	double b = 2 * ray.dir.dot(ray.point);
    
	double c = ray.point.dot(ray.point) - (radius*radius);

    //Find discriminant
    double disc = b * b - 4 * a * c;
    
    // if discriminant is negative there are no real roots, so return 
    // false as ray misses sphere
    if (disc < 0)
        return false;

    // compute q as described above
    double distSqrt = sqrt(disc);
    double q;
    if (b < 0)
        q = (-b - distSqrt)/2.0;
    else
        q = (-b + distSqrt)/2.0;

    // compute t0 and t1
    double t0 = q / a;
    double t1 = c / q;

    // make sure t0 is smaller than t1
    if (t0 > t1)
    {
        // if t0 is bigger than t1 swap them around
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // if t1 is less than zero, the object is in the ray's negative direction
    // and consequently the ray misses the sphere
    if (t1 < 0)
        return false;

    // if t0 is less than zero, the intersection point is at t1
    if (t0 < 0)
    {
        t = t1;
        return true;
    }
    // else the intersection point is at t0
    else
    {
        t = t0;
        return true;
    }

	*/
}