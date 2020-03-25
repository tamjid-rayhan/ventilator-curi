/*Library for reading pressure sensor MPX5050DP
 * Created by Md. Tamjid Rayhan , March 25, 2020
 * Released into public domain
 */
#include "Arduino.h"
#include "pressureSensor.h"

pressureSensor :: pressureSensor( int pin)
{
_pin = pin;
}

int pressureSensor :: read()
{
return analogRead(_pin);
}

double pressureSensor :: readCmWater()
{
int adcval = read();

//convert the adc value into voltage by mapping adcval (0, 1023)
//to voltage (0,5)
double adcvolt = ((double)adcval/1023)*5;

//convert the voltage (0,5) to 
//pressure in cmH20 (0, 56.12)
//1 cmH2O = .98 kPa
double pressure = (adcvolt/5)*56.12;

return pressure;
}