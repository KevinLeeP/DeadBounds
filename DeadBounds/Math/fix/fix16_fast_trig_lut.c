#include <limits.h>
#include "fix16.h"
#include "fix16_fast_trig_lut.h"

fix16_t fix16_fast_sin(fix16_t inAngle){
  fix16_t tempAngle = inAngle % (fix16_pi << 1); //mod 2pi

  if(tempAngle < 0){
    tempAngle += fix16_pi << 1; // sin(-pi/2) => sin(3pi/2) 
  }

  fix16_t tempOut;
  if(tempAngle >= fix16_pi) { //theta > pi is in quadrants III and IV -> must be negative
		tempAngle -= fix16_pi; // sin(3pi/2) => (-)sin(pi/2)
		if(tempAngle >= (fix16_pi >> 1)){ //if theta is >= pi/2
			tempAngle = fix16_pi - tempAngle; //theta = pi - temp_angle 
    }
    //scale temp angle value (0 to pi/2 rads) to a value between (0 to 1023)
    tempAngle = (tempAngle * 1023)/ 102687;  // new angle = (tempAngle * 1023)/(1026687)
		tempOut =  -(tempAngle >= _fix16_fast_sin_lut_count ? fix16_one : fastSineLookupTable[tempAngle]);
	} else {
		if(tempAngle >= (fix16_pi >> 1)){
			tempAngle = fix16_pi - tempAngle;
    }
    tempAngle = (tempAngle * 1023)/ 102687;
		tempOut = (tempAngle >= _fix16_fast_sin_lut_count ? fix16_one : fastSineLookupTable[tempAngle]);
	}

  return tempOut;
}

fix16_t fix16_fast_cos(fix16_t inAngle){
  return fix16_fast_sin(inAngle + (fix16_pi >> 1));
}