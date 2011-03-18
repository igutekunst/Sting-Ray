#include "RTPointLight.h"


RTPointLight::RTPointLight(void)
{
}


RTPointLight::~RTPointLight(void)
{
}


RTPointLight::RTPointLight(RTVector newCenter, RTColor newColor, double newIntensity)
{
	center = newCenter;
	color = newColor;
	intensity = newIntensity;
}

RTVector RTPointLight::getCenter()
{
	return center;
}
RTColor RTPointLight::getColor()
{
	return color;
}
double RTPointLight::getIntensity()
{
	return intensity;
}