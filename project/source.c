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

void selectTraits()
{

}

float damageDealedToEnemy(int weaponDamage, float damageMultiplier, int enemysDefense)
{
    float currentDamage = 0, damageDealed = 0;
    currentDamage = ( float ) weaponDamage * damageMultiplier;
    damageDealed = ( float ) currentDamage - ( currentDamage * ( enemysDefense * 0.1 ));
    damageDealed = criticalStrike(damageDealed);
    return damageDealed;
}

float criticalStrike(float damageDealed)
{
    int chance = 0;
    chance = rand () % 1000;
    if ( chance%3 == 0 || chance%7 == 0 ) {
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

float heal(float playerHP, float input)
{
    playerHP = ( float ) playerHP + input;
    return playerHP;
}

enemyUser spawnEnemy()
{
    enemyUser enemy;
    int r = 0;
    //rand


    return enemy;
}

void drawMenu()
{
    printf ( "1- Play\n");
    printf ( "2- Basics\n");
    printf ( "3- Credits\n");
    printf ( "0- Salir\n");
    printf ( "opcion...");
}
