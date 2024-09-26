// C++ code
//
#include "DHT.h"
#define DHTTYPE DHT11

const int LED_A = 9;
const int LED_B = 8;
const int BUZZ = 1;
const int CHAVE_1 = 2;
const int CHAVE_2 = 3;
const int CHAVE_3 = 4;
const int CHAVE_4 = 5;
const int RGB_RED = "A5";
const int RGB_BLUE = "A6";
const int RGB_GREEN = "A7";
const int BUTTON = 13;
const int ECHO = 6;
const int TRIGGER = 7;
const int SELETOR = 0;
const int DHTPIN = "A0"; //entrada analog

DHT dht(DHTPIN, DHTTYPE);

int converteBinarioDecimal(int a, int b, int c, int d)
{
  return a * 2 + b * 4 + c * 8 + d * 16;
}

void ligarLed(char led)
{
  if(led == "A")
  {
    digitalWrite(LED_A, HIGH);
  }
  else if(led == "B")
  {
    digitalWrite(LED_B, HIGH);
  }
  return;
}

void desligarLed(char led)
{
  if(led == "A")
  {
    digitalWrite(LED_A, LOW);
  }
  else if(led == "B")
  {
    digitalWrite(LED_B, LOW);
  }
  return;
}

void ligarBuzzer()
{
  digitalWrite(BUZZER, HIGH);
  return;
}

void desligarBuzzer()
{
  digitalWrite(BUZZER, LOW);
  return;
}

void lerTemperatura()
{
  float t = dht.readTemperature();

  if(isnan(t))
  {
    Serial.println(F("Falha na leitura de temperatura"));
    return;
  }

  Serial.print(F("Temperatura: "));
  Serial.print(t);
  Serial.print(F("°C"));

  return;
}

void definirCorRGB(int r, int g, int b)
{
  analogWrite(RGB_RED, r);
  analogWrite(RGB_GREEN, g);
  analogWrite(RGB_BLUE, b);
  return;
}

void inicioModoProgramacaoSerial()
{

}

void inicioModoProgramacaoBinario()
{
  int a, b, c, d;
  a = digitalRead(CHAVE_1);
  b = digitalRead(CHAVE_2);
  c = digitalRead(CHAVE_3);
  d = digitalRead(CHAVE_4);
  opcode = converteBinarioDecimal(a, b, c, d);

  while(digitalRead(BUTTON))
  {
    delay(1000);
  }

  switch(opcode)
  {
    case 0:
      ligarLed("A");
    case 1:
      desligarLed("A");
    case 2:
      ligarLed("B");
    case 3:
      desligarLed("B");
    case 4:
      ligarBuzzer();
    case 5:
      desligarBuzzer();
    case 6:
      lerTemperatura();
    case 7:
      lerDistancia();
    case 8:
      definirCorRGB(255, 0, 0); //cor vermelha
    case 9:
      definirCorRGB(0, 255, 0); //cor verde
    case 10:
      definirCorRGB(0, 0, 255); //cor azul
    case 11:
      definirCorRGB(0, 255, 255); //cor ciano
    case 12:
      definirCorRGB(255, 255, 0); //cor amarela
    case 13:
      definirCorRGB(255, 0, 255); //cor magenta
    case 14:
      definirCorRGB(255, 255, 255); //cor branca
  }
  return;
}

void setup()
{
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(CHAVE_1, INPUT);
  pinMode(CHAVE_2, INPUT);
  pinMode(CHAVE_3, INPUT);
  pinMode(CHAVE_4, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(SELETOR, INPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER,OUTPUT);
  digitalWrite(TRIGGER,LOW);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  if(digitalRead(SELETOR)){
    inicioModoProgramacaoBinario();
  }
  else{
    inicioModoProgramacaoSerial():
  }

}