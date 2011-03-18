#pragma once
#include "RTAppearance.h"
class RTtexture
{
public:
	RTtexture(void);
	~RTtexture(void);
	RTColor color;
	double opacity;
	double reflectivity;
	RTtexture(RTColor newColor, double opacity,double reflectivity);
	RTAppearance getAppearance();
	RTAppearance getAppearance(double u, double v);
};

