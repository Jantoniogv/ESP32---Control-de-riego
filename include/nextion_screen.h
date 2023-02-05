#ifndef _NEXTION_SCREEN_H
#define _NEXTION_SCREEN_H

#include "Arduino.h"

#include "nextion.h"
#include "device.h"
#include "serial_tx.h"

// Botones de los depositos del pozo
NexDSButton btDepGaloBajo = NexDSButton(0, 1, "btDepGaloBajo");
NexDSButton btDepHuerto = NexDSButton(0, 2, "btDepHuerto");
NexDSButton btAguaCasa = NexDSButton(0, 4, "btAguaCasa");

// Botones de los sectores del deposito galo bajo
NexDSButton btGaloBajoSec1 = NexDSButton(0, 3, "btGaloBajoSec1");
NexDSButton btGaloBajoSec2 = NexDSButton(0, 5, "btGaloBajoSec2");

// Botones de los sectores del deposito del huerto
NexDSButton btHuertoSec1 = NexDSButton(0, 6, "btHuertoSec1");
NexDSButton btHuertoSec2 = NexDSButton(0, 7, "btHuertoSec2");

// Lista de eventos tactiles
NexTouch *nex_touch_listen[] = {
    &btDepGaloBajo,
    &btDepHuerto,
    &btAguaCasa,
    &btGaloBajoSec1,
    &btGaloBajoSec2,
    &btHuertoSec1,
    &btHuertoSec2,
    NULL};

// Temporizadores que inician periodo espera para la respuesta del los dispositivos y en caso de no recibir, se ejecuta y pone en OFF los botones
// correspondientes de la pantalla
TimerHandle_t timer_dep_galo_bajo;
TimerHandle_t timer_dep_huerto;
TimerHandle_t timer_agua_casa;
TimerHandle_t timer_galo_bajo_sec1;
TimerHandle_t timer_galo_bajo_sec2;
TimerHandle_t timer_huerto_sec1;
TimerHandle_t timer_huerto_sec2;

// Funciones que ejecutan los timers y cambian el estado del boton en caso de no recibir la confirmacion del dipositivo
void await_res_dep_galo_bajo()
{
    uint32_t estado;

    btDepGaloBajo.getValue(&estado);

    if (estado)
    {
        btDepGaloBajo.setValue(false);
    }
    else
    {
        btDepGaloBajo.setValue(true);
    }
}

void await_res_dep_huerto()
{
    uint32_t estado;

    btDepHuerto.getValue(&estado);

    if (estado)
    {
        btDepHuerto.setValue(false);
    }
    else
    {
        btDepHuerto.setValue(true);
    }
}

void await_res_agua_casa()
{
    uint32_t estado;

    btAguaCasa.getValue(&estado);

    if (estado)
    {
        btAguaCasa.setValue(false);
    }
    else
    {
        btAguaCasa.setValue(true);
    }
}

void await_res_galo_bajo_sec1()
{
    uint32_t estado;

    btGaloBajoSec1.getValue(&estado);

    if (estado)
    {
        btGaloBajoSec1.setValue(false);
    }
    else
    {
        btGaloBajoSec1.setValue(true);
    }
}

void await_res_galo_bajo_sec2()
{
    uint32_t estado;

    btGaloBajoSec2.getValue(&estado);

    if (estado)
    {
        btGaloBajoSec2.setValue(false);
    }
    else
    {
        btGaloBajoSec2.setValue(true);
    }
}

void await_res_huerto_sec1()
{
    uint32_t estado;

    btHuertoSec1.getValue(&estado);

    if (estado)
    {
        btHuertoSec1.setValue(false);
    }
    else
    {
        btHuertoSec1.setValue(true);
    }
}

void await_res_huerto_sec2()
{
    uint32_t estado;

    btHuertoSec2.getValue(&estado);

    if (estado)
    {
        btHuertoSec2.setValue(false);
    }
    else
    {
        btHuertoSec2.setValue(true);
    }
}

// Funciones manejadas por lo eventos de la pantalla
void send_dep_galo_bajo()
{
    uint32_t estado;

    btDepGaloBajo.getValue(&estado);

    if (estado)
    {
        serial_tx((String)evDepGaloBajo + "=" + ON);
    }
    else
    {
        serial_tx((String)evDepGaloBajo + "=" + OFF);
    }
}

void send_dep_huerto()
{
    uint32_t estado;

    btDepHuerto.getValue(&estado);

    if (estado)
    {
        serial_tx((String)evDepHuerto + "=" + ON);
    }
    else
    {
        serial_tx((String)evDepHuerto + "=" + OFF);
    }
}

void send_agua_casa()
{
    uint32_t estado;

    btAguaCasa.getValue(&estado);

    if (estado)
    {
        serial_tx((String)evCasa + "=" + ON);
    }
    else
    {
        serial_tx((String)evCasa + "=" + OFF);
    }
}

