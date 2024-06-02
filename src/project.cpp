#define BLYNK_AUTH_TOKEN ""

#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <BH1750.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define SSID ""
#define PASS ""

#define SERVER_ADDRESS "94.19.200.198"
#define SERVER_PORT 8080
#define DHTPIN D0
#define DHTTYPE DHT11   // DHT 11

const int digital_pin_holla = D5;
const int digital_pin_relay = D6;
const int digital_pin_water = D7;
const int digital_pin_motion = D8;

bool relay_state = false;

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
BH1750 lightMeter;

void setup() {
    Serial.begin(115200);
    dht.begin();
    Wire.begin();
    lightMeter.begin();
    bmp.begin();
    pinMode(digital_pin_holla, INPUT);
    pinMode(digital_pin_relay, OUTPUT);
    pinMode(digital_pin_water, INPUT);
    pinMode(digital_pin_motion, INPUT);
    digitalWrite(digital_pin_relay, LOW);
    Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASS, SERVER_ADDRESS, SERVER_PORT);
}

float getHumidity() {
    float h = dht.readHumidity();
    if (isnan(h)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 0;
    }
    return h;
}

float getLight() {
    float lux = lightMeter.readLightLevel();
    return lux;
}

float getTemp() {
    return bmp.readTemperature();
}


int getHolla() {
    int h = digitalRead(digital_pin_holla);
    if (isnan(h)) {
        Serial.println(F("Failed to read from Holla sensor!"));
        return 0;
    }
    return h;
}


int getWater() {
    int h = digitalRead(digital_pin_water);
    if (isnan(h)) {
        Serial.println(F("Failed to read from Water sensor!"));
        return 0;
    }
    return h;
}

int getMotion() {
    int h = digitalRead(digital_pin_motion);
    if (isnan(h)) {
        Serial.println(F("Failed to read from Motion sensor!"));
        return 0;
    }
    return h;
}

void setRelayState() {
    if(relay_state) {
        digitalWrite(digital_pin_relay, LOW);
        relay_state = false;
    }
    else {
        digitalWrite(digital_pin_relay, HIGH);
        relay_state = true;
    }
}

void loop() {
    Blynk.run();
}

BLYNK_READ(V1) {
        Blynk.virtualWrite(V1, getHolla());
}

BLYNK_READ(V2) {
        Blynk.virtualWrite(V2, getLight());
}

BLYNK_READ(V3) {
        Blynk.virtualWrite(V3, getHumidity());
}

BLYNK_READ(V4) {
        Blynk.virtualWrite(V4, getTemp());
}

BLYNK_READ(V5) {
        Blynk.virtualWrite(V5, getWater());
}

BLYNK_READ(V6) {
        Blynk.virtualWrite(V6, getMotion());
}

BLYNK_WRITE(V7){
        setRelayState();
}