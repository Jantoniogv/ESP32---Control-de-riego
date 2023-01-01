#ifndef _MQTT_FUNCTIONS_H
#define _MQTT_FUNCTIONS_H

#include <WiFi.h>
#include <AsyncMqttClient.h>

#include "config.h"
#include "device.h"
#include "serial_tx.h"
#include "log.h"

#define DEBUG
#include "debug_utils.h"

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;

void mqttPublish(String data)
{

  // Se filtra el topic en cual publicar y se publica
  if (data.indexOf((String)nivelDepGaloBajo) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(nivelDepGaloBajo, 1, false, payload.c_str());
  }

  if (data.indexOf((String)nivelDepHuerto) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(nivelDepHuerto, 1, false, payload.c_str());
  }

  if (data.indexOf((String)correinteMotor) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(correinteMotor, 1, false, payload.c_str());
  }

  if (data.indexOf((String)evDepGaloBajoState) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepGaloBajoState, 1, false, payload.c_str());
  }

  if (data.indexOf((String)evDepGaloBajoSec1State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepGaloBajoSec1State, 1, false, payload.c_str());
  }

  if (data.indexOf((String)evDepGaloBajoSec2State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepGaloBajoSec2State, 1, false, payload.c_str());
  }

  if (data.indexOf((String)evDepHuertoState) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepHuertoState, 1, false, payload.c_str());
  }

  if (data.indexOf((String)evDepHuertoSec1State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepHuertoSec1State, 1, false, payload.c_str());
  }

  if (data.indexOf((String)evDepHuertoSec2State) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evDepHuertoSec2State, 1, false, payload.c_str());
  }

  if (data.indexOf((String)evCasaState) != -1)
  {
    String payload = data.substring(data.indexOf("=") + 1);

    mqttClient.publish(evCasaState, 1, false, payload.c_str());
  }
}

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

void connectToMqtt()
{
  DEBUG_PRINT("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttConnect(bool sessionPresent)
{
  DEBUG_PRINT("Connected to MQTT");

  mqttSubscribe();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  DEBUG_PRINT("Disconnected from MQTT.");

  if (WiFi.isConnected())
  {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
  DEBUG_PRINT("Subscribe acknowledged.");
  DEBUG_PRINT("  packetId: ");
  DEBUG_PRINT(packetId);
  DEBUG_PRINT("  qos: ");
  DEBUG_PRINT(qos);
}

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

void onMqttPublish(uint16_t packetId)
{
  DEBUG_PRINT("Publish acknowledged.");
  DEBUG_PRINT("  packetId: ");
  DEBUG_PRINT(packetId);
}

void InitMqtt()
{
  Config configData;

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);

  mqttClient.onSubscribe(onMqttSubscribe);
  // mqttClient.onUnsubscribe(OnMqttUnsubscribe);

  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);

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