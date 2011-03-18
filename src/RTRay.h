#pragma once
#include "RTVector.h"
class RTRay
{
public:
	RTVector point;
	RTVector dir;
	RTRay(void);
	RTRay(RTVector point, RTVector dir);
	~RTRay(void);
};

