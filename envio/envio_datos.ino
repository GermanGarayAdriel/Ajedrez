#include <stdlib.h>

struct Dato{
  int origen_y;
  int origen_x;
  int nuevo_y;
  int nuevo_x;
  bool rey;
  int origen_y2;
  int origen_x2;
  int nuevo_y2;
  int nuevo_x2;
  int id_coronacion;
};
void setup() {
   Serial.begin(9600);
   }

void loop() {
    Recibo_Datos("4");
  }
void Envio_Datos(int cordenaday, int cordenadax,int movimientoy,int movimientox, bool estado_rey,int cordenaday1, int cordenadax1,int movimientoy1,int movimientox1, int id_coronacion){
    Dato unDato;
    unDato.origen_y = cordenaday;
    unDato.origen_x = cordenadax;
    unDato.nuevo_y = movimientoy;
    unDato.nuevo_x = movimientox;
    unDato.rey = estado_rey;
    unDato.origen_y2 = cordenaday1;
    unDato.origen_x2 = cordenadax1;
    unDato.nuevo_y2 = movimientoy1;
    unDato.nuevo_x2 = movimientox1;
    unDato.id_coronacion = id_coronacion; 
}
void Recibo_Datos(String message){
    char hola = message[0];
    int k = hola - '0';
    k = k + 2;
}

