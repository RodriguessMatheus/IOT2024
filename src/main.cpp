#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>    
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#include "atuadores.h"

#define DHTPIN 15
#define SERVOPIN 13         // Pino onde o servo motor está conectado
#define LEDPIN 5             // Pino onde o LED está conectado
#define SCREEN_WIDTH 128    // Comprimento da tela OLED em pixels
#define SCREEN_HEIGHT 64    // Altura da tela OLED em pixels
#define SCREEN_ADDRESS 0x3C // Endereço padrão do display OLED
#define OLED_RESET -1       // Pino Reset (use -1 para reiniciar junto com ESP32)

#define mqtt_topic1 "project/DHT22"
#define mqtt_topic2 ""

DHTesp dht;
Servo servo;                // Instância do servo motor

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

unsigned long tempoAnterior = 0;
const unsigned long intervalo = 1000;

void setup()
{
  dht.setup(DHTPIN, DHTesp::DHT22);
  servo.attach(SERVOPIN);  // Inicia o servo no pino especificado
  pinMode(LEDPIN, OUTPUT);  // Define o pino do LED como saída
  digitalWrite(LEDPIN, LOW); // Inicia o LED apagado

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);

  Serial.begin(115200);
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  inicializa_mqtt();
  inicializa_servos();
  display.display();
}

void loop()
{
  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();

  if(millis() - tempoAnterior >= intervalo)
  {
    tempoAnterior = millis();
    float umidade = dht.getHumidity();
    float temperatura = dht.getTemperature();

    // Controle do Servo e LED
    int servoAngle = 180;  // Exemplo de controle de ângulo do servo
    servo.write(servoAngle);

    bool ledState = true; // Exemplo: Acender o LED
    digitalWrite(LEDPIN, ledState ? HIGH : LOW);

    // Criação do JSON
    String Json;
    JsonDocument doc;

    doc["servo_angle"] = servoAngle;
    doc["led_state"] = ledState ? "on" : "off";

    serializeJson(doc, Json); // Converte o JSON para String
    publica_mqtt(mqtt_topic1, Json);

    // Exemplo de saída JSON: {"umidade":50, "temperatura":30, "servo_angle":90, "led_state":"on"}
  }
}
