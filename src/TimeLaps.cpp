#include "Arduino.h"
#include "esp_camera.h"
#include <stdio.h>
#include "SD.h"

unsigned int fileIndex = 0;
unsigned int lapseIndex = 0;
unsigned long TIMELAPSINTERVAL = 1;
bool mjpeg = true;
bool lapseRunning = false;
unsigned long nexttimelaps = 0;

void TimeLapsSetInterval(unsigned long interval)
{
    TIMELAPSINTERVAL = interval;
}

bool TimeLapsStart()
{
    if(lapseRunning) return true;
    fileIndex = 0;
    char path[32];
    for(; lapseIndex < 10000; lapseIndex++)
    {
        sprintf(path, "/lapse%03u", lapseIndex);
        if (!SDFileExists(path))
        {
            SDCreateDir(path);
            lapseRunning = true;
            return true;
        }
    }
	return false;
}

bool TimeLapsStop()
{
    lapseRunning = false;
    return true;
}

bool TimeLapsProcess()
{
    if(!lapseRunning) return false;
    if(nexttimelaps >  millis() ) return false;
    nexttimelaps = millis() + (1000 * TIMELAPSINTERVAL);

    camera_fb_t *fb = NULL;
    fb = esp_camera_fb_get();
    if (!fb)
    {
        Serial.println("Camera capture failed");
        return false;
    }

    char path[32];
    sprintf(path, "/lapse%03u/pic%05u.jpg", lapseIndex, fileIndex);
    Serial.println(path);
    if(!SDWriteFile(path, (const unsigned char *)fb->buf, fb->len))
    {
        lapseRunning = false;
        return false;
    }
    fileIndex++;
    esp_camera_fb_return(fb);

    return true;
}
