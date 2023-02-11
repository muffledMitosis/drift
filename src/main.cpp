#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 4,5);
}

void loop()
{
  Serial1.println("LOL");
  while(Serial1.available())
  {
    Serial.print(Serial1.read());
  }
  delay(1000);
}