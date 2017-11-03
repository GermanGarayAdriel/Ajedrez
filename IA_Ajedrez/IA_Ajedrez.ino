int rey = 1;
int reina = 2;
int torre = 3;
int alfil = 4;
int caballo = 5;
int peon = 6;

struct Pieza {
  bool color;
  int id_pieza = 0;
  bool movimiento;
  int posicionOrigenX;
  int posicionOrigenY;
};
Pieza tablero[8][8];
int total[16][2];
int total2[16][2];
void Inicializar_Tablero(Pieza Tablero[8][8]);
void cambiar(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox);
bool intercepcion(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox);
bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox, int turno);
bool verificar_reytorre(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox);
bool jaque(Pieza Tablero[8][8], bool color);
bool jaquemate(Pieza Tablero[8][8], bool color);
bool matar(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox);
bool puedeComer(Pieza tablero[8][8], int movimiento[2]);
bool puedoMover(Pieza tablero[8][8], int coordenaday, int coordenadax, int movimiento[2]);
bool Inteligencia(Pieza tablero[8][8], int cordenada[2], int movimiento[2]);

void setup() {
  // put your setup code here, to run once:
  int incomingByte = 0;
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  Inicializar_Tablero(tablero);
  int cordenaday;
  int cordenadax;
  int movimientoy;
  int movimientox;
  int letra;
  bool antiloop = true;
  bool entrar = true;
  int incomingByte;
  int movimiento[2];
  int coordenada[2];
  for (int i = 0; i < 16; i++) {
    if (total[i][0] != 100) {
      Serial.print("pieza: ");
      Serial.print(tablero[total[i][0]][total[i][1]].id_pieza);
      Serial.print(" en Y: ");
      Serial.print(total[i][0]);
      Serial.print(" X: ");
      Serial.println(total[i][1]);
    }
  }
  while (true) {
    Serial.println();
    for (int y = 0; y < 8; y++) {
      if (y == 0) {
        Serial.print("|");
        for (int x = 0; x < 8; x++) {
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print(x);
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print("|");
        }
        Serial.println();
      }
      Serial.print("|");
      for (int x = 0; x < 9; x++) {
        if (x < 8) {
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print(tablero[y][x].id_pieza);
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print("|");
        }
        else {
          Serial.print(y);
          Serial.print(" |");
        }
      }
      Serial.println();
      Serial.println("---------------------------------");
    }

    antiloop = true;
    while (antiloop) {
      Inteligencia(tablero, coordenada, movimiento);
      cordenaday = coordenada[0];
      cordenadax = coordenada[1];
      movimientoy = movimiento[0];
      movimientox = movimiento[1];
      Serial.println("paso");
      if (jaquemate(tablero, true)) {
        Serial.println("rey blanco no existe, fin del juego. Ganan negras");
        break;
      }
      if (jaque(tablero, true)) {
        Serial.println("rey blanco en jaque");
      }
      Serial.println("blancas");
      Serial.print("|");
      Serial.print(tablero[cordenaday][cordenadax].id_pieza);
      Serial.print("|");
      if (Verificar_Movimiento(tablero, cordenaday, cordenadax, movimientoy, movimientox, 1)) {
        Serial.println("movimiento correcto");
        antiloop = false;
      }
      else if (verificar_reytorre(tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
        Serial.println("movimiento correcto");
        antiloop = false;
      }
      else {
        Serial.println("movimiento incorrecto");
        letra = 0;
        antiloop = true;
      }
    }
    Serial.println();
    for (int y = 0; y < 8; y++) {
      if (y == 0) {
        Serial.print("|");
        for (int x = 0; x < 8; x++) {
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print(x);
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print("|");
        }
        Serial.println();
      }
      Serial.print("|");
      for (int x = 0; x < 9; x++) {
        if (x < 8) {
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print(tablero[y][x].id_pieza);
          if (tablero[y][x].id_pieza != 100) {
            Serial.print(" ");
          }
          Serial.print("|");
        }
        else {
          Serial.print(y);
          Serial.print(" |");
        }
      }
      Serial.println();
      Serial.println("---------------------------------");
    }
    antiloop = true;
    while (antiloop) {
      entrar = true;
      int letra = 0;

      while (entrar) {
        if (Serial.available() > 0) {
          // lee el byte de entrada:
          incomingByte = Serial.read();
          if (letra == 0) {
            cordenaday = incomingByte - 48;
          }
          else if (letra == 1) {
            cordenadax = incomingByte - 48;
          }
          else if (letra == 2) {
            movimientoy = incomingByte - 48;
          }
          else if (letra == 3) {
            movimientox = incomingByte - 48;
            entrar = false;
          }
          letra = letra + 1;
          //lo vuelca a pantalla
          Serial.print("He recibido: "); Serial.println(incomingByte - 48, DEC);
        }
      }
      Serial.println("paso");
      letra = 0;
      if (jaquemate(tablero, false)) {
        Serial.println("rey negro no existe, fin del juego. Ganan blancas");
      }
      if (jaque(tablero, false)) {
        Serial.println("rey negro en jaque");
      }
      Serial.println("negras");
      Serial.print("|");
      Serial.print(tablero[cordenaday][cordenadax].id_pieza);
      Serial.print("|");
      if (Verificar_Movimiento(tablero, cordenaday, cordenadax, movimientoy, movimientox, 0)) {
        Serial.println("movimiento correcto");
        antiloop = false;
      }
      else if (verificar_reytorre(tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
        Serial.println("movimiento correcto");
        antiloop = false;
      }
      else {
        Serial.println("movimiento incorrecto");
        antiloop = true;
      }
    }
  }
}



bool puedeComer(Pieza tablero[8][8], int movimiento[2], int coordenada[2]) {
  for (int i = 0; i < 16; i++) {
    if (total[i][0] != 100) {
      if (tablero[total[i][0]][total[i][1]].id_pieza == 6) {
        if (total[i][0] + 1 < 8 && total[i][1] - 1 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 1, total[i][1] - 1) && tablero[total[i][0] + 1][total[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total[i][0] + 1;
            movimiento[1] = total[i][1] - 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] + 1 < 8 && total[i][1] + 1 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 1, total[i][1] + 1) && tablero[total[i][0] + 1][total[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total[i][0] + 1;
            movimiento[1] = total[i][1] + 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
      }
      else if (tablero[total[i][0]][total[i][1]].id_pieza == caballo) {
        if (total[i][0] + 2 < 8 && total[i][1] + 1 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 2, total[i][1] + 1) && tablero[total[i][0] + 2][total[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total[i][0] + 2;
            movimiento[1] = total[i][1] + 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] + 2 < 8 && total[i][1] - 1 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 2, total[i][1] - 1) && tablero[total[i][0] + 2][total[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total[i][0] + 2;
            movimiento[1] = total[i][1] - 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] - 2 >= 0 && total[i][1] + 1 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] - 2, total[i][1] + 1) && tablero[total[i][0] - 2][total[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total[i][0] - 2;
            movimiento[1] = total[i][1] + 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] - 2 >= 0 && total[i][1] - 1 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] - 2, total[i][1] - 1) && tablero[total[i][0] - 2][total[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total[i][0] - 2;
            movimiento[1] = total[i][1] - 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] + 1 < 8 && total[i][1] + 2 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 1, total[i][1] + 2) && tablero[total[i][0] + 1][total[i][1] + 2].id_pieza != 100) {
            movimiento[0] = total[i][0] + 1;
            movimiento[1] = total[i][1] + 2;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] - 1 >= 0 && total[i][1] + 2 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] - 1, total[i][1] + 2) && tablero[total[i][0] - 1][total[i][1] + 2].id_pieza != 100) {
            movimiento[0] = total[i][0] - 1;
            movimiento[1] = total[i][1] + 2;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] + 1 < 8 && total[i][1] - 2 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 1, total[i][1] - 2) && tablero[total[i][0] + 1][total[i][1] - 2].id_pieza != 100) {
            movimiento[0] = total[i][0] + 1;
            movimiento[1] = total[i][1] - 2;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] - 1 >= 0 && total[i][1] - 2 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] - 1, total[i][1] - 2) && tablero[total[i][0] - 1][total[i][1] - 2].id_pieza != 100) {
            movimiento[0] = total[i][0] - 1;
            movimiento[1] = total[i][1] - 2;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
      }
      if (tablero[total[i][0]][total[i][1]].id_pieza == 4 || tablero[total[i][0]][total[i][1]].id_pieza == 2) {
        for (int m = 0; m < 8; m++) {
          if (total[i][0] + m < 8 && total[i][1] + m < 8) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0] + m, total[i][1] + m) && tablero[total[i][0] + m][total[i][1] + m].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0] + m, total[i][1] + m)) {
                movimiento[0] = total[i][0] + m;
                movimiento[1] = total[i][1] + m;
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
          if (total[i][0] - m >= 0 && total[i][1] + m < 8) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0] - m, total[i][1] + m) && tablero[total[i][0] - m][total[i][1] + m].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0] - m, total[i][1] + m)) {
                movimiento[0] = total[i][0] - m;
                movimiento[1] = total[i][1] + m;
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
          if (total[i][0] + m < 8 && total[i][1] - m >= 0) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0] + m, total[i][1] - m) && tablero[total[i][0] + m][total[i][1] - m].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0] + m, total[i][1] - m)) {
                movimiento[0] = total[i][0] + m;
                movimiento[1] = total[i][1] - m;
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
          if (total[i][0] - m >= 0 && total[i][1] - m >= 0) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0] - m, total[i][1] - m) && tablero[total[i][0] - m][total[i][1] - m].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0] - m, total[i][1] - m)) {
                movimiento[0] = total[i][0] - m;
                movimiento[1] = total[i][1] - m;
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
        }
      }
      if (tablero[total[i][0]][total[i][1]].id_pieza == 3 || tablero[total[i][0]][total[i][1]].id_pieza == 2) {
        for (int m = 0; m < 8; m++) {
          if (total[i][1] + m < 8) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0], total[i][1] + m) && tablero[total[i][0]][total[i][1] + m].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0], total[i][1] + m)) {
                movimiento[0] = total[i][0];
                movimiento[1] = total[i][1] + m;
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
          if (total[i][1] - m >= 0) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0], total[i][1] - m) && tablero[total[i][0]][total[i][1] - m].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0], total[i][1] - m)) {
                movimiento[0] = total[i][0];
                movimiento[1] = total[i][1] - m;
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
          if (total[i][0] + m < 8) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0] + m, total[i][1]) && tablero[total[i][0] + m][total[i][1]].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0] + m, total[i][1])) {
                movimiento[0] = total[i][0] + m;
                movimiento[1] = total[i][1];
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
          if (total[i][0] - m >= 0) {
            if (matar(tablero, total[i][0], total[i][1], total[i][0] - m, total[i][1]) && tablero[total[i][0] - m][total[i][1]].id_pieza != 100) {
              if (intercepcion(tablero, total[i][0], total[i][1], total[i][0] - m, total[i][1])) {
                movimiento[0] = total[i][0] - m;
                movimiento[1] = total[i][1];
                coordenada[0] = total[i][0];
                coordenada[1] = total[i][1];
                return true;
              }
            }
          }
        }
      }
      if (tablero[total[i][0]][total[i][1]].id_pieza == 1) {
        if (total[i][0] + 1 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 1, total[i][1]) && tablero[total[i][0] + 1][total[i][1]].id_pieza != 100) {
            movimiento[0] = total[i][0] + 1;
            movimiento[1] = total[i][1];
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] - 1 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] - 1, total[i][1]) && tablero[total[i][0] - 1][total[i][1]].id_pieza != 100) {
            movimiento[0] = total[i][0] - 1;
            movimiento[1] = total[i][1];
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][1] + 1 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0], total[i][1] + 1) && tablero[total[i][0]][total[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total[i][0];
            movimiento[1] = total[i][1] + 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][1] - 1 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0], total[i][1] - 1) && tablero[total[i][0]][total[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total[i][0];
            movimiento[1] = total[i][1] - 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] + 1 < 8 && total[i][1] + 1 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 1, total[i][1] + 1) && tablero[total[i][0] + 1][total[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total[i][0] + 1;
            movimiento[1] = total[i][1] + 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] - 1 >= 0 && total[i][1] + 1 < 8) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] - 1, total[i][1] + 1) && tablero[total[i][0] - 1][total[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total[i][0] - 1;
            movimiento[1] = total[i][1] + 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][0] + 1 < 8 && total[i][1] - 1 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] + 1, total[i][1] - 1) && tablero[total[i][0] + 1][total[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total[i][0] + 1;
            movimiento[1] = total[i][1] - 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
        if (total[i][1] - 1 >= 0 && total[i][0] - 1 >= 0) {
          if (matar(tablero, total[i][0], total[i][1], total[i][0] - 1, total[i][1] - 1) && tablero[total[i][0] - 1][total[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total[i][0] - 1;
            movimiento[1] = total[i][1] - 1;
            coordenada[0] = total[i][0];
            coordenada[1] = total[i][1];
            return true;
          }
        }
      }
    }
  }
  return false;
}
bool puedeComer2(Pieza tablero[8][8], int movimiento[2], int coordenada[2]) {
  for (int i = 0; i < 16; i++) {
    if (total2[i][0] != 100) {
      if (tablero[total2[i][0]][total2[i][1]].id_pieza == 6) {
        if (total2[i][0] - 1 >= 0 && total2[i][1] - 1 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 1, total2[i][1] - 1) && tablero[total2[i][0] - 1][total2[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 1;
            movimiento[1] = total2[i][1] - 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] - 1 >= 0 && total2[i][1] + 1 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 1, total2[i][1] + 1) && tablero[total2[i][0] - 1][total2[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 1;
            movimiento[1] = total2[i][1] + 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
      }
      else if (tablero[total2[i][0]][total2[i][1]].id_pieza == caballo) {
        if (total2[i][0] + 2 < 8 && total2[i][1] + 1 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + 2, total2[i][1] + 1) && tablero[total2[i][0] + 2][total2[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] + 2;
            movimiento[1] = total2[i][1] + 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] + 2 < 8 && total2[i][1] - 1 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + 2, total2[i][1] - 1) && tablero[total2[i][0] + 2][total2[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] + 2;
            movimiento[1] = total2[i][1] - 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] - 2 >= 0 && total2[i][1] + 1 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 2, total2[i][1] + 1) && tablero[total2[i][0] - 2][total2[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 2;
            movimiento[1] = total2[i][1] + 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] - 2 >= 0 && total2[i][1] - 1 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 2, total2[i][1] - 1) && tablero[total2[i][0] - 2][total2[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 2;
            movimiento[1] = total2[i][1] - 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] + 1 < 8 && total2[i][1] + 2 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + 1, total2[i][1] + 2) && tablero[total2[i][0] + 1][total2[i][1] + 2].id_pieza != 100) {
            movimiento[0] = total2[i][0] + 1;
            movimiento[1] = total2[i][1] + 2;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] - 1 >= 0 && total2[i][1] + 2 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 1, total2[i][1] + 2) && tablero[total2[i][0] - 1][total2[i][1] + 2].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 1;
            movimiento[1] = total2[i][1] + 2;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] + 1 < 8 && total2[i][1] - 2 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + 1, total2[i][1] - 2) && tablero[total2[i][0] + 1][total2[i][1] - 2].id_pieza != 100) {
            movimiento[0] = total2[i][0] + 1;
            movimiento[1] = total2[i][1] - 2;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] - 1 >= 0 && total2[i][1] - 2 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 1, total2[i][1] - 2) && tablero[total2[i][0] - 1][total2[i][1] - 2].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 1;
            movimiento[1] = total2[i][1] - 2;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
      }
      if (tablero[total2[i][0]][total2[i][1]].id_pieza == 4 || tablero[total2[i][0]][total2[i][1]].id_pieza == 2) {
        for (int m = 0; m < 8; m++) {
          if (total2[i][0] + m < 8 && total2[i][1] + m < 8) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + m, total2[i][1] + m) && tablero[total2[i][0] + m][total2[i][1] + m].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0] + m, total2[i][1] + m)) {
                movimiento[0] = total2[i][0] + m;
                movimiento[1] = total2[i][1] + m;
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
          if (total2[i][0] - m >= 0 && total2[i][1] + m < 8) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - m, total2[i][1] + m) && tablero[total2[i][0] - m][total2[i][1] + m].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0] - m, total2[i][1] + m)) {
                movimiento[0] = total2[i][0] - m;
                movimiento[1] = total2[i][1] + m;
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
          if (total2[i][0] + m < 8 && total2[i][1] - m >= 0) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + m, total2[i][1] - m) && tablero[total2[i][0] + m][total2[i][1] - m].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0] + m, total2[i][1] - m)) {
                movimiento[0] = total2[i][0] + m;
                movimiento[1] = total2[i][1] - m;
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
          if (total2[i][0] - m >= 0 && total2[i][1] - m >= 0) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - m, total2[i][1] - m) && tablero[total2[i][0] - m][total2[i][1] - m].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0] - m, total2[i][1] - m)) {
                movimiento[0] = total2[i][0] - m;
                movimiento[1] = total2[i][1] - m;
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
        }
      }
      if (tablero[total2[i][0]][total2[i][1]].id_pieza == 3 || tablero[total2[i][0]][total2[i][1]].id_pieza == 2) {
        for (int m = 0; m < 8; m++) {
          if (total2[i][1] + m < 8) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0], total2[i][1] + m) && tablero[total2[i][0]][total2[i][1] + m].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0], total2[i][1] + m)) {
                movimiento[0] = total2[i][0];
                movimiento[1] = total2[i][1] + m;
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
          if (total2[i][1] - m >= 0) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0], total2[i][1] - m) && tablero[total2[i][0]][total2[i][1] - m].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0], total2[i][1] - m)) {
                movimiento[0] = total2[i][0];
                movimiento[1] = total2[i][1] - m;
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
          if (total2[i][0] + m < 8) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + m, total2[i][1]) && tablero[total2[i][0] + m][total2[i][1]].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0] + m, total2[i][1])) {
                movimiento[0] = total2[i][0] + m;
                movimiento[1] = total2[i][1];
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
          if (total2[i][0] - m >= 0) {
            if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - m, total2[i][1]) && tablero[total2[i][0] - m][total2[i][1]].id_pieza != 100) {
              if (intercepcion(tablero, total2[i][0], total2[i][1], total2[i][0] - m, total2[i][1])) {
                movimiento[0] = total2[i][0] - m;
                movimiento[1] = total2[i][1];
                coordenada[0] = total2[i][0];
                coordenada[1] = total2[i][1];
                return true;
              }
            }
          }
        }
      }
      if (tablero[total2[i][0]][total2[i][1]].id_pieza == 1) {
        if (total2[i][0] + 1 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + 1, total2[i][1]) && tablero[total2[i][0] + 1][total2[i][1]].id_pieza != 100) {
            movimiento[0] = total2[i][0] + 1;
            movimiento[1] = total2[i][1];
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] - 1 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 1, total2[i][1]) && tablero[total2[i][0] - 1][total2[i][1]].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 1;
            movimiento[1] = total2[i][1];
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][1] + 1 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0], total2[i][1] + 1) && tablero[total2[i][0]][total2[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total2[i][0];
            movimiento[1] = total2[i][1] + 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][1] - 1 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0], total2[i][1] - 1) && tablero[total2[i][0]][total2[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total2[i][0];
            movimiento[1] = total2[i][1] - 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] + 1 < 8 && total2[i][1] + 1 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + 1, total2[i][1] + 1) && tablero[total2[i][0] + 1][total2[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] + 1;
            movimiento[1] = total2[i][1] + 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] - 1 >= 0 && total2[i][1] + 1 < 8) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 1, total2[i][1] + 1) && tablero[total2[i][0] - 1][total2[i][1] + 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 1;
            movimiento[1] = total2[i][1] + 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][0] + 1 < 8 && total2[i][1] - 1 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] + 1, total2[i][1] - 1) && tablero[total2[i][0] + 1][total2[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] + 1;
            movimiento[1] = total2[i][1] - 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
        if (total2[i][1] - 1 >= 0 && total2[i][0] - 1 >= 0) {
          if (matar(tablero, total2[i][0], total2[i][1], total2[i][0] - 1, total2[i][1] - 1) && tablero[total2[i][0] - 1][total2[i][1] - 1].id_pieza != 100) {
            movimiento[0] = total2[i][0] - 1;
            movimiento[1] = total2[i][1] - 1;
            coordenada[0] = total2[i][0];
            coordenada[1] = total2[i][1];
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool puedoMover(Pieza tablero[8][8], int coordenaday, int coordenadax, int movimiento[2]) {
  Pieza piezaAux = tablero[coordenaday][coordenadax];
  if (piezaAux.id_pieza == peon) { // si la pieza es un peon ejecuta alguna de las siguientes opciones
    if (coordenaday == 6) { // quiere hacer salto doble y para eso verifica que este en la linea del principio
      if (matar(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax)) { // verifica que no haya nadie en el camino ni en el lugara saltar
        movimiento[0] = coordenaday + 2;
        movimiento[1] = coordenadax;
        return true; //mueve y avisa que pudo mover
      }
      if (matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax)) { // de no poder moverse dos puestos intentara moverse uno
        movimiento[0] = coordenaday + 1;
        movimiento[1] = coordenadax;
        return true;
      }
    }
    else if (matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax)) { // de no estar en la linea del principio solo se movera un puesto
      movimiento[0] = coordenaday + 1;
      movimiento[1] = coordenadax;
      return true;
    }
  }
  if (piezaAux.id_pieza == caballo) { // si es un caballo
    if (coordenaday + 2 < 8) { // limite para que no se pase
      if (coordenadax + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax + 1)) { // limite y verificacion
        movimiento[0] = coordenaday + 2;
        movimiento[1] = coordenadax + 1;
        return true;
      }
      if (coordenadax - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax - 1)) {
        movimiento[0] = coordenaday + 2;
        movimiento[1] = coordenadax - 1;
        return true;
      }
    }
    if (coordenadax + 2 < 8) {
      if (coordenaday + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax + 2)) {
        movimiento[0] = coordenaday + 1;
        movimiento[1] = coordenadax + 2;
        return true;
      }
      if (coordenaday - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday - 1, coordenadax + 2)) {
        movimiento[0] = coordenaday - 1;
        movimiento[1] = coordenadax + 2;
        return true;
      }
    }
    if (coordenadax - 2 >= 0) {
      if (coordenaday + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax - 2)) {
        movimiento[0] = coordenaday + 1;
        movimiento[1] = coordenadax - 2;
        return true;
      }
      if (coordenaday - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday - 1, coordenadax - 2)) {
        movimiento[0] = coordenaday - 1;
        movimiento[1] = coordenadax - 2;
        return true;
      }
    }
    if (coordenaday - 2 >= 0) { // solo va para atras en ultima instancia
      if (coordenadax + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday - 2, coordenadax + 1)) { // limite y verificacion
        movimiento[0] = coordenaday - 2;
        movimiento[1] = coordenadax + 1;
        return true;
      }
      if (coordenadax - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday - 2, coordenadax - 1)) {
        movimiento[0] = coordenaday - 2;
        movimiento[1] = coordenadax - 1;
        return true;
      }
    }
  }
  if (piezaAux.id_pieza == alfil || piezaAux.id_pieza == reina) {
    for (int m = 8; m >= 0; m = m - 1) {
      if (coordenaday + m < 8 && coordenadax + m < 8 && coordenaday + m >= 0 && coordenadax + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax + m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax + m)) {
          movimiento[0] = coordenaday + m;
          movimiento[1] = coordenadax + m;
          return true;
        }
      }
      if (coordenaday + m < 8 && coordenadax - m < 8 && coordenaday + m >= 0 && coordenadax - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax - m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax - m)) {
          movimiento[0] = coordenaday + m;
          movimiento[1] = coordenadax - m;
          return true;
        }
      }
      if (coordenaday - m < 8 && coordenadax + m < 8 && coordenaday - m >= 0 && coordenadax + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax + m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax + m)) {
          movimiento[0] = coordenaday - m;
          movimiento[1] = coordenadax + m;
          return true;
        }
      }
      if (coordenaday - m < 8 && coordenadax - m < 8 && coordenaday - m >= 0 && coordenadax - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax - m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax - m)) {
          movimiento[0] = coordenaday - m;
          movimiento[1] = coordenadax - m;
          return true;
        }
      }
    }
  }
  if (piezaAux.id_pieza == torre || piezaAux.id_pieza == reina) {
    for (int m = 8; m >= 0; m = m - 1) {
      if (coordenaday + m < 8 && coordenaday + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax)) {
          movimiento[0] = coordenaday + m;
          movimiento[1] = coordenadax;
          return true;
        }
      }
      if (coordenadax + m < 8 && coordenadax + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday, coordenadax + m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday, coordenadax + m)) {
          movimiento[0] = coordenaday;
          movimiento[1] = coordenadax + m;
          return true;
        }
      }
      if (coordenadax - m < 8 && coordenadax - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday, coordenadax - m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday, coordenadax - m)) {
          movimiento[0] = coordenaday;
          movimiento[1] = coordenadax - m;
          return true;
        }
      }
      if (coordenaday - m < 8 && coordenaday - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax) && intercepcion(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax)) {
          movimiento[0] = coordenaday - m;
          movimiento[1] = coordenadax;
          return true;
        }
      }
    }
  }
  return false;
}
bool puedoMover2(Pieza tablero[8][8], int coordenaday, int coordenadax, int movimiento[2]) {
  Pieza piezaAux = tablero[coordenaday][coordenadax];
  if (piezaAux.id_pieza == peon) { // si la pieza es un peon ejecuta alguna de las siguientes opciones
    if (coordenaday == 6) { // quiere hacer salto doble y para eso verifica que este en la linea del principio
      if (matar(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax)) { // verifica que no haya nadie en el camino ni en el lugara saltar
        movimiento[0] = coordenaday - 2;
        movimiento[1] = coordenadax;
        return true; //mueve y avisa que pudo mover
      }
      if (matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax)) { // de no poder moverse dos puestos intentara moverse uno
        movimiento[0] = coordenaday - 1;
        movimiento[1] = coordenadax;
        return true;
      }
    }
    else if (matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax)) { // de no estar en la linea del principio solo se movera un puesto
      movimiento[0] = coordenaday - 1;
      movimiento[1] = coordenadax;
      return true;
    }
  }
  if (piezaAux.id_pieza == caballo) { // si es un caballo
    if (coordenaday - 2 >= 0) { // limite para que no se pase
      if (coordenadax + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday - 2, coordenadax + 1)) { // limite y verificacion
        movimiento[0] = coordenaday - 2;
        movimiento[1] = coordenadax + 1;
        return true;
      }
      if (coordenadax - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday - 2, coordenadax - 1)) {
        movimiento[0] = coordenaday - 2;
        movimiento[1] = coordenadax - 1;
        return true;
      }
    }
    if (coordenadax + 2 < 8) {
      if (coordenaday - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday - 1, coordenadax + 2)) {
        movimiento[0] = coordenaday - 1;
        movimiento[1] = coordenadax + 2;
        return true;
      }
      if (coordenaday + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax + 2)) {
        movimiento[0] = coordenaday + 1;
        movimiento[1] = coordenadax + 2;
        return true;
      }
    }
    if (coordenadax - 2 >= 0) {
      if (coordenaday + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday + 1, coordenadax - 2)) {
        movimiento[0] = coordenaday + 1;
        movimiento[1] = coordenadax - 2;
        return true;
      }
      if (coordenaday - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday - 1, coordenadax - 2)) {
        movimiento[0] = coordenaday - 1;
        movimiento[1] = coordenadax - 2;
        return true;
      }
    }
    if (coordenaday + 2 < 8) { // solo va para atras en ultima instancia
      if (coordenadax + 1 < 8 && matar(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax + 1)) { // limite y verificacion
        movimiento[0] = coordenaday + 2;
        movimiento[1] = coordenadax + 1;
        return true;
      }
      if (coordenadax - 1 >= 0 && matar(tablero, coordenaday, coordenadax, coordenaday + 2, coordenadax - 1)) {
        movimiento[0] = coordenaday + 2;
        movimiento[1] = coordenadax - 1;
        return true;
      }
    }
  }
  if (piezaAux.id_pieza == alfil || piezaAux.id_pieza == reina) {
    for (int m = 8; m >= 0; m = m - 1) {
      if (coordenaday - m < 8 && coordenadax - m < 8 && coordenaday - m >= 0 && coordenadax - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax - m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax - m)) {
          movimiento[0] = coordenaday - m;
          movimiento[1] = coordenadax - m;
          return true;
        }
      }
      if (coordenaday + m < 8 && coordenadax - m < 8 && coordenaday + m >= 0 && coordenadax - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax - m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax - m)) {
          movimiento[0] = coordenaday + m;
          movimiento[1] = coordenadax - m;
          return true;
        }
      }
      if (coordenaday - m < 8 && coordenadax + m < 8 && coordenaday - m >= 0 && coordenadax + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax + m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax + m)) {
          movimiento[0] = coordenaday - m;
          movimiento[1] = coordenadax + m;
          return true;
        }
      }
      if (coordenaday + m < 8 && coordenadax + m < 8 && coordenaday + m >= 0 && coordenadax + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax + m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax + m)) {
          movimiento[0] = coordenaday + m;
          movimiento[1] = coordenadax + m;
          return true;
        }
      }
    }
  }
  if (piezaAux.id_pieza == torre || piezaAux.id_pieza == reina) {
    for (int m = 8; m >= 0; m = m - 1) {
      if (coordenaday - m < 8 && coordenaday - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax) && intercepcion(tablero, coordenaday, coordenadax, coordenaday - m, coordenadax)) {
          movimiento[0] = coordenaday - m;
          movimiento[1] = coordenadax;
          return true;
        }
      }
      if (coordenadax + m < 8 && coordenadax + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday, coordenadax + m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday, coordenadax + m)) {
          movimiento[0] = coordenaday;
          movimiento[1] = coordenadax + m;
          return true;
        }
      }
      if (coordenadax - m < 8 && coordenadax - m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday, coordenadax - m) && intercepcion(tablero, coordenaday, coordenadax, coordenaday, coordenadax - m)) {
          movimiento[0] = coordenaday;
          movimiento[1] = coordenadax - m;
          return true;
        }
      }
      if (coordenaday + m < 8 && coordenaday + m >= 0) {
        if (matar(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax) && intercepcion(tablero, coordenaday, coordenadax, coordenaday + m, coordenadax)) {
          movimiento[0] = coordenaday + m;
          movimiento[1] = coordenadax;
          return true;
        }
      }
    }
  }
  return false;
}


