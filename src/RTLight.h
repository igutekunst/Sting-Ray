#pragma once
#include "RTVector.h"
#include "RTColor.h"
class RTLight
{
public:
	RTLight(void);
	~RTLight(void);

	virtual RTVector getCenter();
	virtual RTColor getColor();
	virtual double getIntensity();
};

