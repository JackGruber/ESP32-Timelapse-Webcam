#include <Arduino.h>
#include "camera.h"
#include "WiFi_func.h"

void setup() 
{
  Serial.begin(115200);
	Serial.println();

  CameraInit();

  WiFiInit();  
}

void loop() 
{
  
}
