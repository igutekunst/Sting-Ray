#pragma once
#include "RTColor.h"
class RTAppearance
{
public:
	RTAppearance();
	RTAppearance(RTColor newColor, double newOpacity,double theReflectivity,double theSpecular,double theSpecularPower,double theBlinn );
	~RTAppearance(void);
	RTColor color;
	double opacity;
	double specular;
	double reflectivity;
	double blinn;
	double specularPower;
};

