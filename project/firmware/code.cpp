#include <Arduino.h>

float i = 0;

void setup()
{
  Serial.begin(115200);
  delay(1500);   // USB natif : laisse le temps au PC de rouvrir le port
}

void loop()
{
  i += 0.1;
  Serial.print("sin:");
  Serial.println(sin(i));
  delay(10);
}