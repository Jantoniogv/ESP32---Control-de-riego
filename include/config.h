#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <Arduino.h>
#include <wifi.h>

#include <ArduinoJson.h>

#include "save_flash.h"
#include "config_init.h"

#define DEBUG
#include "debug_utils.h"

class Config
{
private:
    // Variables inicializacion wifi
    wifi_mode_t wifiType;

    // Constates conexion STA wifi
    String ssidSTA;
    String passSTA;

    // Constates conexion PA wifi
    String ssidAP;
    String passAP;

    String hostname;

    String IPsta;
    String gateway;
    String subnet;

    String IPap;

    // Variables inicializacion mqtt
    String mqttHost;
    String mqttPort;
    String mqttUser;
    String mqttPass;

    // Metodos serializar y deserializar la configuracion
    String SerializeObject()
    {
        String json;

        const size_t capacity = JSON_OBJECT_SIZE(40);
        StaticJsonDocument<capacity> doc;

        doc["wifiType"] = wifiType;
        doc["ssidSTA"] = ssidSTA;
        doc["ssidAP"] = ssidAP;
        doc["passSTA"] = passSTA;
        doc["passAP"] = passAP;

        doc["host"] = hostname;

        doc["_IPap"] = IPap;
        doc["_IPsta"] = IPsta;
        doc["_gateway"] = gateway;
        doc["_subnet"] = subnet;

        doc["mqttHost"] = mqttHost;
        doc["mqttPort"] = mqttPort;

        doc["mqttUser"] = mqttUser;
        doc["mqttPass"] = mqttPass;

        serializeJson(doc, json);

        DEBUG_PRINT(json);

        return json;
    }

    void DeserializeObject(String json)
    {
        const size_t capacity = JSON_OBJECT_SIZE(40);
        StaticJsonDocument<capacity> doc;

        DeserializationError error = deserializeJson(doc, json);
        if (error)
        {
            return;
        }

        setWifiType(doc["wifiType"]);

        setSsidSTA(doc["ssidSTA"]);
        setSsidAP(doc["ssidAP"]);
        setPassSTA(doc["passSTA"]);
        setPassAP(doc["passAP"]);

        setHost(doc["host"]);

        setIPap(doc["_IPap"]);

        setIPsta(doc["_IPsta"]);
        setGateway(doc["_gateway"]);
        setSubnet(doc["_subnet"]);

        setMqttHost(doc["mqttHost"]);
        setMqttPort(doc["mqttPort"]);

        setMqttUser(doc["mqttUser"]);
        setMqttPass(doc["mqttPass"]);
    }

public:
    Config()
    {
        if (!existKey("config", "config"))
        {

            wifiType = initWifiType;

            ssidSTA = initSsidSTA;
            passSTA = initPassSTA;

            ssidAP = initSsidAP;
            passAP = initPassAP;

            hostname = initHost;

            IPap = initIPap;

            IPsta = initIPsta;
            gateway = initGateway;
            subnet = initSubnet;

            mqttHost = initMqttHost;
            mqttPort = initMqttPort;

            mqttUser = initMqttUser;
            mqttPass = initMqttPass;

            saveChange();
        }
        else
        {
            DeserializeObject(readMemFlash("config", "config"));
        }

        DEBUG_PRINT("Configuracion de red= " + readMemFlash("config", "config"));
    };

    /* static Config *getConfig()
    {
        static Config config;

        return &config;
    } */

    void saveChange() { saveMemFlash("config", "config", SerializeObject()); };

    void setWifiType(wifi_mode_t type) { wifiType = type; };

    void setSsidSTA(String ssid) { ssidSTA = ssid; };
    void setSsidAP(String ssid) { ssidAP = ssid; };
    void setPassSTA(String pass) { passSTA = pass; };
    void setPassAP(String pass) { passAP = pass; };

    void setHost(String host) { hostname = host; };

    void setIPsta(String _IP) { IPsta = _IP; };
    void setGateway(String _gateway) { gateway = _gateway; };
    void setSubnet(String _subnet) { subnet = _subnet; };

    void setIPap(String _IP) { IPap = _IP; };

    void setMqttHost(String host) { mqttHost = host; };
    void setMqttPort(String port) { mqttPort = port; };

    void setMqttUser(String user) { mqttUser = user; };
    void setMqttPass(String pass) { mqttPass = pass; };

    ////////////////////////////////////////////////////////////////////

    const wifi_mode_t getWifiType() { return wifiType; };

    const char *getSsidSTA() { return ssidSTA.c_str(); };
    const char *getSsidAP() { return ssidAP.c_str(); };
    const char *getPassSTA() { return passSTA.c_str(); };
    const char *getPassAP() { return passAP.c_str(); };

    const char *getHost() { return hostname.c_str(); };

    const String getIPap() { return IPap; };

    const String getIPsta() { return IPsta; };
    const String getGateway() { return gateway; };
    const String getSubnet() { return subnet; };

    const String getMqttHost() { return mqttHost; };
    const String getMqttPort() { return mqttPort; };

    const char *getMqttUser() { return mqttUser.c_str(); };
    const char *getMqttPass() { return mqttPass.c_str(); };
};

#endif //_CONFIG_H_