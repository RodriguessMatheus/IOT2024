#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h> // Baixar a biblioteca PubSubClient
#include <ArduinoJson.h>
#include "iot.h"
#include "senhas.h"
#include "saidas.h"
#include "atuadores.h"
#include "DHTesp.h"  // Inclusão para usar o sensor DHT
#include <ESP32Servo.h>   // Inclusão para usar o servo motor

#define mqtt_topic1 "project/DHT22"
#define mqtt_topic2 "project/led"
#define mqtt_topic3 "project/servo"
#define mqtt_topic4  "projeto_integrado/SENAI134/Cienciadedados/GrupoX"

//! ALTERAR O ID DO CLIENTE PARA UM VALOR ÚNICO
#define cliente_id "ESP32Client1783652"

// Pinos e variáveis para o servo motor, LED e DHT
#define DHTPIN 15
#define SERVOPIN 13
#define LEDPIN 5

WiFiClient espClient;
PubSubClient client(espClient);

void tratar_msg(char *topic, String msg);

void callback(char *topic, byte *payload, unsigned int length);
void reconecta_mqtt();

// Inicia a conexão WiFi
void setup_wifi()
{
  Serial.println();
  Serial.print("Conectando-se a Rede WiFi ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado ao WiFi com sucesso com IP: ");
  Serial.println(WiFi.localIP());
}

void inicializa_mqtt()
{
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Inicialização dos periféricos
  dht.setup(DHTPIN, DHTesp::DHT22);
  servo.attach(SERVOPIN);
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW); // Inicia o LED apagado
}

void atualiza_mqtt()
{ 
  client.loop();
  if (!client.connected())
  {
    reconecta_mqtt();
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.printf("Mensagem recebida [ %s ] \n\r", topic);
  String msg = "";
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    msg += (char)payload[i];
  }
  Serial.println();

  tratar_msg(topic, msg);
}

void reconecta_mqtt()
{
  while (!client.connected())
  {
    Serial.print("Tentando se conectar ao Broker MQTT: ");
    Serial.println(mqtt_server);
    if (client.connect(cliente_id))
    {
      Serial.println("Conectado ao Broker MQTT");
      client.subscribe(mqtt_topic4); // Sensores de dados do SENAI134
    }
    else
    {
      Serial.println("Falha ao conectar ao Broker.");
      Serial.println("Havera nova tentativa de conexao em 2 segundos");
      delay(2000);
    }
  }
}

void tratar_msg(char *topic, String msg)
{
  JsonDocument doc;

  if(strcmp(topic, mqtt_topic1) == 0)
  {
   
  }
  else if (strcmp(topic, mqtt_topic2) == 0)
  {
   
  }
  else if (strcmp(topic, mqtt_topic3) == 0)
  {
   
  }
  
  else if(strcmp(topic, mqtt_topic4) == 0)
  {
    deserializeJson(doc, msg);
    float humidity = doc["umidade"];
    float temperature = doc["temperatura"];
    float pressure = doc["pressure"];
    float altitude = doc["altitude"];
    float co2 = doc["co2"];
    String timestamp = doc["timestamp"];

  display.clearDisplay();
  display.setTextSize(0); //Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE); //define a cor do texto
  display.setCursor(34, 10);
  display.drawRect(3,3,120,50, SSD1306_WHITE);
  display.print("temperatura: ");
  display.setCursor(40, 25);
  display.print(temperature, 1); //exibe 1 caracteres decimais 
  display.write(248);
  display.display();
  delay(2000);


  display.clearDisplay();
  display.setTextSize(0); //Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE); //define a cor do texto
  display.setCursor(34, 10);
  display.drawRect(3,3,120,50, SSD1306_WHITE);
  display.print("umidade: ");
  display.setCursor(40, 25);
  display.print(humidity, 0); //exibe 1 caracteres decimais 
  display.println(" % ");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(0); //Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE); //define a cor do texto
  display.setCursor(34, 10);
  display.drawRect(3,3,120,50, SSD1306_WHITE);
  display.print("pressure: ");
  display.setCursor(40, 25);
  display.print(pressure, 0); //exibe 1 caracteres decimais 
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(0); //Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE); //define a cor do texto
  display.setCursor(34, 10);
  display.drawRect(3,3,120,50, SSD1306_WHITE);
  display.print("altura: ");
  display.setCursor(40, 25);
  display.print(altitude, 0); //exibe 1 caracteres decimais 
  display.display();
  delay(2000);

   
  display.clearDisplay();
  display.setTextSize(0); //Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE); //define a cor do texto
  display.setCursor(34, 10);
  display.drawRect(3,3,120,50, SSD1306_WHITE);
  display.print("CO2: ");
  display.setCursor(40, 25);
  display.print(co2, 0); //exibe 1 caracteres decimais 
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(0); //Define o tamanho do texto
  display.setTextColor(SSD1306_WHITE); //define a cor do texto
  display.setCursor(34, 10);
  display.drawRect(3,3,120,50, SSD1306_WHITE);
  display.print("hora: ");
  display.setCursor(40, 25);
  display.print(timestamp); //exibe 1 caracteres decimais 
  display.display();
  delay(2000);
  }
}

void publica_mqtt(String topico, String msg)
{
  client.publish(topico.c_str(), msg.c_str());
}
