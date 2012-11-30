#include <stdlib.h>
#include <stdio.h>
#include "SDL.h"
#include "vectors.h"
#include <time.h>

#include <iostream>
#include <fstream>

#include "RTColor.h"
#include "RTRay.h"

#include "RTTransformation.h"
#include "RTLight.h"
#include "RTAppearance.h"
#include "RTSphere.h"
#include "RTPointLight.h"

#define MAX_REFLECTION_DEPTH 12
#define MIN_REFLECTION_COEF 0
#define w 1280
#define h 1000
#define sw w
#define sh h
int key;
int old[w][h];
int newBoard[w][h];
int big_pixel = 10;
int paused;
int width = sw;
int height = sh;
double test;
int neighbors;
#define TICK_INTERVAL    30



//for now, scene is described here... sort of lame but seems like the simplest thing for now
RTSphere  sceneObjects[100]; 
RTPointLight lights[16];
int numLights = 1; 

int numObjects=2;


/**
* Sweet inv squaroot from quake :D
*/
float invSqrt (float x){
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}


Uint32 TimeLeft(void)
{
    static Uint32 next_time = 0;
    Uint32 now;

    now = SDL_GetTicks();
    if ( next_time <= now ) {
        next_time = now+TICK_INTERVAL;
        return(0);
    }
    return(next_time-now);
}

void setpixel(SDL_Surface *screen,int x,int y, Uint8 r, Uint8 g, Uint8 b)
{
    Uint32 color = SDL_MapRGB(screen->format, r, g, b);

    if ( SDL_MUSTLOCK(screen) ) {
        if ( SDL_LockSurface(screen) < 0 ) {
            return;
        }
    }
    switch (screen->format->BytesPerPixel) {
        case 1: { /* Assuming 8-bpp */
            Uint8 *bufp;

            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *bufp = color;
        }
        break;

        case 2: { /* Probably 15-bpp or 16-bpp */
            Uint16 *bufp;

            bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
            *bufp = color;
        }
        break;

        case 3: { /* Slow 24-bpp mode, usually not used */
            Uint8 *bufp;

            bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
            *(bufp+screen->format->Rshift/8) = r;
            *(bufp+screen->format->Gshift/8) = g;
            *(bufp+screen->format->Bshift/8) = b;
        }
        break;

        case 4: { /* Probably 32-bpp */
            Uint32 *bufp;

            bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
            *bufp = color;
        }
        break;
    }
    if ( SDL_MUSTLOCK(screen) ) {
        SDL_UnlockSurface(screen);
    }
  //  SDL_UpdateRect(screen, x, y, 1, 1);
}


void RTSetPixel(SDL_Surface *screen, int x, int y, RTColor color)
{
	double r = color.r*double(254);
	double g = color.g*254.0;
	double b =  color.b*254.0;
	setpixel(screen,x,y,r,g,b);

}
//calculates the lighting on a specific point
/**
*
*
* @param center the center of the object whos color we are calculating 
* @param point the point we are calculating color/lighting for 
*/ 
RTColor light(RTSphere object,int object_i, RTVector point)
{
	
	
	RTAppearance appearance = object.getAppearance(point);
	for(int i=0; i <numLights;i++)
	{
		RTPointLight currentLight = (RTPointLight)  lights[i];
		


		

		

		//generate a ray from the intersection point to a the current light souurce
		//is made from a vector from point to light.getCenter() normalized (for the direction) , and the point
		RTVector fromLight = point - currentLight.getCenter();
		double distance = 	fromLight.magnitude();
		RTVector dirFromLight = fromLight.normal();

		RTRay rayFromLight = RTRay(object.getCenter(),dirFromLight);
		for(int i=0; i <numObjects;i++)
		{

		
			double t = 2000.0l;
			

			if(i!=object_i){
				if(!sceneObjects[i].intersects(rayFromLight,t) )
				{
 					//finally some damn shading..
					RTVector n = object.getNormal(point);
					float lambert = (rayFromLight.dir * n) * .1;
					return RTColor(.8,.6,.1).scale(lambert);
					
				}else{

				}
			}

		
	}
	}
	return RTColor(0,0,0);
}
RTColor trace(RTRay viewRay)
{

	double best = 5000.0l;
	double t = 5000.0l;
	RTSphere object = RTSphere();

	int depth = 0;
	RTColor color = RTColor(0,0,0);

	double rCoeff = 1.0;
	do{

			// looking for first intersection
            double t =  5000.0;
            int currentObjectIndex= -1;

            for ( int i = 0; i < numObjects; ++i) 
            { 
				RTSphere current = sceneObjects[i];
                if (current.intersects(viewRay,t)) 
                {
                    currentObjectIndex = i;
					object = current;
                }
            }

            if (currentObjectIndex == -1)
                break;

			//vector ending on point of intersection.
            RTVector intersection = viewRay.point +  viewRay.dir * t; 

			//want normal at point of intersection
			RTVector n = object.getNormal(intersection);

			//want Appearance at intersection (should be renamed to Material i Think)
			RTAppearance appearance = object.getAppearance(intersection);
			
			//now loop through some lights

			for(int j = 0; j < numLights; j++)
			{
				RTPointLight currentLight = lights[j];
				RTVector toLight = currentLight.center - intersection;
				
				
				
				RTVector normToLight = toLight.normal();
				RTRay lightRay = RTRay(intersection,normToLight);	

				//think about moving on if light is reflect right back...
				double lightAngle = lightRay.dir * n;
				//elliniate lights on the wrong side of the object quickly (should work for objects besides spheres??)

				if(lightAngle <= 0.0L)
					continue;


				//reduces intensity of light by inverse square law
				double lightDist = lightRay.dir * lightRay.dir;
					{
					double temp = lightDist;
					if ( temp == 0.0L )
						continue;
					temp = invSqrt(temp);
					lightRay.dir =  lightRay.dir * temp;
					lightAngle *= temp;
					}

				//worry about shadows
				// The idea is to loop throuhg objects and see if any are blocking the current light
				bool inDarkness =  false;
				for(int k = 0; k< numObjects; k++)
				{
					if(k!=currentObjectIndex)
					{

						if(sceneObjects[k].intersects(lightRay,t)){
							inDarkness = true;
							break;
						}
					}
				}

				if(!inDarkness)
				{

					
					//do some shading, in this case lambartian
					double lambert = lightRay.dir * n;
					
					color.r  += lambert * currentLight.getColor().r * appearance.color.r; 
					color.g += lambert *  currentLight.getColor().g * appearance.color.g; 
					color.b += lambert *  currentLight.getColor().b * appearance.color.b; 

					if(color.r>1)
						color.r=1;
					if(color.g>1)
						color.g=1;
					if(color.b>1)
						color.b=1;
																							
					/*
					// do some blinn
					
					float viewAngle=  viewRay.dir * n;
					RTVector blinnDir = lightRay.dir -viewRay.dir;
					float temp = blinnDir * blinnDir;
					if(temp!=0.0f)
					{
						float blinn = invSqrt((temp) * max(lightAngle - viewAngle, 0.0f));
						blinn = rCoeff * powf(blinn,appearance.specularPower);
						color.r += blinn *appearance.specular * .7;
						color.g += blinn *appearance.specular * .7;
						color.b += blinn *appearance.specular * .7;
					}
				*/	
				}

				

			}
			
                
            


			
			
		// Move onto the next reflection
		rCoeff *= appearance.reflectivity;
        double reflection = 1.2 * (viewRay.dir * n);
        viewRay.point = intersection;
        viewRay.dir = viewRay.dir - n * reflection;


		depth++;
		
	
	}while(depth < MAX_REFLECTION_DEPTH && rCoeff > MIN_REFLECTION_COEF);

	return color;
}

