#include <Arduino.h>
#include <rtspstream.h>

#include <WebServer.h>
#include <CStreamer.h>
#include "SimStreamer.h"
#include <CRtspSession.h>
#include <OV2640Streamer.h>
#include "OV2640.h"

WiFiServer rtspServer(554);
WiFiClient rtspClient;

/** Stream for the camera video */
CStreamer *streamer = NULL;
/** Session to handle the RTSP communication */
CRtspSession *session = NULL;

OV2640 cam;

void RTSPStreamIni(void)
{
    rtspServer.begin();
    rtspServer.setTimeout(1);
    //cam.init(esp32cam_aithinker_config);
    Serial.print("RTSP Stream: ");
    Serial.print("rtsp://");
    Serial.print(WiFi.localIP());
    Serial.print(":554/mjpeg/1");
}

void RTSPStream(void)
{
   	uint32_t msecPerFrame = 500;
	static uint32_t lastimage = millis();

    // If we have an active client connection, just service that until gone
    if (session)
    {
        session->handleRequests(0); // we don't use a timeout here,
        // instead we send only if we have new enough frames

        uint32_t now = millis();
        if (now > lastimage + msecPerFrame || now < lastimage)
        { // handle clock rollover
            session->broadcastCurrentFrame(now);
            lastimage = now;
        }

        // Handle disconnection from RTSP client
        if (session->m_stopped)
        {
            Serial.println("RTSP client closed connection");
            delete session;
            delete streamer;
            session = NULL;
            streamer = NULL;
        }
    }
    else
    {
        rtspClient = rtspServer.accept();
        // Handle connection request from RTSP client
        if (rtspClient)
        {
            Serial.println("RTSP client started connection");
            streamer = new OV2640Streamer(&rtspClient, cam); // our streamer for UDP/TCP based RTP transport

            session = new CRtspSession(&rtspClient, streamer); // our threads RTSP session and state
            delay(100);
        }
    }
}