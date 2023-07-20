#include "source.h"

void askNickname(char nickname[])
{
    int confirm = 1;
    do {
        printf ( "Ingrese nombre\n" );
        gets ( nickname );
        printf ( "Seguro que '%s' es correcto? 1-Si, 0-No ", nickname );
        scanf ( "%d", &confirm );
    } while ( confirm != 1 );
}

int selectTraits(traitUser traits[], int totalTraits)       //falta completar (colocar mas rasgos)
{



    return totalTraits;
}

float damageDealedToEnemy(int weaponDamage, float damageMultiplier, int enemyDefense, float luck, int difficulty)
{
    float currentDamage = 0, damageDealed = 0;
    currentDamage = ( float ) weaponDamage * damageMultiplier;
    damageDealed = ( float ) currentDamage - ( currentDamage * ( enemyDefense * 0.1 ));
    damageDealed = criticalStrike(damageDealed, luck, difficulty);
    return damageDealed;
}

float damageDealedToPlayer(int playerDefense, float enemyDMG, float enemyDMGmultiplier) //terminar
{
    float damageReceived = 0;
    damageReceived = ( float ) (( enemyDMG * enemyDMGmultiplier ) + enemyDMG );
    return damageReceived;
}

bool dodgeOrBlockSuccess(bool dodge, bool block, int difficulty, float playerLuck, int weaponBlockChance)
{
    bool success = false;
    float pool = (float) rand() / ((float) 100), chances = 0;
    if ( dodge ) {
        chances = chanceOfDodging(difficulty, playerLuck);
        if ( pool < chances ) {
            success = true;
        } else {
                printf ( "Dodge failed\n" );
            }
    }
    if ( block ) {
        chances = chanceOfBlocking(difficulty, playerLuck, weaponBlockChance);
        if ( pool < chances ) {
            success = true;
        } else {
                printf ( "Block failed\n" );
            }
    }
    return success;
}

float chanceOfDodging(int difficulty, float playerLuck)
{
    float chances;
    switch ( difficulty ) {
    case 1:
        chances = 65;
        break;
    case 2:
        chances = 60;
        break;
    case 3:
        chances = 55;
        break;
    case 4:
        chances = 50;
        break;
    }
    chances = ( float ) chances + ( chances * playerLuck );
    return chances;
}

float chanceOfBlocking(int difficulty, float playerLuck, int weaponBlockChance)
{
    float chances;
    switch ( difficulty ) {
    case 1:
        weaponBlockChance = weaponBlockChance + 2;
        break;
    case 2:
        weaponBlockChance = weaponBlockChance - 1;
        break;
    case 3:
        weaponBlockChance = weaponBlockChance - 4;
        break;
    case 4:
        weaponBlockChance = weaponBlockChance - 7;
        break;
    }
    chances = ( float ) weaponBlockChance + ( weaponBlockChance * playerLuck );
    return chances;
}

float criticalStrike(float damageDealed, float luck, int difficulty)
{
    float criticalStrikeChance = 8.0;
    float pool = (float) rand () / ((float) 100);
    criticalStrikeChance = (criticalStrikeChance * luck) * (convertDifValueToMultiplier(difficulty));
    if ( pool < criticalStrikeChance ) {
        damageDealed = ( float ) damageDealed * 2;
        printf ( "Critical Strike!!!\n" );
    }
    return damageDealed;
}

float calculateHp(float hp, float input)
{
    hp = ( float ) hp - input;
    return hp;
}

float heal(float playerHP, float input, float hpMultiplier)
{
    playerHP = ( float ) playerHP + ( input * hpMultiplier );
    return playerHP;
}

enemyUser spawnEnemy()      //falta completar (colocar mas enemigos)
{
    enemyUser enemy;
    int r = rand () % totalEnemies;
    switch ( r ) {
    case 1:
        strcpy(enemy.enemyType, "skeleton");
        break;
    }
    return enemy;
}

