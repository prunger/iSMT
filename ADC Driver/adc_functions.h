//Functions file for adc.c

void init(void);
void readADC(void);
void getData(int);
uint16_t changeToInt(void);
float convertToVoltage(uint16_t);
float convertToHumidity(float);
float convertToTemperature(float);
void writeToFile(uint16_t, float, int);

extern FILE * fileOut;
extern unsigned char buffer[BUFFER_SIZE];
extern float prevMillis;
extern float tempSensorCommonVoltage;

//Initialize WiringPi, SPI, & GPIO
void init(void){
  wiringPiSetup();
  wiringPiSPISetup(SPI_CHNL, SPI_CLK);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  return;
}

//Calls getData() to read analog inputs from the ADC if they're enabled (enable/disable in macros file)
void readADC(void){
  if(CH0_EN) getData(CH0);
  if(CH1_EN) getData(CH1);
  if(CH2_EN) getData(CH2);
  if(CH3_EN) getData(CH3);
  if(CH4_EN) getData(CH4);
  if(CH5_EN) getData(CH5);
  if(CH6_EN) getData(CH6);
  if(CH7_EN) getData(CH7);
  return;
}

//Loads hexadecimal values into buffer[] to enable reading of one of the eight analog inputs, initiates
//SPI communication with the ADC, then calls functions to process recieved data and write data to files
void getData(int channelNumber){
  uint16_t ADCVal;
  float voltage;
	buffer[0] = BUF_ZERO;
  switch (channelNumber){
    case CH0:
      buffer[1] = CH0_BUF_ONE;
      break;
    case CH1:
      buffer[1] = CH1_BUF_ONE;
      break;
    case CH2:
      buffer[1] = CH2_BUF_ONE;
      break;
    case CH3:
      buffer[1] = CH3_BUF_ONE;
      break;
    case CH4:
      buffer[1] = CH4_BUF_ONE;
      break;
    case CH5:
      buffer[1] = CH5_BUF_ONE;
      break;
    case CH6:
      buffer[1] = CH6_BUF_ONE;
      break;
    case CH7:
      buffer[1] = CH7_BUF_ONE;
      break;
  }
	buffer[2] = BUF_TWO;
	digitalWrite(CS_PIN, LOW);
	wiringPiSPIDataRW (SPI_CHNL, buffer, BUFFER_LENGTH);
	digitalWrite(CS_PIN, HIGH);
  ADCVal = changeToInt();
  voltage = convertToVoltage(ADCVal);
  writeToFile(ADCVal, voltage, channelNumber);
	return;
}

//Takes the two 8-bit analog values returned by the ADC and converts them into one 16-bit integer
uint16_t changeToInt(void){
  uint16_t ADCInt;
  int bufOne;
	int bufTwo;
	bufOne = (int)buffer[1];
	bufTwo = (int)buffer[2];
	ADCInt = (bufOne << L_SHIFT_EIGHT) | bufTwo;
	return ADCInt;
}

//Takes the 16-bit integer and converts it to a corresponding voltage
//The 'VOLTAGE_CONVERSION' macro needs to be changed to accomodate the ADC's reference
//See macros file for more info
float convertToVoltage(uint16_t data){
  return (data*VOLTAGE_CONVERSION);
}

float convertToHumidity(float voltage){
  return ((38.92*voltage) - 42.017);
}

float convertToTemperature(float thermistorVoltage){
  float thermistorCurrent = ((tempSensorCommonVoltage - thermistorVoltage)/RESISTANCE_FIXED);
  float thermistorResistance = (thermistorVoltage/thermistorCurrent);
  float kelvin = (B_COEFF/(log(thermistorResistance/R_INF)));
  float celcius = (kelvin - 273.15);
  float fahrenheit = ((celcius*1.8) + 32);
  return fahrenheit;
}

//Writes the ADC's digital output code & voltage conversion to a file with a name corresponding
//to the input channel. The file name and write type can be changed in the macros file
//See macros file for more info
void writeToFile(uint16_t data, float voltage, int channelNumber){
  switch (channelNumber){
    case CH0:
      fileOut = fopen(CH0_FILENAME, WRITE_TYPE);
      tempSensorCommonVoltage = voltage;
      fprintf(fileOut, "Temperature sensor common voltage: %.2f V\n", voltage);
      break;
    case CH1:
      fileOut = fopen(CH1_FILENAME, WRITE_TYPE);
      //fprintf(fileOut, "Duct temperature: %.1f F\n", convertToTemperature(voltage));
      fprintf(fileOut, "%.1f\n", convertToTemperature(voltage));
	printf("Duct temperature: %.1f F\n", convertToTemperature(voltage));
	break;
    case CH2:
      fileOut = fopen(CH2_FILENAME, WRITE_TYPE);
      //fprintf(fileOut, "Ambient temperature: %.1f F\n", convertToTemperature(voltage));
      fprintf(fileOut, "%.1f\n", convertToTemperature(voltage));
	printf("Ambient temperature: %.1f F\n", convertToTemperature(voltage));
      break;
    case CH3:
      fileOut = fopen(CH3_FILENAME, WRITE_TYPE);
      //fprintf(fileOut, "Duct relative humidity: %.1f %%\n", convertToHumidity(voltage));
      fprintf(fileOut, "%.1f\n", convertToHumidity(voltage));
	printf("Duct relative humidity: %.1f %%\n", convertToHumidity(voltage));
      break;
    case CH4:
      fileOut = fopen(CH4_FILENAME, WRITE_TYPE);
      //fprintf(fileOut, "Ambient relative humidity: %.1f %%\n", convertToHumidity(voltage));
      fprintf(fileOut, "%.1f\n", convertToHumidity(voltage));
	printf("Ambient relative humidity: %.1f %%\n\n", convertToHumidity(voltage));
      break;
    case CH5:
      fileOut = fopen(CH5_FILENAME, WRITE_TYPE);
      fprintf(fileOut, "Digital output code: %d, Measured voltage: %.3f\n", data, voltage);
      break;
    case CH6:
      fileOut = fopen(CH6_FILENAME, WRITE_TYPE);
      fprintf(fileOut, "Digital output code: %d, Measured voltage: %.3f\n", data, voltage);
      break;
    case CH7:
      fileOut = fopen(CH7_FILENAME, WRITE_TYPE);
      fprintf(fileOut, "Digital output code: %d, Measured voltage: %.3f\n", data, voltage);
      break;
  }
  fclose(fileOut);
  return;
}
