#include "FastLED.h"
#include "TM1637.h"
#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

// fast led constants
#define STRIP    2        // change to your data pin
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define NUM_LEDS    64       // change to the number of LEDs in your strip

// change WS2812B to match your type of LED, if different
// list of supported types is here:
// https://github.com/FastLED/FastLED/wiki/Overview
#define LED_TYPE    WS2812B

// Width of pulse to trigger the shift register to read and latch
#define PULSE_WIDTH_USEC   5

// Optional delay between shift register reads
#define POLL_DELAY_MSEC   1

// Pines del SN74HC165N
#define CLOCK     5   // Connects to the Clock pin the 165
#define LOAD 			4   // Connects to Parallel load pin the 165
#define DATA      3  // Connects to the Q7 pin the 165
#define ENABLE 		1	// Connects to Clock Enable pin the 165

// Pines botonera externa
#define PIN     32
#define N_LEDS  1
#define DIO 33
#define CLK 31

int boton = 30;
int segundos = 0;
int decimas = 0;
int centesimas = 0;
int numero;

byte Digitos[] = {0,0,0,0};            // Valor inicial para el display

// instancia display 7 segmentos
TM1637 tm1637(CLK,DIO);   

// instancia led boton
Adafruit_NeoPixel botonLed = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800); 

// this creates a LED array to hold the values for each led in your strip
CRGB leds[NUM_LEDS];
// instancia LCD 16x2
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // RS, EN, D4, D5, D6, D7

void muestraNumero(int num)
{
  int8_t Digito0 = num %10 ;
  int8_t Digito1 = (num % 100) / 10 ;
  int8_t Digito2 = (num % 1000) / 100 ;
  int8_t Digito3 = num  / 1000  ;

  Digitos[3] = Digito0 ;
  Digitos[2] = Digito1 ;
  Digitos[1] = Digito2 ;
  Digitos[0] = Digito3 ;

  tm1637.display(Digitos);
}

byte tablero[8][8];
byte tableroAnterior[8][8];

// desplaza bit a bit para lectura de los registros
void leer_registros()
{
	int fila, columna;
    // envio orden de lectura
    digitalWrite(ENABLE, HIGH);
    digitalWrite(LOAD, LOW);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(LOAD, HIGH);
    digitalWrite(ENABLE, LOW);

    // Lectura bit a bit de los registros de los SN74HC165N
    for(fila = 0; fila < 8; fila++)
    {
    	// Lectura desde la derecha debido al cableado de los SN74HC165N
	    for(columna = 7; columna >= 0; columna--)
	    {
	        // Set the corresponding bit in tablero
	        tablero[fila][columna] = digitalRead(DATA);

	        // Pulso de Clock (flanco ascendente, desplaza el bit leido)
	        digitalWrite(CLOCK, HIGH);
	        delayMicroseconds(PULSE_WIDTH_USEC);
	        digitalWrite(CLOCK, LOW);
	    }
	}
}

// comparo el estado actual del tablero respecto al anterior para verificar si hubo algun cambio
int cambio_detectado()
{
	int fila, columna;
	for(fila = 0; fila < 8; fila++)
	{
		for(columna = 0; columna < 8; columna++)
			if (tablero[fila][columna] != tableroAnterior[fila][columna]) return 1;
	}
	return 0;
}

// Guardo el estado actual del tablero para ver si hubo algun cambio
void guardar_estado_tablero()
{
	int fila, columna;
	
	for(fila = 0; fila < 8; fila++)
	{
		for(columna = 0; columna < 8; columna++)
			tableroAnterior[fila][columna] = tablero[fila][columna];
	}
}

void encender_led(int led)
{
    leds[led] = CRGB::Blue;
    FastLED.show();
}

void apagar_led(int led)
{
	leds[led] = leds[led] = CRGB::Black;
	FastLED.show();
}

// Muestro el estado del tablero
void mostrar_estado_tablero()
{
    int fila, columna, led = 0;

    for(fila = 0; fila < 8; fila++)
    {
	    for(columna = 0; columna < 8; columna++)
	    {
	    	if(tablero[fila][columna] >= 1)
	    		encender_led(led);
	    	else
	    		apagar_led(led);

            led++;
	    }
	}
}

///////////////////////////////////////////////////////////////////////////////////

void setup()
{
  // the wiki features a much more basic setup line:
  FastLED.addLeds<LED_TYPE, STRIP, COLOR_ORDER>(leds, NUM_LEDS);

    // Initialize our digital pins...
    pinMode(LOAD, OUTPUT);
    pinMode(ENABLE, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, INPUT);

    digitalWrite(CLOCK, LOW);
    digitalWrite(LOAD, HIGH);

    // inicializa botonera externa
    pinMode(boton, INPUT); // pin boton como entrada
    tm1637.init(); // Inicializa modulo
    botonLed.begin(); // Inicializa Led RGB
    tm1637.set(4); // Brillo, 0 (minimo) a 7 (maximo)
    tm1637.point(POINT_ON); // Enciende 2 puntos
    botonLed.setPixelColor(0, botonLed.Color(255, 0, 0)); // Rojo: (255, 0, 0)), Azul: (0, 0, 255));
    botonLed.show(); // This sends the updated pixel color to the hardware.

    // inicializa display LCD
    lcd.begin(16, 2);           // Fijamos el numero de caracteres y filas
    lcd.setCursor(4, 0);    // Ponte en la line 0, posicion 4
    lcd.print("TABLERO");  // Aqi va el mensaje
    lcd.setCursor(4, 1);    // Ponte en la line 1, posicion 4
    lcd.print("BLANCAS") ;

    // Read in and display the pin states at startup.
    leer_registros();
    mostrar_estado_tablero();
    guardar_estado_tablero();
}

  int apreto = 0;
  bool todavia = true;
void loop() 
{
    // Read the state of all zones
    leer_registros();

     // If there was a chage in state, display which ones changed
    if(cambio_detectado)
    {
        mostrar_estado_tablero();
        guardar_estado_tablero();
    }

   // entra
  if(digitalRead(boton) == LOW && todavia)
  {
      apreto = 1 - apreto;
      todavia = false;
  }
  else if(digitalRead(boton) == HIGH){
    todavia = true;
  }
  if(apreto == 1){
    centesimas++;
    if(centesimas == 440) { 
      centesimas = 0;
      decimas++;
    }
    if(decimas == 10) {
      decimas = 0;
      segundos++;
    }
    if(segundos == 60) {
      centesimas = 0;
      decimas = 0;
      segundos = 0;
    }
    botonLed.setPixelColor(0, botonLed.Color(0, 255, 0)); // Rojo: (255, 0, 0)), Azul: (0, 0, 255));
    botonLed.show(); // This sends the updated pixel color to the hardware.
  }
  if(centesimas % 4 == 0){
    numero = (centesimas/4) + decimas * 10 + segundos * 100;
    muestraNumero(numero);
  }
  delay(10);
  if(apreto == 0){
    botonLed.setPixelColor(0, botonLed.Color(255, 0, 0)); // Rojo: (255, 0, 0)), Azul: (0, 0, 255));
    botonLed.show(); // This sends the updated pixel color to the hardware.
  }


}