int selectDifficulty()
{
    int difficulty = 0;
    do {
        printf ( "Seleccionar dificultad:\n" );
        printf ( "1- easy modo: modo de juego amigable para los mas novatos\n" );
        printf ( "2- normal mode: experiencia de juego estandar\n" );
        printf ( "3- hard mode: juego desafiante, para los mas experimentados\n" );
        printf ( "4- Lunatic mode: ni siquiera lo intentes\n" );
        printf ( "0- Return\n" );
        scanf ( "%d", &difficulty );
        if ( difficulty == 4 ) {
            system("cls");
            printf ( "You are about to play on the highest difficulty. Enemies will deal +x1.50 DMG than usual, the run could last much more time\n" );
            printf ( "Dodgerolls and blocks will have more chance of fail. Some things could be unbalanced. are you sure you want to continue?\n" );
            printf ( "1-easy modo / 2-normal mode / 3-hard mode / 4-continue in lunatic mode / 0-Return" );
            scanf ( "%d", &difficulty );
        }
        system("cls");
    } while ( difficulty < 0 || difficulty > 4 );
    return difficulty;
}

void showInitialStats(playerUser player)
{
    printf ( "Current status:\n" );
    printf ( "Initial hp: %.1f\n", player.HP );
    printf ( "Initial DMG: %.2f\n", player.DMG );
    printf ( "Initial def: %d", player.defense );
    printf ( "hp Multiplier: x%.1f\n", player.hpMultiplier );
    printf ( "Initial Luck: x%.1f\n", player.luck );
    switch ( player.difficulty ) {
    case 1:
        printf ( "Difficulty: 'easy modo'\n" );
        break;
    case 2:
        printf ( "Difficulty: 'normal mode'\n" );
        break;
    case 3:
        printf ( "Difficulty: 'hard mode'\n" );
    case 4:
        printf ( "Difficulty: 'POSTAL Difficulty'\n" );
    }
    showPlayerTraits(player.traits, player.amountTraits);
}

void showAllStats(playerUser player)
{
    printf ( "'%s' Stats:\n", player.nickname );
    printf ( "Final hp: %.1f\n", player.HP );
    printf ( "Final hpMultiplier: x%.1f\n", player.hpMultiplier );
    printf ( "Amount of healing used: %d", player.healingUsed );
    printf ( "Final DMG: %.2f\n", player.DMG );
    printf ( "Total DMG dealed: %.2f\n", player.DMGdealed );
    printf ( "Total DMG taken: %.2f\n", player.DMGtaken );
    printf ( "Final DEF: %d", player.defense );
    printf ( "Final Luck: x%.1f\n", player.luck );
    printf ( "Final Inventory: %d items\n", player.amountItems );
    showPlayerInventory(player.inventory, player.amountItems);
    showPlayerTraits(player.traits, player.amountTraits);
    switch ( player.difficulty ) {
    case 1:
        printf ( "Difficulty: 'easy modo'\n" );
        break;
    case 2:
        printf ( "Difficulty: 'normal mode'\n" );
        break;
    case 3:
        printf ( "Difficulty: 'hard mode'\n" );
    case 4:
        printf ( "Difficulty: 'Lunatic mode'\n" );
    }
    printf ( "Final Score: %d", player.score );
}

bool dodgeroll(float dodgerollChance, float luck, int difficulty)
{
    bool dodgeSuccess = false;
    float pool = (float) rand() / ((float) 100);
    float difficultyDebuff = convertDifValueToMultiplier(difficulty);
    dodgerollChance = ( float ) (( dodgerollChance * luck ) + dodgerollChance ) * difficultyDebuff;
    pool = rand () % 100;
    if ( pool < dodgerollChance ) {
        dodgeSuccess = true;
    }
    return dodgeSuccess;
}

bool blockAttack(float weaponBlockChance, float luck, int difficulty)
{
    bool dodgeSuccess = false;
    float pool = (float) rand() / ((float) 100);
    float difficultyDebuff = convertDifValueToMultiplier(difficulty);
    weaponBlockChance = ( float ) (( weaponBlockChance * luck ) + weaponBlockChance ) * difficultyDebuff;
    pool = rand () % 100;
    if ( pool < weaponBlockChance ) {
        dodgeSuccess = true;
    }
    return dodgeSuccess;
}

bool willDodgeroll()    //en showactions
{
    int confirm = 0;
    bool will = false;
    do {
        printf ( "are you sure you want to dodgeroll? 1-yes 0-No\n" );
        scanf ( "%d", &confirm );
    } while ( confirm != 1 || confirm != 0 );
    if ( confirm == 1 ) {
        will = true;
    }
    return will;
}

