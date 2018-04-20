// WildfootW 2018
// https://github.com/Wildfoot

//#include "lwip/tcp_impl.h"
#include <ESP8266WiFi.h>
#include "CUSTOM_SETTING.hpp"
#include "library/PanControl_BackEnd_Communicate/PanControl_BackEnd_Communicate.hpp"
#include "library/PanControl_BackEnd_Communicate/DebugMacros.h"

extern "C"
{
    #include <cont.h>
    extern cont_t g_cont;
}

PanControl_BackEnd_Communicate * client;
void setup()
{
    Serial.begin(115200);
    Serial.flush();

    // stack & heap analysis
    Serial.println(String("(in setup())Free heap  : ") + ESP.getFreeHeap());
    Serial.println(String("(in setup())Free stack : ") + cont_get_free_stack(&g_cont));

    // set wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin(my_wifi_ssid, my_wifi_password);

    client = new PanControl_BackEnd_Communicate(google_docs_host, fingerprint, GScriptID_GET, GScriptID_POST, httpsPort);
}

void loop()
{
    // stack & heap analysis
    Serial.println(String("(loop top)Free heap  : ") + ESP.getFreeHeap());
    Serial.println(String("(loop top)Free stack : ") + cont_get_free_stack(&g_cont));

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
//    void tcpCleanup()
//    {
//        while(tcp_tw_pcbs!=NULL)
//        {
//            tcp_abort(tcp_tw_pcbs);
//        }
//    }
    while(!client->connected())
    {
        Serial.print("connecting to ");
        Serial.print(google_docs_host);
        Serial.println(" ...");
        client->connect();
        client->verify();
        delay(1000);
        if(client->connected())
        {
            Serial.println("remote server connected");
        }
    }
//////////////////////////// connect to backend /////////////////////////////
    String response_body;
    response_body = client->Get_whole_table(String("CardInfo"));
    Serial.print(response_body);
    delay(10000);
    response_body = client->Get_if_CardID_active(String("0000000066"));
    Serial.print(response_body);
    delay(10000);
    response_body = client->Get_the_CardID_reserve_data(String("0000000002"));
    Serial.print(response_body);
    delay(10000);
    response_body = client->Post_save_CardInfo(String("0978645666"), String("PANCONTROL"), String("3"), String(""));
    Serial.print(response_body);
    delay(10000);
    response_body = client->Post_save_CardType(String("ADMIN"));
    Serial.print(response_body);
    delay(10000);
    response_body = client->Post_save_Team(String("ADMINGROUP"));
    Serial.print(response_body);
    delay(10000);

    // stack & heap analysis
    Serial.println(String("(before delete)Free heap  : ") + ESP.getFreeHeap());
    Serial.println(String("(before delete)Free stack : ") + cont_get_free_stack(&g_cont));

//    delete client;
//    client = nullptr;

    // stack & heap analysis
    Serial.println(String("(after delete)Free heap  : ") + ESP.getFreeHeap());
    Serial.println(String("(after delete)Free stack : ") + cont_get_free_stack(&g_cont));
}

