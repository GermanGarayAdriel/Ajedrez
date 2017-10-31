#include <Adafruit_NeoPixel.h> // hay que instalarlo
#define NUM_LEDS 64 //Cantidad de LEDS
#define DATA_PIN 11 //El pin
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  pixels.begin();
}

void loop() {
    pixels.setPixelColor(12, pixels.Color(250,161,165)); // el primer numero es el led y luego el color mediante rgb
    pixels.show();// muestra todos los leds pre-configurados
    delay(1000);
      
    pixels.setPixelColor(12, pixels.Color(0,0,0));
    pixels.show();
    delay(1000);
  
}