bool willBlock()    //en showactions
{
    int confirm = 0;
    bool will = false;
    do {
        printf ( "are you sure you want to block? 1-yes 0-No\n" );
        scanf ( "%d", &confirm );
    } while ( confirm != 1 || confirm != 0 );
    if ( confirm == 1 ) {
        will = true;
    }
    return will;
}

float convertDifValueToMultiplier(int difficulty)
{
    float difficultyDebuff = 0;
    switch ( difficulty ) {
    case 1:
        difficultyDebuff = 1.0;
        break;
    case 2:
        difficultyDebuff = 0.9;
        break;
    case 3:
        difficultyDebuff = 0.8;
        break;
    case 4:
        difficultyDebuff = 0.7;
        break;
    default:
        difficultyDebuff = 1.0;
        break;
    }
    return difficultyDebuff;
}

void showPlayerTraits(traitUser traits[], int total)
{
    if ( total != 0 ) {
        printf ( "Traits selected:\n" );
        for ( int i = 0; i < total; i++ ) {
            printf ( "'%s' | ", traits[i].name);
            if ( traits[i].isPositive ) {
                printf ( "(Positive)\n" );
            } else {
                    printf ( "(Negative)\n" );
                }
            if ( traits[i].defenseBuff != 0 ) {
                printf ( "DEF: %d\n", traits[i].defenseBuff );
            }
            if ( traits[i].DMGBuff != 0 ) {
                printf ( "DMG: %.2f\n", traits[i].DMGBuff );
            }
            if ( traits[i].hpMultiplierBuff != 0 ) {
                printf ( "hpMultiplier: %.2f", traits[i].hpMultiplierBuff );
            }
            if ( traits[i].luckBuff != 0 ) {
                printf ( "luck modifier: %.2f", traits[i].luckBuff );
            }
        }
    }
}

void showPlayerInventory(itemUser inventory[], int total)
{
    if ( total != 0 ) {
        for ( int i = 0; i < total; i++ ) {
            if ( inventory[i].itemIsDiscard == false ) {
                printf ( "Item: '%s' ", inventory[i].name);
                if ( inventory[i].isItem ) {
                    printf ( "(Utility)\n" );
                    printf ( "modifier DEF: %d\n", inventory[i].defenseBonus );
                    printf ( "restores: %d life\n", inventory[i].lifeHealPoints );
                    printf ( "luck: %.2f\n", inventory[i].luckBonus );
                    printf ( "+%d score having this item when run finished\n\n", inventory[i].scoreBonus );
                }
                if ( inventory[i].isWeapon ) {
                    printf ( "(Weapon)\n" );
                    printf ( "DMG: %d\n", inventory[i].weaponDMG );
                    printf ( "Block-Chance: %d\n\n", inventory[i].blockChance );
                }
            }
        }
    }
}

itemUser giveBasicWeapon()
{
    itemUser weapon;
    weapon.isWeapon = true;
    weapon.isItem = false;
    weapon.itemIsDiscard = false;
    weapon.blockChance = (60 - 40) * ((float) rand() / 60) + 40;
    weapon.weaponDMG = (50 - 30) * ((float) rand() / 50) + 30;
    weapon.defenseBonus = 0;
    weapon.lifeHealPoints = 0;
    weapon.luckBonus = 0;
    weapon.scoreBonus = 0;
    strcpy(weapon.name, "basic dagger" );
    return weapon;
}

itemUser generateItem()
{
    itemUser item;
    item.isItem = true;
    item.isWeapon = false;
    item.itemIsDiscard = false;
    item.blockChance = 0;
    item.defenseBonus = 0;
    item.luckBonus = 0;
    item.scoreBonus = 0;
    item.weaponDMG = 0;
    int r = rand() % 10;
    if ( r < 5 ) {
        r = rand() % 10;
        if ( r < 5 ) {
            strcpy(item.name,"HealingPotion");
            item.lifeHealPoints = rand() % (50 - 25) * (rand() % 50) + 25;
        } else {
                strcpy(item.name,"GreaterHealingPotion");
                item.lifeHealPoints = rand() % (100 - 60) * (rand() % 100) + 60;
            }
    } else {
            item = itemPool();
        }
    return item;
}

