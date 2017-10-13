// ACLARACION: la funcion cambiar podria estar implementada directamente en cada if pero como requiere mover todos los datos de una posicion a otra y eliminar los de la anterior fue mejor
//             crear la funcion
int rey = 1;
int reina = 2;
int torre = 3;
int alfil = 4;
int caballo = 5;
int peon = 6;

struct Pieza{
    bool color;
    int id_pieza=0;
    bool movimiento;
    int posicionOrigenX;
    int posicionOrigenY;
};
Pieza tablero[8][8];

  // void
  void arreglar(Pieza Tablero[8][8],int turno);
  void cambiar(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
  void Inicializar_Tablero(Pieza Tablero[8][8]);
  // bool
  bool caminoPrendido(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
  bool intercepcion(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
  bool seguir(Pieza Tablero[8][8]);
  bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox,int turno);
  bool verificar_reytorre(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
  bool jaque(Pieza Tablero[8][8],int turno);
  bool matar(Pieza Tablero[8][8], int cordenaday,int cordenadax,int movimientoy,int movimientox);

void setup() {
  int incomingByte = 0;
  Serial.begin(9600);
}

void loop() {
  Inicializar_Tablero(tablero);
  int cordenaday;
  int cordenadax;
  int movimientoy;
  int movimientox;
  int letra;
  bool antiloop = true;
  bool antiloop2 = true;
  int incomingByte;
  while(true){
    letra = 0;
    Serial.println("blancas");
    while(antiloop2){
      while(antiloop){
        if (Serial.available() > 0) {//Lee mensaje
          incomingByte = Serial.read();
            if(letra == 0){
              cordenaday = incomingByte - 65;
            }
            else if(letra == 1){
              cordenadax = incomingByte - 49;
            }
            else if(letra == 2){
              movimientoy = incomingByte - 65;
            }
            else if(letra == 3){
              movimientox = incomingByte - 49;
              antiloop = false;
            }
            letra = letra+1;
        }
      }
      Serial.print("|");
      Serial.print(tablero[cordenaday][cordenadax].id_pieza);
      Serial.print("|");
      if(Verificar_Movimiento(tablero,cordenaday,cordenadax,movimientoy,movimientox,1)){
        Serial.println("movimiento correcto");
        antiloop2 = false;
      }
      else if(verificar_reytorre(tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        Serial.println("movimiento correcto");
        antiloop2 = false;
      }
      else{
        Serial.println("movimiento incorrecto");
        letra = 0;
        antiloop2 = true;
        antiloop = true;
      }
    }
    antiloop = true;
    antiloop2 = true;
    //Gana o pierde? (Iluminar)
    //Actualizar el movimiento enemigo (comió? cambió?)
    //Busca jaque (Hay? Mostrar desde donde e iluminar el boton)
    //Imprimir menu (tiempo, ultimo movimiento y menu: enroque corto, largo, ofrecer tablas y rendirse)
      //Se rinde? 
    //CICLO    
      //Esperar movimiento del chaboncito (Mostrar posiciones posibles, ofrecer movimientos especiales)
      letra = 0;
      Serial.println("negras");
      while(antiloop2){
        while(antiloop){
        if (Serial.available() > 0) {//Lee mensaje
          incomingByte = Serial.read();
            if(letra == 0){
              cordenaday = incomingByte - 65;
            }
            else if(letra == 1){
              cordenadax = incomingByte - 49;
            }
            else if(letra == 2){
              movimientoy = incomingByte - 65;
            }
            else if(letra == 3){
              movimientox = incomingByte - 49;
              antiloop = false;
            }
            letra = letra+1;
        }
      }
      Serial.print("|");
      Serial.print(tablero[cordenaday][cordenadax].id_pieza);
      Serial.print("|");
      if(Verificar_Movimiento(tablero,cordenaday,cordenadax,movimientoy,movimientox,0)){
        Serial.println("movimiento correcto");
        antiloop2 = false;
      }
      else if(verificar_reytorre(tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        Serial.println("movimiento correcto");
        antiloop2 = false;
      }
      else{
        Serial.println("movimiento incorrecto");
        letra = 0;
        antiloop2 = true;
        antiloop = true;
      }
    }
    antiloop = true;
    antiloop2 = true;
      //Verificar movimiento (Si está mal poner el tablero en rojo. Si mueve varios titila en rojo el boton tambien. Verificar captura al paso)
      
    //Coronacion?
    //Espera boton
    //Envia mensaje (Cambia de tablero)
}
}

void Inicializar_Tablero(Pieza Tablero[8][8]){
    for(int y = 0;y < 8;  y++){
        for(int x = 0;x < 8;x++){
            //a partir de aca pone las fichas negras
            if((x == 0 || x == 7) && (y == 0)){
                Tablero[y][x].id_pieza = torre;
                Tablero[y][x].color = true;
                Tablero[y][x].movimiento = true;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            else if((x == 2 || x == 5) && y == 0){
                Tablero[y][x].id_pieza = alfil;
                Tablero[y][x].color = true;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
                }
            else if((x == 1 || x == 6) && y == 0){
                Tablero[y][x].id_pieza = caballo;
                Tablero[y][x].color = true;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
                }
            else if(x == 3 && y == 0){
                Tablero[y][x].id_pieza = reina;
                Tablero[y][x].color = true;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
                }
            else if(x == 4 && y == 0){
                Tablero[y][x].id_pieza = rey;
                Tablero[y][x].color = true;
                Tablero[y][x].movimiento = true;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
                }
            else if(y == 1){
                Tablero[y][x].id_pieza = peon;
                Tablero[y][x].color = true;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            // a partir de aca es con las fichas blancas
            else if((x == 0 || x == 7) && y == 7){
                Tablero[y][x].id_pieza = torre;
                Tablero[y][x].color = false;
                Tablero[y][x].movimiento = true;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            else if((x == 2 || x == 5) && y == 7){
                Tablero[y][x].id_pieza = alfil;
                Tablero[y][x].color = false;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            else if((x == 1 || x == 6) && y == 7){
                Tablero[y][x].id_pieza = caballo;
                Tablero[y][x].color = false;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            else if(x == 3 && y == 7){
                Tablero[y][x].id_pieza = reina;
                Tablero[y][x].color = false;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            else if(x == 4 && y == 7){
                Tablero[y][x].id_pieza = rey;
                Tablero[y][x].color = false;
                Tablero[y][x].movimiento = true;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            else if(y == 6){
                Tablero[y][x].id_pieza = peon;
                Tablero[y][x].color = false;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
            else{
                Tablero[y][x].id_pieza = 100;
                Tablero[y][x].color = false;
                Tablero[y][x].movimiento = false;
                Tablero[y][x].posicionOrigenX = x;
                Tablero[y][x].posicionOrigenY = y;
            }
        }
    }
}

bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox,int turno){ //Se verifica el movimiento de una pieza
  
    int comprobantey, comprobantex;
    comprobantey = cordenaday - movimientoy;    //comporabante X e Y sirven pasa saber cuanto se movio independiente mente de su direccion
    comprobantex = cordenadax - movimientox;    //solo en el peon es necesario saber si el movimiento fue positivo o negativo
    comprobantex = sqrt(pow(comprobantex,2)); //pasa los numeros a positivo
    comprobantey = sqrt(pow(comprobantey,2)); //pasa los numeros a positivo
    Serial.print("comprobantes");
    Serial.print(comprobantey);
    Serial.print(" ");
    Serial.print(comprobantex);
    Serial.print(" ");
    Serial.print("|");
    Serial.print(" ");
    Serial.print(turno);
    Serial.print(" ");
    Serial.print("| ");
    Serial.print("M: ");
    Serial.print(movimientoy);
    Serial.print(" ");
    Serial.print(movimientox);
    Serial.print(" ");
    Serial.print("| ");
    Serial.print("C: ");
    Serial.print(cordenaday);
    Serial.print(" ");
    Serial.print(cordenadax);
    Serial.print("|");
    // a partir de aca todos los if's y elseif's corresponden a una pieza y su forma de moverse
    // para que esta clase funcione hay que tener: una clase intercepcion que vustre que en su trayecto la pieza no se tope con otra de su color y
    // la posicion de las piezas tienen que ser matrizes que tengan id's, color, posicion X e Y, movimiento(para saber si es la primera vez que se mueve)
    if(tablero[cordenaday][cordenadax].id_pieza == caballo && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))){
        if((comprobantex + comprobantey) == 3 && (comprobantex != 3 || comprobantey != 3) && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox);
        }
        else{
            return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
        }
    }
    else if(tablero[cordenaday][cordenadax].id_pieza == alfil && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))&& intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        if(comprobantex == comprobantey && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
        }
        else{
            return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
        }
    }
    else if(tablero[cordenaday][cordenadax].id_pieza == torre && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0)) && intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        if(comprobantex == 0 && comprobantey > 0 && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
        }
        else if(comprobantey == 0 && comprobantey > 0 && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox);
        }
        else{
            return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
        }
    }
    else if(tablero[cordenaday][cordenadax].id_pieza == reina && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))&& intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        if(comprobantey == comprobantex && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
        }
        else if(comprobantey == 0 && comprobantex > 0 && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox);
        }
        else if(comprobantex == 0 && comprobantey > 0 && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox);
        }
        else{
            return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
        }
    }
    else if(tablero[cordenaday][cordenadax].id_pieza == rey && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))){
        if(comprobantex < 2 && comprobantey < 2 && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
        }
        else{
            return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
        }
    }
    else if(tablero[cordenaday][cordenadax].id_pieza == 6 && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))){
      if((turno==1 && cordenaday < movimientoy) || (turno == 0 && cordenaday > movimientoy)){
        if(comprobantex == 0){
          if(comprobantey == 1 && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
          }
          else if(comprobantey == 2 && (cordenaday == 1 || cordenaday == 6) && matar(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
            cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
          }
          else{
              return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
          }
        }
        else if(comprobantex == 1 && comprobantey == 1){
          cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
        }
        else{
            return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
        }
      }
      else{
          return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
      }
    }
    else{
        return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
    }
    return true;
}

