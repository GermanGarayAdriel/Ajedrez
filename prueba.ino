#include <String.h>
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
  String hola = "1";
  hola = Assemble_Turn(1,1,1,1,1,1,1,1,1,1);
  Dato Hola = Dissemble_Turn(hola);
  Serial.println(Hola.rey);
}

String Assemble_Turn(int cordenaday, int cordenadax,int movimientoy,int movimientox, bool estado_rey,int cordenaday1, int cordenadax1,int movimientoy1,int movimientox1, int id_coronacion){
    String mensaje;
    mensaje += String(cordenaday)+ '|';
    mensaje += String(cordenadax)+ '|';
    mensaje += String(movimientoy)+ '|';
    mensaje += String(movimientox)+ '|';
    mensaje += String(estado_rey)+ '|';
    mensaje += String(cordenaday1)+ '|';
    mensaje += String(movimientoy1)+ '|';
    mensaje += String(movimientox1)+ '|';
    mensaje += String(id_coronacion);
    return mensaje;
}
Dato Dissemble_Turn(String Mensaje){
  int k = Mensaje.length();
  Dato unDato;
  while (k!=0){
    if(k == 17){
      unDato.origen_y = int(Mensaje[0]);    
    }if(k == 17){
      unDato.origen_x = int(Mensaje[2]);    
    }if(k == 17){
      unDato.nuevo_y = int(Mensaje[4]);    
    }if(k == 17){
      unDato.nuevo_x = int(Mensaje[6]);    
    }if(k == 17){
      unDato.rey = int(Mensaje[8]);    
    }if(k == 17){
      unDato.origen_y2 = int(Mensaje[10]);    
    }if(k == 17){
      unDato.origen_x2 = int(Mensaje[12]);    
    }if(k == 17){
      unDato.nuevo_y2 = int(Mensaje[14]);    
    }if(k == 17){
      unDato.nuevo_x2 = int(Mensaje[16]);
    }if(k == 17){
      unDato.id_coronacion = int(Mensaje[18]);
    }k -=1;  
  }
  return unDato;
}

