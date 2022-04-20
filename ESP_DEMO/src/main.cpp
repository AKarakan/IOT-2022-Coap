#include <Arduino.h>
#include <WiFi.h>
#include "../lib/ESP-CoAP/coap_client.h"

// DEFINE PINS
const int buttonPin = 16;
// DEFINE WIFI PARAMETER
#define SSID "*****"
#define WIFI_PASS "*****"
// INITIALIZE COAP CLIENT
coapClient coap;
// DEFINE SERVER ADRESS
IPAddress ip(134,102,218,18); // ETH Zurich (coap.me) server
int port = 5683;
// Boolean for ISR
bool buttonPressed = false;

void wifi_setup();
void ISRButtonClicked();
void callback_response(coapPacket &packet, IPAddress ip, int port);

void setup() {
    Serial.begin(115200);
    delay(10);
    pinMode(buttonPin, INPUT);
    attachInterrupt(buttonPin, ISRButtonClicked, RISING);
    wifi_setup();
    coap.response(callback_response);
    coap.start();
    Serial.println("Ready to Send COAP-Request. Press the button...");
}

void loop() {
    if (buttonPressed) {
        Serial.print("Sending Message");
        for (int i = 0; i <= 4; ++i) {
            Serial.print(".");
            delay(250);
        }
        Serial.println(".");
        Serial.println("GET 'coap://coap.me/test' sent succesfully!");
        Serial.println(" ");
        coap.get(ip, port,"test");
        buttonPressed = false;
    }
    coap.loop();
}

void wifi_setup()
{
    Serial.println("Connecting to ");
    Serial.println(SSID);
    WiFi.begin(SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print("*");
    }
    Serial.println("");
    Serial.println("*** WiFi connected ***");
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());
}

void ISRButtonClicked() {
    buttonPressed = true;
}

void callback_response(coapPacket &packet, IPAddress ip, int port) {
    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
    p[packet.payloadlen] = NULL;

    if(packet.type==3 && packet.code==0){
        Serial.println("ping ok");
    }
    Serial.println("Received Message: ");
    Serial.println(p);
    Serial.println(" ");
}