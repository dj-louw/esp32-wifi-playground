#include <Arduino.h>
#include "WiFi.h"

#include "credentials.h"
#include "eventNames.h"

bool wifi_connected; // Wifi Connect Flag

void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{

  Serial.println();
  Serial.print(eventName[event]);
  Serial.print(" ");

  switch (event)
  {
  case SYSTEM_EVENT_STA_DISCONNECTED:
    Serial.print(info.wifi_sta_disconnected.reason);
    // Serial.println("trying to reconnect...");
    // WiFi.begin(WIFI_SSID, WIFI_PASS);
    wifi_connected = false;
    break;
  case SYSTEM_EVENT_STA_CONNECTED:
    Serial.println("Yay!");
    wifi_connected = true;
    break;
  default:
    break;
  }
  Serial.println();
}

void setup()
{
  WiFi.setHostname("WIFI_TEST_BENCH");
  Serial.begin(115200);
  WiFi.onEvent(WiFiEvent);
  WiFi.mode(WIFI_STA);

  WiFi.disconnect(false, true);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait for connection
  int timer = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(timer++);
    if (timer >= 60) // restart the board after one minute.
      ESP.restart();
  }
}

void loop()
{
  if (wifi_connected)
  {
    Serial.println("Wifi Connected");
    Serial.println(WiFi.localIP());
    delay(1000);
  }
  else
  {
    ESP.restart();
  }
}