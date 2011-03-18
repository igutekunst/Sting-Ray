#include "RTAppearance.h"


RTAppearance::RTAppearance(RTColor newColor, double newOpacity,double theReflectivity,double theSpecular,double theSpecularPower,double theBlinn )
{
	color = newColor;
	opacity = newOpacity;
	reflectivity = theReflectivity;
	specular = theSpecular;
	blinn = theBlinn;
	specularPower = theSpecularPower;
}

RTAppearance::RTAppearance()
{
	color = RTColor();
	opacity = 1;
}


RTAppearance::~RTAppearance(void)
{
}