itemUser itemPool()
{
    itemUser item;
    int r = rand() % 3;
    switch ( r ) {
    case 1: //rings

        break;




    }


    return item;
}

itemUser generateWeapon()       //hacer
{
    itemUser weapon;

    return weapon;
}

int doAction(playerUser player)      //mejorar
{
    int input = 0;
    do {
        printf ( "1- Attack\n" );
        printf ( "2- block next attack\n" );
        printf ( "3- DodgeRoll\n" );
        printf ( "4- Heal\n" );
        printf ( "5- Check Inventory\n" );
        printf ( "0- Do nothing\n" );
        printf ( "Answer..." );
        scanf ( "%d", &input );
        if ( input == 5 ) {
            showPlayerInventory(player.inventory, player.amountItems);
        }
        //condicionales si input == 4 o input == 5
    } while ( input > 4 || input < 0 );
    return input;
}

void showHands(itemUser weapon)
{
    printf ( "Weapon obtained: '%s'\n", weapon.name );
    printf ( "DMG: %d\n", weapon.weaponDMG );
    printf ( "Block chance %d", weapon.blockChance );
    system("pause");
}

void mainMenu()
{
    int input = 1;
    do {
        printf ( "1- Play\n" );
        printf ( "2- Basics\n" );
        printf ( "3- Credits\n" );
        printf ( "4- Story\n" );
        printf ( "0- Leave\n" );
        printf ( "Insert number..." );
        scanf ( "%d", &input );
        switch ( input ) {
        case 1:
            system("cls");
            playMenu();
            break;
        case 2:
            system("cls");
            basicsMenu();
            break;
        case 3:
            system("cls");
            printfCredits();
            break;
        case 4:
            system("cls");
            story();
            break;
        }
        system("cls");
    } while ( input != 0 );
}

void playMenu()
{
    int input = 1;
    do {
        printf ( "1- New Run\n" );
        printf ( "2- Print history\n" );
        printf ( "3- Print player with HiScore\n" );
        printf ( "0- Return\n" );
        scanf ( "%d", &input );
        switch ( input ) {
        case 1:
            system("cls");
            newRun();
            break;
        case 2:
            system("cls");
            printfHistory();
            break;
        case 3:
            system("cls");
            printfHiScore();
            break;
        }
        system("cls");
    } while ( input != 0 );
}

void newRun()                   //completar
{
    int action = 0;
    float damage = 0;   //va a recibir el daño hecho tanto por parte del jugador como del enemigo
    bool block = false, dodge = false;  //indica si el jugador va a esquivar el ataque o bloquearlo
    bool success = false;   //posibilidad de bloquear o esquivar el ataque
    playerUser player;
    itemUser item;
    player.difficulty = selectDifficulty();
    player.amountTraits = selectTraits(player.traits, player.amountTraits);
    player.hands = giveBasicWeapon();
    showHands(player.hands);
    enemyUser enemy;
    enemy = spawnEnemy();
    do {
        if ( enemy.HP < 0 ) {
            //generar enemigo
            //funciones con printf's que indiquen al jugador el enemigo, su vida y daño, además de dar ambientación para aumentar la jugabilidad
        }
        action = doAction(player);
        switch ( action ) {
        case 1:     //si jugador ataca
            damage = damageDealedToEnemy(player.hands.weaponDMG, player.DMG, enemy.defense, player.luck, player.difficulty);
            enemy.HP = calculateHp(enemy.HP, damage);
            player.DMGdealed = player.DMGdealed + damage;
            printf ( "Damage dealed: %.2f\n", damage );
            system("pause");
            system("cls");
            break;
        case 2:     //si jugador bloquea
            block = willBlock();
            break;
        case 3:     //si jugador esquiva
            dodge = willDodgeroll();
            break;
        }
        if ( enemy.HP > 0 ) {   //El enemigo ataca si no está muerto
            damage = damageDealedToPlayer(player.defense, enemy.DMG, enemy.DMGmultiplier);
            if ( block ) {
                success = dodgeOrBlockSuccess(dodge, block, player.difficulty, player.luck, player.hands.weaponDMG);
            }
            if ( dodge ) {
                success = dodgeOrBlockSuccess(dodge, block, player.difficulty, player.luck, player.hands.weaponDMG);
            }
            if ( success ) {
                damage = 0;
                printf ( "Attack evaded\n" );
                system("pause");
            } else {
                    player.HP = player.HP - damage;
                }
        } else {
                printf ( "Enemy defeated!\n" );
                //aumentar en 1 la sala, falta crear el sistema de mapa
            }



        block = false;
        dodge = false;
        success = false;
    } while ( player.HP > 0 );


}

