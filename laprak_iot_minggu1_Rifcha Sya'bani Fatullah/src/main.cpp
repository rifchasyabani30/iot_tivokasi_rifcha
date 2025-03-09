#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  
    Serial.begin(115200);
    Serial.println("Hello, ESP32!");
  
    pinMode(23, OUTPUT); // Red 
    pinMode(22, OUTPUT); // Yellow 
    pinMode(21, OUTPUT); // Green
  }
  
  void loop() {
    
    digitalWrite(23, HIGH);
    digitalWrite(22, LOW);
    digitalWrite(21, LOW);
    delay(30000);
  
    
    digitalWrite(23, LOW);
    digitalWrite(22, HIGH);
    digitalWrite(21, LOW);
    delay(5000);
  
    
    digitalWrite(23, LOW);
    digitalWrite(22, LOW);
    digitalWrite(21, HIGH);
    delay(20000);
  }