void cambiar(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox) { //Cambia la pieza de un lugar a otro
  int comprobante;
  comprobante = cordenaday - movimientoy;
  comprobante = sqrt(pow(comprobante, 2));
  for (int i = 0; i < 16; i++) {
    if (total[i][0] == cordenaday && total[i][1] == cordenadax) {
      total[i][0] = movimientoy;
      total[i][1] = movimientox;
    }
    else if (total[i][0] == movimientoy && total[i][1] == movimientox) {
      total[i][0] = 100;
      total[i][1] = 100;
    }
  }
  for (int i = 0; i < 16; i++) {
    if (total2[i][0] == cordenaday && total2[i][1] == cordenadax) {
      total2[i][0] = movimientoy;
      total2[i][1] = movimientox;
    }
    else if (total2[i][0] == movimientoy && total2[i][1] == movimientox) {
      total2[i][0] = 100;
      total2[i][1] = 100;
    }
  }
  Tablero[movimientoy][movimientox].id_pieza = Tablero[cordenaday][cordenadax].id_pieza;
  Tablero[movimientoy][movimientox].color = Tablero[cordenaday][cordenadax].color;
  Tablero[movimientoy][movimientox].posicionOrigenX = movimientox;
  Tablero[movimientoy][movimientox].posicionOrigenY = movimientoy;
  if (Tablero[cordenaday][cordenadax].id_pieza == peon) {
    if (comprobante == 2) {
      Tablero[movimientoy][movimientox].movimiento = Tablero[cordenaday][cordenadax].movimiento;
    }
    else {
      Tablero[movimientoy][movimientox].movimiento = false;
    }
  }
  else {
    Tablero[movimientoy][movimientox].movimiento = false;
  }
  //borra la posicion en la que estaba anteriormente
  Tablero[cordenaday][cordenadax].id_pieza = 100;
  Tablero[cordenaday][cordenadax].color = false;
  Tablero[cordenaday][cordenadax].movimiento = false;
  Tablero[cordenaday][cordenadax].posicionOrigenX = cordenadax;
  Tablero[cordenaday][cordenadax].posicionOrigenY = cordenaday;
}

