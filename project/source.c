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

int selectTraits(char traits[][dimChar], int totalTraits)       //falta completar (colocar mas rasgos)
{



    return totalTraits;
}

float damageDealedToEnemy(int weaponDamage, float damageMultiplier, int enemysDefense, float luck)
{
    float currentDamage = 0, damageDealed = 0;
    currentDamage = ( float ) weaponDamage * damageMultiplier;
    damageDealed = ( float ) currentDamage - ( currentDamage * ( enemysDefense * 0.1 ));
    damageDealed = criticalStrike(damageDealed, luck);
    return damageDealed;
}

float criticalStrike(float damageDealed, float luck)
{
    float criticalStrikeChance = 8.0;
    int pool = rand () % 100;
    criticalStrikeChance = criticalStrikeChance * luck;
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
        printf ( "Seleccionar dificultad\n" );
        printf ( "1- easy modo\n2- normal mode\n3- hard mode\n4- POSTAL difficulty\n0- Return\n" );
        scanf ( "%d", &difficulty );
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
        printf ( "Difficulty: 'POSTAL Difficulty'\n" );
    }
    printf ( "Final Score: %d", player.score );
}

bool dodgeroll(float dodgerollChance, float luck, int difficulty)
{
    bool dodgeSuccess = false;
    int pool = 0;
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
    int pool = 0;
    float difficultyDebuff = convertDifValueToMultiplier(difficulty);
    weaponBlockChance = ( float ) (( weaponBlockChance * luck ) + weaponBlockChance ) * difficultyDebuff;
    pool = rand () % 100;
    if ( pool < weaponBlockChance ) {
        dodgeSuccess = true;
    }
    return dodgeSuccess;
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


void showActions()
{
    printf ( "1- Attack\n" );
    printf ( "2- block next attack\n" );
    printf ( "3- DodgeRoll\n" );
    printf ( "4- Heal\n" );
    printf ( "5- Check Inventory\n" );
    printf ( "0- Do nothing\n" );
    printf ( "Answer..." );
}

void mainMenu()
{
    int input = 1;
    do {
        printf ( "1- Play\n");
        printf ( "2- Basics\n");
        printf ( "3- Credits\n");
        printf ( "0- Salir\n");
        printf ( "opcion...");
        scanf ( "%d", &input );
        switch ( input ) {
        case 1:
            system("cls");

            break;
        case 2:
            system("cls");

            break;
        case 3:
            system("cls");

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
        switch ( input ) {
        case 1:
            system("cls");
            //menu de new run
            break;
        case 2:
            system("cls");
            //history print
            break;
        case 3:
            system("cls");
            //HiScore print
            break;
        }
        system("cls");
    } while ( input != 0 );
}
