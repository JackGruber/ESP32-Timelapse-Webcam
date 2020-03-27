#include <WiFi.h>
#include "lapse.h"

const char* ssid = "...";
const char* password = "...";
const char* ap_password = "esp32_time_lapse"; // password to connect to this esp32 when in AP mode

void startCameraServer();

void setup()
{
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();
 
	startCameraServer();
}

void loop()
{
	unsigned long t = millis();
	static unsigned long ot = 0;
	unsigned long dt = t - ot;
	ot = t;
	processLapse(dt);
}
