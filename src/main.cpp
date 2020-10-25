#include <Arduino.h>
#include "camera.h"
#include "WiFi_func.h"
#include "SD.h"
#include "TimeLapse.h"
#include "HTTPApp.h"
#include "version.h"
#include "version_build.h"
#include "Pref.h"


bool STOP_RESET = false;
unsigned long ESP_RESTART = 0;

void setup() 
{
  Serial.begin(115200);
  Serial.println("ESP32 Timelapse Webcam");
  Serial.println("Sketch: " VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH "." BUILD_COMMIT "-" BUILD_BRANCH);
  Serial.println("Builddate: " BUILD_DATE " " BUILD_TIME);

  if(DEEPSLEEP_TIMELAPSE != true) 
  {
    if (PrefLoadInt("clearsettings",1,true)) { PrefClear(); }
    PrefSaveInt("clearsettings",1 , true);
  }

  SDInitFileSystem();
  CameraInit();
  if(CameraLoadSettings()) { Serial.println("Setting Load OK"); };

  if(DEEPSLEEP_TIMELAPSE == true) 
  { 
    Serial.println("DEEPSLEEP_TIMELAPSE");
    TimeLapseProcess(); 
  }

  WiFiInit();

  HTTPAppStartCameraServer();
}

void loop() 
{
	TimeLapseProcess();
  if(millis() > 1000*10 && STOP_RESET == false) 
  { 
    Serial.println("Stop config reset on boot");
    PrefSaveInt("clearsettings",0 , true); 
    STOP_RESET = true;
  }

  if(ESP_RESTART != 0 && millis() > ESP_RESTART)
  {
    ESP.restart();
  }
}
