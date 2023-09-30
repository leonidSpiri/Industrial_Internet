#define BLYNK_AUTH_TOKEN "JblLA6ceU3gmG5W-NkJJDNdSAWwb1_Ht"

#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <BH1750.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial
#define SSID "My.Macbook(Pro)"
#define PASS "WirelessFromMac"
#define SERVER_ADDRESS "158.160.125.107"
#define SERVER_PORT 8080
#define DHTPIN 2     // use pins 3, 4, 5, 12, 13 or 14
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
BH1750 lightMeter;

void setup() {
    Serial.begin(115200);
    dht.begin();
    Wire.begin();
    lightMeter.begin();
    bmp.begin();
    Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASS, SERVER_ADDRESS, SERVER_PORT);
}

float getHumidity() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return 0;
    }
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
    Serial.print(F("Humidity: "));
    Serial.print(h);
    //Serial.print(F("%  Temperature: "));
    //Serial.print(t);
    //Serial.print(F("°C "));
    Serial.print(F(" Heat index: "));
    Serial.print(hic);
    Serial.print(F("°C "));
    Serial.println();
    return h;
}

float getLight() {
    float lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
    return lux;
}

float getTemp() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    return bmp.readTemperature();
}


float getPressure() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    // you can get a more precise measurement of altitude
    // if you know the current sea level pressure which will
    // vary with weather and such. If it is 1015 millibars
    // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(102000));
    Serial.println(" meters");

    Serial.println();
    return bmp.readPressure();
}

void loop() {
    //getTempAndPressure();
    Blynk.run();
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
    Blynk.virtualWrite(V5, getPressure());
}

BLYNK_WRITE(V1) {
    analogWrite(15, param[0].asInt());
    analogWrite(12, param[1].asInt());
    analogWrite(13, param[2].asInt());
}