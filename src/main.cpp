#include <Arduino.h>

#include "config.h"
#include "serial_init.h"
#include "wifi_functions.h"
#include "mqtt_functions.h"
#include "server_functions.h"
#include "serial_rx.h"

#include "debug_utils.h"
#define DEBUG

void setup()
{
  // Borra todas las claves del espacio de nombres en memoria
  // eraseFlash("config");

  // Inicializa el objeto con la variables de configuracion
  Config configData;

  // Inicializa la conexion serial
  serial_init();

  // Iniciamos los temporizadores encargados de reconectar la conexion wifi y mqtt, en caso de desconexion
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(wifiConnectSTA));

  // Se captura los eventos de la conexion wifi
  WiFi.onEvent(WiFiEvent);

  // Inicializa el servidor mqtt
  InitMqtt();

  // Configuramos el modo del wifi
  WiFi.mode(configData.getWifiType());

  // Iniciamos la conexion wifi como punto de acceso
  wifiConnectAP();

  // Iniciamos la conexion wifi como cliente
  wifiConnectSTA();

  // Configura el servidor web
  serverHandlers();

  // Inicia ElegantOTA
  AsyncElegantOTA.begin(&server);

  // Inicia el servidor
  server.begin();

  write_log("Servidor HTTP iniciado...");

  DEBUG_PRINT("Servidor HTTP iniciado...");

  DEBUG_PRINT("Configuracion de red= " + readMemFlash("config", "config"));
}

void loop()
{
  serial_rx();
}