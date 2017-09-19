#include <FastLED.h> //Incluyo libreria (Hay que instalarla)
#define NUM_LEDS 40 //Cantidad de LEDS
#define DATA_PIN 6 //El pin

CRGB leds[NUM_LEDS]; //Arreglo con los leds

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //Inicializacion
}

void loop() {
    leds[0] = CRGB::Red; //Indico el color
    leds[12] = CRGB::Green; 
    FastLED.show(); //Actualizo
    delay(1000);
      
    leds[0] = CRGB::Black;
    leds[12] = CRGB::Black; //Apago
    FastLED.show();
    delay(1000);
  
}
