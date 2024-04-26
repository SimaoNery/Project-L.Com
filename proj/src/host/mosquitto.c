#include "mosquitto.h"

struct mosquitto *mosq = NULL;


static const redirect_t redirect[] = {
    {LIGHT_MASK, LIGHT_TOPIC},
    {BUZZER_MASK, BUZZER_TOPIC}, 
    {LCD_DISPLAY_TEXT_MASK, LCD_DISPLAY_TEXT_TOPIC},
    {LCD_DISPLAY_ANIMATION_MASK, LCD_DISPLAY_ANIMATION_TOPIC},
    {MOTOR_MASK, MOTOR_TOPIC},
    {HUMIDITY_SENSOR_MASK, HUMIDITY_SENSOR_TOPIC},
    {DECIBEL_SENSOR_MASK, DECIBEL_SENSOR_TOPIC},
    {CAMERA_MASK, CAMERA_TOPIC}
};

void humidity_received(const struct mosquitto_message* msg) {

}

void decibel_received(const struct mosquitto_message* msg){

}

void camera_photo_received(const struct mosquitto_message* msg){
    
}

void camera_stream_received(const struct mosquitto_message* msg){

}

static const MessageHandler_t messageHandler[] = {
    {HUMIDITY_TOPIC_RX, humidity_received},
    {DECIBEL_TOPIC_RX, decibel_received},
    {CAMERA_PHOTO_TOPIC_RX, camera_photo_received},
    {CAMERA_STREAM_TOPIC_RX, camera_stream_received}
};

void commmand_byte_received(uint8_t command) {
    uint8_t device = (command >> 5);
    uint8_t param = command & 0x1F;

    size_t num_topics = sizeof(redirect) / sizeof(redirect[0]);

    for (size_t i = 0; i < num_topics; i++)
    {
        if (redirect[i].device == device) {
            mosquitto_publish(mosq, NULL, redirect[i].topic, 1, &param, 1, false);
        }
    }
}

void on_message_received(struct mosquitto *mosq, void *userdata, const struct mosquitto_message *message)
{
    const char *topic = (const char *)message->topic;
    size_t num_topics = sizeof(messageHandler) / sizeof(messageHandler[0]);

    for (size_t i = 0; i < num_topics; i++)
    {
        if (strcmp(topic, messageHandler[i].topic) == 0)
        {
            messageHandler[i].handler(message);
        }
    }
}

void initial_connection(struct mosquitto *mosq, void *userdata, int rc)
{
    if (rc == 0)
    {
        const char* topics[] = {
            HUMIDITY_TOPIC_RX,
            DECIBEL_TOPIC_RX,
            CAMERA_PHOTO_TOPIC_RX
            CAMERA_STREAM_TOPIC_RX
        };

        if (mosquitto_subscribe_multiple(mosq, NULL, sizeof(topics) / sizeof(char*), topics, 1, 0, NULL) != MOSQ_ERR_SUCCESS){
            printf("Error subscribing topics\n");
        } 
    }
    
    else {
        fprintf(stderr, "Failed to connect to MQTT broker: %s\n", mosquitto_connack_string(rc));
    }
}


int initial_config()
{
    
    mosquitto_lib_init();

    mosq = mosquitto_new(NULL, true, NULL);
    
    if (!mosq)
    {
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    mosquitto_connect_callback_set(mosq, initial_connection);
    mosquitto_message_callback_set(mosq, on_message_received);

    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS)
    {
        fprintf(stderr, "Unable to connect to MQTT broker.\n");
        return 1;
    }

    mosquitto_loop_start(mosq);
    return 0;
}


void destroy()
{
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}


int main()
{
    if (initial_config()) return 1;

    destroy();

    return 0;
}