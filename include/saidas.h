
void inicializa_saidas();

void atualiza_saidas();

#include <DHTesp.h> // Inclua a biblioteca DHTesp
#include <ESP32Servo.h>  // Inclua a biblioteca Servo

extern bool LedBuiltInState;
extern bool ledState;
extern DHTesp dht;
extern Servo servo;

#include <Adafruit_SSD1306.h>
#include <Wire.h>

extern Adafruit_SSD1306 display;
