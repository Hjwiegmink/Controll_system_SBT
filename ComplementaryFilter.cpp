/* 
 * File:   ComplementaryFilter.cpp
 * Author: arjan
 * 
 * Created on 1 maart 2019, 11:49
 */

#include "ComplementaryFilter.h"
#include <stdio.h>      /* printf */
#include <math.h>       /* sin */
// in 2 angles from the sensors, roll from xsens, acceleration from xsens and out 1 roll , 1 hoogte 
ComplementaryFilter::ComplementaryFilter() {
   
}

ComplementaryFilter::ComplementaryFilter(const ComplementaryFilter& orig) {
}

ComplementaryFilter::~ComplementaryFilter() {
}

float ComplementaryFilter::CalculateRealHeight(float angle_left, float angle_right, float accel_z, float Xsens_roll)
{
  

   float Length_vlotter=0.7;
   float height_left=0;
   float height_right=0;
   float roll_front=0;
   float distance_between_vlotters=1.3;
   float real_roll=0;
   float real_height=0;
   float height_xsens=0;
   float dt=0.1;
   
   height_left=sin(angle_left*3.14/180)*Length_vlotter;
   height_right=sin(angle_right*3.14/180)*Length_vlotter;
   roll_front=tan(height_left-height_right/distance_between_vlotters);
   height_xsens=accel_z*pow(dt,2);
   real_roll=(roll_front+Xsens_roll)/2;
   real_height=(height_left+height_right+height_xsens)/3;
   
return real_height,real_roll;
        
}           