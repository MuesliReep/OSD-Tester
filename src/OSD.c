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
    int l = 30; //Horizon line length
    
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
    int angle = attitude->roll;
    int A = 0;
    int B = 0;
    int C = 7*t; //Horizon offset from center
    int AB = 90;
    int AC = 180-AB-angle;
    int BC = angle;
    
    calcTriangleSides(&A,&B,&C,&AB,&AC,&BC);

    //Adjust for pitch angle
    int offset = yres / vSteps;
    int pitch = attitude->pitch * offset;

    //Draw right horizon
    int rightX = xres /2 + B;
    int rightY = yres /2 - A + pitch;
    
    drawLine(rightX,rightY,t,angle, l, grid);
    
    //Draw left horizon
    //Flip right side to get left side
    int leftX = xres /2 - B;
    int leftY = yres /2 + A + pitch;

    drawLine(leftX,leftY,t,angle +180, l, grid);

    //Draw pitch positive steps

    //Calculate angle from horizon
    angle += 90; //90 degrees from horizon
    A = 0;
    B = 0;
    C = offset * vStepSize;
    AB = 90;
    AC = 180 - AB - angle;
    BC = angle;

    calcTriangleSides(&A,&B,&C,&AB,&AC,&BC);
    int Astep = A; int Bstep = B;

    //Calculate pitch step end
    A = 0;
    B = 0;
    C = l;
    AB = 90;
    AC = 180 - AB - (angle-90);
    BC = angle - 90;

    calcTriangleSides(&A,&B,&C,&AB,&AC,&BC);
    int AstepEnd = A; int BstepEnd = B;

    //For each positive pitch step draw a line
    int pitchSteps = 180 / vStepSize;
    int lastRX = rightX; int lastRY = rightY;
    int lastLX = leftX;  int lastLY = leftY;
    for(int x=0;x < pitchSteps; x++) {
        
        //Draw right
        lastRX += Bstep;
        lastRY -= Astep;
        drawLine(lastRX,lastRY,t,angle-90,l,grid);

        //Draw left
        lastLX += Bstep;
        lastLY -= Astep;
        drawLine(lastLX,lastLY,t,angle+90,l,grid);
        //drawPoint(lastLX,lastLY,1,grid);

        //For each pitch step draw a line towards horizon
        drawLine(lastRX+BstepEnd,lastRY-AstepEnd,t,angle-180,l/4,grid);
        drawLine(lastLX-BstepEnd,lastLY+AstepEnd,t,angle-180,l/4,grid);

        //TODO: Draw pitch number
    }

    //For each negative pitch step draw a line
    lastRX = rightX; lastRY = rightY;
    lastLX = leftX;  lastLY = leftY;
    for(int x=0;x < pitchSteps; x++) {

        //Draw right
        lastRX -= Bstep;
        lastRY += Astep;
        drawLine(lastRX,lastRY,t,angle-90,l/3,grid);
        drawLine(lastRX+BstepEnd,lastRY-AstepEnd,t,angle+90,l/3,grid);

        //Draw left
        lastLX -= Bstep;
        lastLY += Astep;
        drawLine(lastLX,lastLY,t,angle+90,l/3,grid);
        drawLine(lastLX-BstepEnd,lastLY+AstepEnd,t,angle-90,l/3,grid);

        //For each pitch step draw a line towards horizon
        drawLine(lastRX,lastRY,t,angle,l/4,grid);
        drawLine(lastLX,lastLY,t,angle,l/4,grid);
        
        //TODO: Draw pitch number
    }


}
