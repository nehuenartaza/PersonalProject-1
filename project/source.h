#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#define inventoryLimit 10
#define dimChar 25
#define nameLen 10
#define maxStages 3
#define maxRooms 10
#define scoresFile "history.bin"

/*typedef struct{
char name[dimChar];
int defenseBuff;
float hpMultiplierBuff;
float luckBuff;
float DMGBuff;
int skillPoints;
bool isPositive;
} traitUser;*/

typedef struct {
char name[dimChar];
bool isWeapon;          //indica si el objeto es un arma, en caso true tendr� los siguientes 2 atributos
int blockChance;
int weaponDMG;
float DMGmultiplierBonus;   //aumenta elmultiplicador de da�o del jugador
bool isItem;            //indica si el objeto es un item, en caso trie tendr� los siguientes 4 posibles atributos
int lifeHealPoints;
float HPmultiplierBonus;
int defenseBonus;
float luckBonus;
int scoreBonus;
bool itemIsDiscard;     //indica si fue descartado o no el objeto
bool canBeDiscard;      //indica si el item puede ser descartado
bool buffAdquired;      //indica si los potenciadores de los items se sumaron a las estad�sticas del jugador
} itemUser;

typedef struct {
char nickname[nameLen];
float HP;                    //vida de jugador. Default 100 / M�ximo 200
float hpMultiplier;     //multiplicador de vida. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int score;
float DMGtaken;       //total de da�o recibido
float DMGdealed;     //total de da�o hecho
float DMG;                //multiplicador de da�o. Default x1.0 / M�nimo x0.5 / M�ximo x1.5
int defense;               //defensa del jugador. Default 0 / M�nimo -5 / M�ximo 8
float luck;                 //mejora o empeora la posibilidad de un esquive exitoso, golpe cr�tico y todo lo que pueda ser afectado por la suerte. Default x1 / M�nimo x0.7 / M�ximo x1.3
itemUser inventory[inventoryLimit];  //listado de items
int amountItems;        //cantidad total de items
//traitUser traits[dimChar];   //buffs y debuffs de jugador
//int amountTraits;               //cantidad total de rasgos
int difficulty;             //1 - easy modo / 2 - normal mode / 3 - hard mode / 4 - Lunatic mode
int healingUsed;        //cuenta la cantidad de pociones de vida usadas
itemUser hands;
int stage;              //actual stage
int room;               //actual room
char killedBy[dimChar];         //Muestra la raz�n de muerte
} playerUser;

typedef struct {
char enemyType[dimChar];    //nombre del enemigo
float HP;
int DMG;
int defense;                // M�nimo 0 / M�ximo 7
float DMGmultiplier;        // easy modo x0.9 / normal mode x1.0 / hard mode x1.2 / Lunatic mode x1.5
bool isBoss;        //indica si el enemigo es un boss de nivel
} enemyUser;

//Player
void askNickname(char[]);                  //Pide ingresar un nombre de jugador
//int selectTraits(traitUser[], int);         //Pide seleccionar los rasgos de jugador
int selectDifficulty();                //Selecciona el n�mero de dificultad y la retorna
//void showPlayerTraits(traitUser[], int);    //Muestra todos los rasgos actuales del jugador
void showPlayerInventory(itemUser[], int);  //Muestra el inventario actual del jugador
void showBasicPlayerStats(playerUser);        //Muestra las estad�sticas iniciales, usado en la creaci�n de personaje

//Gameplay
void newRun();              //Lugar donde se desempe�a toda la traves�a
int doAction();                                 //Retorna la acci�n del jugador
float damageDealedToEnemy(int, float, int, float, int);       //Retorna el da�o total hecho al enemigo
float criticalStrike(float, float, int);                //Duplica el da�o o no, luego retorna el valor definitivo del da�o
float calculateHp(float, float);              //Resta a la vida el da�o, sirve para el hp de jugador y hp de enemigo
float returnHealing(int, float);             //Devuelve el valor total de la curacion
enemyUser spawnEnemy(int, int, float);           //Crea al enemigo que el jugador debe enfrentar, dandole valores aleatorios a cada caracter�stica
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
void printCurrentLocation(int, int);    //Muestra el stage y sala actual
enemyUser spawnBoss(int, int, float);  //Genera un jefe a derrotar
bool openChest();       //Indica si el jugador abre el cofre o no
float validLuckLimit(float);
int validDefenseLimit(int);
float validDMGmultiplierLimit(float);
float validHPmultiplierLimit(float);
float validMaxHealtLimit(float);
playerUser getItemsBonus(playerUser);   //Aplica las mejoras de los item al jugador y las resta cuando un objeto ya no est� en el inventario
itemUser changeWeaponInHands(itemUser, itemUser);   //Cambia de arma
bool healingInInventory(itemUser[], int);       //Busca que haya al menos 1 poci�n en el inventario
playerUser checkAndUseHealing(playerUser);      //Muestra una por una las pociones y le pregunta al jugador si desea usarla
float healOverTime(float, int);         //Da un peque�o bonificador de vida al matar un enemigo

//Menus
void mainMenu();
void playMenu();
void basicsMenu();
void howToPlay();
void explainPlayerStats();
void story();

//Misc
void error();               //Mensaje de error de archivo
void printHiScore();       //Busca el jugador con el HiScore de todos y lo muestra
void printCredits();       //Muestra qui�nes hicieron esta cosa (S�lo yo)
void printHistory();        //Muestra toda la informaci�n de todos los jugadores registrados
void saveRunData(playerUser);       //Guarda los datos del jugador luego de la partida
void showAllStats(playerUser);          //Muestra la totalidad de las stats del jugador, usado al finalizar una run
void printRandomEnemyMessage(char[]);    //Genera mensaje de enemigo al azar
void showEnemyStats(enemyUser);     //Muestra las estad�sticas del enemigo
void printRandomChestMessage();         //Genera mensaje de cofre al azar
int discardItemFromInventory(playerUser);   //Busca un espacio libre en el inventario
void showWeapon(itemUser);          //Muestra un arma
void showItem(itemUser);                //Muestra un item
int orderInventory(itemUser[], int);    //Ordena el inventario y la cantidad real de items tapando los espacios libres
void printRandomBossMessage(char[]); //Muestra un mensaje al azar de jefe
void printGameOverMessages(int);       //Muestra un mensaje humillante seg�n la dificultad si el jugador muere
void printWinMessages(int);      //Muestra un mensaje de victoria seg�n la dificultad, adem�s de agradecer al jugador por jugar

// empezado el 16/07/2023
// terminado el --/--/----

/* APARTADO DE IDEAS
FALTA: testear opcion de check inventory, testear manejo de inventario, testear esquive y bloqueo

RASGOS: fuerte + x0.2 DMG, debil - x0.2 DMG, resistente +1def, piel de acero +2def, raquitico -3def, suertudo +0.1luck, desafortunado -0.1luck, maldito - 0.2luck
aprovechador de nutrientes +0.3hpmultiplier, insuficiencia cal�rica - x0.3hpmultiplier
*/
