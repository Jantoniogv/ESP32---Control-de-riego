#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "Arduino.h"

// Topic recibidos
const char evDepGaloBajo[] = "deposito/galo/bajo";
const char evDepGaloBajoSec1[] = "regar/galo/bajo/sec1";
const char evDepGaloBajoSec2[] = "regar/galo/bajo/sec2";

const char evDepHuerto[] = "deposito/huerto";
const char evDepHuertoSec1[] = "regar/huerto/sec1";
const char evDepHuertoSec2[] = "regar/huerto/sec2";

const char evCasa[] = "deposito/casa";

// Topic enviar estados
const char evDepGaloBajoState[] = "deposito/galo/bajo/state";
const char evDepGaloBajoSec1State[] = "regar/galo/bajo/sec1/state";
const char evDepGaloBajoSec2State[] = "regar/galo/bajo/sec2/state";

const char evDepHuertoState[] = "deposito/huerto/state";
const char evDepHuertoSec1State[] = "regar/huerto/sec1/state";
const char evDepHuertoSec2State[] = "regar/huerto/sec2/state";

const char evCasaState[] = "deposito/casa/state";

// Topic enviar
const char nivelDepGaloBajo[] = "nivel/deposito/galo/bajo";
const char nivelDepHuerto[] = "nivel/deposito/huerto";

// Topic enviar corriente consumida motor
const char correinteMotor[] = "corriente/motor";

#endif // _DEVICE_H_