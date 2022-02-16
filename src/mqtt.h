#ifndef _MQTT_H
#define _MQTT_H

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
//#include "modem.h"

// Configuracion MQTT
#define AIO_SERVER      "campana.redefine.cl"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "campana"
#define AIO_KEY         "19Cvid118764"
//#define ADAFRUIT_FONA_DEBUG true
#define RETRIES                10
#define WAIT_BETWEEN_PUBLISHES 1000

bool mqtt_start(void);

bool mqtt_connect(void);

bool mqtt_publish(String msg, String topic);

void mqtt_disconnect(void);

bool mqtt_reconnect();

void mqtt_callback(char* topic, byte* payload, unsigned int len);

#endif // _MQTT_H
