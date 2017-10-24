// ACLARACION: la funcion cambiar podria estar implementada directamente en cada if pero como requiere mover todos los datos de una posicion a otra y eliminar los de la anterior fue mejor
//             crear la funcion
int rey = 1;
int reina = 2;
int torre = 3;
int alfil = 4;
int caballo = 5;
int peon = 6;

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
#define LOAD       9   // Connects to Parallel load pin the 165
#define DATA      10  // Connects to the Q7 pin the 165
#define ENABLE    12  // Connects to Clock Enable pin the 165

// 0 Significa que está siendo tocadillo

// this creates a LED array to hold the values for each led in your strip

byte tablero_buscar[8][8];
byte tableroAnterior[8][8];
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
  bool jaquemate(Pieza Tablero[8][8],bool color);
  bool matar(Pieza Tablero[8][8], int cordenaday,int cordenadax,int movimientoy,int movimientox);

void setup() {
  int incomingByte = 0;
  Serial.begin(9600);
    pinMode(LOAD, OUTPUT);
    pinMode(ENABLE, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA, INPUT);
    digitalWrite(CLOCK, LOW);
    digitalWrite(LOAD, HIGH);

    // Read in and display the pin states at startup.
}
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
        tablero_buscar[fila][columna] = digitalRead(DATA);

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
    for(columna = 0; columna < 8; columna++){
      if (tablero_buscar[fila][columna] != tableroAnterior[fila][columna] && tablero_buscar[fila][columna] == 1){
        posicion[0] = fila;
        posicion[1] = columna;
        return;
      }
      else if (tablero_buscar[fila][columna] != tableroAnterior[fila][columna] && (tablero_buscar[fila][columna] == 0)){
        nueva_posicion[0] = fila;
        nueva_posicion[1] = columna;
        return;
      }
    }
  }
  return 0;
}

// Guardo el estado actual del tablero para ver si hubo algun cambio




