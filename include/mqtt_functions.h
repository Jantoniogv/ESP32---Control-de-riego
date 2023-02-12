#ifndef _MQTT_FUNCTIONS_H
#define _MQTT_FUNCTIONS_H

#include <WiFi.h>
#include <AsyncMqttClient.h>

#include "config.h"
#include "device.h"
#include "nextion_screen.h"
#include "serial_tx.h"
#include "log.h"

#define DEBUG
#include "debug_utils.h"

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;

// Funcion que publica los mensajes en los diferentes topic
void mqttPublish(String data)
{

  // Se comprueba el topic y se publica
  if (data.indexOf((String)nivelDepGaloBajo) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(nivelDepGaloBajo, 1, false, payload.c_str());

    set_nivel_dep_galo_bajo(payload.c_str());
  }

  if (data.indexOf((String)nivelDepHuerto) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(nivelDepHuerto, 1, false, payload.c_str());

    set_nivel_dep_huerto(payload.c_str());
  }

  if (data.indexOf((String)correinteMotor) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(correinteMotor, 1, false, payload.c_str());

    set_consumo_motor(payload.c_str());
  }

  if (data.indexOf((String)evDepGaloBajoState) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepGaloBajoState, 1, false, payload.c_str());

    xTimerStop(timer_dep_galo_bajo, 0);
    set_dep_galo_bajo(payload);
  }

  if (data.indexOf((String)evDepGaloBajoSec1State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepGaloBajoSec1State, 1, false, payload.c_str());

    xTimerStop(timer_galo_bajo_sec1, 0);
    set_galo_bajo_sec1(payload);
  }

  if (data.indexOf((String)evDepGaloBajoSec2State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepGaloBajoSec2State, 1, false, payload.c_str());

    xTimerStop(timer_galo_bajo_sec2, 0);
    set_galo_bajo_sec2(payload);
  }

  if (data.indexOf((String)evDepHuertoState) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepHuertoState, 1, false, payload.c_str());

    xTimerStop(timer_dep_huerto, 0);
    set_dep_huerto(payload);
  }

  if (data.indexOf((String)evDepHuertoSec1State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepHuertoSec1State, 1, false, payload.c_str());

    xTimerStop(timer_huerto_sec1, 0);
    set_huerto_sec1(payload);
  }

  if (data.indexOf((String)evDepHuertoSec2State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepHuertoSec2State, 1, false, payload.c_str());

    xTimerStop(timer_huerto_sec2, 0);
    set_huerto_sec2(payload);
  }

  if (data.indexOf((String)evCasaState) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evCasaState, 1, false, payload.c_str());

    xTimerStop(timer_agua_casa, 0);
    set_agua_casa(payload);
  }
}

// Topic que se suscribe
void mqttSubscribe()
{
  mqttClient.subscribe(evDepGaloBajo, 1);
  mqttClient.subscribe(evDepGaloBajoSec1, 1);
  mqttClient.subscribe(evDepGaloBajoSec2, 1);

  mqttClient.subscribe(evDepHuerto, 1);
  mqttClient.subscribe(evDepHuertoSec1, 1);
  mqttClient.subscribe(evDepHuertoSec2, 1);

  mqttClient.subscribe(evCasa, 1);
}

// Funcion que conecta al servidor mqtt
void connectToMqtt()
{
  DEBUG_PRINT("Connecting to MQTT...");
  mqttClient.connect();
}

// Funcion que se ejecuta cuando se ha conectado al servidor
void onMqttConnect(bool sessionPresent)
{
  DEBUG_PRINT("Connected to MQTT");

  mqttSubscribe();
}

// Funcion que se ejecuta cuando se ha desconectado del servidor
void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  DEBUG_PRINT("Disconnected from MQTT.");

  if (WiFi.isConnected())
  {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

// Funcion que recibe las publicaciones suscritas
void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  DEBUG_PRINT("Publish received.");
  DEBUG_PRINT("  topic: ");
  DEBUG_PRINT(topic);
  DEBUG_PRINT("  qos: ");
  DEBUG_PRINT(properties.qos);

  String pload = "";
  for (int i = 0; i < len; i++)
  {
    pload += payload[i];
  }

  DEBUG_PRINT("  payload: ");
  DEBUG_PRINT(pload);

  String data = topic;
  data.concat("=" + pload);

  serial_tx(data);
}

// Configura e inicia el servidor mqtt
void InitMqtt()
{
  Config configData;

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  mqttClient.onMessage(onMqttMessage);

  IPAddress IPMqtt;
  IPMqtt.fromString(configData.getMqttHost());

  mqttClient.setServer(IPMqtt, configData.getMqttPort().toInt());

  mqttClient.setCredentials(configData.getMqttUser(), configData.getMqttPass());

  write_log("Cliente mqtt iniciado...");

  DEBUG_PRINT("Cliente mqtt iniciado...");
  DEBUG_PRINT("Ip mqtt: " + IPMqtt.toString() + "User mqtt: " + configData.getMqttUser() + "Pass mqtt: " + configData.getMqttPass() + "Port mqtt: " + configData.getMqttPort());

  /* mqttClient.setServer(IPAddress(192, 168, 1, 176), 1883);

  mqttClient.setCredentials("mqtt", "MQTT"); */
}

#endif // _MQTT_FUNCTIONS_H