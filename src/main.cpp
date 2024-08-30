/*************************
 * Projeto IOT com ESP32
 * Escola SENAI de Informática
 * Curso de Apredizagem industrial
 * Integrador de soluções em nuvem
 * Data: 01/08/2024
 *
 * Autor: matheus rodrigues
 *
 * Descrição: Projeto de automação utilizando ESP32
 * com conexão WiFi e MQTT.
 *
 * versão: 0.9
 *************************/

#include <Arduino.h>
#include <ArduinoJson.h>
#include "iot.h"
#include "saidas.h"
#include "entradas.h"
#include "tempo.h"
#include "atuadores.h"
#include "funcoes.h"

// Definição dos tópicos de publicação
#define mqtt_pub_topic1 "project/esp32"

// Criacao de objetos

// Variáveis globais
unsigned long tempo_anterior = 0;
const unsigned long intervalo = 1000;

// Prototipo das funcoes

void setup()
{
  Serial.begin(115200);
  setup_wifi();
  setup_time();
  inicializa_entradas();
  inicializa_saidas();
  inicializa_mqtt();
  randomSeed(analogRead(0));
}

void loop()
{
  atualiza_time();
  atualiza_saidas();
  atualiza_botoes();
  atualiza_mqtt();

  JsonDocument doc;
  String json;
  bool mensagemEmFila = false;

  if (millis() - tempo_anterior >= intervalo)
  {
    tempo_anterior = millis();
    doc["timeStamp"] = timeStamp();
    mensagemEmFila = true;
  }

  if (botao_boot_pressionado())
  {
    LedBuiltInState = !LedBuiltInState;
    doc["LedState"] = LedBuiltInState;
    doc["BotaoState"] = true;
    doc["timeStamp"] = timeStamp();
    mensagemEmFila = true;
  }

  else if (botao_boot_solto())
  {
    doc["BotaoState"] = false;
    doc["timeStamp"] = timeStamp();
    mensagemEmFila = true;
  }

  if (mensagemEmFila)
  {
    serializeJson(doc, json);
    publica_mqtt(mqtt_pub_topic1, json);
    mensagemEmFila = false;
  }
}

int senha;
const unsigned long intervaloNormal = 30000;
const unsigned long intervaloEstendido = 90000;
unsigned long tempoInicialResetSenha = 0;
unsigned long intervaloResetSenha = 0;

int randomiza_senha()
resetaUsuario();

{
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoInicialResetSenha >= intervaloResetSenha)
  {
    if (intervaloResetSenha != intervaloNormal)
      intervaloResetSenha = intervaloNormal;
    tempoInicialResetSenha = tempoAtual;
    senha = random(1000, 9999);
    Serial.printf("Nova Senha: %d\n", senha);
  }
  return senha;
}

void tempoSenhaEstendido()
{
  if (intervaloResetSenha != intervaloEstendido)
  {
    unsigned long tempoAtual = millis();
    tempoInicialResetSenha = tempoAtual;
    intervaloResetSenha = intervaloEstendido;
    Serial.println("Senha estendida por 90 segundos");
  }
}