void Inicializar_Tablero(Pieza Tablero[8][8]) {
  int pasando = 0;
  int pasando2 = 0;
  for (int y = 0; y < 8;  y++) {
    for (int x = 0; x < 8; x++) {
      //a partir de aca pone las fichas negras
      if ((x == 0 || x == 7) && (y == 0)) {
        total[pasando][0] = y;
        total[pasando][1] = x;
        pasando = pasando + 1;
        Tablero[y][x].id_pieza = torre;
        Tablero[y][x].color = true;
        Tablero[y][x].movimiento = true;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if ((x == 2 || x == 5) && y == 0) {
        total[pasando][0] = y;
        total[pasando][1] = x;
        pasando = pasando + 1;
        Tablero[y][x].id_pieza = alfil;
        Tablero[y][x].color = true;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if ((x == 1 || x == 6) && y == 0) {
        total[pasando][0] = y;
        total[pasando][1] = x;
        pasando = pasando + 1;
        Tablero[y][x].id_pieza = caballo;
        Tablero[y][x].color = true;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if (x == 3 && y == 0) {
        total[pasando][0] = y;
        total[pasando][1] = x;
        pasando = pasando + 1;
        Tablero[y][x].id_pieza = reina;
        Tablero[y][x].color = true;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if (x == 4 && y == 0) {
        total[pasando][0] = y;
        total[pasando][1] = x;
        pasando = pasando + 1;
        Tablero[y][x].id_pieza = rey;
        Tablero[y][x].color = true;
        Tablero[y][x].movimiento = true;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if (y == 1) {
        total[pasando][0] = y;
        total[pasando][1] = x;
        pasando = pasando + 1;
        Tablero[y][x].id_pieza = peon;
        Tablero[y][x].color = true;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      // a partir de aca es con las fichas blancas
      else if ((x == 0 || x == 7) && y == 7) {
        total2[pasando2][0] = y;
        total2[pasando2][1] = x;
        pasando2 = pasando2 + 1;
        Tablero[y][x].id_pieza = torre;
        Tablero[y][x].color = false;
        Tablero[y][x].movimiento = true;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if ((x == 2 || x == 5) && y == 7) {
        total2[pasando2][0] = y;
        total2[pasando2][1] = x;
        pasando2 = pasando2 + 1;
        Tablero[y][x].id_pieza = alfil;
        Tablero[y][x].color = false;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if ((x == 1 || x == 6) && y == 7) {
        total2[pasando2][0] = y;
        total2[pasando2][1] = x;
        pasando2 = pasando2 + 1;
        Tablero[y][x].id_pieza = caballo;
        Tablero[y][x].color = false;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if (x == 3 && y == 7) {
        total2[pasando2][0] = y;
        total2[pasando2][1] = x;
        pasando2 = pasando2 + 1;
        Tablero[y][x].id_pieza = reina;
        Tablero[y][x].color = false;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if (x == 4 && y == 7) {
        total2[pasando2][0] = y;
        total2[pasando2][1] = x;
        pasando2 = pasando2 + 1;
        Tablero[y][x].id_pieza = rey;
        Tablero[y][x].color = false;
        Tablero[y][x].movimiento = true;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else if (y == 6) {
        total2[pasando2][0] = y;
        total2[pasando2][1] = x;
        pasando2 = pasando2 + 1;
        Tablero[y][x].id_pieza = peon;
        Tablero[y][x].color = false;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
      else {
        Tablero[y][x].id_pieza = 100;
        Tablero[y][x].color = false;
        Tablero[y][x].movimiento = false;
        Tablero[y][x].posicionOrigenX = x;
        Tablero[y][x].posicionOrigenY = y;
      }
    }
  }
}
bool jaque(Pieza Tablero[8][8], bool color) { // esta funcion verifica si el rey está en jaque. También devuelve el lugar desde donde se está haciendo el jaque.
  int reyPropio[2];
  int i = 0;
  int x = 0;
  while (i < 8) {
    while (x < 8) {
      if (Tablero[i][x].id_pieza == 1 && Tablero[i][x].color == color) {
        reyPropio[0] = i;
        reyPropio[1] = x;
      }
      x = x + 1;
    }
    x = 0;
    i = i + 1;
  }
  i = 1;
  while (i < 8) {
    if (Tablero[reyPropio[0] + 2][reyPropio[1] + 1].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] + 2][reyPropio[1] + 1].id_pieza == 5) {
        return true;
      }
    }
    if (Tablero[reyPropio[0] + 2][reyPropio[1] - 1].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] + 2][reyPropio[1] - 1].id_pieza == 5) {
        return true;
      }
    }
    if (Tablero[reyPropio[0] - 2][reyPropio[1] + 1].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] - 2][reyPropio[1] + 1].id_pieza == 5) {
        return true;
      }
    }
    if (Tablero[reyPropio[0] - 2][reyPropio[1] - 1].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] - 2][reyPropio[1] - 1].id_pieza == 5) {
        return true;
      }
    }
    if (Tablero[reyPropio[0] + 1][reyPropio[1] + 2].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] + 1][reyPropio[1] + 2].id_pieza == 5) {
        return true;
      }
    }
    if (Tablero[reyPropio[0] - 1][reyPropio[1] + 2].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] - 1][reyPropio[1] + 2].id_pieza == 5) {
        return true;
      }
    }
    if (Tablero[reyPropio[0] + 1][reyPropio[1] - 2].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] + 1][reyPropio[1] - 2].id_pieza == 5) {
        return true;
      }
    }
    if (Tablero[reyPropio[0] - 1][reyPropio[1] - 2].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
      if (Tablero[reyPropio[0] - 1][reyPropio[1] - 2].id_pieza == 5) {
        return true;
      }
    }
    if ((reyPropio[0] + i) < 8) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0] + i, reyPropio[1]) && Tablero[reyPropio[0] + i][reyPropio[1]].id_pieza != 100) {
        if (Tablero[reyPropio[0] + i][reyPropio[1]].id_pieza == 2 || Tablero[reyPropio[0] + i][reyPropio[1]].id_pieza == 3) {
          if (Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
            return true;
          }
        }
      }
    }
    if ((reyPropio[1] + i) < 8) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0], reyPropio[1] + i) && Tablero[reyPropio[0]][reyPropio[1] + i].id_pieza != 100) {
        if (Tablero[reyPropio[0]][reyPropio[1] + i].id_pieza == 2 || Tablero[reyPropio[0]][reyPropio[1] + i].id_pieza == 3) {
          if (Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
            return true;
          }
        }
      }
    }
    if ((reyPropio[0] - i) >= 0) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0] - i, reyPropio[1]) && Tablero[reyPropio[0] - i][reyPropio[1]].id_pieza != 100) {
        if (Tablero[reyPropio[0] - i][reyPropio[1]].id_pieza == 2 || Tablero[reyPropio[0] - i][reyPropio[1]].id_pieza == 3) {
          if (Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
            return true;
          }
        }
      }
    }
    if ((reyPropio[1] - i) >= 0) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0], reyPropio[1] - i) && Tablero[reyPropio[0]][reyPropio[1] - i].id_pieza != 100 && (reyPropio[1] - i) >= 0) {
        if (Tablero[reyPropio[0]][reyPropio[1] - i].id_pieza == 2 || Tablero[reyPropio[0]][reyPropio[1] - i].id_pieza == 3) {
          if (Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
            return true;
          }
        }
      }
    }
    if ((reyPropio[0] + i) < 8 && (reyPropio[1] + i) < 8) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0] + i, reyPropio[1] + 1) && Tablero[reyPropio[0] + i][reyPropio[1] + i].id_pieza != 100) {
        if (Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
          if (Tablero[reyPropio[0] + i][reyPropio[1] + i].id_pieza == 4) {
            return true;
          }
          if (Tablero[reyPropio[0] + i][reyPropio[1] + i].id_pieza == 6 && i == 1) {
            return true;
          }
        }
      }
    }
    if ((reyPropio[0] - i) >= 0 && (reyPropio[1] - i) >= 0) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0] - i, reyPropio[1] - i) && Tablero[reyPropio[0] - i][reyPropio[1] - i].id_pieza != 100) {
        if (Tablero[reyPropio[0]][reyPropio[1] - i].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
          if (Tablero[reyPropio[0] - i][reyPropio[1] - i].id_pieza == 4) {
            return true;
          }
          if (Tablero[reyPropio[0] - i][reyPropio[1] - i].id_pieza == 6 && i == 1) {
            return true;
          }
        }
      }
    }
    if ((reyPropio[0] - i) >= 0 && (reyPropio[1] + i) < 8) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0] - i, reyPropio[1] + i) && Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza != 100) {
        if (Tablero[reyPropio[0] - i][reyPropio[1] + i].color != Tablero[reyPropio[0]][reyPropio[1]].color) {
          if (Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza == 4) {
            return true;
          }
          if (Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza == 2) {
            return true;
          }
          if (Tablero[reyPropio[0] - i][reyPropio[1] + i].id_pieza == 6 && i == 1) {
            return true;
          }
        }
      }
    }
    if ((reyPropio[0] + i) < 8 && (reyPropio[1] - i) >= 0) {
      if (intercepcion(Tablero, reyPropio[0], reyPropio[1], reyPropio[0] + i, reyPropio[1] - i) && Tablero[reyPropio[0] + i][reyPropio[1] - i].id_pieza != 100 && matar(Tablero, reyPropio[0], reyPropio[1], reyPropio[0] + i, reyPropio[1] - i)) {
        if (Tablero[reyPropio[0] + i][reyPropio[1] - i].id_pieza == 4) {
          return true;
        }
        if (Tablero[reyPropio[0] + i][reyPropio[1] - i].id_pieza == 6 && i == 1) {
          return true;
        }
      }
    }
    i = i + 1;
  }
  return false;
}
bool jaquemate(Pieza Tablero[8][8], bool color) {
  int reyPropio[2];
  bool hayRey = true;
  int i = 0;
  int x = 0;
  while (i < 8) {
    while (x < 8) {
      if (Tablero[i][x].id_pieza == 1 && Tablero[i][x].color == color) {
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
bool caminoPrendido(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox) { //Enciende los LEDs que conforman el camino del jaque
  int comprobantey, comprobantex;
  comprobantey = cordenaday - movimientoy;
  comprobantex = cordenadax - movimientox;
  comprobantex = sqrt(pow(comprobantex, 2));
  comprobantey = sqrt(pow(comprobantey, 2));
  int leds2[2];
  if (comprobantex == comprobantey) { // si la pieza se mueve en diagonal utiliza este IF
    for (int i = 1; i < comprobantex; i++) {
      leds2[0] = cordenadax + i;
      leds2[1] = cordenaday + i;
      if (cordenadax < movimientox && cordenaday < movimientoy) {
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday + i][cordenadax + i].id_pieza != 0) {
          return false;
        }
      }
      else if (cordenadax > movimientox && cordenaday > movimientoy) {
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday - i][cordenadax - i].id_pieza != 0) {
          return false;
        }
      }
      else if (cordenadax < movimientox && cordenaday > movimientoy) {
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday - i][cordenadax + i].id_pieza != 0) {
          return false;
        }
      }
      else if (cordenadax > movimientox && cordenaday < movimientoy) {
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday + i][cordenadax - i].id_pieza != 0) {
          return false;
        }
      }
    }
  }
  else if (comprobantex == 0) { // si se mueve de forma vertical utiliza este IF
    leds2[0] = cordenadax;
    for (int i = 1; i < comprobantey; i++) { // mueve la pieza de lugar en lugar hasta hallar a una pieza
      leds2[1] = cordenaday + i;
      if (cordenaday < movimientoy) { // va de arriba a abajo
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday + i][cordenadax].id_pieza != 0) { // si encuentra un lugar en con una id valida significa que hay una pieza y devuelve false *2
          return false;
        }
      }
      else if (cordenaday > movimientoy) { // va de abajo a arriba
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday - i][cordenadax].id_pieza != 0) { // * same2
          return false;
        }
      }
    }
  }
  else if (comprobantey == 0) { // si se mueve de forma horizontal utiliza este IF
    leds2[1] = cordenaday;
    for (int i = 1; i < comprobantex; i++) {
      leds2[0] = cordenaday + i;
      if (cordenadax < movimientox) { // va de izquierda a derecha
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday][cordenadax + i].id_pieza != 0) { // * same2
          return false;
        }
      }
      else if (cordenadax > movimientox) { // va de derecha a izquierda
        //prenden el led de la cordenada leds[]
        if (Tablero[cordenaday][cordenadax - i].id_pieza != 0) { // * same2
          return false;
        }
      }
    }
  }
  return true;
}
bool matar(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox) { // esta funcion verifica si el lugar a donde semueve la pieza esta desocupado o ocupado por una pieza enemiga
  if (Tablero[movimientoy][movimientox].id_pieza != 100 && Tablero[movimientoy][movimientox].color != Tablero[cordenaday][cordenadax].color) {
    return true;
  }
  else if (Tablero[movimientoy][movimientox].id_pieza != 100 && Tablero[movimientoy][movimientox].color == Tablero[cordenaday][cordenadax].color) {
    return false;
  }
  else {
    return true;
  }
}
bool verificar_reytorre(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox) {
  int comprobantey, comprobantex;
  comprobantey = cordenaday - movimientoy;
  comprobantex = cordenadax - movimientox;
  comprobantex = sqrt(pow(comprobantex, 2));
  comprobantey = sqrt(pow(comprobantey, 2));
  if ((cordenaday == 0 || cordenaday == 7) && (cordenadax == 0 || cordenadax == 7 || cordenadax == 4)) {
    if ((comprobantex == 2 || comprobantex == 3) && comprobantey == 0) {
      if (Tablero[cordenaday][cordenadax].movimiento == true) {
        if (movimientox < cordenadax) { // enroque largo
          if (Tablero[cordenaday][7].movimiento == true && intercepcion(Tablero, cordenaday, 4, cordenaday, 1)) {
            Tablero[cordenaday][cordenadax].movimiento = false;
            Tablero[movimientoy][movimientox].movimiento = false;
            cambiar(Tablero, cordenaday, 4, cordenaday, 2);
            cambiar(Tablero, cordenaday, 0, cordenaday, 3);
            return true;
          }
        }
        else if (movimientox > cordenadax) { // enroque corto
          if (Tablero[cordenaday][0].movimiento == true && intercepcion(Tablero, cordenaday, 4, cordenaday, 6)) {
            Tablero[cordenaday][cordenadax].movimiento = false;
            Tablero[movimientoy][movimientox].movimiento = false;
            cambiar(Tablero, cordenaday, 4, cordenaday, 6);
            cambiar(Tablero, cordenaday, 7, cordenaday, 5);
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool Verificar_Movimiento(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox, int turno) { //Se verifica el movimiento de una pieza

  int comprobantey, comprobantex;
  comprobantey = cordenaday - movimientoy;    //comporabante X e Y sirven pasa saber cuanto se movio independiente mente de su direccion
  comprobantex = cordenadax - movimientox;    //solo en el peon es necesario saber si el movimiento fue positivo o negativo
  comprobantex = sqrt(pow(comprobantex, 2)); //pasa los numeros a positivo
  comprobantey = sqrt(pow(comprobantey, 2)); //pasa los numeros a positivo
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
  if (tablero[cordenaday][cordenadax].id_pieza == caballo && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))) {
    if ((comprobantex + comprobantey) == 3 && (comprobantex != 3 || comprobantey != 3) && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox);
    }
    else {
      return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
    }
  }
  else if (tablero[cordenaday][cordenadax].id_pieza == alfil && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0)) && intercepcion(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
    if (comprobantex == comprobantey && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox); // * same
    }
    else {
      return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
    }
  }
  else if (tablero[cordenaday][cordenadax].id_pieza == torre && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0)) && intercepcion(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
    if (comprobantex == 0 && comprobantey > 0 && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox); // * same
    }
    else if (comprobantey == 0 && comprobantey > 0 && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox);
    }
    else {
      return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
    }
  }
  else if (tablero[cordenaday][cordenadax].id_pieza == reina && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0)) && intercepcion(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
    if (comprobantey == comprobantex && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox); // * same
    }
    else if (comprobantey == 0 && comprobantex > 0 && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox);
    }
    else if (comprobantex == 0 && comprobantey > 0 && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox);
    }
    else {
      return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
    }
  }
  else if (tablero[cordenaday][cordenadax].id_pieza == rey && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))) {

    if (comprobantex < 2 && comprobantey < 2 && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
      cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox); // * same
    }
    else {
      return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
    }
  }
  else if (tablero[cordenaday][cordenadax].id_pieza == 6 && ((tablero[cordenaday][cordenadax].color == true && turno == 1) || (tablero[cordenaday][cordenadax].color == false && turno == 0))) {
    if ((turno == 1 && cordenaday < movimientoy) || (turno == 0 && cordenaday > movimientoy)) {
      if (comprobantex == 0) {
        if (comprobantey == 1 && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
          cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox); // * same
        }
        else if (comprobantey == 2 && (cordenaday == 1 || cordenaday == 6) && matar(Tablero, cordenaday, cordenadax, movimientoy, movimientox)) {
          cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox); // * same
        }
        else {
          return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
        }
      }
      else if (comprobantex == 1 && comprobantey == 1) {
        cambiar(Tablero, cordenaday, cordenadax, movimientoy, movimientox); // * same
      }
      else {
        return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
      }
    }
    else {
      return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
    }
  }
  else {
    return false; // si el movimiento o pieza no son validas devuelve false de lo contrario sera true
  }
  return true;
}

