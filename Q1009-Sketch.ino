/*
     CÓDIGO:	  Q1009
     AUTOR:		  BrincandoComIdeias
     APRENDA: 	https://cursodearduino.net/
     SKETCH:    Teste 1x Helice - Projeto Drone
     DATA:		  25/04/2023
*/

// INCLUSÃO DE BIBLIOTECAS
#include <Servo.h>

// DEFINIÇÕES DE PINOS
#define pinESC 8
#define pinPot A0
#define pinCalibra 12

// DEFINIÇÕES
/*Descomentar o Define abaixo para utilizar o Monitor Serial*/
// #define DEBUG

#define APERTADO LOW

// INSTANCIANDO OBJETOS
Servo esc;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  pinMode(A0, INPUT);
  pinMode(pinCalibra, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  /* define o pulso do pwm entre 1000us e 2000us */
  esc.attach(pinESC, 1000, 2000); 

  if (digitalRead(pinCalibra) ==  APERTADO) {
    esc.write(180);
    delay(3000);
  }

  esc.write(0); 
  delay(3000);

  while (analogRead(pinPot) > 10) {
    /*Pisca rápido indicando que está esperando o pot "zerar"*/
    digitalWrite(LED_BUILTIN, bitRead(millis(), 7));
  }

  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  int leitura = analogRead(pinPot);
  int velocidade = map(leitura, 0, 1023, 0, 180);

#ifdef DEBUG
  Serial.println("Leitura: " + String(leitura));
  Serial.println("Velocidade: " + String(velocidade));
#endif

  esc.write(velocidade);
  delay(20); /* A biblioteca Servo.h só atualiza a cada 20ms */
}
