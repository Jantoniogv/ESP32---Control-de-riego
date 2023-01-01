#ifndef _CONFIG_INIT_H_
#define _CONFIG_INIT_H_
#include <Arduino.h>

#include <wifi.h>

// Variables inicializacion wifi
wifi_mode_t initWifiType = WIFI_MODE_APSTA;

String initSsidSTA = "DIGIFIBRA-Ap99";
String initSsidAP = "MyESP32AP_2022";

String initPassSTA = "612018_2482019";
String initPassAP = "adminadmin";

String initHost = "ESP32_2022";

String initIPap = "192.168.10.1";

String initIPsta = "";
String initGateway = "";
String initSubnet = "";

// Variables inicializacion mqtt
String initMqttHost = "192.168.1.200";
String initMqttPort = "1883";
String initMqttUser = "mqtt";
String initMqttPass = "MQTT";

#endif //_CONFIG_INIT_H_