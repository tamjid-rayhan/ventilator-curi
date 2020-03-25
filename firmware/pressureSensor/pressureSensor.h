/*Library for reading pressure sensor MPX5050DP
 * Created by Md. Tamjid Rayhan , March 25, 2020
 * Released into public domain
 */

#ifndef pressureSensor_h
#define pressureSensor_h

#include "Arduino.h"

class pressureSensor
{
  public:
    pressureSensor(int pin);
    double readCmWater();

  private:
    int read();
    int _pin;
};

#endif