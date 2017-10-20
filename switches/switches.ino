#include "FastLED.h"

// fast led constants
#define DATA_PIN    11        // change to your data pin
#define COLOR_ORDER GRB      // if colors are mismatched; change this
#define NUM_LEDS    64       // change to the number of LEDs in your strip

#define LED_TYPE    WS2812B

// Width of pulse to trigger the shift register to read and latch
#define PULSE_WIDTH_USEC   5

// Optional delay between shift register reads
#define POLL_DELAY_MSEC   1

// Pines del SN74HC165N
#define CLOCK     8   // Connects to the Clock pin the 165
#define LOAD 			9   // Connects to Parallel load pin the 165
#define DATA      10  // Connects to the Q7 pin the 165
#define ENABLE 		12	// Connects to Clock Enable pin the 165

// 0 Significa que está siendo tocadillo

// this creates a LED array to hold the values for each led in your strip
CRGB leds[NUM_LEDS];

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
int cambio_detectado(int posicion[2], int nueva_posicion[2])
{
	int fila, columna;
	for(fila = 0; fila < 8; fila++)
	{
		for(columna = 0; columna < 8; columna++)
			if (tablero[fila][columna] != tableroAnterior[fila][columna] && tablero[fila][columna] == 1){
			  posicion[0] = fila;
        posicion[1] = columna;
        return;
			}
      else if (tablero[fila][columna] != tableroAnterior[fila][columna] && (tablero[fila][columna] == 0)){
        nueva_posicion[0] = fila;
        nueva_posicion[1] = columna;
        return;
      }
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



//Muestro el estado del tablero
void mostrar_estado_tablero()
{
    int fila, columna, led = 0;

    for(fila = 0; fila < 8; fila++)
    {
	    for(columna = 0; columna < 8; columna++)
	    {
	    	if(tablero[fila][columna] == 0 && (fila != 5 && columna != 5)){
	    		encender_led(63 - led);
	    	}
	    	else
	    		apagar_led(63 - led);

            led++;
	    }
    }
}

///////////////////////////////////////////////////////////////////////////////////

void setup()
{
  // the wiki features a much more basic setup line:
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

    // Initialize our digital pins...
    pinMode(LOAD, OUTPUT);
    pinMode(ENABLE, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, INPUT);
    Serial.begin(9600);
    digitalWrite(CLOCK, LOW);
    digitalWrite(LOAD, HIGH);

    // Read in and display the pin states at startup.
    leer_registros();
    mostrar_estado_tablero();
    guardar_estado_tablero();
}

void loop() 
{
    leer_registros();
    
    int posicion[2];
    int nueva_posicion[2];
    cambio_detectado(posicion, nueva_posicion);
    mostrar_estado_tablero();
    guardar_estado_tablero();
    if (posicion[0] != 5 && posicion[1] != 5){
      Serial.print(posicion[0]);
      Serial.print("  -  ");
      Serial.print(posicion[1]);
      Serial.print("---------");
      Serial.print(nueva_posicion[0]);
      Serial.print("  -  ");
      Serial.println(nueva_posicion[1]);
      delay(1000);
    }
    delay(POLL_DELAY_MSEC);
}
