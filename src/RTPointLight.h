#pragma once
#include "rtlight.h"
class RTPointLight :
	public RTLight
{
public:
	RTVector center;
	RTColor color;
	double intensity;
	RTPointLight(void);
	~RTPointLight(void);
	RTPointLight(RTVector newCenter, RTColor newColor, double newIntensity);
	virtual RTVector getCenter();
	virtual RTColor getColor();
	virtual double getIntensity();
};

