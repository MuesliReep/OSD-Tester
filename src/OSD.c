#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Config.h"
#include "Telemetry.h"
#include "OSD.h"
#include "Graphics.h"


void updateOSD(int8_t grid[][yres], struct TelemetryData * data) {

    //Init graphics
    initialiseGraphics();

    //Display craft attitude information
    drawAttitude(grid, &data->attitude);

    //Display compass/radar
    drawCompassRadar(grid,&data->position);

    //Display GPS coordinates
    drawGPSCoordinates(grid,&data->position);

    char buffer[3];
    snprintf (buffer,4,"%d",data->attitude.pitch);
    drawString(20,20,5,0,buffer,3,grid);

    //showBattery
    //showFlightTime
    //showRSSI
}

void drawAttitude(int8_t grid[][yres], struct Attitude * attitude) {
    //TODO: these variables should be in the config file
    int t = lineThickness; //Thickness -> should be in user config
    int l = 30; //Horizon line length

    //TODO: Craft center should be a vector
    //Start with drawing the craft center
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

    //Now draw the horizon
    //First we find the base starting point of the right side of the horizon
    //which will be rotated by the crafts roll

    int angle = attitude->roll;
    int A = 0;
    int B = 0;
    int C = 7*t; //Horizon offset from center
    int AB = 90;
    int AC = 180-AB-angle;
    int BC = angle;

    calcTriangleSides_int(&A,&B,&C,&AB,&AC,&BC);

    int baseX = B;
    int baseY = A;

    //Next we must find the offset due to pitch angle
    int pitchMX = yres / vSteps; //Pitch multiplier(Number of pixels per pitch angle degree)

    angle = attitude->roll + 90;
    A = 0;
    B = 0;
    C = pitchMX * attitude->pitch;
    AB = 90;
    AC = 180-AB-angle;
    BC = angle;

    calcTriangleSides_int(&A,&B,&C,&AB,&AC,&BC);

    int horizonOffsetX = B;
    int horizonOffsetY = A;

    //The horizon can now be drawn
    int rightX = xres /2 + baseX - horizonOffsetX;
    int rightY = yres /2 - baseY + horizonOffsetY;

    drawLine(rightX,rightY,t,attitude->roll, l*2, grid);
    //Flip the values to draw the left side
    int leftX = xres /2 - baseX - horizonOffsetX;
    int leftY = yres /2 + baseY + horizonOffsetY;

    drawLine(leftX,leftY,t,attitude->roll + 180, l*2, grid);

    //Next we will calculate the positive pitch ladder steps
    //First the distance between the ladder steps needs to be calculated

    angle = attitude->roll + 90;
    A = 0;
    B = 0;
    C = pitchMX * vStepSize;
    AB = 90;
    AC = 180-AB-angle;
    BC = angle;

    calcTriangleSides_int(&A,&B,&C,&AB,&AC,&BC);
    int Astep = A; int Bstep = B;

    //Calculate the end point of the ladder step
    angle = attitude->roll;
    A = 0;
    B = 0;
    C = l;
    AB = 90;
    AC = 180-AB-angle;
    BC = angle;

    calcTriangleSides_int(&A,&B,&C,&AB,&AC,&BC);
    int AstepEnd = A; int BstepEnd = B;

    //For each positive pitch ladder step draw a line
    int pitchSteps = 180 / vStepSize; //Calculate the number of ladder steps
    int lastRX = rightX; int lastRY = rightY; //These variables are used to store the last ladder step position
    int lastLX = leftX;  int lastLY = leftY;
    for(int x=0;x < pitchSteps; x++) {
        //Draw right side
        lastRX += Bstep;
        lastRY -= Astep;
        drawLine(lastRX,lastRY,t,attitude->roll,l,grid);

        //Draw left side
        lastLX += Bstep;
        lastLY -= Astep;
        drawLine(lastLX,lastLY,t,attitude->roll+180,l,grid);
        //drawPoint(lastLX,lastLY,1,grid);

        //For each pitch ladder step draw a line towards horizon
        drawLine(lastRX+BstepEnd,lastRY-AstepEnd,t,attitude->roll-90,l/4,grid);
        drawLine(lastLX-BstepEnd,lastLY+AstepEnd,t,attitude->roll-90,l/4,grid);

        //For each pitch ladder step draw the number of degrees next to it
        char buffer[4];
        snprintf (buffer,5,"%d",x*vStepSize);
        drawString(lastRX+BstepEnd,lastRY-AstepEnd,4,0,buffer,4,grid);

        //TODO: memset buffer to -1
        //TODO: Improve text alignment with the pitch ladder step
        //TODO: Add option to rotate the text
    }


    //Finally calculate the negative pitch ladder steps
    lastRX = rightX; lastRY = rightY;
    lastLX = leftX;  lastLY = leftY;
    for(int x=0;x < pitchSteps; x++) {

        //Draw right side
        lastRX -= Bstep;
        lastRY += Astep;
        drawLine(lastRX,lastRY,t,attitude->roll,l/3,grid);
        drawLine(lastRX+BstepEnd,lastRY-AstepEnd,t,attitude->roll,l/3,grid);

        //Draw left side
        lastLX -= Bstep;
        lastLY += Astep;
        drawLine(lastLX,lastLY,t,attitude->roll+180,l/3,grid);
        drawLine(lastLX-BstepEnd,lastLY+AstepEnd,t,attitude->roll+180,l/3,grid);

        //For each pitch ladder step draw a line towards horizon
        drawLine(lastRX,lastRY,t,attitude->roll+90,l/4,grid);
        drawLine(lastLX,lastLY,t,attitude->roll+90,l/4,grid);

        //For each pitch ladder step draw the number of degrees
        char buffer[4];
        snprintf (buffer,5,"%d",x*vStepSize);
        drawString(lastRX+BstepEnd,lastRY-AstepEnd,4,0,buffer,4,grid);
    }

}

