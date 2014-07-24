
#include <stdint.h>
#include <stdlib.h>

#include "Config.h"
#include "Telemetry.h"
#include "OSD.h"
#include "Graphics.h"


void updateOSD(int8_t grid[][yres], struct TelemetryData data) {
    
    //Display craft attitude information
    drawAttitude(grid);
    
    
    //showCompasRadar();
    //showGPS
}

void drawAttitude(int8_t grid[][yres]) {
    
    int t = 2; //Thickness -> should be in user config
    
    //Draw craft center
    drawPoint(xres/2,yres/2,t,grid);
	//Left
    drawPoint(xres/2-t,yres/2+t,t,grid);
    drawPoint(xres/2-t*2,yres/2+t*2,t,grid);
    drawPoint(xres/2-t*3,yres/2+t,t,grid);  
    drawPoint(xres/2-t*4,yres/2,t,grid);
    drawPoint(xres/2-t*5,yres/2,t,grid);
    
    //Right
    drawPoint(xres/2+t,yres/2+t,t,grid);
    drawPoint(xres/2+t*2,yres/2+t*2,t,grid);
    drawPoint(xres/2+t*3,yres/2+t,t,grid);
    drawPoint(xres/2+t*4,yres/2,t,grid);
    drawPoint(xres/2+t*5,yres/2,t,grid);

    
	//Draw horizon
	plotLine(xres/2+13,yres/2,xres/2+33,yres/2,grid);
    plotLine(xres/2+13,yres/2+1,xres/2+33,yres/2,grid);
	
	//Draw positive steps
    //Divide screen into 3 sections(there should always be 3 horizon lines on screen)
    
    //Draw negative steps
}