void send_galo_bajo_sec1()
{
    uint32_t estado;

    btGaloBajoSec1.getValue(&estado);

    if (estado)
    {
        serial_tx((String)evDepGaloBajoSec1 + "=" + ON);
    }
    else
    {
        serial_tx((String)evDepGaloBajoSec1 + "=" + OFF);
    }
}

void send_galo_bajo_sec2()
{
    uint32_t estado;

    btGaloBajoSec2.getValue(&estado);

    if (estado)
    {
        serial_tx((String)evDepGaloBajoSec2 + "=" + ON);
    }
    else
    {
        serial_tx((String)evDepGaloBajoSec2 + "=" + OFF);
    }
}

void send_huerto_sec1()
{
    uint32_t estado;

    btHuertoSec1.getValue(&estado);

    if (estado)
    {
        serial_tx((String)evDepHuertoSec1 + "=" + ON);
    }
    else
    {
        serial_tx((String)evDepHuertoSec1 + "=" + OFF);
    }
}

void send_huerto_sec2()
{
    uint32_t estado;

    btHuertoSec2.getValue(&estado);

    if (estado)
    {
        serial_tx((String)evDepHuertoSec2 + "=" + ON);
    }
    else
    {
        serial_tx((String)evDepHuertoSec2 + "=" + OFF);
    }
}

// Funciones que cambian el estado de los botones en caso de recibir un cambio desde el servidor mqtt
void set_dep_galo_bajo(String state)
{
    if (state == ON)
    {
        btDepGaloBajo.setValue(true);
    }
    else
    {
        btDepGaloBajo.setValue(false);
    }
}

void set_dep_huerto(String state)
{
    if (state == ON)
    {
        btDepHuerto.setValue(true);
    }
    else
    {
        btDepHuerto.setValue(false);
    }
}

void set_agua_casa(String state)
{
    if (state == ON)
    {
        btAguaCasa.setValue(true);
    }
    else
    {
        btAguaCasa.setValue(false);
    }
}

void set_galo_bajo_sec1(String state)
{
    if (state == ON)
    {
        btGaloBajoSec1.setValue(true);
    }
    else
    {
        btGaloBajoSec1.setValue(false);
    }
}

void set_galo_bajo_sec2(String state)
{
    if (state == ON)
    {
        btGaloBajoSec2.setValue(true);
    }
    else
    {
        btGaloBajoSec2.setValue(false);
    }
}

void set_huerto_sec1(String state)
{
    if (state == ON)
    {
        btHuertoSec1.setValue(true);
    }
    else
    {
        btHuertoSec1.setValue(false);
    }
}

void set_huerto_sec2(String state)
{
    if (state == ON)
    {
        btHuertoSec2.setValue(true);
    }
    else
    {
        btHuertoSec2.setValue(false);
    }
}

// Inicializa la pantalla nextion y las funciones que manejaran los eventos
void init_nextion()
{
    nexInit();

    btDepGaloBajo.attachPop((NexTouchEventCb)send_dep_galo_bajo);
    btDepHuerto.attachPop((NexTouchEventCb)send_dep_huerto);
    btAguaCasa.attachPop((NexTouchEventCb)send_agua_casa);
    btGaloBajoSec1.attachPop((NexTouchEventCb)send_galo_bajo_sec1);
    btGaloBajoSec2.attachPop((NexTouchEventCb)send_galo_bajo_sec2);
    btHuertoSec1.attachPop((NexTouchEventCb)send_huerto_sec1);
    btHuertoSec2.attachPop((NexTouchEventCb)send_huerto_sec2);

    // Iniciamos los temporizadores encargados de reconectar la conexion wifi y mqtt, en caso de desconexion
    timer_dep_galo_bajo = xTimerCreate("timer_dep_galo_bajo", pdMS_TO_TICKS(15000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(await_res_dep_galo_bajo));
    timer_dep_huerto = xTimerCreate("timer_dep_huerto", pdMS_TO_TICKS(15000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(await_res_dep_huerto));
    timer_agua_casa = xTimerCreate("timer_agua_casa", pdMS_TO_TICKS(15000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(await_res_agua_casa));
    timer_galo_bajo_sec1 = xTimerCreate("timer_galo_bajo_sec1", pdMS_TO_TICKS(15000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(await_res_galo_bajo_sec1));
    timer_galo_bajo_sec2 = xTimerCreate("timer_galo_bajo_sec2", pdMS_TO_TICKS(15000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(await_res_galo_bajo_sec2));
    timer_huerto_sec1 = xTimerCreate("timer_huerto_sec1", pdMS_TO_TICKS(15000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(await_res_huerto_sec1));
    timer_huerto_sec2 = xTimerCreate("timer_huerto_sec2", pdMS_TO_TICKS(15000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(await_res_huerto_sec2));
}

#endif //_NEXTION_SCREEN_H