bool intercepcion(Pieza Tablero[8][8], int cordenaday, int cordenadax, int movimientoy, int movimientox) { //Verifica si hay alguna pieza entre dos posiciones
  int comprobantey, comprobantex;
  comprobantey = cordenaday - movimientoy;
  comprobantex = cordenadax - movimientox;
  comprobantex = sqrt(pow(comprobantex, 2));
  comprobantey = sqrt(pow(comprobantey, 2));
  if (comprobantex == comprobantey) { // si la pieza se mueve en diagonal utiliza este IF
    for (int i = 1; i <= comprobantex; i++) {
      if (cordenadax < movimientox && cordenaday < movimientoy) {
        if ((Tablero[cordenaday + i][cordenadax + i].id_pieza != 100 && Tablero[cordenaday + i][cordenadax + i].color == Tablero[cordenaday][cordenadax].color)) {
          return false;
        }
      }
      else if (cordenadax > movimientox && cordenaday > movimientoy) {
        if ((Tablero[cordenaday - i][cordenadax - i].id_pieza != 100 && Tablero[cordenaday - i][cordenadax - i].color == Tablero[cordenaday][cordenadax].color)) {
          return false;
        }
      }
      else if (cordenadax < movimientox && cordenaday > movimientoy) {
        if ((Tablero[cordenaday - i][cordenadax + i].id_pieza != 100 && Tablero[cordenaday - i][cordenadax + i].color == Tablero[cordenaday][cordenadax].color)) {
          return false;
        }
      }
      else if (cordenadax > movimientox && cordenaday < movimientoy) {
        if ((Tablero[cordenaday + i][cordenadax - i].id_pieza != 100 && Tablero[cordenaday + i][cordenadax - i].color == Tablero[cordenaday][cordenadax].color)) {
          return false;
        }
      }
    }
  }
  else if (comprobantex == 0) { // si se mueve de forma vertical utiliza este IF
    for (int i = 1; i <= comprobantey; i++) { // mueve la pieza de lugar en lugar hasta hallar a una pieza
      if (cordenaday < movimientoy) { // va de arriba a abajo
        if ((Tablero[cordenaday + i][cordenadax].id_pieza != 100 && Tablero[cordenaday + i][cordenadax].color == Tablero[cordenaday][cordenadax].color)) { // si encuentra un lugar en con una id valida significa que hay una pieza y devuelve false *2
          return false;
        }
      }
      else if (cordenaday > movimientoy) { // va de abajo a arriba
        if ((Tablero[cordenaday - i][cordenadax].id_pieza != 100 && Tablero[cordenaday - i][cordenadax].color == Tablero[cordenaday][cordenadax].color)) { // * same2
          return false;
        }
      }
    }
  }
  else if (comprobantey == 0) { // si se mueve de forma horizontal utiliza este IF
    for (int i = 1; i <= comprobantex; i++) {
      if (cordenadax < movimientox) { // va de izquierda a derecha
        if ((Tablero[cordenaday][cordenadax + i].id_pieza != 100 && Tablero[cordenaday][cordenadax + i].color == Tablero[cordenaday][cordenadax].color)) { // * same2
          return false;
        }
      }
      else if (cordenadax > movimientox) { // va de derecha a izquierda
        if ((Tablero[cordenaday][cordenadax - i].id_pieza != 100 && Tablero[cordenaday][cordenadax - i].color == Tablero[cordenaday][cordenadax].color)) { // * same2
          return false;
        }
      }
    }
  }
  return true;
}

