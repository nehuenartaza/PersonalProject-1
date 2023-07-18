#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define dimInt 10
#define dimChar 40
#define nameLen 10
#define totalEnemies 5
#define totalBosses 3
#define scoresFile "history.bin"
#define auxiliarFile "auxiliar.bin" //usado para mostrar las estad�sticas iniciales y compararlos con las estad�sticas finales

typedef struct {
char name[nameLen];
bool isWeapon;          //indica si el objeto es un arma, en caso true tendr� los siguientes 2 atributos
int blockChance;
int weaponDMG;
bool isItem;            //indica si el objeto es un item, en caso trie tendr� los siguientes 4 posibles atributos
int lifeHealPoints;
int defenseBonus;
float luckBonus;
int scoreBonus;
bool itemIsDiscard;     //indica si fue descartado o no el objeto
} itemUser;

typedef struct {
char nickname[nameLen];
float HP;                    //vida de jugador. Default ???
float hpMultiplier;     //multiplicador de vida. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int score;
float DMGtaken;       //total de da�o recibido
float DMGdealed;     //total de da�o hecho
float DMG;                //multiplicador de da�o. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int defense;               //defensa del jugador. Default 0 / M�nimo -5 / M�ximo 8
float luck;                 //mejora o empeora la posibilidad de un esquive exitoso, golpe cr�tico y todo lo que pueda ser afectado por la suerte. Default x0 / M�nimo x-0.3 / M�ximo x0.3
itemUser inventory[dimInt];  //listado de items
int amountItems;        //cantidad total de items
char traits[dimInt][dimChar];   //buffs y debuffs de jugador
int amountTraits;               //cantidad total de rasgos
int difficulty;             //1 - easy / 2 - normal / 3 - hard / 4 - POSTAL Difficulty
int healingUsed;        //cuenta la cantidad de pociones de vida usadas
} playerUser;

typedef struct {
char enemyType[dimChar];    //nombre del enemigo
int HP;
char DMG;
int defense;
float DMGmultiplier;        // easy modo x0.9 / normal mode x1.0 / hard mode x1.2 / POSTAL Difficulty x1.5
} enemyUser;



void askNickname(char[]);                  //Pide ingresar un nombre de jugador
int selectTraits(char[][dimChar], int);         //Pide seleccionar los rasgos de jugador
float damageDealedToEnemy(int, float, int, float);       //Retorna el da�o total hecho al enemigo
float criticalStrike(float, float);                //Duplica el da�o o no, luego retorna el valor definitivo del da�o
float calculateHp(float, float);              //Resta a la vida el da�o, sirve para el hp de jugador y hp de enemigo
float heal(float, float, float);                 //Suma al hp del jugador el valor de la curaci�n, como pociones, etc.
enemyUser spawnEnemy();           //Crea al enemigo que el jugador debe enfrentar, dandole valores aleatorios a cada caracter�stica
int selectDifficulty();                //Selecciona el n�mero de dificultad y la retorna
void showInitialStats(playerUser);        //Muestra las estad�sticas iniciales, usado en la creaci�n de personaje
void showAllStats(playerUser);          //Muestra la totalidad de las stats del jugador, usado al finalizar una run
bool dodgeroll(float, float, int);     //Decide si es efectivo el dodgeroll o no
bool blockAttack(float, float, int);      //Decide si el bloqueo con arma es efectivo o no
float convertDifValueToMultiplier(int);     //Transforma el dato de la dificultad en un multiplicador



void drawMenu();
void showActions();


// empezado el 16/07/2023
// terminado el --/--/----

/* APARTADO DE IDEAS
ENEMIGOS: esqueleto, esqueleto armado (armadura),


RASGOS: fuerte + x0.2 DMG, debil - x0.2 DMG, resistente +1def, piel de acero +2def, raquitico -3def, suertudo +0.1luck, desafortunado -0.1luck, maldito - 0.2luck
aprovechador de nutrientes +0.3hpmultiplier, insuficiencia cal�rica - x0.3hpmultiplier


Estructura de rasgos para mejor manipulaci�n
*/
