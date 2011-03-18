#pragma once
#include "RTMatrix.h"
#include "RTVector.h"
#include "RTObject.h"

class RTTransformation
{
public:
private:
    RTMatrix trans_m;
	RTMatrix inv_m; // transformation matrix and its inverse
public:

	
	RTTransformation(void);
	RTTransformation(RTMatrix newTransM, RTMatrix newInvM);
	
	~RTTransformation(void);
	//Mutiply a position vector
	RTVector multiply_m_v(RTMatrix & m, RTVector & v);
	//multiply a direction vector
	RTVector multiply_m_v_dir(RTMatrix & m, RTVector & vdir);
	// transform a point
	RTVector transform_point(RTVector & pt);

	// transform a ray direction
	RTVector transform_direction(RTVector & dir);
	// transform a normal vector
	RTVector transform_normal(RTVector & nrm);

	//transform an RTObject (transforms dir and point using correct methods and returns 
	RTObject transformObject(RTObject & object);
	RTRay transformRay(RTRay & ray);
};

