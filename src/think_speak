#include <Arduino.h>
#include <ESP8266WiFi.h> // Библиотека для работы с Wi-Fi на ESP
// подключаем библиотеки
// #include <библиотека>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>

String api_key = "AYVRVJ8WY75281YI";       // Введите свой ключ Write API записи из ThingSpeak
const char *ssid = "NullPointerException"; // Замените на ваш Wi-Fi ssid и ключ wpa2
const char *pass = "1qazZAQ!";             // Замените на ваш пароль Wi-Fi
const char *server = "api.thingspeak.com"; // "184.106.153.149" или api.thingspeak.com

#define DHTPIN D5     // Пин подключения DHT11
#define DHTTYPE DHT11 // Тип датчика DHT11

DHT dht(DHTPIN, DHTTYPE); // Создаем объект для датчика

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);

  // "подключаем" компоненты (например, Wire.begin())
  Wire.begin(D2, D1);
  dht.begin();
  // Подключаемся к Wi-Fi
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop()
{
  // Записываем данные с датчиков в переменные
  float temp = dht.readTemperature();  // Считываем температуру
  float humidity = dht.readHumidity(); // Считываем влажность

  if (client.connect(server, 80)) // Отправляем HTTP запрос на сервер ThingSpeak - по простому - отправляем данные в ThingSpeak
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += temp;
    data_to_send += "\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);
    delay(1000);
  }

  client.stop();
  Serial.println("Waiting...");

  delay(10 * 1000); // 10 секунд
}