bool intercepcion(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox){ //Verifica si hay alguna pieza entre dos posiciones
    int comprobantey, comprobantex;
    comprobantey = cordenaday - movimientoy;
    comprobantex = cordenadax - movimientox;
    comprobantex = sqrt(pow(comprobantex,2));
    comprobantey = sqrt(pow(comprobantey,2));
    if(comprobantex == comprobantey){ // si la pieza se mueve en diagonal utiliza este IF
        for(int i = 1;i < comprobantex;i++){
            if(cordenadax < movimientox && cordenaday < movimientoy){
                if((Tablero[cordenaday+i][cordenadax+i].id_pieza != 100 && Tablero[cordenaday+i][cordenadax+i].color == Tablero[cordenaday][cordenadax].color)){
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday > movimientoy){
                if((Tablero[cordenaday-i][cordenadax-i].id_pieza != 100 && Tablero[cordenaday-i][cordenadax-i].color == Tablero[cordenaday][cordenadax].color)){
                    return false;
                }
            }
            else if(cordenadax < movimientox && cordenaday > movimientoy){
                if((Tablero[cordenaday-i][cordenadax+i].id_pieza != 100 && Tablero[cordenaday-i][cordenadax+i].color == Tablero[cordenaday][cordenadax].color)){
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday < movimientoy){
                if((Tablero[cordenaday+i][cordenadax-i].id_pieza != 100 && Tablero[cordenaday+i][cordenadax-i].color == Tablero[cordenaday][cordenadax].color)){
                    return false;
                }
            }
        }
    }
    else if(comprobantex == 0){ // si se mueve de forma vertical utiliza este IF
        for(int i = 1;i < comprobantey;i++){ // mueve la pieza de lugar en lugar hasta hallar a una pieza
            if(cordenaday < movimientoy){ // va de arriba a abajo
                if((Tablero[cordenaday+i][cordenadax].id_pieza != 100 && Tablero[cordenaday+i][cordenadax].color == Tablero[cordenaday][cordenadax].color)){ // si encuentra un lugar en con una id valida significa que hay una pieza y devuelve false *2
                    return false;
                }
            }
            else if(cordenaday > movimientoy){ // va de abajo a arriba
                if((Tablero[cordenaday-i][cordenadax].id_pieza != 100 && Tablero[cordenaday-i][cordenadax].color == Tablero[cordenaday][cordenadax].color)){ // * same2
                    return false;
                }
            }
        }
    }
    else if(comprobantey == 0){ // si se mueve de forma horizontal utiliza este IF
        for(int i = 1;i < comprobantex;i++){
            if(cordenadax < movimientox){ // va de izquierda a derecha
                if((Tablero[cordenaday][cordenadax+i].id_pieza != 100 && Tablero[cordenaday][cordenadax+i].color == Tablero[cordenaday][cordenadax].color)){ // * same2
                    return false;
                }
            }
            else if(cordenadax > movimientox){ // va de derecha a izquierda
                if((Tablero[cordenaday][cordenadax-i].id_pieza != 100 && Tablero[cordenaday][cordenadax-i].color == Tablero[cordenaday][cordenadax].color)){ // * same2
                    return false;
                }
            }
        }
    }
    return true;
}
void cambiar(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox){ //Cambia la pieza de un lugar a otro
    int comprobante;
    comprobante = cordenaday - movimientoy;
    comprobante = sqrt(pow(comprobante,2));
    Tablero[movimientoy][movimientox].id_pieza = Tablero[cordenaday][cordenadax].id_pieza;
    Tablero[movimientoy][movimientox].color = Tablero[cordenaday][cordenadax].color;
    Tablero[movimientoy][movimientox].posicionOrigenX = movimientox;
    Tablero[movimientoy][movimientox].posicionOrigenY = movimientoy;
    if(Tablero[cordenaday][cordenadax].id_pieza == peon){
        if(comprobante == 2){
            Tablero[movimientoy][movimientox].movimiento = Tablero[cordenaday][cordenadax].movimiento;
        }
        else{
            Tablero[movimientoy][movimientox].movimiento = false;
        }
    }
    else{
        Tablero[movimientoy][movimientox].movimiento = false;
    }
    //borra la posicion en la que estaba anteriormente
    Tablero[cordenaday][cordenadax].id_pieza = 0;
    Tablero[cordenaday][cordenadax].color = false;
    Tablero[cordenaday][cordenadax].movimiento = false;
    Tablero[cordenaday][cordenadax].posicionOrigenX = cordenadax;
    Tablero[cordenaday][cordenadax].posicionOrigenY = cordenaday;
}

bool jaque(Pieza Tablero[8][8],bool color, int lugar[2]){ // esta funcion verifica si el rey está en jaque. También devuelve el lugar desde donde se está haciendo el jaque.
    int reyPropio{2};
    bool jaquemate = true;
    for(int i = 0;i++;i < 8){ // busca a su rey
      for(int x = 0;x++;x < 8){
        if(Tablero[i][x].id_pieza == 1){
          reyPropio[0] = i;
          reyPropio[1] = x;
          jaquemate = false;
        }
      }
    }
    if(jaquemate){
      return false
    }
    else{
      for(int i = 0;i++;i < 8){
        if((reyPropio[0] + i) < 8){
           
        }
        if((reyPropio[1] + i) < 8){
           
        }
        if((reyPropio[0] - i) >= 0){
           
        }
        if((reyPropio[1] - i) >= 0){
           
        }
        if((reyPropio[0] + i) < 8 && (reyPropio[1] + i) < 8){
          
        }
        if((reyPropio[0] - i) >= 0 && (reyPropio[1] - i) >= 0){
          
        }
        if((reyPropio[0] - i) >= 0 && (reyPropio[1] + i) < 8){
          
        }
        if((reyPropio[0] + i) < 8 && (reyPropio[1] - i) >= 0){
          
        }
      }
    }
}
bool caminoPrendido(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox){ //Enciende los LEDs que conforman el camino del jaque
    int comprobantey, comprobantex;
    comprobantey = cordenaday - movimientoy;
    comprobantex = cordenadax - movimientox;
    comprobantex = sqrt(pow(comprobantex,2));
    comprobantey = sqrt(pow(comprobantey,2));
    int leds[2];
    if(comprobantex == comprobantey){ // si la pieza se mueve en diagonal utiliza este IF
        for(int i = 1;i < comprobantex;i++){
            leds[0] = cordenadax + i;
            leds[1] = cordenaday + i;
            if(cordenadax < movimientox && cordenaday < movimientoy){
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday+i][cordenadax+i].id_pieza != 0){
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday > movimientoy){
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday-i][cordenadax-i].id_pieza != 0){
                    return false;
                }
            }
            else if(cordenadax < movimientox && cordenaday > movimientoy){
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday-i][cordenadax+i].id_pieza != 0){
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday < movimientoy){
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday+i][cordenadax-i].id_pieza != 0){
                    return false;
                }
            }
        }
    }
    else if(comprobantex == 0){ // si se mueve de forma vertical utiliza este IF
        leds[0] = cordenadax;
        for(int i = 1;i < comprobantey;i++){ // mueve la pieza de lugar en lugar hasta hallar a una pieza
            leds[1] = cordenaday + i;
            if(cordenaday < movimientoy){ // va de arriba a abajo
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday+i][cordenadax].id_pieza != 0){ // si encuentra un lugar en con una id valida significa que hay una pieza y devuelve false *2
                    return false;
                }
            }
            else if(cordenaday > movimientoy){ // va de abajo a arriba
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday-i][cordenadax].id_pieza != 0){ // * same2
                    return false;
                }
            }
        }
    }
    else if(comprobantey == 0){ // si se mueve de forma horizontal utiliza este IF
        leds[1] = cordenaday;
        for(int i = 1;i < comprobantex;i++){
            leds[0] = cordenaday + i;
            if(cordenadax < movimientox){ // va de izquierda a derecha
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday][cordenadax+i].id_pieza != 0){ // * same2
                    return false;
                }
            }
            else if(cordenadax > movimientox){ // va de derecha a izquierda
                //prenden el led de la cordenada leds[]
                if(Tablero[cordenaday][cordenadax-i].id_pieza != 0){ // * same2
                    return false;
                }
            }
        }
    }
    return true;
}
bool matar(Pieza Tablero[8][8], int cordenaday,int cordenadax,int movimientoy,int movimientox){ // esta funcion verifica si el lugar a donde semueve la pieza esta desocupado o ocupado por una pieza enemiga
    if(Tablero[movimientoy][movimientox].id_pieza != 100 && Tablero[movimientoy][movimientox].color != Tablero[cordenaday][cordenadax].color){
        return true;
    }
    else if(Tablero[movimientoy][movimientox].id_pieza != 100 && Tablero[movimientoy][movimientox].color == Tablero[cordenaday][cordenadax].color){
        return false;
    }
    else{
        return true;
    }
}
bool verificar_reytorre(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox){
    int comprobantey, comprobantex;
    comprobantey = cordenaday - movimientoy;
    comprobantex = cordenadax - movimientox;
    comprobantex = sqrt(pow(comprobantex,2));
    comprobantey = sqrt(pow(comprobantey,2));
    if((cordenaday == 0 || cordenaday == 7) && (cordenadax == 0 || cordenadax == 7 || cordenadax == 4)){
      if((comprobantex == 2 || comprobantex == 3) && comprobantey == 0){
          if(Tablero[cordenaday][cordenadax].movimiento == true){
              if(movimientox > cordenadax){ // enroque largo
                  if(Tablero[cordenaday][7].movimiento == true && intercepcion(Tablero,cordenaday,4,cordenaday,7)){
                      Tablero[cordenaday][cordenadax].movimiento = false;
                      Tablero[movimientoy][movimientox].movimiento = false;
                      cambiar(Tablero,cordenaday,4,cordenaday,6);
                      cambiar(Tablero,cordenaday,7,cordenaday,5);
                      return true;
                  }
              }
              else if(movimientox < cordenadax){// enroque corto
                  if(Tablero[cordenaday][0].movimiento == true && intercepcion(Tablero,cordenaday,4,cordenaday,0)){
                      Tablero[cordenaday][cordenadax].movimiento = false;
                      Tablero[movimientoy][movimientox].movimiento = false;
                      cambiar(Tablero,cordenaday,4,cordenaday,2);
                      cambiar(Tablero,cordenaday,0,cordenaday,3);
                      return true;
                  }
              }
          }
      }
    }
    return false;
}
