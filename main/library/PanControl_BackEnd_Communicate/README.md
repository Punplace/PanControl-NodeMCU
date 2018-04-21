PanControl BackEnd Communicate class
===
WiFiClientSecure    <= HTTPSRedirect    <= PanControl_BackEnd_Communicate

## include
```
include "library/PanControl_BackEnd_Communicate/PanControl_BackEnd_Communicate.hpp"
```

## Member
```
(constructor)(const char * host, const char * fingerprint, const char * GScriptID_GET, const char * GScriptID_POST, const int TLS_port)
(destructor)(void)

bool connect(const int max_retry = 5)
bool verify(void)

String Get_whole_table(const String& table_name)
String Get_if_CardID_active(const String& CardID)
String Get_the_CardID_reserve_data(const String& CardID)
String Post_save_CardInfo(const String& CardID, const String& Owner, const String& CardTypeID, const String& Team)
String Post_save_CardType(const String& Name)
String Post_save_Team(const String& Name)
```
