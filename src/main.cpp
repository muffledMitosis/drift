#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 4,5);

  Serial1.println("AT");
  delay(1000);
  Serial1.println("AT+CGNSPWR=1");
  delay(1000);
}

void loop()
{
  Serial1.println("AT+CGNSINF");
  delay(1000);
  if(Serial1.available())
  {
    String res = Serial1.readString();
    Serial.println(res);
  }
}