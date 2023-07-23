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
#define traitsFile "traitsSource.bin"

typedef struct{
char name[dimChar];
int defenseBuff;
float hpMultiplierBuff;
float luckBuff;
float DMGBuff;
int skillPoints;
bool isPositive;
} traitUser;

typedef struct {
char name[dimChar];
bool isWeapon;          //indica si el objeto es un arma, en caso true tendr� los siguientes 2 atributos
int blockChance;
int weaponDMG;
bool isItem;            //indica si el objeto es un item, en caso trie tendr� los siguientes 4 posibles atributos
int lifeHealPoints;
int defenseBonus;
float luckBonus;
int scoreBonus;
bool itemIsDiscard;     //indica si fue descartado o no el objeto
bool canBeDiscard;      //indica si el item puede ser descartado
} itemUser;

typedef struct {
char nickname[nameLen];
float HP;                    //vida de jugador. Default 100
float hpMultiplier;     //multiplicador de vida. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int score;
float DMGtaken;       //total de da�o recibido
float DMGdealed;     //total de da�o hecho
float DMG;                //multiplicador de da�o. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int defense;               //defensa del jugador. Default 0 / M�nimo -5 / M�ximo 8
float luck;                 //mejora o empeora la posibilidad de un esquive exitoso, golpe cr�tico y todo lo que pueda ser afectado por la suerte. Default x1 / M�nimo x0.7 / M�ximo x1.3
itemUser inventory[dimInt];  //listado de items
int amountItems;        //cantidad total de items
traitUser traits[dimChar];   //buffs y debuffs de jugador
int amountTraits;               //cantidad total de rasgos
int difficulty;             //1 - easy / 2 - normal / 3 - hard / 4 - Lunatic mode
int healingUsed;        //cuenta la cantidad de pociones de vida usadas
itemUser hands;
} playerUser;

typedef struct {
char enemyType[dimChar];    //nombre del enemigo
float HP;
int DMG;
int defense;                // M�nimo 0 / M�ximo 7
float DMGmultiplier;        // easy modo x0.9 / normal mode x1.0 / hard mode x1.2 / Lunatic mode x1.5
bool IsBoss;        //indica si el enemigo es un boss de nivel
} enemyUser;

//Player
void askNickname(char[]);                  //Pide ingresar un nombre de jugador
int selectTraits(traitUser[], int);         //Pide seleccionar los rasgos de jugador
int selectDifficulty();                //Selecciona el n�mero de dificultad y la retorna
void showPlayerTraits(traitUser[], int);    //Muestra todos los rasgos actuales del jugador
void showPlayerInventory(itemUser[], int);  //Muestra el inventario actual del jugador
void showInitialStats(playerUser);        //Muestra las estad�sticas iniciales, usado en la creaci�n de personaje

//Gameplay
void newRun();
int doAction(playerUser);
float damageDealedToEnemy(int, float, int, float, int);       //Retorna el da�o total hecho al enemigo
float criticalStrike(float, float, int);                //Duplica el da�o o no, luego retorna el valor definitivo del da�o
float calculateHp(float, float);              //Resta a la vida el da�o, sirve para el hp de jugador y hp de enemigo
float heal(float, float, float);             //Suma al hp del jugador el valor de la curaci�n, como pociones, etc.
enemyUser spawnEnemy();           //Crea al enemigo que el jugador debe enfrentar, dandole valores aleatorios a cada caracter�stica
bool dodgeroll(float, float, int);     //Decide si es efectivo el dodgeroll o no
bool blockAttack(float, float, int);      //Decide si el bloqueo con arma es efectivo o no
float convertDifValueToMultiplier(int);     //Transforma el dato de la dificultad en un multiplicador
float chanceOfBlocking(int, float, int);    //Retorna la posibilidad que hay de bloquear
float chanceOfDodging(int, float);          //Retorna la posibilidad que hay de esquivar
bool dodgeOrBlockSuccess(bool, bool, int, float, int);  //Decide si el esquive o el bloqueo fall� o no
itemUser giveBasicWeapon();         //Le otorga un arma inicial al jugador
void showHands(itemUser);         //Muestra el arma que el jugador lleva equipado
itemUser generateItem();        //Decide si generar un item o una poci�n
itemUser itemPool();          //Genera un item dentro de un listado de posibilidades
itemUser generateWeapon();      //Genera un arma al azar





//Menus
void mainMenu();
void playMenu();
void basicsMenu();
void howToPlay();
void explainPlayerStats();
void story();

//Misc
void error();
void printHiScore();       //Busca el jugador con el HiScore de todos y lo muestra
void printfCredits();
void printHistory();        //Muestra toda la informaci�n de todos los jugadores registrados
void saveRunData(playerUser);       //Guarda los datos del jugador luego de la partida
void showAllStats(playerUser);          //Muestra la totalidad de las stats del jugador, usado al finalizar una run

// empezado el 16/07/2023
// terminado el --/--/----

/* APARTADO DE IDEAS
ENEMIGOS: esqueleto, esqueleto armado (armadura),


RASGOS: fuerte + x0.2 DMG, debil - x0.2 DMG, resistente +1def, piel de acero +2def, raquitico -3def, suertudo +0.1luck, desafortunado -0.1luck, maldito - 0.2luck
aprovechador de nutrientes +0.3hpmultiplier, insuficiencia cal�rica - x0.3hpmultiplier

*/
