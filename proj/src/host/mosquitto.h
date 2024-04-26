#ifndef _MOSQUITTO_C_
#define _MOSQUITTO_C_

#include <stdlib.h>
#include "../mosquitto_headers.h"
#include "../headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mosquitto.h>

#define MQTT_HOST

typedef struct 
{
    uint8_t device;
    char* topic;
} redirect_t;

typedef struct {
    const char *topic;
    void (*handler)(const struct mosquitto_message *);
} MessageHandler_t;

#endif