void drawCompassRadar(int8_t grid[][yres], struct Position * position) {

    int edgeDistance = 10; //Distance to edge of the screen. (Should be in config)

    //Calculate compass center position
    int centerX = xres - edgeDistance - compassRadius;
    int centerY = 0 + edgeDistance + compassRadius;

    //Draw outer ring
    plotCircle(centerX, centerY, compassRadius, grid);

    //Draw inner ring
    plotCircle(centerX, centerY, compassRadius/2, grid);

    //Draw compass notches
    //Calculate angle to north first
    int angle = 90 - position->heading;
    int A = 0;
    int B = 0;
    int C = compassRadius-5;
    int AB = 90;
    int AC = 180-AB-angle;
    int BC = angle;

    calcTriangleSides_int(&A,&B,&C,&AB,&AC,&BC);

    //Draw every notch
    int notches     = 4;
    int notchStep   = 360/notches;
#ifdef compassSubNotch
    bool subNotch = true;
    notches     *= 2;
    notchStep   *= 2;
#endif
    for(int x=0; x<notches; x++) {

        int notchLength = 5;
#ifdef compassSubNotch
        if(subNotch == true)
            notchLength /= 2;
#endif
        angle += notchStep;
        A = 0;
        B = 0;
        AC = 180-AB-angle;
        BC = angle;
        calcTriangleSides_int(&A,&B,&C,&AB,&AC,&BC);

        drawLine(centerX+B,centerY-A,1,angle,notchLength,grid);

        //TODO: Draw compass letters
        //drawCharacter(centerX+B, centerY-A, 4, 0, 78, grid);

#ifdef compassSubNotch
        if(subNotch == true)
            subNotch = false;
        else
            subNotch = true;
#endif
    }

#ifdef compassViewAngle
    int viewAngle = 90; //TODO: in config based on camera

    drawLine(centerX, centerY, 1, 90-viewAngle/2, compassRadius, grid);
    drawLine(centerX, centerY, 1, 90+viewAngle/2, compassRadius, grid);

#endif

    //TODO: make heading optional
    //Display the current heading
    //TODO: Draw below compass circle plus height of font in center. Will need new graphics functions
}

void drawBatteryInfo(int8_t grid[][yres], struct Battery * battery) {

    char buffer[5];

    //TODO: convert voltage to float then to char, eg: 127 = 12.7v

    buffer[0] = (int)"1";
    buffer[1] = (int)"2";

    drawString(battPosX,battPosY,1,0,buffer,5,grid);

    //TODO: calculate mah usage to find battery percentage
}

void drawGPSCoordinates(int8_t grid[][yres], struct Position * position) {

  //convert int32 to float
  float latitude = (float)position->latitude;
  float longitude = (float)position->longitude;

  char buffer[10];
  snprintf (buffer,10,"%f",latitude);
  //TODO: fill buffer with lat data

  //Draw latitude coordinate
  drawString(positionPosX,positionPosY,5,0,buffer,10,grid);

  //TODO: fill buffer with long data

  //Draw longitude coordinate
  drawString(positionPosX,positionPosY+20,5,0,buffer,10,grid);
}