int main(int argc, char *argv[])
{
	
	RTMatrix a = RTMatrix(0,2,1,1,
						4,1,2,7,
						4,5,2,1,
						7,8,2,5);
    std::cout << "Hello bitches\n";
	 RTMatrix b = a.inverse();
 SDL_Surface *surface;


 ///
 /// Defining the scene
 ///

	RTColor blue = RTColor(.1,.4,.6);
	RTColor red = RTColor(1,0,.0);
	RTColor purple = RTColor(.9,.1,.9);
	RTColor white = RTColor(1,1,1);
	RTColor sun = RTColor(1,1,.8);
	RTColor green = RTColor(0,1,0);
	RTColor cyan = RTColor(.2,1,.8);
	RTColor dark = RTColor(0,0,0);
	const double shiny = .45;
	const double dull = .1;
	const double transparent = .1;
	const double opaque = .9;
	const double dim = .3;
	const double bright = .7;

	RTtexture mirror(blue,.99,.99);

	sceneObjects[0] = RTSphere(RTVector(250,250,0),250, mirror); sceneObjects[2] = RTSphere(RTVector(750,250,0),250, mirror);
	sceneObjects[1] = RTSphere(RTVector(250,750,0),250,RTtexture(white,0,0)); sceneObjects[3] = RTSphere(RTVector(750,750,0),250,RTtexture(white,0,0));
	
	sceneObjects[4] = RTSphere(RTVector(250,250,4000),250, mirror); sceneObjects[5] = RTSphere(RTVector(750,250,400),250, mirror);
	sceneObjects[6] = RTSphere(RTVector(250,750,4000),250,RTtexture(white,0,0)); sceneObjects[7] = RTSphere(RTVector(750,750,400),250,RTtexture(white,0,0));
	
	sceneObjects[4] = RTSphere(RTVector(500,500,0),100,RTtexture(white,0,0));
	numObjects = 8;
	numLights=2;
	lights [0] = RTPointLight(RTVector(100, 1000, -1000), white, bright);
	lights [1] = RTPointLight(RTVector(100, 500, -4000), green, bright);

    surface = SDL_SetVideoMode(sw, sh, 32, SDL_SWSURFACE);
    if ( surface == NULL ) {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }
	
 //seed the initial array

	for (int y = 0; y < sh; ++y) 
	{
		for (int x = 0; x < sw; ++x) 
		{
			// genrerate a Ray

			RTVector origin = RTVector(double(x),double(y),-1000.0);
			RTVector dir    = RTVector(0.0,0.0,1.0);
			RTRay viewRay = RTRay(origin,dir);

			RTColor pixel  = trace(viewRay);
			RTSetPixel(surface,x,y,pixel);
			
		}
		SDL_UpdateRect(surface,0,0,0,0);
			SDL_GL_SwapBuffers();
       
 }

    
   
 SDL_Event event;
 int grid = 0;
 
 int left=1;//offset of viewing widow from the left in big_pixels
 
 int top=1; //offset of viewing widow from the top in big_pixels
while(1){
  

    
    
    
    
    while ( SDL_PollEvent(&event) ) {
        switch (event.type) {
         
            
            
            
                       
                break;
            case SDL_QUIT:
				exit(0);

        }
    }

    

        SDL_UpdateRect(surface,0,0,0,0);
        SDL_GL_SwapBuffers();
       SDL_Delay(5);

        
}
    
}
