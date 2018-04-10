// This file is a test of get request to a https connection
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "CUSTOM_SETTING.h"

void setup() 
{
    Serial.begin(115200);
    Serial.println();
    WiFi.mode(WIFI_STA);
    WiFi.begin(my_wifi_ssid, my_wifi_password);
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
	
////////////////////// connect to remote host //////////////////////
    const char* host = "wildfoot.tw";
    const int httpsPort = 443;
    //remote host SHA1 fingerprint of the certificate
    const char* fingerprint = "b78ef5280778e06b892bf78c6f1db2e593807f6e";

    // Use WiFiClientSecure class to create TLS connection
    WiFiClientSecure client;
    Serial.print("Connecting to ");
    Serial.println(host);
    if(!client.connect(host, httpsPort)) 
    {
        Serial.print("Connection to");
        Serial.print(host);
        Serial.println(" failed.");
        return;
    }
    if(client.verify(fingerprint, host)) 
        Serial.println("Certificate matches");
    else 
        Serial.println("Warning : Certificate doesn't match");

////////////////////// get request //////////////////////
    String url_path = "/get_test.html";

    Serial.print("requesting URL: ");
    Serial.print(host);
    Serial.println(url_path);
    client.print(String("GET ") + url_path + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: BuildFailureDetectorESP8266\r\n" +
                 "Connection: close\r\n" +
                 "\r\n");
    Serial.println("request sent");

    // receive header
    while(client.connected()) 
    {
        String line = client.readStringUntil('\n');
        if (line == "\r") 
        {
            Serial.println("headers receive end");
            break;
        }
    }
    // receive container
    while(client.connected())
    {
        String line = client.readStringUntil('\n');
        Serial.println(line);
    }
}