//Muestro el estado del tablero


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
    leer_registros();
    int posicion[2];
    int nueva_posicion[2];
    
    if (posicion[0] != nueva_posicion[0] && posicion[1] != nueva_posicion[1]){
       cordenadax = posicion[0];
       cordenaday = 7 - posicion[1];
       movimientox = nueva_posicion[0];
       movimientoy = 7 - nueva_posicion[1];
    } 
    letra = 0;
    if(jaquemate(tablero,true)){
      Serial.println("rey blanco no existe, fin del juego. Ganan negras");
      delay(100000000);
      break;
    }
    if(jaque(tablero,true)){
      Serial.println("rey blanco en jaque");
    }
    Serial.println("blancas");
    
      Serial.print("|");
      Serial.print(tablero[cordenaday][cordenadax].id_pieza);
      Serial.print("|");
      if(Verificar_Movimiento(tablero,cordenaday,cordenadax,movimientoy,movimientox,1)){
        Serial.println("movimiento correcto");
        break;
      }
      else if(verificar_reytorre(tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        Serial.println("movimiento correcto");
        break;
      }
      else{
        Serial.println("movimiento incorrecto");
        letra = 0;
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
      if(jaquemate(tablero,false)){
        Serial.println("rey negro no existe, fin del juego. Ganan blancas");
      }
      if(jaque(tablero,false)){
        Serial.println("rey negro en jaque");
      }
      Serial.println("negras");
      while(antiloop2){
        while(antiloop){
        if(letra == 0){
              cordenaday = 7 - incomingByte;
            }
            else if(letra == 1){
              cordenadax = incomingByte;
            }
            else if(letra == 2){
              movimientoy = 7 - incomingByte;
            }
            else if(letra == 3){
              movimientox = incomingByte;
              antiloop = false;
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
          Serial.println ("segundo");
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
    Serial.println(" ZERO ");
    Serial.print("cy: ");
    Serial.print(cordenaday);
    Serial.print(" | cx: ");
    Serial.print(cordenadax);
    Serial.print(" | my: ");
    Serial.print(movimientoy);
    Serial.print(" | mx: ");
    Serial.println(movimientox);
    if(comprobantex == comprobantey){ // si la pieza se mueve en diagonal utiliza este IF
      Serial.println(" 1ro ");
        for(int i = 1;i <= comprobantex;i++){
          Serial.println(" 2do ");
            if(cordenadax < movimientox && cordenaday < movimientoy){
              Serial.println(" 3ro ++");
                if((Tablero[cordenaday+i][cordenadax+i].id_pieza != 100 && Tablero[cordenaday+i][cordenadax+i].color == Tablero[cordenaday][cordenadax].color)){
                  Serial.println(" 4to ");
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday > movimientoy){
              Serial.println(" 3ro ++++");
                if((Tablero[cordenaday-i][cordenadax-i].id_pieza != 100 && Tablero[cordenaday-i][cordenadax-i].color == Tablero[cordenaday][cordenadax].color)){
                  Serial.println(" 4to ");
                    return false;
                }
            }
            else if(cordenadax < movimientox && cordenaday > movimientoy){
              Serial.println(" 3ro ..");
                if((Tablero[cordenaday-i][cordenadax+i].id_pieza != 100 && Tablero[cordenaday-i][cordenadax+i].color == Tablero[cordenaday][cordenadax].color)){
                  Serial.println(" 4to ");
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday < movimientoy){
              Serial.println(" 3ro ....");
                if((Tablero[cordenaday+i][cordenadax-i].id_pieza != 100 && Tablero[cordenaday+i][cordenadax-i].color == Tablero[cordenaday][cordenadax].color)){
                  Serial.println(" 4to ");
                    return false;
                }
            }
        }
    }
    else if(comprobantex == 0){ // si se mueve de forma vertical utiliza este IF
        for(int i = 1;i <= comprobantey;i++){ // mueve la pieza de lugar en lugar hasta hallar a una pieza
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
        for(int i = 1;i <= comprobantex;i++){
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
    Serial.println("fin");
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
    Tablero[cordenaday][cordenadax].id_pieza = 100;
    Tablero[cordenaday][cordenadax].color = false;
    Tablero[cordenaday][cordenadax].movimiento = false;
    Tablero[cordenaday][cordenadax].posicionOrigenX = cordenadax;
    Tablero[cordenaday][cordenadax].posicionOrigenY = cordenaday;
}

bool jaque(Pieza Tablero[8][8],bool color){ // esta funcion verifica si el rey está en jaque. También devuelve el lugar desde donde se está haciendo el jaque.
    int reyPropio[2];
    int i = 0;
    int x = 0;
    while(i < 8){
      while(x < 8){
        if(Tablero[i][x].id_pieza == 1 && Tablero[i][x].color == color){
          reyPropio[0] = i;
          reyPropio[1] = x;
          Serial.print(Tablero[i][x].id_pieza);
          Serial.print(" | ");
          Serial.println(Tablero[i][x].color);
        }
        x = x + 1;
      }
      x = 0;
      i = i + 1;
    }
    i = 1;
    while(i < 8){
      if(Tablero[reyPropio[0] + 2][reyPropio[1] + 1].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 1ro");
        Serial.println(Tablero[reyPropio[0] + 2][reyPropio[1] + 1].id_pieza);
        if(Tablero[reyPropio[0] + 2][reyPropio[1] + 1].id_pieza == 5){
          return true;
        }
      }
      if(Tablero[reyPropio[0] + 2][reyPropio[1] - 1].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 2do");
        Serial.println(Tablero[reyPropio[0] + 2][reyPropio[1] - 1].id_pieza);
        if(Tablero[reyPropio[0] + 2][reyPropio[1] - 1].id_pieza == 5){
          return true;
        }
      }
      if(Tablero[reyPropio[0] - 2][reyPropio[1] + 1].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 3ro");
        Serial.println(Tablero[reyPropio[0] - 2][reyPropio[1] + 1].id_pieza);
        if(Tablero[reyPropio[0] - 2][reyPropio[1] + 1].id_pieza == 5){
          return true;
        }
      }
      if(Tablero[reyPropio[0] - 2][reyPropio[1] - 1].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 4to");
        Serial.println(Tablero[reyPropio[0] - 2][reyPropio[1] - 1].id_pieza);
        if(Tablero[reyPropio[0] - 2][reyPropio[1] - 1].id_pieza == 5){
          return true;
        }
      }
      if(Tablero[reyPropio[0] + 1][reyPropio[1] + 2].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 5to");
        Serial.println(Tablero[reyPropio[0] + 1][reyPropio[1] + 2].id_pieza);
        if(Tablero[reyPropio[0] + 1][reyPropio[1] + 2].id_pieza == 5){
          return true;
        }
      }
      if(Tablero[reyPropio[0] - 1][reyPropio[1] + 2].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 6to");
        Serial.println(Tablero[reyPropio[0] - 1][reyPropio[1] + 2].id_pieza);
        if(Tablero[reyPropio[0] - 1][reyPropio[1] + 2].id_pieza == 5){
          return true;
        }
      }
      if(Tablero[reyPropio[0] + 1][reyPropio[1] - 2].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 7mo");
        Serial.println(Tablero[reyPropio[0] + 1][reyPropio[1] - 2].id_pieza);
        if(Tablero[reyPropio[0] + 1][reyPropio[1] - 2].id_pieza == 5){
          return true;
        }
      }
      if(Tablero[reyPropio[0] - 1][reyPropio[1] - 2].color != Tablero[reyPropio[0]][reyPropio[1]].color){
        Serial.println("f 8vo");
        Serial.println(Tablero[reyPropio[0] - 1][reyPropio[1] - 2].id_pieza);
        if(Tablero[reyPropio[0] - 1][reyPropio[1] - 2].id_pieza == 5){
          return true;
        }
      }
      if((reyPropio[0] + i) < 8){
         if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0] + i,reyPropio[1]) && Tablero[reyPropio[0] + i][reyPropio[1]].id_pieza != 100){
          if(Tablero[reyPropio[0] + i][reyPropio[1]].id_pieza == 2 || Tablero[reyPropio[0] + i][reyPropio[1]].id_pieza == 3){
            if(Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color){
            Serial.println("adentro: 1");
            Serial.println(i);
            return true;
            }
          }
         }
      }
      if((reyPropio[1] + i) < 8){
         if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0],reyPropio[1] + i) && Tablero[reyPropio[0]][reyPropio[1] + i].id_pieza != 100){
          if(Tablero[reyPropio[0]][reyPropio[1] + i].id_pieza == 2 || Tablero[reyPropio[0]][reyPropio[1] + i].id_pieza == 3){
            if(Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color){
            Serial.println("adentro: 2");
            Serial.println(i);
            return true;
            }
          }
         }
      }
      if((reyPropio[0] - i) >= 0){
         if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0] - i,reyPropio[1]) && Tablero[reyPropio[0] - i][reyPropio[1]].id_pieza != 100){
          if(Tablero[reyPropio[0] - i][reyPropio[1]].id_pieza == 2 || Tablero[reyPropio[0] - i][reyPropio[1]].id_pieza == 3){
            if(Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color){
            Serial.println("adentro: 3");
            Serial.println(i);
            return true;
            }
          }
         }
      }
      if((reyPropio[1] - i) >= 0){
         if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0],reyPropio[1] - i) && Tablero[reyPropio[0]][reyPropio[1] - i].id_pieza != 100 && (reyPropio[1] - i) >= 0){
          if(Tablero[reyPropio[0]][reyPropio[1] - i].id_pieza == 2 || Tablero[reyPropio[0]][reyPropio[1] - i].id_pieza == 3){
            if(Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color){
              Serial.print("adentro: 4 i: ");
              Serial.print(i);
              Serial.print(" reyPropio: ");
              Serial.println(reyPropio[1] - i);
              return true;
            }
          }
         }
      }
      if((reyPropio[0] + i) < 8 && (reyPropio[1] + i) < 8){
        if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0] + i,reyPropio[1] + 1) && Tablero[reyPropio[0] + i][reyPropio[1] + i].id_pieza != 100){
          if(Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color){
            if(Tablero[reyPropio[0] + i][reyPropio[1] + i].id_pieza == 4){
              Serial.println("adentro: 5");
              return true;
            }
            if(Tablero[reyPropio[0] + i][reyPropio[1] + i].id_pieza == 6 && i == 1){
              Serial.println("adentro: 6");
              return true;
            }
          }
        }
      }
      if((reyPropio[0] - i) >= 0 && (reyPropio[1] - i) >= 0){
        if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0] - i,reyPropio[1] - i) && Tablero[reyPropio[0] - i][reyPropio[1] - i].id_pieza != 100){
          if(Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color){
            if(Tablero[reyPropio[0] - i][reyPropio[1] - i].id_pieza == 4){
              Serial.println("adentro: 7");
              return true;
            }
            if(Tablero[reyPropio[0] - i][reyPropio[1] - i].id_pieza == 6 && i == 1){
              Serial.println("adentro: 8");
              return true;
            }
          }
        }
      }
      if((reyPropio[0] - i) >= 0 && (reyPropio[1] + i) < 8){
        if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0] - i,reyPropio[1] + i) && Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza != 100){
        Serial.print("primero adentro: ");
        Serial.print(i);
        Serial.print(" | ");
        Serial.print(reyPropio[0] - i);
        Serial.print(" | ");
        Serial.print(reyPropio[1] + i);
        Serial.print(" | ");
        Serial.print(Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza);
        Serial.print(" | ");
        Serial.println(Tablero[reyPropio[0] - i][reyPropio[1] + i].color);
        
          if(Tablero[reyPropio[0] - i][reyPropio[1] + i].color != Tablero[reyPropio[0]][reyPropio[1]].color){
            Serial.println("segundo adentro: ");
            if(Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza == 4){
              Serial.println("adentro: 9");
              return true;
            }
            if(Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza == 2){
              Serial.println("adentro: 9,5"); 
              return true;
            }
            if(Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza == 6 && i == 1){
              Serial.println("adentro: 10");
              return true;
            }
          }
        }
      }
      if((reyPropio[0] + i) < 8 && (reyPropio[1] - i) >= 0){
        if(intercepcion(Tablero,reyPropio[0],reyPropio[1],reyPropio[0] + i,reyPropio[1] - i) && Tablero[reyPropio[0] + i][reyPropio[1] - i].id_pieza != 100 && matar(Tablero,reyPropio[0],reyPropio[1],reyPropio[0] + i,reyPropio[1] - i)){
          if(Tablero[reyPropio[0] + i][reyPropio[1] - i].id_pieza == 4){
            Serial.println("adentro: 11");
            return true;
          }
          if(Tablero[reyPropio[0] + i][reyPropio[1] - i].id_pieza == 6 && i == 1){
            Serial.println("adentro: 12");
            return true;
          }
        }
      }
      i = i + 1;
    }
    return false;
}
bool jaquemate(Pieza Tablero[8][8],bool color){
  int reyPropio[2];
    bool hayRey = true;
    int i = 0;
    int x = 0;
    while(i < 8){
      while(x < 8){
        if(Tablero[i][x].id_pieza == 1 && Tablero[i][x].color == color){
          reyPropio[0] = i;
          reyPropio[1] = x;
          hayRey = false;
        }
        x = x + 1;
      }
      x = 0;
      i = i + 1;
    }
    return hayRey;
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
