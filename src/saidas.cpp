#include <Arduino.h>
#include "saidas.h"
#define LedBuiltInPin 2
const int LEDPIN = 5;

bool LedBuiltInState = LOW;
bool ledState = LOW;


void inicializa_saidas()
{
    pinMode(LedBuiltInPin, OUTPUT);
    pinMode(LEDPIN, OUTPUT);
}

void atualiza_saidas()
{
    digitalWrite(LedBuiltInPin, LedBuiltInState);
    digitalWrite(LEDPIN, ledState);
}

