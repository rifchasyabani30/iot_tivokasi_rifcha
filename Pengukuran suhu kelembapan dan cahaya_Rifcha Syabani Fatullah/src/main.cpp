#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define LDRPIN 32  
#define TIMEDHT 3000  

// sensor dan LCD
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// save data sensor
float humidity, celsius;
int lightIntensity;
uint32_t timerDHT = 0;

// suhu dan kelembapan
void getTemperature() {
    humidity = dht.readHumidity();
    celsius = dht.readTemperature();

    if (isnan(humidity) || isnan(celsius)) {
        Serial.println("Failed to read from DHT sensor!");
        humidity = 0.0;
        celsius = 0.0;
    }
}

// intensitas cahaya
void getLightIntensity() {
    lightIntensity = analogRead(LDRPIN);
}

// LCD terdeteksi di I2C
void checkI2C() {
    Wire.begin();
    Serial.println("Scanning for I2C devices...");
    for (byte address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        if (Wire.endTransmission() == 0) {
            Serial.print("Found I2C device at address 0x");
            Serial.println(address, HEX);
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Monitoring Started...");

    checkI2C(); 

    dht.begin();
    lcd.init();  
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("System Starting...");
    delay(2000);
    lcd.clear();
}

void loop() {
    getTemperature();
    getLightIntensity();

    Serial.print("Suhu: "); Serial.print(celsius); Serial.print(" °C | ");
    Serial.print("Kelembapan: "); Serial.print(humidity); Serial.print(" % | ");
    Serial.print("Cahaya: "); Serial.println(lightIntensity);

    // Tampilkan di LCD tanpa flicker
    lcd.setCursor(0, 0);
    lcd.print("S: "); lcd.print(celsius, 1); lcd.print("C ");
    lcd.print("H: "); lcd.print(humidity, 1); lcd.print("% ");

    lcd.setCursor(0, 1);
    lcd.print("Light: "); lcd.print(lightIntensity);
    lcd.print("    "); 

    delay(3000);
}