void printfHistory()
{
    playerUser player;
    FILE * historyFile = fopen(scoresFile,"ab");
    if ( historyFile != NULL ) {
        while ( !feof(historyFile)) {
            fread(&player, sizeof(playerUser), 1, historyFile);
            if ( !feof(historyFile)) {
                showAllStats(player);
            }
        }
        fclose(historyFile);
    } else {
            error();
        }
}

void printfHiScore()
{
    playerUser HSplayer;
    FILE * historyFile = fopen(scoresFile,"rb");
    int HiScore = 0, positionOfBest = 0, timesMoving = 0;
    if ( historyFile != NULL ) {
        for ( timesMoving = 0; !feof(historyFile); timesMoving++ ) {
            fread(&HSplayer, sizeof(playerUser), 1, historyFile);
            if ( !feof(historyFile) && HiScore < HSplayer.score ) {
                HiScore = HSplayer.score;
                positionOfBest = timesMoving;
            }
        }
        fseek(historyFile, sizeof(playerUser) * positionOfBest, SEEK_SET);
        fread(&HSplayer, sizeof(playerUser), 1, historyFile);
        showAllStats(HSplayer);
        fclose(historyFile);
    } else {
            error();
        }
}

void saveRunData(playerUser player)
{
    FILE * destiny = fopen(scoresFile,"ab");
    if ( destiny != NULL ) {
        fwrite(&player, sizeof(playerUser), 1, destiny);
        fclose(destiny);
        printf ( "Data saved\n" );
        system("pause");
    } else {
            error();
        }
}

void basicsMenu()
{
    int input = 1;
    do {
        printf ( "1- How to play\n" );
        printf ( "2- Items\n" );
        printf ( "3- Player stats explained\n" );
        printf ( "0- Return\n" );
        scanf ( "%d", &input );
        switch ( input ) {
        case 1:
            system("cls");
            howToPlay();
            break;
        case 2:
            system("cls");
            explainItems();
            break;
        case 3:
            system("cls");
            explainPlayerStats();
            break;
        }
        system("cls");
    } while ( input != 0 );
}

void howToPlay()
{
    printf ( "You start by default with 100HP and 1 default weapon\n" );
    system("pause");
    printf ( "Each enemy has their own health, damage and damage multiplier and defense\n" );
    system("pause");
    printf ( "You can attack them or dodge or block their attacks with a chance of failing and taking damage\n" );
    system("pause");
    printf ( "You can also heal yourself with items like potions\n" );
    system("pause");
}

void explainItems()                 //completar
{

}

void explainPlayerStats()               //completar
{
    printf ( "Defense: player by default starts with 0, minimal defense is -5 and max is 8, each 1 defense equals to x0.1 damage reduction\n" );
    system("pause");
    printf ( "hpMultiplier: by default x1.0, minimal is x0.5 and max is x1.5. This increases or decreases the total hp gained when the player heals\n" );
    system("pause");
    printf ( "Luck: x1 by default, minimal x0.7, max x1.3.Buffs or debuffs chances of dodging, critical hit and all that can be afected by it\n" );
    system("pause");
    printf ( "Player DMG: by default x1.0, minimal x0.5, max x1.5. This stat multiplies the damage of the weapon the player is using\n" );
    system("pause");
    printf ( "Difficulty: this afects chances of dodging and critical hit chances\n" );
}

void story()
{
    printf ( "I dont have imagination and this doesnt have story, create you own\n- I understand..." );
    system("pause");
}

void printfCredits()
{
    printf ( "Project coded in 'Code::Blocks' with C\n" );
    printf ( "Game Designer\nNehuen Artaza\n\n" );
    printf ( "Game Code by\nNehuen Artaza\n\n" );
    system("pause");
}

void error()
{
    printf ( "File doesnt exist or failed at open\n" );
}

