//https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "louisguan";
const char* password = "0989839679";
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin("http://api.thingspeak.com/apps/thinghttp/send_request?api_key=QORL1RTHWA8VDNLL");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
//    Serial.println(httpCode);
    http.end();   //Close connection
 
  }
 
  delay(1000);    //Send a request every 30 seconds
 
}
