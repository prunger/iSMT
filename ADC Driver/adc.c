//Main file for adc.c
//Reads the 8 analog inputs of the MCP3008 and writes the data to a file for each channel
//Read interval, file output names, and active channels can be configured in 'adc_macros.h'
//Compile with gcc -Wall -o adc adc.c -lwiringPi -lm
//Last modified: 03/10/2020

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include "adc_macros.h"
#include "adc_functions.h"

FILE * fileOut;
unsigned char buffer[BUFFER_SIZE];
float prevMillis;
float tempSensorCommonVoltage;
int counter = 0;

int main(void){
  init();
  while (ALWAYS){
    if(millis() >= (prevMillis + READ_INTERVAL)){
      if(counter >= 1000) break;
      readADC();
      prevMillis = millis();
      counter++;
    }
  }
  return EXIT_SUCCESS;
}
