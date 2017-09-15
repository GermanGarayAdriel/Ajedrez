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

// voids
void arreglar(Pieza tablero[8][8],int turno);
void cambiar(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
void Inicializar_Tablero(Pieza Tablero[8][8]);
// bools
bool intercepcion(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox);
bool seguir(Pieza tablero[8][8]);
bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox,int turno);
// ints
int jaque(Pieza Tablero[8][8],int turno);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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

bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox,int turno){
    // aca se ingresan todas las posiciones del tablero, la pieza a mover, hacia donde se movio y el turno (para que no se muevan piezas blancas en turno de negras
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

bool intercepcion(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox){
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
void cambiar(Pieza Tablero[8][8], int cordenaday, int cordenadax,int movimientoy,int movimientox){
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
bool seguir(Pieza tablero[8][8]){ // esta funcion verifica si los reyes siguen vivos. De estarlos la funcion devolvera True, caso contrario la repuesta sera False
  int reyes = 0;
  for(int y = 0;y < 8;y++){
      for(int x = 0;x < 8;x++){
          if(tablero[y][x].id_pieza == rey){
              reyes++;
              if(tablero[y][x].color == 127 || tablero[y][x].color == 111){
                  ganador = false;
              }
              else{
                  ganador = true;
              }
          }
      }
  }
  if(reyes != 2){
      color(15);
      system("cls");
      cout << "han ganado las ";
      if(ganador == false){
          cout << "blancas" << endl;
      }
      else{
          cout << "negras" << endl;
      }
      system("pause");
      system("cls");
      return False;
      break;
  }
  return True;
}
int jaque(Pieza Tablero[8][8],int turno){ // esta funcion verifica si alguno de los reyes esta en jaque. si el rey blanco esta en jaque devuelve 1 y si el que esta en jaque es el rey negro
                                          // retorna 2, pero si ninguno esta en jaque la función devuelve 0
    int reyBlanco[2]; // la posicion del rey es un array de 2 para guardar X e Y
    int reyNegro[2];
    for(int y = 0;y < 8;y++){
        for(int x = 0;x < 8;x++){
            if(Tablero[y][x].id_pieza == rey){
                if(Tablero[y][x].color == 127 || Tablero[y][x].color == 111){
                    reyBlanco[0] = y;
                    reyBlanco[1] = x;
                }
                else{
                    reyNegro[0] = y;
                    reyNegro[1] = x;
                }
            }
        }
    }
    for(int x = 0;x < 8;x++){
        if(reyBlanco[1]+x < 8){
            if((Tablero[reyBlanco[0]][reyBlanco[1]+x].id_pieza == torre || Tablero[reyBlanco[0]][reyBlanco[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0],reyBlanco[1]+x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0],reyBlanco[1]+x)){
                return 1;
            }
        }
        if(reyBlanco[1]-x >= 0){
            if((Tablero[reyBlanco[0]][reyBlanco[1]-x].id_pieza == torre || Tablero[reyBlanco[0]][reyBlanco[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0],reyBlanco[1]-x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0],reyBlanco[1]-x)){
                return 1;
            }
        }
        if(reyNegro[1]+x < 8){
            if((Tablero[reyNegro[0]][reyNegro[1]+x].id_pieza == torre || Tablero[reyNegro[0]][reyNegro[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0],reyNegro[1]+x,1) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0],reyNegro[1]+x)){
                return 2;
            }
        }
        if(reyNegro[1]-x >= 0){
            if((Tablero[reyNegro[0]][reyNegro[1]-x].id_pieza == torre || Tablero[reyNegro[0]][reyNegro[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0],reyNegro[1]-x,1) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0],reyNegro[1]-x)){
                return 2;
            }
        }
        if(reyBlanco[0]+x < 8){
            if((Tablero[reyBlanco[0]+x][reyBlanco[1]].id_pieza == torre || Tablero[reyBlanco[0]+x][reyBlanco[1]].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]+x,reyBlanco[1],0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]+x,reyBlanco[1])){
                return 1;
            }
        }
        if(reyBlanco[0]-x >= 0){
            if((Tablero[reyBlanco[0]-x][reyBlanco[1]].id_pieza == torre || Tablero[reyBlanco[0]-x][reyBlanco[1]].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]-x,reyBlanco[1],0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]-x,reyBlanco[1])){
                return 1;
            }
        }
        if(reyNegro[0]+x < 8){
            if((Tablero[reyNegro[0]+x][reyNegro[1]].id_pieza == torre || Tablero[reyNegro[0]+x][reyNegro[1]].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0]+x,reyNegro[1],1) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0]+x,reyNegro[1])){
                return 2;
            }
        }
        if(reyNegro[0]-x >= 0){
            if((Tablero[reyNegro[0]-x][reyNegro[1]].id_pieza == torre || Tablero[reyNegro[0]-x][reyNegro[1]].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0]-x,reyNegro[1],1) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0]-x,reyNegro[1])){
                return 2;
            }
        }
        //alfil
        if(reyBlanco[1]+x < 8 && reyBlanco[0]+x < 8){
            if((Tablero[reyBlanco[0]+x][reyBlanco[1]+x].id_pieza == torre || Tablero[reyBlanco[0]+x][reyBlanco[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]+x,reyBlanco[1]+x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]+x,reyBlanco[1]+x)){
                return 1;
            }
        }
        if(reyBlanco[1]-x >= 0 && reyBlanco[0]-x >= 0){
            if((Tablero[reyBlanco[0]-x][reyBlanco[1]-x].id_pieza == torre || Tablero[reyBlanco[0]][reyBlanco[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]-x,reyBlanco[1]-x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]-x,reyBlanco[1]-x)){
                return 1;
            }
        }
        if(reyBlanco[0]+x < 8 && reyBlanco[1]-x >= 0){
            if((Tablero[reyBlanco[0]+x][reyBlanco[1]-x].id_pieza == torre || Tablero[reyBlanco[0]+x][reyBlanco[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]+x,reyBlanco[1]-x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]+x,reyBlanco[1]-x)){
                return 1;
            }
        }
        if(reyBlanco[0]-x >= 0 && reyBlanco[1]+x < 8){
            if((Tablero[reyBlanco[0]-x][reyBlanco[1]+x].id_pieza == torre || Tablero[reyBlanco[0]-x][reyBlanco[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyBlanco[0]-x,reyBlanco[1]+x,0) && intercepcion(Tablero,reyBlanco[0],reyBlanco[1],reyBlanco[0]-x,reyBlanco[1]+x)){
                return 1;
            }
        }
        //alfil negro
        if(reyNegro[1]+x < 8 && reyNegro[0]+x < 8){
            if((Tablero[reyNegro[0]+x][reyNegro[1]+x].id_pieza == torre || Tablero[reyNegro[0]+x][reyNegro[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0]+x,reyNegro[1]+x,0) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0]+x,reyNegro[1]+x)){
                return 2;
            }
        }
        if(reyNegro[1]-x >= 0 && reyNegro[0]-x >= 0){
            if((Tablero[reyNegro[0]-x][reyNegro[1]-x].id_pieza == torre || Tablero[reyNegro[0]][reyNegro[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0]-x,reyNegro[1]-x,0) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0]-x,reyNegro[1]-x)){
                return 2;
            }
        }
        if(reyNegro[0]+x < 8 && reyNegro[1]-x >= 0){
            if((Tablero[reyNegro[0]+x][reyNegro[1]-x].id_pieza == torre || Tablero[reyNegro[0]+x][reyNegro[1]-x].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0]+x,reyNegro[1]-x,0) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0]+x,reyNegro[1]-x)){
                return 2;
            }
        }
        if(reyNegro[0]-x >= 0 && reyNegro[1]+x < 8){
            if((Tablero[reyNegro[0]-x][reyNegro[1]+x].id_pieza == torre || Tablero[reyNegro[0]-x][reyNegro[1]+x].id_pieza == reina) && confirmarEnemigo(Tablero,reyNegro[0]-x,reyNegro[1]+x,0) && intercepcion(Tablero,reyNegro[0],reyNegro[1],reyNegro[0]-x,reyNegro[1]+x)){
                return 2;
            }
        }
    }
    return 0;
}
