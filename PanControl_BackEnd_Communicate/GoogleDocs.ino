// 
// WildfootW 2018
// https://github.com/Wildfoot

#include <ESP8266WiFi.h>
#include "HTTPSRedirect.hpp"
#include "DebugMacros.h"
#include "CUSTOM_SETTING.h"

class PanControl_BackEnd_Communicate : public HTTPSRedirect
{
    private:
        char * _host;
        char * _fingerprint;
    public:
        PanControl_BackEnd_Communicate(void);
}

PanControl_BackEnd_Communicate::PanControl_BackEnd_Communicate(void):
HTTPSRedirect(void)
{

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

