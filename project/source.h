#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define dimInt 10
#define dimChar 40
#define nameLen 10
#define scoresFile "history.bin"

typedef struct {
char nickname[nameLen];
float HP;                    //vida de jugador. Default ???
float hpMultiplier;     //multiplicador de vida. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int score;
float DMGtaken;       //total de da�o recibido
float DMGdealed;     //total de da�o hecho
float DMG;                //multiplicador de da�o. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int defense;               //defensa del jugador. Default 0 / M�nimo -5 / M�ximo 8
float luck;                 //mejora o empeora la posibilidad de un esquive exitoso, golpe cr�tico y todo lo que pueda ser afectado por la suerte
int inventory[dimInt];  //listado de items
int amountItems;        //cantidad total de items
char Traits[dimInt][dimChar];   //buffs y debuffs de jugador
} playerUser;

typedef struct{
char enemy[dimChar];
int HP;
char DMG;
int defense;
} enemyUser;

void askNickname(char[]);                                         //Pide ingresar un nombre de jugador
void selectTraits();                                                       //Pide seleccionar los rasgos de jugador
float damageDealedToEnemy(int, float, int);         //Retorna el da�o total hecho al enemigo
float criticalStrike(float);                                           //Duplica el da�o o no, luego retorna el valor definitivo del da�o
float calculateHp(float, float);                                //Resta a la vida el da�o, sirve para el hp de jugador y hp de enemigo
float heal(float, float);                                                 //Suma al hp del jugador el valor de la curaci�n, como pociones, etc.
enemyUser spawnEnemy();


void drawMenu();
















// empezado el 16/07/2023
// terminado el --/--/----

/* APARTADO DE IDEAS
ENEMIGOS: esqueleto con espada, esqueleto armado (armadura),


RASGOS: fuerte + x0.2 DMG, debil - x0.2 DMG, resistente +1def, piel de acero +2def, raquitico -3def - x0.1 DMG, suertudo +0.1luck, desafortunado -0.1luck, maldito - 0.2luck
aprovechador de nutrientes

*/
