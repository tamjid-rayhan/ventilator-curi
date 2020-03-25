#include <pressureSensor.h>

pressureSensor ps(A0);

void setup() {
 Serial.begin(9600);
}

void loop() {
  Serial.println(ps.readCmWater());
}
