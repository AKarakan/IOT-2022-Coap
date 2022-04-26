#include <Arduino.h>
#include <WiFi.h>
#include "../lib/ESP-CoAP/coap_client.h"
#include "WIFI_CREDENTIALS.h"

/*
 * Constance/Variables Declaration
 */
const int kButtonPin = 16;
const int kLedPin = 26;
// CoAP Client Declaration
coapClient coap;
// SERVER ADRESS
IPAddress ip(134, 102, 218, 18); // ETH Zurich (coap.me) server
const int kPort = 5683;
// Boolean for ISR
bool buttonPressed = false;

/*
 * Function Declarations
 */
void wifi_setup();

void ISRButtonClicked();

void callback_response(coapPacket &packet, IPAddress ip, int port);

/*
 * SETUP
 */
void setup() {
    Serial.begin(115200);
    delay(10);
    pinMode(kButtonPin, INPUT);
    pinMode(kLedPin, OUTPUT);
    attachInterrupt(kButtonPin, ISRButtonClicked, RISING);
    wifi_setup();
    coap.response(callback_response);
    coap.start();
    Serial.println("Ready to Send COAP-Request. Press the button...");
}

/*
 * LOOP
 */
void loop() {
    if (buttonPressed) {
        Serial.print("Sending Message");
        for (int i = 0; i <= 4; ++i) {
            Serial.print(".");
            delay(100);
        }
        Serial.println(".");
        Serial.println("GET 'coap://coap.me/hello' sent successfully!");
        Serial.println(" ");
        coap.get(ip, kPort, "hello");
        buttonPressed = false;
    }
    coap.loop();
}

/*
 * Function Implementations
 */
void wifi_setup() {
    Serial.println("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
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
    digitalWrite(kLedPin, HIGH);
    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
    p[packet.payloadlen] = NULL;

    if (packet.type == 3 && packet.code == 0) {
        Serial.println("ping ok");
    }
    Serial.println("Received Message: ");
    Serial.println(p);
    Serial.println(" ");
    delay(100);
    digitalWrite(kLedPin, LOW);

}