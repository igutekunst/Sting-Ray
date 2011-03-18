#include "RTtexture.h"
#include "RTColor.h"
#include <stdlib.h>
RTtexture::RTtexture(void)
{
}

RTtexture::RTtexture(RTColor newColor, double newOpacity,double newReflectivity)
{
	color = newColor;
	opacity = newOpacity;
	reflectivity = newReflectivity;

}

RTtexture::~RTtexture(void)
{
}

RTAppearance RTtexture::getAppearance(){
	return RTAppearance(RTColor(1,0,0),1,0,0.5,.7,.3);
}
RTAppearance RTtexture::getAppearance(double u, double v){
	
	RTColor white = RTColor(1.0/u,1,u);

	RTAppearance r =  RTAppearance(color,opacity,reflectivity,0.01,.01,.01);
	return r;

}
