#ifndef _MOSQUITTO_C_
#define _MOSQUITTO_C_

#include "../headers.h"
#include "../mosquitto_headers.h"
#include <arpa/inet.h>
#include <mosquitto.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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


