#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "Config.h"
#include "Telemetry.h"
#include "OSD.h"
#include "Graphics.h"


void updateOSD(int8_t grid[][yres], struct TelemetryData * data) {
    
    //Display craft attitude information
    drawAttitude(grid, &data->attitude);
    
    
    //showCompasRadar();
    //showGPS
}

void drawAttitude(int8_t grid[][yres], struct Attitude * attitude) {
    
    int t = lineThickness; //Thickness -> should be in user config
    int l = 20; //Line length
    
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
    //End craft center

	//Draw horizon
	
    //Find left and right sides of horizon   
    int angle = 90 - attitude->roll;
    int A = 0;
    int B = 0;
    int C = 5*t-1; //Horizon offset from center
    int AB = 90;
    int AC = 180-angle;
    int BC = angle;
    
    calcTriangleSides(&A,&B,&C,&AB,&AC,&BC);
    
    int rightX = xres /2 + B;
    int rightY = yres /2 - A;
    
    drawLine(rightX,rightY,t,angle, l, grid);
    
    //Flip right side to get left side
    //use Negative value
    int leftX = xres /2 - B;
    int leftY = yres /2 + A;

    drawLine(leftX,leftY,t,angle +180, l, grid);

    //setPixel(grid,xres/2-B,yres/2+A);

    //check if horizon is on screen
    attitude->pitch > vSteps / 2;
	
    //Hier moet ook abc formule voor horizon plaatsing
    //Find where the horizon starts...
    
	//Draw positive steps
    //Divide screen into vStepSize
    
    //Draw negative steps
}
