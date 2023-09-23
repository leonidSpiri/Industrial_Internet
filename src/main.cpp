#include <Arduino.h>
#include "DHT.h"
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <BH1750.h>

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
}

void getHumidity() {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
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
}

void getLight() {
    float lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
}

void getTempAndPressure() {
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
}

void loop() {
    delay(10000);
    getHumidity();
    getLight();
    getTempAndPressure();
}

