#include <Arduino.h>
#include <ESP32Servo.h>
#include "atuadores.h"

#define BUTTON_PIN 5 // Pino do botão
#define SERVO_PIN 33 // Pino do servo

bool portaAberta = false; // Variável para monitorar o estado da porta

Servo servoMotor; // Cria um objeto Servo

void Servosetup()
{
  Serial.begin(115200);              // Iniciar comunicação serial
  servoMotor.attach(SERVO_PIN);      // Atacha o servo ao pino especificado
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configura o botão como entrada com pull-up interno

  servoMotor.write(0); // Garante que o servo inicie na posição 0 graus
}

void Servoloop()
{
  // Verifica se o botão foi pressionado
  if (digitalRead(BUTTON_PIN) == LOW)
  { // O botão é pressionado (LOW devido ao pull-up)
    portaAberta = !portaAberta;

    if (portaAberta)
    {
      Serial.println("Abrindo a porta...");
      servoMotor.write(90); // Gira o servo para 90 graus
    }

    else
    {
      servoMotor.write(0); // Retorna o servo para 0 graus
      Serial.println("Fechando a porta...");
    }
  }
}
