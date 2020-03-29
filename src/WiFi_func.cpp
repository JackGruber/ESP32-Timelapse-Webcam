#include "Arduino.h"
#include "WiFi_func.h"
#include "WiFi.h"
#include "wifi_credentials.h"

const char* STA_SSID = WIFI_SSID;
const char* STA_PASSWORD = WIFI_PASSWORD;
const char* AP_SSID = WIFI_AP_SSID;
const char* AP_PASSWORD = WIFI_AP_PASSWORD;

void WiFiInit(void)
{
  Serial.println("WiFi connected");
  if(WiFiDetermineMode() == 1)
  {
    WiFiConnectSTA();
  }
  else
  {
    WiFiCreateAP();
  }
}

void WiFiConnectSTA(void)
{
  Serial.print("Connect WiFi ..");

  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID, STA_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("=======================================");
  Serial.println("WiFi connected");
  Serial.print("ESP32 MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("IP Subnetmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.println("=======================================");
}

void WiFiCreateAP(void)
{
  Serial.println("Starting AP ...");

  IPAddress apIP(192,168,4,22);
  IPAddress gateway(192,168,4,9);
  IPAddress subnet(255,255,255,0);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, gateway, subnet);

  if (!WiFi.softAP(AP_SSID, AP_PASSWORD, 1, 0))
  {
      Serial.println("AP Config failed.");
      return;
  }
  else
  {
      Serial.println("=======================================");
      Serial.println("AP Config Success.");
      Serial.print("AP MAC: ");
      Serial.println(WiFi.softAPmacAddress());

      IPAddress ip = WiFi.softAPIP();
      Serial.print("IP Address: ");
      Serial.println(ip);

      Serial.print("AP Name: ");
      Serial.println(AP_SSID);

      Serial.print("AP Password: ");
      Serial.println(AP_PASSWORD);
      Serial.println("=======================================");
  }
}

// 0 = AP Mode, 1 = STA Mode
int WiFiDetermineMode(void)
{
  Serial.println("WiFi Scan start ...");

  // WiFi.scanNetworks will return the number of networks found
  int number_ssid = WiFi.scanNetworks();
  Serial.println("Scan complete :)");
  
  if (number_ssid == 0)
  {
    Serial.println("No networks found :(");
    return 0;
  } 
  else 
  {
    Serial.print(number_ssid);
    Serial.println(" networks found:");
    for (int i = 0; i < number_ssid; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
      if (WiFi.SSID(i).equals(STA_SSID)) 
      {
        return 1;
      }
    }
  }

  return 0;
}