bool Inteligencia(Pieza tablero[8][8], int cordenada[2], int movimiento[2]) {
  bool entrar = true;
  if (puedeComer(tablero, movimiento, cordenada)) {
    cordenada[1];
    cordenada[0];
    movimiento[0];
    movimiento[1];
  }
  else {
    Serial.println("aun no puede comer");
    int ran = 0;
    while (entrar) {
      ran = random(0, 15);
      cordenada[0] = total[ran][0];
      cordenada[1] = total[ran][1];
      if (puedoMover(tablero, total[ran][0], total[ran][1], movimiento)) {
        movimiento[0];
        movimiento[1];
        entrar = false;
      }
    }
  }
  return true;
}
bool Inteligencia2(Pieza tablero[8][8], int cordenada[2], int movimiento[2]) {
  bool entrar = true;
  if (puedeComer2(tablero, movimiento, cordenada)) {
    cordenada[1];
    cordenada[0];
    movimiento[0];
    movimiento[1];
  }
  else {
    Serial.println("aun no puede comer");
    int ran = 0;
    while (entrar) {
      ran = random(0, 15);
      cordenada[0] = total[ran][0];
      cordenada[1] = total[ran][1];
      if (puedoMover2(tablero, total[ran][0], total[ran][1], movimiento)) {
        movimiento[0];
        movimiento[1];
        entrar = false;
      }
    }
  }
  return true;
}

