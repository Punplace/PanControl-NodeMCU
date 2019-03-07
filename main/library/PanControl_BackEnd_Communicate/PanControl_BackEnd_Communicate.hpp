// For PanControl communicate between IoT and Google apps script
// Version 1.0
// https://github.com/WildfootW
// Copyright (C) 2018 WildfootW
// All rights reserved
//

//#include "lwip/tcp_impl.h"
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.hpp"
#include "DebugMacros.h"

#ifndef PC_BEC_HPP
#define PC_BEC_HPP
class PanControl_BackEnd_Communicate : public HTTPSRedirect
{
    private:
        void _PanC_initial(void);
        String _do_get_data(const String& get_url);
        String _do_post_data(const String& post_parameter);

    protected:
        const char * _remote_host;
        const char * _fingerprint;
        String _get_url_path;
        String _post_url_path;

    public:
        //constructor
        PanControl_BackEnd_Communicate(void);
        PanControl_BackEnd_Communicate(const char*, const char*, const char*, const char*, const int);
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
        String Post_save_CardInfo(const String& CardID, const String& Owner, const String& CardTypeID, const String& Team);
        String Post_save_CardType(const String& Name);
        String Post_save_Team(const String& Name);
};

PanControl_BackEnd_Communicate::PanControl_BackEnd_Communicate(void):
HTTPSRedirect()
{
    _PanC_initial();
}
PanControl_BackEnd_Communicate::PanControl_BackEnd_Communicate(const char * host, const char * fingerprint, const char * GScriptID_GET, const char * GScriptID_POST, const int TLS_port):
HTTPSRedirect(TLS_port)
{
    _remote_host = host;
    _fingerprint = fingerprint;
    _get_url_path = String("/macros/s/") + GScriptID_GET + "/dev?";
    _post_url_path = String("/macros/s/") + GScriptID_POST + "/dev";
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
String PanControl_BackEnd_Communicate::_do_get_data(const String& get_url)
{
    String TypeName = "application/json";
    setContentTypeHeader(TypeName.c_str());
    if(GET(get_url, _remote_host))
        return getResponseBody();
    else
        return String("");
}
String PanControl_BackEnd_Communicate::_do_post_data(const String& post_parameter)
{
    String TypeName = "application/x-www-form-urlencoded";
    setContentTypeHeader(TypeName.c_str());
    if(POST(_post_url_path, _remote_host, post_parameter))
        return getResponseBody();
    else
        return String("");
}
String PanControl_BackEnd_Communicate::Get_whole_table(const String& table_name)
{
    return _do_get_data(_get_url_path + "TableName=" + table_name);
}
String PanControl_BackEnd_Communicate::Get_if_CardID_active(const String& CardID)
{
    return _do_get_data(_get_url_path + "TableName=CardInfo&CardNumber=" + CardID);
}
String PanControl_BackEnd_Communicate::Get_the_CardID_reserve_data(const String& CardID)
{
    return _do_get_data(_get_url_path + "TableName=Reservation&CardNumber=" + CardID);
}
String PanControl_BackEnd_Communicate::Post_save_CardInfo(const String& CardID, const String& Owner, const String& CardTypeID, const String& Team)
{
    return _do_post_data("TableName=CardInfo&CardNumber=" + CardID + "&Owner=" + Owner + "&CardTypeID=" + CardTypeID + "&Team=" + Team);
}
String PanControl_BackEnd_Communicate::Post_save_CardType(const String& Name)
{
    return _do_post_data("TableName=CardType&Name=" + Name);
}
String PanControl_BackEnd_Communicate::Post_save_Team(const String& Name)
{
    return _do_post_data("TableName=Team&Name=" + Name);
}
#endif //PC_BEC_HPP
