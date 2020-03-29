#include <Arduino.h>
#include "camera.h"
#include "WiFi_func.h"
#include "SD.h"
#include "TimeLaps.h"
#include "HTTPApp.h"

void setup() 
{
  Serial.begin(115200);
  Serial.println();

  SDInitFileSystem();
  CameraInit();

  WiFiInit();

  HTTPAppStartCameraServer();
}

void loop() 
{
	TimeLapsProcess();
}
