// ACLARACION: la funcion cambiar podria estar implementada directamente en cada if pero como requiere mover todos los datos de una posicion a otra y eliminar los de la anterior fue mejor
//             crear la funcion
#define rey 1
#define reina 2
#define torre 3
#define alfil 4
#define caballo 5
#define peon 6

struct Pieza{
    bool color;
    int id_pieza=0;
    bool movimiento;
    int posicionOrigenX;
    int posicionOrigenY;
};

Pieza tablero[8][8]

void setup() {
  
  // void
  void arreglar(Pieza tablero[8][8],int turno);
  void cambiar(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
  void Inicializar_Tablero(Pieza Tablero[8][8]);
  // bool
  bool caminoPrendido(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
  bool intercepcion(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
  bool seguir(Pieza tablero[8][8]);
  bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox,int turno);
  bool jaque(Pieza Tablero[8][8],int turno);

}

void loop() {
  Inicializar_Tablero(tablero[8][8]);
  while(true){
    
    //Lee mensaje
    //Gana o pierde? (Iluminar)
    //Actualizar el movimiento enemigo (comió? cambió?)
    //Busca jaque (Hay? Mostrar desde donde e iluminar el boton)
    //Imprimir menu (tiempo, ultimo movimiento y menu: enroque corto, largo, ofrecer tablas y rendirse)
      //Se rinde? 
    //CICLO    
      //Esperar movimiento del chaboncito (Mostrar posiciones posibles, ofrecer movimientos especiales)
      //Verificar movimiento (Si está mal poner el tablero en rojo. Si mueve varios titila en rojo el boton tambien. Verificar captura al paso)
    //Coronacion?
    //Espera boton
    //Envia mensaje (Cambia de tablero)
  }
}

void Inicializar_Tablero(Pieza Tablero[8][8])
{
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
        }
    }
}

bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox,int turno){ //Se verifica el movimiento de una pieza
  
    int comprobantey, comprobantex;
    comprobantey = cordenaday - movimientoy;    //comporabante X e Y sirven pasa saber cuanto se movio independiente mente de su direccion
    comprobantex = cordenadax - movimientox;    //solo en el peon es necesario saber si el movimiento fue positivo o negativo
    comprobantex = sqrt(pow(comprobantex,2)); //pasa los numeros a positivo
    comprobantey = sqrt(pow(comprobantey,2)); //pasa los numeros a positivo
    // a partir de aca todos los if's y elseif's corresponden a una pieza y su forma de moverse
    // para que esta clase funcione hay que tener: una clase intercepcion que vustre que en su trayecto la pieza no se tope con otra de su color y
    // la posicion de las piezas tienen que ser matrizes que tengan id's, color, posicion X e Y, movimiento(para saber si es la primera vez que se mueve),
    if(((comprobantex + comprobantey) == 3 && (comprobantex != 3 || comprobantey != 3)) && (Tablero[cordenaday][cordenadax].id_pieza == caballo)){
        cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); //esta clase cambia la posicion de un objeto de lugar, habria que hacer otra similar * 
    }
    else if(Tablero[cordenaday][cordenadax].id_pieza == alfil && (comprobantex==comprobantey)  && intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
    }
    else if(((comprobantey==0 && comprobantex!=0)||(comprobantex==0 && comprobantey!=0))&& Tablero[cordenaday][cordenadax].id_pieza==torre && intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
    }
    else if(((comprobantex == 0 && comprobantey > 0) || (comprobantex > 0 && comprobantey == 0) || (comprobantex == comprobantey)) && (Tablero[cordenaday][cordenadax].id_pieza==reina) && intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
    }
    else if((comprobantex==1 || comprobantey ==1) && Tablero[cordenaday][cordenadax].id_pieza==rey && intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
    }
    else if(((turno==1 && cordenaday < movimientoy) || (turno == 0 && cordenaday > movimientoy)) && (comprobantex == 0 && comprobantey == 1) || ((cordenaday == 6 || cordenaday == 1) && (comprobantex == 0 && comprobantey == 2)) && (Tablero[cordenaday][cordenadax].id_pieza==peon) && intercepcion(Tablero,cordenaday,cordenadax,movimientoy,movimientox)){
        cambiar(Tablero,cordenaday,cordenadax,movimientoy,movimientox); // * same
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
                if(Tablero[cordenaday+i][cordenadax+i].id_pieza != 0){
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday > movimientoy){
                if(Tablero[cordenaday-i][cordenadax-i].id_pieza != 0){
                    return false;
                }
            }
            else if(cordenadax < movimientox && cordenaday > movimientoy){
                if(Tablero[cordenaday-i][cordenadax+i].id_pieza != 0){
                    return false;
                }
            }
            else if(cordenadax > movimientox && cordenaday < movimientoy){
                if(Tablero[cordenaday+i][cordenadax-i].id_pieza != 0){
                    return false;
                }
            }
        }
    }
    else if(comprobantex == 0){ // si se mueve de forma vertical utiliza este IF
        for(int i = 1;i < comprobantey;i++){ // mueve la pieza de lugar en lugar hasta hallar a una pieza
            if(cordenaday < movimientoy){ // va de arriba a abajo
                if(Tablero[cordenaday+i][cordenadax].id_pieza != 0){ // si encuentra un lugar en con una id valida significa que hay una pieza y devuelve false *2
                    return false;
                }
            }
            else if(cordenaday > movimientoy){ // va de abajo a arriba
                if(Tablero[cordenaday-i][cordenadax].id_pieza != 0){ // * same2
                    return false;
                }
            }
        }
    }
    else if(comprobantey == 0){ // si se mueve de forma horizontal utiliza este IF
        for(int i = 1;i < comprobantex;i++){
            if(cordenadax < movimientox){ // va de izquierda a derecha
                if(Tablero[cordenaday][cordenadax+i].id_pieza != 0){ // * same2
                    return false;
                }
            }
            else if(cordenadax > movimientox){ // va de derecha a izquierda
                if(Tablero[cordenaday][cordenadax-i].id_pieza != 0){ // * same2
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
void arreglar(Pieza tablero[8][8],int turno){ // este void pasa por las filas 4 y 6 para verificar que los peones que ya se movieron dos movimientos tengan la variable movimiento en true
    if(turno == 0){                           // de esta forma no se permite comer al paso si la oportunidad de hacerlo no se ejecuto el turno anterior.
        for(int i = 0;i < 8;i++){
            if(tablero[3][i].id_pieza == peon && (!tablero[3][i].movimiento)){
                tablero[3][i].movimiento = true;
            }
        }
    }
    if(turno == 1){
        for(int i = 0;i < 8;i++){
            if(tablero[4][i].id_pieza == peon && (!tablero[4][i].movimiento)){
                tablero[4][i].movimiento = true;
            }
        }
    }
}

bool jaque(Pieza Tablero[8][8],bool color, int lugar[2]){ // esta funcion verifica si el rey está en jaque. También devuelve el lugar desde donde se está haciendo el jaque.
                                          
    int reyBlanco[2]; // la posicion del rey es un array de 2 para guardar X e Y
    for(int y = 0;y < 8;y++){
        for(int x = 0;x < 8;x++){
            if(Tablero[y][x].id_pieza == rey){
                if(Tablero[y][x].color == color){
                    reyBlanco[0] = y;
                    reyBlanco[1] = x;
                }
            }
        }
    }
    for(int x = 0;x < 8;x++){
        if(reyBlanco[1]+x < 8){
            if((Tablero[reyBlanco[0]][reyBlanco[1]+x].id_pieza == torre || Tablero[reyBlanco[0]][reyBlanco[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0],reyBlanco[1]+x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0],reyBlanco[1]+x)){
                lugar[0] = reyBlanco[0]
                lugar[1] = reyBlanco[1]+x
                return true;
            }
        }
        if(reyBlanco[1]-x >= 0){
            if((Tablero[reyBlanco[0]][reyBlanco[1]-x].id_pieza == torre || Tablero[reyBlanco[0]][reyBlanco[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0],reyBlanco[1]-x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0],reyBlanco[1]-x)){
                lugar[0] = reyBlanco[0]
                lugar[1] = reyBlanco[1]-x
                return true;
            }
        }
        if(reyBlanco[0]+x < 8){
            if((Tablero[reyBlanco[0]+x][reyBlanco[1]].id_pieza == torre || Tablero[reyBlanco[0]+x][reyBlanco[1]].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]+x,reyBlanco[1],0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]+x,reyBlanco[1])){
                lugar[0] = reyBlanco[0]+x
                lugar[1] = reyBlanco[1]
                return true;
            }
        }
        if(reyBlanco[0]-x >= 0){
            if((Tablero[reyBlanco[0]-x][reyBlanco[1]].id_pieza == torre || Tablero[reyBlanco[0]-x][reyBlanco[1]].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]-x,reyBlanco[1],0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]-x,reyBlanco[1])){
                lugar[0] = reyBlanco[0]-x
                lugar[1] = reyBlanco[1]
                return true;
            }
        }
        //alfil
        if(reyBlanco[1]+x < 8 && reyBlanco[0]+x < 8){
            if((Tablero[reyBlanco[0]+x][reyBlanco[1]+x].id_pieza == alfil || Tablero[reyBlanco[0]+x][reyBlanco[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]+x,reyBlanco[1]+x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]+x,reyBlanco[1]+x)){
                lugar[0] = reyBlanco[0]+x
                lugar[1] = reyBlanco[1]+x
                return true;
            }
        }
        if(reyBlanco[1]-x >= 0 && reyBlanco[0]-x >= 0){
            if((Tablero[reyBlanco[0]-x][reyBlanco[1]-x].id_pieza == alfil || Tablero[reyBlanco[0]][reyBlanco[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]-x,reyBlanco[1]-x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]-x,reyBlanco[1]-x)){
                lugar[0] = reyBlanco[0]-x
                lugar[1] = reyBlanco[1]-x
                return true;
            }
        }
        if(reyBlanco[0]+x < 8 && reyBlanco[1]-x >= 0){
            if((Tablero[reyBlanco[0]+x][reyBlanco[1]-x].id_pieza == alfil || Tablero[reyBlanco[0]+x][reyBlanco[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]+x,reyBlanco[1]-x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]+x,reyBlanco[1]-x)){
                lugar[0] = reyBlanco[0]+x
                lugar[1] = reyBlanco[1]-x
                return true;
            }
        }
        if(reyBlanco[0]-x >= 0 && reyBlanco[1]+x < 8){
            if((Tablero[reyBlanco[0]-x][reyBlanco[1]+x].id_pieza == alfil || Tablero[reyBlanco[0]-x][reyBlanco[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]-x,reyBlanco[1]+x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]-x,reyBlanco[1]+x)){
                lugar[0] = reyBlanco[0]-x
                lugar[1] = reyBlanco[1]+x
                return true;
            }
        }
    }
    return false;
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
        leds[0] = cordenadax
        for(int i = 1;i < comprobantey;i++){ // mueve la pieza de lugar en lugar hasta hallar a una pieza
            leds[1] = cordenaday + i
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
        leds[1] = cordenaday
        for(int i = 1;i < comprobantex;i++){
            leds[0] = cordenaday + i
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
