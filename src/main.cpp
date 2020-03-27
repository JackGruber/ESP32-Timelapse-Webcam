#include <Arduino.h>
#include "camera.h"
#include "WiFi_func.h"
#include "SD.h"

void setup() 
{
  Serial.begin(115200);
	Serial.println();

  SDInitFileSystem();
  CameraInit();

  WiFiInit();  
}

void loop() 
{
  
}
