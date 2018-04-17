// 
// WildfootW 2018
// https://github.com/Wildfoot

#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include "DebugMacros.h"
#include "CUSTOM_SETTING.h"

class GoogleDocs_Communicate : public HTTPSRedirect
{
    private:
        // Write to Google Spreadsheet
        String url = String("/macros/s/") + GScriptId + "/dev?value=Hello";
        // Fetch Google Calendar events for 1 week ahead
        String url2 = String("/macros/s/") + GScriptId + "/exec?cal";
        // Read from Google Spreadsheet
        String url3 = String("/macros/s/") + GScriptId + "/exec?read";
        String payload_base =  "{\"command\": \"appendRow\", \"sheet_name\": \"Sheet1\", \"values\": ";
        String payload = "";
}

void setup()
{
    Serial.begin(115200);
    Serial.flush();

}

void loop()
{
////////////////////// check if WIFI still connected //////////////////////
    while(WiFi.status() != WL_CONNECTED) 
    {
        Serial.print("connecting to ");
        Serial.print(my_wifi_ssid);
        Serial.println(" ...");
        delay(1000);
        if(WiFi.status() == WL_CONNECTED)
        {
            Serial.print("WiFi connected, IP address : ");
            Serial.println(WiFi.localIP());
        }
    }


}

