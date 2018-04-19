// 
// WildfootW 2018
// https://github.com/Wildfoot

#include <ESP8266WiFi.h>
#include "HTTPSRedirect.hpp"
#include "DebugMacros.h"
#include "CUSTOM_SETTING.hpp"

class PanControl_BackEnd_Communicate : public HTTPSRedirect
{
    private:
        const char * _remote_host;
        const char * _fingerprint;
        void _PanC_initial(void);
        String _url_path;

    public:
        //constructor
        PanControl_BackEnd_Communicate(void);
        PanControl_BackEnd_Communicate(const char*, const char*, const char*, const int);
        //destructor
        ~PanControl_BackEnd_Communicate();

        //overload connect()
        using HTTPSRedirect::connect;
        bool connect(const int max_retry = 5);
        //overload verify()
        using HTTPSRedirect::verify;
        bool verify(void);

        String Get_whole_table(const String& table_name);
        String Get_if_CardID_active(const String& CardID);
        String Get_the_CardID_reserve_data(const String& CardID);
};

PanControl_BackEnd_Communicate::PanControl_BackEnd_Communicate(void):
HTTPSRedirect()
{
    _PanC_initial();
}
PanControl_BackEnd_Communicate::PanControl_BackEnd_Communicate(const char * host, const char * fingerprint, const char * GScriptID, const int TLS_port):
HTTPSRedirect(TLS_port)
{
    _remote_host = host;
    _fingerprint = fingerprint;
    _url_path = String("/macros/s/") + GScriptID + "/dev?";
    _PanC_initial();
}
PanControl_BackEnd_Communicate::~PanControl_BackEnd_Communicate()
{
}

void PanControl_BackEnd_Communicate::_PanC_initial(void)
{
    setPrintResponseBody(false);
    setContentTypeHeader("application/json");
}

bool PanControl_BackEnd_Communicate::connect(const int max_retry)
{
    for(int i = 0;i < max_retry;i++)
    {
        if(connect(_remote_host, _httpsPort))
            return true;
    }
    return false;
}
bool PanControl_BackEnd_Communicate::verify(void)
{
    return verify(_fingerprint, _remote_host);
}
String PanControl_BackEnd_Communicate::Get_whole_table(const String& table_name)
{
    if(GET(_url_path + "TableName=" + table_name, _remote_host))
        return getResponseBody();
    else
        return String("");
}
String PanControl_BackEnd_Communicate::Get_if_CardID_active(const String& CardID)
{
    if(GET(_url_path + "TableName=CardInfo&CardNumber=" + CardID, _remote_host))
        return getResponseBody();
    else
        return String("");
}
String PanControl_BackEnd_Communicate::Get_the_CardID_reserve_data(const String& CardID)
{
    if(GET(_url_path + "TableName=Reservation&CardNumber=" + CardID, _remote_host))
        return getResponseBody();
    else
        return String("");
}

void setup()
{
    Serial.begin(115200);
    Serial.flush();
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
//////////////////////////// connect to backend /////////////////////////////
    PanControl_BackEnd_Communicate * client = new PanControl_BackEnd_Communicate(google_docs_host, fingerprint, GScriptID, httpsPort);
    client->connect();
    client->verify();
    String response_body;
    response_body = client->Get_whole_table(String("CardInfo"));
    Serial.print(response_body);
    response_body = client->Get_if_CardID_active(String("0000000066"));
    Serial.print(response_body);
    response_body = client->Get_the_CardID_reserve_data(String("0000000002"));
    Serial.print(response_body);
    delete client;
}

