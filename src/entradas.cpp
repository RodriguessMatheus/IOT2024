#include <Arduino.h>
#include <Bounce2.h>
#include "entradas.h"
#include "saidas.h"


#define BOTAO_BOOT_PIN 0
#define BOTAO_PIN 12

Bounce botao_boot = Bounce();
Bounce botao_2 = Bounce();



void inicializa_entradas()
{
    botao_boot.attach(BOTAO_BOOT_PIN, INPUT_PULLUP);
    botao_2.attach(BOTAO_PIN, INPUT_PULLUP);
}

void atualiza_botoes()
{
    // Atualiza o estado do botão
    botao_boot.update();
    botao_2.update();
}

bool botao_boot_pressionado()
{
    return botao_boot.fell();
}

bool botao_pressionado()
{
    return botao_2.fell();
}