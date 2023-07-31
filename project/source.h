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

typedef struct {
char name[dimChar];
bool isWeapon;          //indica si el objeto es un arma, en caso true tendrá los siguientes 2 atributos
int blockChance;
int weaponDMG;
bool isItem;            //indica si el objeto es un item, en caso true tendrá los siguientes 6 posibles atributos
float DMGmultiplierBonus;
int lifeHealPoints;
float HPmultiplierBonus;
int defenseBonus;
float luckBonus;
int scoreBonus;
bool itemIsDiscard;     //indica si fue descartado o no el objeto (incompatible con armas)
bool canBeDiscard;      //indica si el item puede ser descartado (incompatible con armas)
bool buffAdquired;      //indica si los potenciadores de los items se sumaron a las estadísticas del jugador (incompatible con armas)
} itemUser;

typedef struct {
char nickname[nameLen];
float HP;                    //vida de jugador. Default 100 / Máximo 200
float hpMultiplier;     //multiplicador de vida. Default x1.0 / Mínimo x0.5 / Máximo x1.5
int score;
float DMGtaken;       //total de daño recibido
float DMGdealed;     //total de daño hecho
float DMG;                //multiplicador de daño. Default x1.0 / Mínimo x0.5 / Máximo x1.5
int defense;               //defensa del jugador. Default 0 / Mínimo -5 / Máximo 8
float luck;                 //mejora o empeora la posibilidad de un esquive exitoso, golpe crítico y todo lo que pueda ser afectado por la suerte. Default x1 / Mínimo x0.7 / Máximo x1.3
itemUser inventory[inventoryLimit];  //listado de items
int amountItems;        //cantidad total de items
int difficulty;             //1 - easy modo / 2 - normal mode / 3 - hard mode / 4 - Lunatic mode
int healingUsed;        //cuenta la cantidad de pociones de vida usadas
itemUser hands;     //arma equipada
int stage;              //actual stage
int room;               //actual room
char killedBy[dimChar];         //Muestra la razón de muerte
} playerUser;

typedef struct {
char enemyType[dimChar];    //nombre del enemigo
float HP;
int DMG;
int defense;                // Mínimo 0 / Máximo 7
float DMGmultiplier;        // easy modo x0.9 / normal mode x1.0 / hard mode x1.2 / Lunatic mode x1.5
bool isBoss;        //indica si el enemigo es un boss de nivel
} enemyUser;


//Player
void askNickname(char[]);                  //Pide ingresar un nombre de jugador
int selectDifficulty();                             //Selecciona el número de dificultad y la retorna
itemUser giveBasicWeapon();         //Le otorga un arma inicial al jugador


//Gameplay
float damageDealedToEnemy(int, float, int, float, int);     //Retorna el daño total hecho al enemigo
float damageDealedToPlayer(int, float, float);               //Retorna el daño hecho al jugador
float criticalStrike(float, float, int);                          //Duplica el daño o no, luego retorna el valor definitivo del daño
float calculateHp(float, float);                             //Resta a la vida el daño, sirve para el hp de jugador y hp de enemigo
float returnHealing(int, float);                         //Devuelve el valor total de la curacion
float convertDifValueToMultiplier(int);     //Transforma el dato de la dificultad en un multiplicador ( nerfea la chance de critical strike )
void newRun();                               //Lugar donde se desempeña toda la travesía
float healOverTime(float, int);                 //Da un pequeño bonificador de vida al matar un enemigo
itemUser changeWeaponInHands(itemUser, itemUser);             //Cambia de arma del jugador
void printGameOverMessages(int);                    //Muestra un mensaje humillante según la dificultad si el jugador muere
void printWinMessages(int);                //Muestra un mensaje de victoria según la dificultad, además de agradecer al jugador por jugar


//Dodging/Blocking & player actions
bool dodgeOrBlockSuccess(bool, bool, int, float, int);      //Decide si el esquive o el bloqueo falló o no
float chanceOfDodging(int, float);                                    //Retorna la posibilidad que hay de esquivar
float chanceOfBlocking(int, float, int);                              //Retorna la posibilidad que hay de bloquear
bool dodgeroll(float, float, int);                                  //Decide si es efectivo el dodgeroll o no
bool blockAttack(float, float, int);                              //Decide si el bloqueo es efectivo o no
bool willDodgeroll();                                                   //Pregunta al jugador si de verdad quiere esquivar
bool willBlock();                                                           //Pregunta al jugador si de verdad quiere bloquear
bool openChest();                                                      //Indica si el jugador abre el cofre o no
int doAction();                                              //Retorna la acción del jugador
playerUser checkAndUseHealing(playerUser);      //Muestra una por una las pociones disponibles y le pregunta al jugador si desea usarla
playerUser discardItemFromInventory(playerUser);   //Recorre el inventario y pregunta al jugador si desea soltar un item


//Generation
enemyUser spawnEnemy(int, int);           //Crea al enemigo dandole valores aleatorios a cada característica
enemyUser spawnBoss(int, int);               //Genera un jefe a derrotar
itemUser generateItem();                     //Decide si generar un item o una poción
itemUser itemPool();                                //Genera un item dentro de un listado de posibilidades
itemUser generateWeapon();               //Genera un arma al azar


//Validations ( se valida límite de las características del jugador para calcular algo, como reducción de daño )
float validLuckLimit(float);
int validDefenseLimit(int);
float validDMGmultiplierLimit(float);
float validHPmultiplierLimit(float);
float validMaxHealtLimit(float);
float realDamageReceived(float, float);      //if HP < 0, then calculate exact damage for HP == 0, used for player.DMGdealed and DMGtaken
bool healingInInventory(itemUser[], int);        //Busca que haya al menos 1 poción en el inventario
int returnScoreFromInventory(itemUser[], int);      //Cuenta el total de score almacenado en el inventario y lo suma al finalizar la run
playerUser getItemsBonus(playerUser);         //Aplica las mejoras de los items al jugador y las resta cuando un objeto ya no está en el inventario
int orderInventory(itemUser[], int);      //Ordena el inventario y la cantidad real de items tapando los espacios libres


//Print stats
void showBasicPlayerStats(playerUser);        //Muestra las estadísticas básicas del jugador
void showAllStats(playerUser);          //Muestra la totalidad de las stats del jugador
void showPlayerInventory(itemUser[], int);  //Muestra el inventario actual del jugador
void showHands(itemUser);         //Muestra el arma que el jugador lleva equipado
void showWeapon(itemUser);          //Muestra un arma
void showItem(itemUser);                //Muestra un item
void printCurrentLocation(int, int);    //Muestra el stage y sala actual
void showEnemyStats(enemyUser);     //Muestra las estadísticas del enemigo


//Menus
void mainMenu();
void playMenu();
void basicsMenu();
void howToPlay();
void explainPlayerStats();
void story();
void printCredits();       //Muestra quiénes hicieron esta cosa (Sólo yo)


//Miscelaneous
void printRandomChestMessage();                      //Genera mensaje de cofre al azar
void printRandomEnemyMessage(char[]);             //Genera mensaje de enemigo al azar
void printRandomBossMessage(char[]);                     //Muestra un mensaje al azar de jefe
void printHistory();                                              //Muestra toda la información de todos los jugadores registrados
void printHiScore();                                        //Busca el jugador con el HiScore de todos y lo muestra
void saveRunData(playerUser);                   //Guarda los datos del jugador luego de la partida
void error();                                                       //Mensaje de error de archivo
