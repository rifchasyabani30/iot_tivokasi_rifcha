
#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL6Ja8aRzLu"
#define BLYNK_TEMPLATE_NAME "rifcha syabani fatullah 30"
#define BLYNK_AUTH_TOKEN "7629iSGppGh8Dg97pzmNobQ-dqZmlkeP"


#define BLYNK_DEVICE_NAME "Esp32IoT"
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHTesp.h> 

char auth[] = BLYNK_AUTH_TOKEN ; 

char ssid[] = "Wokwi-GUEST"; //nama hotspot yang digunakan
char pass[] = ""; 

const int DHT_PIN = 15;

int value0, value1, value2, value3, value6;

byte LED_R = 26;
byte LED_Y = 27;
byte LED_G = 14;
byte LED_B = 12;

DHTesp dht;

BlynkTimer timer;

//function untuk pengiriman sensor
void sendSensor()
{
 TempAndHumidity  data = dht.getTempAndHumidity();

//menampilkan temperature pada Serial monitor
Serial.print("% Temperature: ");
Serial.print(data.temperature);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(data.humidity);
Serial.println("% ");

Blynk.virtualWrite(V4, data.temperature); 
Blynk.virtualWrite(V1, data.humidity); 
}

BLYNK_WRITE(V2)
{
  int nilaiBacaIO =param.asInt();
  digitalWrite(LED_R, nilaiBacaIO);
  Blynk.virtualWrite(V3, nilaiBacaIO);
}

void setup()
{
// Debug console
Serial.begin(115200); 
dht.setup(DHT_PIN, DHTesp::DHT22);
pinMode(LED_R, OUTPUT);

Blynk.begin(auth, ssid, pass); 
timer.setInterval(1000, sendSensor); 
}

void loop()
{

Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}