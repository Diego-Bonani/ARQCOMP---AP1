// C++ code
//
#include "dht.h"

#define VEL_SOM 340
const int LED_Y = 9;
const int LED_R = 10;
const int LED_B = 11;
const int BUZZER = 12;
const int CHAVE_1 = 22;
const int CHAVE_2 = 23;
const int CHAVE_3 = 24;
const int CHAVE_4 = 25;
const int RGB_RED = 4;
const int RGB_5V = 5;
const int RGB_BLUE = 7;
const int RGB_GREEN = 6;
const int BUTTON = 2;
const int ECHO = 28;
const int TRIG = 29;
const int SELETOR = 27;
const int pinoDHT11 = A0; //entrada analog
dht DHT;

int converteBinarioDecimal(int a, int b, int c, int d)  //chave 1 = a, chave 2 = b, chave 3 = c, chave 4 = d 
{
  return a * 1 + b * 2 + c * 4 + d * 8;
}

void ligarLed(char led)
{
  Serial.println(led);
  if(led == 'A')
  {
    Serial.println("LED");
    digitalWrite(LED_Y, HIGH);
  }
  else if(led == 'B')
  {
    Serial.println("LED");
    digitalWrite(LED_R, HIGH);
  }
  else if(led == 'C')
  {
    Serial.println("LED");
    digitalWrite(LED_B, HIGH);
  }
  return;
}

void desligarLed(char led)
{
  if(led == 'A')
  {
    digitalWrite(LED_Y, LOW);
  }
  else if(led == 'B')
  {
    digitalWrite(LED_R, LOW);
  }
  else if(led == 'C')
  {
    digitalWrite(LED_B, LOW);
  }
  return;
}

void ligarBuzzer()
{
  analogWrite(BUZZER, 10);
  return;
}

void desligarBuzzer()
{
  digitalWrite(BUZZER, LOW);
  return;
}

void lerTemperatura()
{
  DHT.read11(pinoDHT11); //Lê os valores do sensor
  Serial.print("Humidade: "); //Imprime Umidade na porta serial
  Serial.print(DHT.humidity); //Imprime o Valor de umidade lido pelo sensor
  Serial.print("%"); // Imprime simbolo
  Serial.print(" Temperatura: "); //Imprime Temperatura na porta serial
  Serial.print(DHT.temperature, 0); //Imprime o valor medido e remove a parte decimal
  Serial.println("C"); //Imprime unidade de medica

  return;
}

float disparaTrig(){  // A função diapara um sinal de trigger no pino pinTrig com largura de 10 microssegundos
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH);  // determina o tempo em microssegundos
}

void lerDistancia()
{
  float tempo, distancia;
  tempo = disparaTrig(); // dispara sinal de Trig E retorna a duracao do pulso (em microssegundos) que indica a distancia
  Serial.print(tempo);
  distancia = tempo * 0.000001 * VEL_SOM * 100/2; // determina a distancia em cm     
  Serial.println("Distancia em centimetros: "); // apresenta o resultado
  Serial.println(distancia,DEC); 
  return;
}

void definirCorRGB(int r, int g, int b)
{
  digitalWrite(RGB_5V, HIGH);
  analogWrite(RGB_RED, r);
  analogWrite(RGB_GREEN, g);
  analogWrite(RGB_BLUE, b);
  return;
}

void inicioModoProgramacaoSerial()
{
  return;
}

void inicioModoProgramacaoBinario()
{
  int a, b, c, d, opcode;
  a = digitalRead(CHAVE_1);
  b = digitalRead(CHAVE_2);
  c = digitalRead(CHAVE_3);
  d = digitalRead(CHAVE_4);
  opcode = converteBinarioDecimal(a, b, c, d);

  while(digitalRead(BUTTON))
  {
    
  }
  Serial.println("Botao apertado");

  switch(opcode)
  {
    case 0:
      ligarLed('A');
      break;
    case 1:
      desligarLed('A');
      break;
    case 2:
      ligarLed('B');
      break;
    case 3:
      desligarLed('B');
      break;
    case 4:
      ligarLed('C');
      break;
    case 5:
      desligarLed('C');
      break;
    case 6:
      ligarBuzzer();
      break;
    case 7:
      desligarBuzzer();
      break;
    case 8:
      lerTemperatura();
      break;
    case 9:
      lerDistancia();
      break;
    case 10:
      definirCorRGB(255, 0, 255); //cor verde
      break;
    case 11:
      definirCorRGB(255, 0, 0); //cor ciano
      break;
    case 12:
      definirCorRGB(0, 255, 0); //cor magenta
      break;
    case 13:
      definirCorRGB(0, 0, 0); //cor branca
      break;
    case 14:
      definirCorRGB(255, 255, 255); //desligar o led
      break;
    case 15:

      break;
  }
  return;
}

void setup()
{
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(CHAVE_1, INPUT);
  pinMode(CHAVE_2, INPUT);
  pinMode(CHAVE_3, INPUT);
  pinMode(CHAVE_4, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_5V, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(SELETOR, INPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG,OUTPUT);
  digitalWrite(TRIG,LOW);
  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(SELETOR)){
    inicioModoProgramacaoBinario();
  }
  else{
    inicioModoProgramacaoSerial();
  }

}