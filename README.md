# PanControl
NodeMCU part of PanControl

## develope
### environment
1. Prepare your arduino IDE.
2. Install ESP8266 library [library GitHub](https://github.com/esp8266/Arduino)
    1. Paste `http://arduino.esp8266.com/versions/2.4.1/package_esp8266com_index.json` in `file > preferences > Additional Boards Manager URLs: ` field.
    2. In `Tools > Board: > Boards manager...` choose type to `Contributed` find `esp8266 by ESP8266 Community` and install it.
3. Select `Tools > Board:` to NodeMCU
4. Select the correct Port for your NodeMCU
5. Find a example in `File > Examples > NodeMCU`. And try to burn it.

## custom setting
1. copy `CUSTOM_SETTING_example.h` as `CUSTOM_SETTING.h` to the directory where your `.ino` is.

## simple trubleshooting
### Arduino IDE
##### Can't access: /dev/tty
[stackoverflow](https://askubuntu.com/questions/210177/serial-port-terminal-cannot-open-dev-ttys0-permission-denied?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa)
##### Serial Monitor mojibake texts
Make sure you choose the currect speed of data transmission

## library usage
[PanControl BackEnd Communicate](https://github.com/Punplace/PanControl-NodeMCU/blob/master/main/library/PanControl_BackEnd_Communicate/)

## reference
* [HTTPSRedirect](https://github.com/electronicsguy/ESP8266/tree/master/HTTPSRedirect)
* [Arduino ESP8266/ESP32 Exception Stack Trace Decoder](https://github.com/me-no-dev/EspExceptionDecoder)
* [ESP8266 document](http://arduino-esp8266.readthedocs.io/en/latest/index.html)
