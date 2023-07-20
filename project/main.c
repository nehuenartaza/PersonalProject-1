#include "source.h"

int main()
{
    /*playerUser player;
    player.amountItems = 0;
    player.defense = 0;
    player.difficulty = -1;
    player.DMG = 7.0;
    player.DMGdealed = 0;
    player.DMGtaken = 0;
    player.HP = 100.0;
    player.hpMultiplier = 1.0;
    player.inventory;
    player.luck = 0.0;
    strcpy(player.nickname, "?");
    player.score = 0;
    player.traits;*/
    //enemyUser enemy;
    srand(time(NULL));

    int option;
    do {
        mainMenu();
        scanf ( "%d", &option );


    } while ( option != 0 );
    return 0;
}
