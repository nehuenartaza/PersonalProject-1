#include "source.h"

void askNickname(char nickname[])
{
    int confirm = 1;
    do {
        printf ( "Insert your name\n" );
        fflush(stdin);
        gets ( nickname );
        printf ( "Are you sure that '%s' is correct? This cant be reversed. 1-Yes, 0-No\n", nickname );
        scanf ( "%d", &confirm );
    } while ( confirm != 1 );
}

/*int selectTraits(traitUser traits[], int totalTraits)       //falta completar (colocar mas rasgos)
{



    return totalTraits;
}*/

float damageDealedToEnemy(int weaponDamage, float damageMultiplier, int enemyDefense, float luck, int difficulty)
{
    float currentDamage = 0, damageDealed = 0;
    damageMultiplier = validDMGmultiplierLimit(damageMultiplier);
    currentDamage = ( float ) weaponDamage * damageMultiplier;
    damageDealed = ( float ) currentDamage - ( currentDamage * ( enemyDefense * 0.1 ));
    damageDealed = criticalStrike(damageDealed, luck, difficulty);
    return damageDealed;
}

float damageDealedToPlayer(int playerDefense, float enemyDMG, float enemyDMGmultiplier)
{
    float damageReceived = 0;
    playerDefense = validDefenseLimit(playerDefense);
    damageReceived = ( float ) enemyDMG * enemyDMGmultiplier;
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
    playerLuck = validLuckLimit(playerLuck);
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
    playerLuck = validLuckLimit(playerLuck);
    chances = ( float ) weaponBlockChance + ( weaponBlockChance * playerLuck );
    return chances;
}

float criticalStrike(float damageDealed, float luck, int difficulty)
{
    float criticalStrikeChance = 8.0;
    float pool = (float) rand () / ((float) 100);
    luck = validLuckLimit(luck);
    criticalStrikeChance = ( float ) (criticalStrikeChance * luck) * (convertDifValueToMultiplier(difficulty));
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

float returnHealing(int input, float hpMultiplier)
{
    hpMultiplier = validHPmultiplierLimit(hpMultiplier);
    float totalHealing = ( float ) input * hpMultiplier;
    return totalHealing;
}

float validLuckLimit(float luck)
{
    if ( luck > 1.3 ) {
        luck = 1.3;
    } else if ( luck < 0.7 ) {
            luck = 0.7;
        }
        return luck;
}

int validDefenseLimit(int playerDefense)
{
    if ( playerDefense > 8 ) {
        playerDefense = 8;
    } else if ( playerDefense < -5 ) {
            playerDefense = -5;
        }
    return playerDefense;
}

float validDMGmultiplierLimit(float DMGmultiplier)
{
     if ( DMGmultiplier > 1.5 ) {
        DMGmultiplier = 1.5;
    } else if ( DMGmultiplier < 0.5 ) {
            DMGmultiplier = 0.5;
        }
        return DMGmultiplier;
}

float validHPmultiplierLimit(float HPmultiplier)
{
    if ( HPmultiplier > 1.5 ) {
        HPmultiplier = 1.5;
    } else if ( HPmultiplier < 0.5 ) {
            HPmultiplier = 0.5;
        }
    return HPmultiplier;
}

float validMaxHealtLimit(float playerHealth)
{
    if ( playerHealth > 200.0 ) {
        playerHealth = 200.0;
    }
    return playerHealth;
}

enemyUser spawnEnemy(int stage, int difficulty)
{
    enemyUser enemy;
    enemy.isBoss = false;
    int r = 0;
    switch ( difficulty ) {
    case 1:
        enemy.DMGmultiplier = 0.9;
        break;
    case 2:
        enemy.DMGmultiplier = 1.0;
        break;
    case 3:
        enemy.DMGmultiplier = 1.2;
        break;
    case 4:
        enemy.DMGmultiplier = 1.5;
        break;
    }

    switch ( stage ) {
    case 1:
        r = rand () % 6;
        switch ( r ) {
        case 0:
            strcpy(enemy.enemyType, "totally normal skeleton");
            enemy.defense = ( rand () % ( 3 - 2 + 1 ) ) + 0;
            enemy.DMG = ( rand () % ( 13 - 7 + 1 ) ) + 7;
            enemy.HP = ( float ) ( rand () % ( 28 - 23 + 1 ) ) + 23;
            break;
        case 1:
            strcpy(enemy.enemyType, "clockwork thing");
            enemy.defense = ( rand () % ( 4 - 2 + 1 ) ) + 2;
            enemy.DMG = ( rand () % ( 17 - 9 + 1 ) ) + 9;
            enemy.HP = ( float ) ( rand () % ( 43 - 29 + 1 ) ) + 29;
            break;
        case 2:
            strcpy(enemy.enemyType, "flying eye");
            enemy.defense = ( rand () % ( 2 - 0 + 1 ) ) + 0;
            enemy.DMG = ( rand () % ( 18 - 5 + 1 ) ) + 5;
            enemy.HP = ( float ) ( rand () % ( 29 - 17 + 1 ) ) + 17;
            break;
        case 3:
            strcpy(enemy.enemyType, "book head");
            enemy.defense = ( rand () % ( 3 - 2 + 1 ) ) + 2;
            enemy.DMG = ( rand () % ( 18 - 10 + 1 ) ) + 10;
            enemy.HP = ( float ) ( rand () % ( 30 - 21 + 1 ) ) + 21;
            break;
        case 4:
            strcpy(enemy.enemyType, "ant");
            enemy.defense = ( rand () % ( 1 - 0 + 1 ) ) + 0;
            enemy.DMG = ( rand () % ( 15 - 9 + 1 ) ) + 9;
            enemy.HP = ( float ) ( rand () % ( 12 - 9 + 1 ) ) + 9;
            break;
        case 5:
            strcpy(enemy.enemyType, "possesed radio");
            enemy.defense = ( rand () % ( 2 - 1 + 1 ) ) + 1;
            enemy.DMG = ( rand () % ( 24 - 18 + 1 ) ) + 18;
            enemy.HP = ( float ) ( rand () % ( 29 - 23 + 1 ) ) + 23;
            break;
        }
        break;
    case 2:
        r = rand () % 6;
        switch ( r ) {
        case 0:
            strcpy(enemy.enemyType, "jellyfish");
            enemy.defense = ( rand () % ( 1 - 0 + 1 ) ) + 0;
            enemy.DMG = ( rand () % ( 28 - 20 + 1 ) ) + 20;
            enemy.HP = ( float ) ( rand () % ( 51 - 48 + 1 ) ) + 48;
            break;
        case 1:
            strcpy(enemy.enemyType, "diamond elemental");
            enemy.defense = ( rand () % ( 6 - 5 + 1 ) ) + 5;
            enemy.DMG = ( rand () % ( 29 - 26 + 1 ) ) + 26;
            enemy.HP = ( float ) ( rand () % ( 78 - 69 + 1 ) ) + 69;
            break;
        case 2:
            strcpy(enemy.enemyType, "pirate");
            enemy.defense = ( rand () % ( 2 - 1 + 1 ) ) + 1;
            enemy.DMG = ( rand () % ( 33 - 27 + 1 ) ) + 27;
            enemy.HP = ( float ) ( rand () % ( 60 - 50 + 1 ) ) + 50;
            break;
        case 3:
            strcpy(enemy.enemyType, "gargoile");
            enemy.defense = ( rand () % ( 6 - 4 + 1 ) ) + 4;
            enemy.DMG = ( rand () % ( 33 - 31 + 1 ) ) + 31;
            enemy.HP = ( float ) ( rand () % ( 73 - 68 + 1 ) ) + 68;
            break;
        case 4:
            strcpy(enemy.enemyType, "armored snowball");
            enemy.defense = ( rand () % ( 4 - 2 + 1 ) ) + 2;
            enemy.DMG = ( rand () % ( 39 - 33 + 1 ) ) + 33;
            enemy.HP = ( float ) ( rand () % ( 26 - 21 + 1 ) ) + 21;
            break;
        case 5:
            strcpy(enemy.enemyType, "chess tower");
            enemy.defense = ( rand () % ( 3 - 2 + 1 ) ) + 2;
            enemy.DMG = ( rand () % ( 43 - 38 + 1 ) ) + 38;
            enemy.HP = ( float ) ( rand () % ( 79 - 56 + 1 ) ) + 56;
            break;
        }
        break;
    case 3:
        r = rand () % 6;
        switch ( r ) {
        case 0:
            strcpy(enemy.enemyType, "fallen star");
            enemy.defense = ( rand () % ( 4 - 2 + 1 ) ) + 2;
            enemy.DMG = ( rand () % ( 27 - 19 + 1 ) ) + 19;
            enemy.HP = ( float ) ( rand () % ( 14 - 10 + 1 ) ) + 10;
            break;
        case 1:
            strcpy(enemy.enemyType, "undead armor");
            enemy.defense = ( rand () % ( 5 - 4 + 1 ) ) + 4;
            enemy.DMG = ( rand () % ( 26 - 23 + 1 ) ) + 23;
            enemy.HP = ( float ) ( rand () % ( 60 - 57 + 1 ) ) + 57;
            break;
        case 2:
            strcpy(enemy.enemyType, "water mage");
            enemy.defense = ( rand () % ( 4 - 3 + 1 ) ) + 3;
            enemy.DMG = ( rand () % ( 47 - 40 + 1 ) ) + 40;
            enemy.HP = ( float ) ( rand () % ( 73 - 68 + 1 ) ) + 68;
            break;
        case 3:
            strcpy(enemy.enemyType, "corpse");
            enemy.defense = ( rand () % ( 2 - 1 + 1 ) ) + 1;
            enemy.DMG = ( rand () % ( 37 - 26 + 1 ) ) + 26;
            enemy.HP = ( float ) ( rand () % ( 69 - 66 + 1 ) ) + 66;
            break;
        case 4:
            strcpy(enemy.enemyType, "hanged woman");
            enemy.defense = ( rand () % ( 3 - 2 + 1 ) ) + 2;
            enemy.DMG = ( rand () % ( 39 - 28 + 1 ) ) + 28;
            enemy.HP = ( float ) ( rand () % ( 44 - 40 + 1 ) ) + 40;
            break;
        case 5:
            strcpy(enemy.enemyType, "lightning core");
            enemy.defense = ( rand () % ( 3 - 1 + 1 ) ) + 1;
            enemy.DMG = ( rand () % ( 68 - 64 + 1 ) ) + 64;
            enemy.HP = ( float ) ( rand () % ( 23 - 20 + 1 ) ) + 20;
            break;
        }
        break;
    }
    return enemy;
}

enemyUser spawnBoss(int stage, int difficulty)
{
    enemyUser boss;
    boss.isBoss = true;
    int r = 0;
    switch ( difficulty ) {
    case 1:
        boss.DMGmultiplier = 0.9;
        break;
    case 2:
        boss.DMGmultiplier = 1.0;
        break;
    case 3:
        boss.DMGmultiplier = 1.2;
        break;
    case 4:
        boss.DMGmultiplier = 1.5;
        break;
    }

    switch ( stage ) {
    case 1:
        r = rand() % 3;
        switch ( r ) {
        case 0:
            strcpy(boss.enemyType, "Elif the big colossus");
            boss.defense = ( rand () % ( 5 - 2 + 1 ) ) + 2;;
            boss.DMG = ( rand () % ( 53 - 48 + 1 ) ) + 48;
            boss.HP = ( float ) ( rand () % ( 90 - 87 + 1 ) ) + 87;
            break;
        case 1:
            strcpy(boss.enemyType, "Phantasmal Seeker");
            boss.defense = ( rand () % ( 3 - 2 + 1 ) ) + 2;
            boss.DMG = ( rand () % ( 51 - 47 + 1 ) ) + 47;
            boss.HP = ( float ) ( rand () % ( 113 - 110 + 1 ) ) + 110;
            break;
        case 2:
            strcpy(boss.enemyType, "Anxiety");
            boss.defense = ( rand () % ( 5 - 3 + 1 ) ) + 3;
            boss.DMG = ( rand () % ( 50 - 46 + 1 ) ) + 46;
            boss.HP = ( float ) ( rand () % ( 105 - 95 + 1 ) ) + 95;
            break;
        }
        break;
    case 2:
        r = rand() % 3;
        switch ( r ) {
        case 0:
            strcpy(boss.enemyType, "Enchanted Runic Dress");
            boss.defense = ( rand () % ( 5 - 4 + 1 ) ) + 4;
            boss.DMG = ( rand () % ( 59 - 43 + 1 ) ) + 43;
            boss.HP = ( float ) ( rand () % ( 116 - 110 + 1 ) ) + 110;
            break;
        case 1:
            strcpy(boss.enemyType, "Bullet Hell");
            boss.defense = ( rand () % ( 5 - 4 + 1 ) ) + 4;
            boss.DMG = ( rand () % ( 53 - 46 + 1 ) ) + 46;
            boss.HP = ( float ) ( rand () % ( 120 - 100 + 1 ) ) + 100;
            break;
        case 2:
            strcpy(boss.enemyType, "Kenopsia");
            boss.defense = ( rand () % ( 6 - 4 + 1 ) ) + 4;
            boss.DMG = ( rand () % ( 56 - 49 + 1 ) ) + 49;
            boss.HP = ( float ) ( rand () % ( 107 - 100 + 1 ) ) + 100;
            break;
        }
        break;
    case 3:
        strcpy(boss.enemyType, "The Powerful");
        boss.defense = ( rand () % ( 7 - 6 + 1 ) ) + 6;
        boss.DMG = ( rand () % ( 59 - 57 + 1 ) ) + 57;
        boss.HP = ( float ) ( rand () % ( 175 - 160 + 1 ) ) + 160;
        break;
    }
    return boss;
}

int selectDifficulty()
{
    int difficulty = 0;
    do {
        printf ( "Select game difficulty:\n" );
        printf ( "1- easy modo: friendly gamemode for the most novices\n" );
        printf ( "2- normal mode: standar game experience\n" );
        printf ( "3- hard mode: challenging game, for most experienced\n" );
        printf ( "4- Lunatic mode: don't even try it\n" );
        printf ( "0- Return\n" );
        scanf ( "%d", &difficulty );
        if ( difficulty == 4 ) {
            system("cls");
            printf ( "You are about to play on the highest difficulty. Enemies will deal +x1.50 DMG than usual\n" );
            printf ( "Dodgerolls and blocks will have more chance of fail. Some things could be unbalanced. are you sure you want to continue?\n" );
            printf ( "1-Yes 0-No\n" );
            scanf ( "%d", &difficulty );
            if ( difficulty == 1 ) {
                difficulty = 4;
            } else {
                    difficulty = 5;
                }
        }
        system("cls");
    } while ( difficulty < 0 || difficulty > 4 );
    return difficulty;
}

void showBasicPlayerStats(playerUser player)
{
    printf ( "Current status:\n" );
    if ( player.HP < 50.0 ) {
        printf ( "HP: %.2f | !!! |\n", player.HP );
    } else {
            printf ( "HP: %.2f\n", player.HP );
        }
    printf ( "DEF: %d\n", player.defense );
    printf ( "Score: %d\n", player.score );
    //showPlayerTraits(player.traits, player.amountTraits);
}

void showAllStats(playerUser player)
{
    printf ( "'%s' Stats:\n", player.nickname );
    printf ( "Final hp: %.2f\n", player.HP );
    printf ( "Final hpMultiplier: x%.1f\n", player.hpMultiplier );
    printf ( "Healing used: %d\n", player.healingUsed );
    printf ( "Final DMG multiplier: %.1f\n", player.DMG );
    printf ( "Total DMG dealed: %.2f\n", player.DMGdealed );
    printf ( "Total DMG taken: %.2f\n", player.DMGtaken );
    printf ( "Final DEF: %d\n", player.defense );
    printf ( "Final Luck: x%.1f\n", player.luck );
    showHands(player.hands);
    printf ( "Final Inventory: %d items\n", player.amountItems );
    showPlayerInventory(player.inventory, player.amountItems);
    printf ( "--------------------------------\n" );
    //showPlayerTraits(player.traits, player.amountTraits);
    printf ( "Difficulty: ");
    switch ( player.difficulty ) {
    case 1:
        printf ( "'easy modo'\n" );
        break;
    case 2:
        printf ( "'normal mode'\n" );
        break;
    case 3:
        printf ( "'hard mode'\n" );
        break;
    case 4:
        printf ( "'Lunatic mode'\n" );
        break;
    }
    printf ( "Final Score: %d\n", player.score );
    printf ( "Killed by: %s\n", player.killedBy );
    printf ( "Stage %d, room %d\n", player.stage, player.room );
}

bool dodgeroll(float dodgerollChance, float luck, int difficulty)
{
    bool dodgeSuccess = false;
    float pool = (float) rand() / ((float) 100);
    float difficultyDebuff = convertDifValueToMultiplier(difficulty);
    luck = validLuckLimit(luck);
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
    luck = validLuckLimit(luck);
    weaponBlockChance = ( float ) (( weaponBlockChance * luck ) + weaponBlockChance ) * difficultyDebuff;
    pool = rand () % 100;
    if ( pool < weaponBlockChance ) {
        dodgeSuccess = true;
    }
    return dodgeSuccess;
}

bool willDodgeroll()
{
    int confirm = 0;
    bool will = false;
    do {
        printf ( "are you sure you want to dodgeroll? 1-yes 0-No\n" );
        scanf ( "%d", &confirm );
    } while ( confirm != 1 && confirm != 0 );
    if ( confirm == 1 ) {
        will = true;
    }
    return will;
}

bool willBlock()
{
    int confirm = 0;
    bool will = false;
    do {
        printf ( "are you sure you want to block? 1-yes 0-No\n" );
        scanf ( "%d", &confirm );
    } while ( confirm != 1 && confirm != 0 );
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

/*void showPlayerTraits(traitUser traits[], int total)
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
}*/

void showPlayerInventory(itemUser inventory[], int total)
{
    if ( total != 0 ) {
        for ( int i = 0; i < total; i++ ) {
            if ( !inventory[i].itemIsDiscard ) {
                showItem(inventory[i]);
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
    weapon.canBeDiscard = true;
    weapon.weaponDMG = ( rand () % ( 13 - 10 + 1) ) + 10;
    weapon.blockChance = ( rand () % ( 37 - 28 + 1) ) + 28;
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
    item.canBeDiscard = true;
    item.buffAdquired = false;
    item.DMGmultiplierBonus = 0;
    item.HPmultiplierBonus = 0;
    item.blockChance = 0;
    item.defenseBonus = 0;
    item.luckBonus = 0;
    item.scoreBonus = 0;
    item.weaponDMG = 0;
    item.lifeHealPoints = 0;

    int r = rand() % 10;
    if ( r < 5 ) {
        r = rand() % 10;
        if ( r <= 6 ) {
            strcpy(item.name,"AverageHealingPotion");
            item.lifeHealPoints = ( rand () % ( 40 - 25 + 1 ) ) + 25;
        } else if ( r <= 9 ) {
                strcpy(item.name,"GreaterHealingPotion");
                item.lifeHealPoints = ( rand () % ( 60 - 40 + 1 ) ) + 40;
            } else {
                    strcpy(item.name,"SuperHealingPotion");
                    item.lifeHealPoints = ( rand () % ( 100 - 83 + 1 ) ) + 83;
                }
        return item;
    } else {
            item = itemPool();
        }
    return item;
}

bool openChest()
{
    bool willOpen = false;
    int confirm = 0;
    printf ( "Will you open the chest? 1-Yes 0-No\n" );
    scanf ( "%d", &confirm );
    if ( confirm == 1 ) {
        willOpen = true;
    }
    return willOpen;
}

itemUser itemPool()
{
    itemUser item;
    item.isWeapon= false;
    item.blockChance = 0;
    item.weaponDMG = 0;
    item.DMGmultiplierBonus = 0;
    item.isItem = true;
    item.lifeHealPoints = 0;
    item.luckBonus = 0;
    item.defenseBonus = 0;
    item.scoreBonus = 0;
    item.HPmultiplierBonus = 0;
    item.itemIsDiscard = false;
    item.canBeDiscard = true;
    item.buffAdquired = false;
    int r = rand() % 4;
    switch ( r ) {
    case 1: //rings & others
        r = rand() % 4;
        if ( r == 0 ) {
            strcpy(item.name,"Lucky Ring");
            item.luckBonus = 0.1;
        }
        if ( r == 1 ) {
            strcpy(item.name,"Ring of Resistance");
            item.defenseBonus = 1;
            item.HPmultiplierBonus = 0.1;
        }
        if ( r == 2 ) {
            strcpy(item.name,"Unknown Ring");
            item.luckBonus = -0.1;
            item.HPmultiplierBonus = -0.1;
        }
        if ( r == 3 ) {
            strcpy(item.name,"Revenge Charm");
            item.defenseBonus = -1;
            item.HPmultiplierBonus = 0.2;
            item.DMGmultiplierBonus = 0.1;
        }
        break;
    case 2: //gloves
        r = rand() % 3;
        if ( r == 0 ) {
            strcpy(item.name,"Nasty Gloves");
            item.luckBonus = -0.2;
            item.DMGmultiplierBonus = -0.1;
        }
        if ( r == 1 ) {
            strcpy(item.name,"Defensive Gloves");
            item.defenseBonus = 1;
        }
        if ( r == 2 ) {
            strcpy(item.name,"Cursed Gloves");
            item.luckBonus = -0.1;
            item.canBeDiscard = false;
            item.DMGmultiplierBonus = -0.1;
        }
        break;
    case 3:    //boots
        r = rand() % 4;
        if ( r == 0 ) {
            strcpy(item.name,"Sigile Boots");
            item.luckBonus = 0.1;
            item.DMGmultiplierBonus = 0.1;
        }
        if ( r == 1 ) {
            strcpy(item.name,"Horrible Boots");
            item.defenseBonus = -1;
            item.luckBonus = 0.1;
            item.DMGmultiplierBonus = -0.3;
        }
        if ( r == 2 ) {
            strcpy(item.name,"Mythical Boots");
            item.defenseBonus = 2;
            item.scoreBonus = 250;
            item.HPmultiplierBonus = 0.2;
            item.DMGmultiplierBonus = 0.2;
        }
        if ( r == 3 ) {
            strcpy(item.name,"Rainbow Boots");
            item.DMGmultiplierBonus = 0.2;
            item.defenseBonus = 1;
        }
        break;
    default:    //Score items
        r = rand() % 4;
        if ( r == 0 ) {
            strcpy(item.name,"Strange Orb");
            item.scoreBonus = 400;
        }
        if ( r == 1 ) {
            strcpy(item.name,"Supreme Orb");
            item.scoreBonus = 700;
        }
        if ( r == 2 ) {
            strcpy(item.name,"Mini Monolith");
            item.scoreBonus = 500;
        }
        if ( r == 3 ) {
            strcpy(item.name,"???");
            item.scoreBonus = 2 * (( rand () % ( 600 - 500 + 1 ) ) + 500 );
        }
        break;
    }
    return item;
}

itemUser generateWeapon()
{
    itemUser weapon;
    weapon.isWeapon = true;
    weapon.blockChance = 0;
    weapon.weaponDMG = 0;
    weapon.isItem = false;
    weapon.lifeHealPoints = 0;
    weapon.HPmultiplierBonus = 0;
    weapon.luckBonus = 0;
    weapon.defenseBonus = 0;
    weapon.scoreBonus = 0;
    weapon.buffAdquired = false;
    weapon.itemIsDiscard = false;
    weapon.canBeDiscard = true;
    int r = rand() % 3;
    switch ( r ) {
    case 1: //daggers
        r = rand() % 3;
        if ( r == 0 ) {
            strcpy(weapon.name,"Advanced Dagger");
            weapon.blockChance = ( rand () % ( 65 - 50 + 1 ) ) + 50;
            weapon.weaponDMG = ( rand () % ( 50 - 40 + 1 ) ) + 40;
        }
        if ( r == 1 ) {
            strcpy(weapon.name,"Broken Dagger");
            weapon.blockChance = ( rand () % ( 20 - 10 + 1 ) ) + 10;
            weapon.weaponDMG = ( rand () % ( 25 - 20 + 1 ) ) + 20;
        }
        if ( r == 2 ) {
            strcpy(weapon.name,"Average Dagger");
            weapon.blockChance = ( rand () % ( 50 - 40 + 1 ) ) + 40;
            weapon.weaponDMG = ( rand () % ( 55 - 50 + 1 ) ) + 50;
        }
        break;
    case 2: //swords & others
        r = rand() % 102;
        if ( r >= 0 && r <= 20 ) {
            strcpy(weapon.name,"Diamond Sword");
            weapon.blockChance = ( rand () % ( 70 - 68 + 1 ) ) + 68;
            weapon.weaponDMG = ( rand () % ( 58 - 55+ 1 ) ) + 55;
        }
        if ( r >= 21 && r <= 56 ) {
            strcpy(weapon.name,"Heavy Sword");
            weapon.blockChance = ( rand () % ( 43 - 30 + 1 ) ) + 30;
            weapon.weaponDMG = ( rand () % ( 58 - 55 + 1 ) ) + 55;
        }
        if ( r >= 57 && r <= 99 ) {
            strcpy(weapon.name,"Origami Sword");
            weapon.blockChance = ( rand () % ( 28 - 25 + 1 ) ) + 25;
            weapon.weaponDMG = ( rand () % ( 35 - 30 + 1 ) ) + 30;
        }
        if ( r == 100 ) {
            strcpy(weapon.name,"Faka");
            weapon.blockChance = ( rand () % ( 77 - 70 + 1 ) ) + 70;
            weapon.weaponDMG = ( rand () % ( 90 - 84 + 1 ) ) + 84;
        }
        if ( r == 101 ) {
            strcpy(weapon.name,"Developer Weapon");
            weapon.blockChance = ( rand () % ( 95 - 93 + 1 ) ) + 93;
            weapon.weaponDMG = ( rand () % ( 95 - 93 + 1 ) ) + 93;
        }
        break;
    default: //ranged
        r = rand() % 101;
        if ( r >= 0 && r <= 30 ) {
            strcpy(weapon.name,"Wodden Bow");
            weapon.blockChance = ( rand () % ( 15 - 7 + 1 ) ) + 7;
            weapon.weaponDMG = ( rand () % ( 18 - 15 + 1 ) ) + 15;
        }
        if ( r >= 31 && r <= 60 ) {
            strcpy(weapon.name,"CrossBow");
            weapon.blockChance = ( rand () % ( 30 - 28 + 1 ) ) + 28;
            weapon.weaponDMG = ( rand () % ( 45 - 36 + 1 ) ) + 36;
        }
        if ( r >= 61 && r <= 85 ) {
            strcpy(weapon.name,"Unexpected Bow");
            weapon.blockChance = ( rand () % ( 80 - 20 + 1 ) ) + 20;
            weapon.weaponDMG = ( rand () % ( 80 - 20 + 1 ) ) + 20;
        }
        if ( r >= 86 && r <= 99 ) {
            strcpy(weapon.name,"Lead Bow");
            weapon.blockChance = ( rand () % ( 65 - 46 + 1 ) ) + 46;
            weapon.weaponDMG = ( rand () % ( 61 - 52 + 1 ) ) + 52;
        }
        if ( r == 100 ) {
            strcpy(weapon.name,"Sniper");
            weapon.blockChance = ( rand () % ( 70 - 61 + 1 ) ) + 61;
            weapon.weaponDMG = ( rand () % ( 91 - 87 + 1 ) ) + 87;
        }
        break;
    }
    return weapon;
}

int doAction()
{
    int input = 0;
    do {
        printf ( "1- Attack\n" );
        printf ( "2- block next attack\n" );
        printf ( "3- DodgeRoll\n" );
        printf ( "4- Check Inventory\n" );
        printf ( "5- Check and use healing\n" );
        printf ( "0- Do nothing\n" );
        printf ( "Answer..." );
        scanf ( "%d", &input );
        if ( input < 0 || input > 5 ) {
            system("cls");
        }
    } while ( input > 5 || input < 0 );
    return input;
}

void showHands(itemUser weapon)
{
    printf ( "In hands: " );
    printf ( "(Weapon) '%s'\n", weapon.name );
    printf ( "DMG: %d\n", weapon.weaponDMG );
    printf ( "Block chance: %d\n", weapon.blockChance );
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
            printCredits();
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
            printHistory();
            break;
        case 3:
            system("cls");
            printHiScore();
            break;
        }
        system("cls");
    } while ( input != 0 );
}

void newRun()
{
    bool willOpen = false;
    bool haveHealing = false;   //indica si el jugador tiene algo para curarse
    int action = 0;
    int random = 0;
    float damage = 0;   //va a recibir el daño hecho tanto por parte del jugador como del enemigo
    bool block = false, dodge = false;  //indica si el jugador va a esquivar el ataque o bloquearlo
    bool success = false;   //posibilidad de bloquear o esquivar el ataque
    itemUser item;
    enemyUser enemy;
    playerUser player;
    player.HP = 100.0;
    player.defense = 0;
    player.DMG = 1.0;
    player.DMGdealed = 0;
    player.DMGtaken = 0;
    player.healingUsed = 0;
    player.hpMultiplier = 1.0;
    player.luck = 1.0;
    player.amountItems = 0;
    player.score = 0;
    player.stage = 0;
    player.room = 0;
    strcpy(player.killedBy,"Nothing");
    player.difficulty = selectDifficulty();
    //player.amountTraits = selectTraits(player.traits, player.amountTraits);
    player.hands = giveBasicWeapon();
    showHands(player.hands);

    for ( int i = 0; i < maxStages; i++ ) {
        player.stage = i + 1;
        for ( int j = 0; j < maxRooms; j++ ) {
            player.room = j + 1;
            printCurrentLocation(player.stage, player.room);
            enemy = spawnEnemy(player.stage, player.difficulty);
            printRandomEnemyMessage(enemy.enemyType);
            do {
                showBasicPlayerStats(player);
                showHands(player.hands);
                printf ("\n");
                showEnemyStats(enemy);
                action = doAction();
                switch ( action ) {
                case 1:     //si jugador ataca
                    damage = damageDealedToEnemy(player.hands.weaponDMG, player.DMG, enemy.defense, player.luck, player.difficulty);
                    enemy.HP = calculateHp(enemy.HP, damage);
                    player.DMGdealed = ( float ) player.DMGdealed + damage;
                    printf ( "Damage dealed: %.2f\n", damage );
                    player.score = player.score + ( damage / 2 );
                    system("pause");
                    system("cls");
                    break;
                case 2:     //si jugador bloquea
                    block = willBlock();
                    break;
                case 3:     //si jugador esquiva
                    dodge = willDodgeroll();
                    break;
                case 4:     //si jugador quiere ver inventario
                    if ( player.amountItems != 0 ) {
                        showPlayerInventory(player.inventory, player.amountItems);
                    } else {
                            printf ( "You don't have items\n" );
                        }
                    break;
                case 5:     //si jugador se quiere curar
                    player.amountItems = orderInventory(player.inventory, player.amountItems);
                    haveHealing = healingInInventory(player.inventory, player.amountItems);
                    if ( haveHealing ) {
                        player = checkAndUseHealing(player);
                    } else {
                            printf ( "No potions in inventory\n" );
                            system("pause");
                        }
                    break;
                }
                if ( enemy.HP > 0 ) {   //El enemigo ataca si no está muerto
                    damage = damageDealedToPlayer(player.defense, enemy.DMG, enemy.DMGmultiplier);
                }
                if ( block ) {
                    success = dodgeOrBlockSuccess(dodge, block, player.difficulty, player.luck, player.hands.weaponDMG);
                }
                if ( dodge ) {
                    success = dodgeOrBlockSuccess(dodge, block, player.difficulty, player.luck, player.hands.weaponDMG);
                }
                if ( success && enemy.HP > 0 ) {
                    damage = 0;
                    printf ( "Attack evaded\n" );
                    system("pause");
                    player.score = player.score + 50;
                } else if ( !success && enemy.HP > 0 ) {
                        printf ( "You took %.2f damage\n", damage );
                        player.HP = ( float ) player.HP - damage;
                        player.DMGtaken = ( float ) player.DMGtaken + damage;
                        system("pause");
                    }
                block = false;
                dodge = false;
                success = false;
                willOpen = false;
                haveHealing = false;
            } while ( enemy.HP > 0 && player.HP > 0 );  //hasta matar al enemigo

            if ( player.HP <= 0 ) {             //si jugador muere
                strcpy(player.killedBy,enemy.enemyType);
                break;
            }
            if ( enemy.HP <= 0 ) {
                printf ( "Enemy defeated!\n" );
                player.score = player.score + 100;
                player.HP = healOverTime(player.HP, player.difficulty);
                player.HP = validMaxHealtLimit(player.HP);
                system("pause");
            }
            if ( enemy.HP <= 0 && ( j % 2 == 0 )  ) {
                printRandomChestMessage();
                printf ( "Open it? 1-Yes 0-no\n" );
                scanf ( "%d", &action );
                if ( action == 1 ) {
                    willOpen = true;
                }
            }
            if ( willOpen ) {
                random = rand () % 2;   //genera item o arma
                if ( random == 0 ) {
                    item = generateItem();
                } else {
                        item = generateWeapon();
                    }
            }
            if ( willOpen && item.isItem ) {
                showItem(item);
            }
            if ( item.isWeapon && willOpen ) {
                player.hands = changeWeaponInHands(player.hands, item);
            }
            if ( player.amountItems != inventoryLimit && item.isItem && willOpen ) {    //se agrega item al inventario si aún no se llenó
                player.inventory[player.amountItems] = item;
                player.amountItems++;
                player = getItemsBonus(player);
            } else if ( player.amountItems == inventoryLimit && item.isItem && willOpen ) {     //se consulta en caso de que el inventario esté lleno
                    do {
                        printf ( "1- Discard item from inventory\n" );
                        printf ( "2- Discard item founded\n" );
                        scanf ( "%d", &action );
                        if ( action != 1 && action != 2 ) {
                            system("cls");
                        }
                    } while ( action <= 0 || action >= 3 );
                    if ( action == 1 ) {
                        player.amountItems = discardItemFromInventory(player);
                        player.inventory[player.amountItems] = item;
                        player.amountItems++;
                        player = getItemsBonus(player);
                    }
                }
        }   //hasta completar 10 salas

        if ( player.HP <=  0 ) {
            strcpy(player.killedBy, enemy.enemyType);
            break;
        }
        enemy = spawnBoss(player.stage, player.difficulty);
        printRandomBossMessage(enemy.enemyType);
        do {
            showBasicPlayerStats(player);
            showEnemyStats(enemy);
            showHands(player.hands);
            printf ("\n");
            action = doAction();
            switch ( action ) {
            case 1:     //si jugador ataca
                damage = damageDealedToEnemy(player.hands.weaponDMG, player.DMG, enemy.defense, player.luck, player.difficulty);
                enemy.HP = calculateHp(enemy.HP, damage);
                player.DMGdealed = ( float ) player.DMGdealed + damage;
                printf ( "Damage dealed: %.2f\n", damage );
                player.score = player.score + ( damage / 2 );
                system("pause");
                system("cls");
                break;
            case 2:     //si jugador bloquea
                block = willBlock();
                break;
            case 3:     //si jugador esquiva
                dodge = willDodgeroll();
                break;
            case 4:     //si jugador quiere ver inventario
                if ( player.amountItems != 0 ) {
                        showPlayerInventory(player.inventory, player.amountItems);
                    } else {
                            printf ( "You don't have items\n" );
                        }
                break;
            case 5:     //si jugador se quiere curar
                player.amountItems = orderInventory(player.inventory, player.amountItems);
                haveHealing = healingInInventory(player.inventory, player.amountItems);
                if ( haveHealing ) {
                    player = checkAndUseHealing(player);
                } else {
                        printf ( "No potions in inventory\n" );
                        system("pause");
                    }
                break;
            }
            if ( enemy.HP > 0 ) {   //El boss ataca si no está muerto
                damage = damageDealedToPlayer(player.defense, enemy.DMG, enemy.DMGmultiplier);
            }
            if ( block ) {
                success = dodgeOrBlockSuccess(dodge, block, player.difficulty, player.luck, player.hands.weaponDMG);
            }
            if ( dodge ) {
                success = dodgeOrBlockSuccess(dodge, block, player.difficulty, player.luck, player.hands.weaponDMG);
            }
            if ( success && enemy.HP > 0 ) {
                damage = 0;
                printf ( "Attack evaded\n" );
                system("pause");
                player.score = player.score + 50;
            } else if ( !success && enemy.HP > 0 ) {
                    printf ( "You took %.2f damage\n", damage );
                    player.HP = ( float ) player.HP - damage;
                    player.DMGtaken = ( float ) player.DMGtaken + damage;
                    system("pause");
                }
            block = false;
            dodge = false;
            success = false;
            willOpen = false;
            haveHealing = false;
        } while ( enemy.HP > 0 && player.HP > 0 );  //hasta matar al boss

            if ( player.HP <=  0 ) {
                strcpy(player.killedBy, enemy.enemyType);
                break;
            }
            if ( enemy.HP <= 0 ) {
                printf ( "Boss defeated!\n" );
                player.score = player.score + 700;
                player.HP = ( float ) 10 + healOverTime(player.HP, player.difficulty);
                player.HP = validMaxHealtLimit(player.HP);
                system("pause");
            }
        }   //hasta completar 3 stages

    if ( strcmpi(player.killedBy,"Nothing") == 0 ) {
        printWinMessages(player.difficulty);
    } else {
            printGameOverMessages(player.difficulty);
        }
    player.amountItems = orderInventory(player.inventory, player.amountItems);
    if ( player.amountItems != 0 ) {
        player.score = player.score + returnScoreFromInventory(player.inventory, player.amountItems);
    }
    askNickname(player.nickname);
    showAllStats(player);
    saveRunData(player);
}

float healOverTime(float hpPlayer, int difficulty)
{
    switch ( difficulty ) {
    case 1:
        hpPlayer = hpPlayer + 10;
        break;
    case 2:
        hpPlayer = hpPlayer + 8;
        break;
    case 3:
        hpPlayer = hpPlayer + 7;
        break;
    case 4:
        hpPlayer = hpPlayer + 5;
        break;
    }
    return hpPlayer;
}

bool healingInInventory(itemUser inv[], int totalItems)
{
    bool haveHealing = false;
    for ( int i = 0; i < totalItems; i++ ) {
        if ( inv[i].lifeHealPoints != 0 ) {
            haveHealing = true;
        }
    }
    return haveHealing;
}

playerUser checkAndUseHealing(playerUser player)
{
    int action = 0;
    for ( int i = 0; i < player.amountItems; i++ ) {
        if ( player.inventory[i].isItem && player.inventory[i].lifeHealPoints != 0 ) {
            printf ( "Your health: %.2f\n", player.HP );
            showItem(player.inventory[i]);
            do {
                printf ( "Use healing potion? 1-Yes 0-No\n" );
                scanf ( "%d", &action );
            } while ( action != 1 && action != 0 );
            if ( action == 1 ) {
                player.HP = ( float ) player.HP + returnHealing(player.inventory[i].lifeHealPoints, player.hpMultiplier);
                player.HP = validMaxHealtLimit(player.HP);
                player.healingUsed++;
                player.inventory[i].itemIsDiscard = true;
                action = 0;
            }
            system("cls");
        }
    }
    return player;
}

int returnScoreFromInventory(itemUser inv[], int totalItems)
{
    int scoreCount = 0;
    for ( int i = 0; i < totalItems; i++ ) {
        if ( !inv[i].itemIsDiscard && inv[i].scoreBonus != 0 ) {
            scoreCount = scoreCount + inv[i].scoreBonus;
        }
    }
    return scoreCount;
}

itemUser changeWeaponInHands(itemUser hands, itemUser newWeapon)
{
    int action = 0;
    printf ( "Change weapon? 1-Yes 0-No\n" );
    printf ( "Your weapon:\n" );
    showHands(hands);
    printf ( "Weapon founded:\n" );
    showWeapon(newWeapon);
    scanf ( "%d", &action );
    if ( action == 1 ) {
        hands = newWeapon;
        printf ( "Weapon changed\n" );
        system("pause");
        system("cls");
    }
    return hands;
}

playerUser getItemsBonus(playerUser player)
{
    for ( int i = 0; i < player.amountItems; i++ ) {
        if ( !player.inventory[i].buffAdquired && !player.inventory[i].itemIsDiscard ) {
            player.defense = player.defense + player.inventory[i].defenseBonus;
            player.hpMultiplier = ( float ) player.hpMultiplier + player.inventory[i].lifeHealPoints;
            player.DMG = ( float ) player.DMG + player.inventory[i].DMGmultiplierBonus;
            player.luck = ( float ) player.luck + player.inventory[i].luckBonus;
            player.inventory[i].buffAdquired = true;
        } else if ( player.inventory[i].buffAdquired && player.inventory[i].itemIsDiscard ) {
                player.defense = player.defense - player.inventory[i].defenseBonus;
                player.hpMultiplier = ( float ) player.hpMultiplier - player.inventory[i].lifeHealPoints;
                player.DMG = ( float ) player.DMG - player.inventory[i].DMGmultiplierBonus;
                player.luck = ( float ) player.luck - player.inventory[i].luckBonus;
                player.inventory[i].buffAdquired = false;
            }
    }
    return player;
}

void showWeapon(itemUser weapon)
{
    printf ( "Name: '%s'\n", weapon.name );
    printf ( "DMG: %d\n", weapon.weaponDMG );
    printf ( "Block chance: %d\n", weapon.blockChance );
}

void showItem(itemUser item)
{
    printf ( "(Utility) '%s'\n", item.name );
    if ( item.defenseBonus != 0 ) {
        printf ( "DEFbonus: %d\n", item.defenseBonus );
    }
    if ( item.lifeHealPoints != 0 ) {
        printf ( "HP heal: %d\n", item.lifeHealPoints );
    }
    if ( item.HPmultiplierBonus != 0 ) {
        printf ( "HP multiplier: %.2f\n", item.HPmultiplierBonus );
    }
    if ( item.luckBonus != 0 ) {
        printf ( "Luck bonus: %.2f\n",  item.luckBonus );
    }
    if ( item.scoreBonus != 0 ) {
        printf ( "Score bonus: %d\n", item.scoreBonus );
    }
    if ( item.DMGmultiplierBonus != 0 ) {
        printf ( "DMG multiplier: %.2f\n\n", item.DMGmultiplierBonus );
    }
}

int discardItemFromInventory(playerUser player)
{
    int input = 0;
    for ( int i = 0; i < player.amountItems; i++ ) {
        if ( !player.inventory[i].itemIsDiscard ) {
            showItem(player.inventory[i]);
            printf ( "Discard this item? 1-Yes\n" );
            scanf ( "%d", &input );
            if ( input == 1 ) {
                player.inventory[i].itemIsDiscard = true;
            }
        }
    }
    player.amountItems = orderInventory(player.inventory, player.amountItems);
    return player.amountItems;
}

int orderInventory(itemUser inv[], int totalItems)
{
    int realTotalItems = 0;     //items con itemIsDiscard = false
    for ( int i = 0; i < totalItems; i++ ) {
        if ( !inv[i].itemIsDiscard ) {
            realTotalItems++;
        }
    }
    for ( int i = 0; totalItems != realTotalItems; i++ ) {  //encuentra y los siguientes items se mueven una posición menos
        if ( inv[i].itemIsDiscard ) {
            do {
                for ( int j = i; j < (totalItems - 1); j++ ) {
                    inv[j] = inv[j+1];
                }
                totalItems--;
            } while ( inv[i].itemIsDiscard && totalItems != realTotalItems );   //en caso de que haya 2 o mas items consecutivos con itemIsDiscard = true
        }
    }
    return realTotalItems;
}

void printCurrentLocation(int stage, int room)
{
    printf ( "Stage %d / Room %d\n", stage, room );
}

void printRandomChestMessage()
{
    int r = rand() % 4;
    switch ( r ) {
    case 0:
        printf ( "Encontraste un cofre\n" );
        break;
    case 1:
        printf ( "Que es esa caja? ah si, un cofre, abrilo si queres\n" );
        break;
    case 2:
        printf ( "Vas a abrir el cofre que encontraste?\n" );
        break;
    case 3:
        printf ( "Habia una vez un cofre\n" );
        break;
    }
}

void printRandomEnemyMessage(char enemyName[])
{
    int r = rand() % 10;
    switch ( r ) {
    case 0:
        printf ( "Avanzas y te encuentras con '%s'\n", enemyName );
        system("pause");
        break;
    case 1:
        printf ( "Mientras mirabas una polilla aparece '%s'\n", enemyName );
        system("pause");
        break;
    case 2:
        printf ( "Te das cuenta que un enemigo te estaba mirando hace 5 minutos. '%s'\n", enemyName );
        system("pause");
        break;
    case 3:
        printf ( "Aparece '%s' y estas pensando en que comer al llegar a casa\n", enemyName );
        system("pause");
        break;
    case 4:
        printf ( "'%s' te dice que si te dejas matar vas a revivir en tu casa con un cofre lleno de diamantes\n", enemyName );
        system("pause");
        break;
    case 5:
        printf ( "Escuchas susurros en tu mente, pero te das la vuelta y era un enemigo. '%s'\n", enemyName );
        system("pause");
        break;
    case 6:
        printf ( "Has muerto...\nMentira, el enemigo es: '%s'\n", enemyName );
        system("pause");
        break;
    case 7:
        printf ( "Buscas algo que te pueda servir y te encontras con '%s'\n", enemyName );
        system("pause");
        break;
    case 8:
        printf ( "Que queres? ah cierto, el enemigo es '%s'\n", enemyName );
        system("pause");
        break;
    case 9:
        printf ( "Alguna vez viste un '%s'? Bueno, ahora si\n", enemyName );
        system("pause");
        break;
    }
}

void printRandomBossMessage(char bossName[])
{
    int r = rand() % 3;
    switch ( r ) {
    case 0:
        printf ( "Te encuentras cara a cara con %s\n", bossName );
        system("pause");
        break;
    case 1:
        printf ( "Mata a %s o muere\n", bossName );
        system("pause");
        break;
    case 2:
        printf ( "La velocidad con la que %s aparece para detenerte deja de que hablar\n", bossName );
        system("pause");
    }
}

void showEnemyStats(enemyUser enemy)
{
    printf ( "'%s'\n", enemy.enemyType );
    printf ( "HP: %.2f\n", enemy.HP );
    printf ( "DMG: %d\n", enemy.DMG );
    printf ( "DEF: %d\n\n", enemy.defense );
}

void printHistory()
{
    playerUser player;
    FILE * historyFile = fopen(scoresFile,"rb");
    if ( historyFile != NULL ) {
        while ( !feof(historyFile)) {
            fread(&player, sizeof(playerUser), 1, historyFile);
            if ( !feof(historyFile)) {
                showAllStats(player);
                printf ( "-----------------------\n" );
                system("pause");
            }
        }
        fclose(historyFile);
    } else {
            error();
        }
}

void printHiScore()
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
        system("pause");
        fclose(historyFile);
    } else {
            error();
        }
}

void printGameOverMessages(int difficulty)
{
    int r = 0;
    printf ( "You died\n" );
    system("pause");
    switch ( difficulty ) {
    case 1:
        r = rand () % 3;
        switch ( r ) {
        case 0:
            printf ( "eeEeH. easy modo?\n" );
            break;
        case 1:
            printf ( "That was easy or not?\n" );
            break;
        case 2:
            printf ( "Did you press 'Do Nothing'?\n" );
            break;
        }
        break;
    case 2:
        r = rand () % 2;
        switch ( r ) {
        case 0:
            printf ( "What a shame, keep trying\n" );
            break;
        case 1:
            printf ( "If you have low chances of blocking with the weapon, remember you can dodgeroll to have more chances\n" );
            break;
        }
        break;
    case 3:
        r = rand () % 2;
        switch ( r ) {
        case 0:
            printf ( "I see you are going to something more challenging\n" );
            break;
        case 1:
            printf ( "Dont stress\n" );
            break;
        }
        break;
    case 4:
        r = rand () % 5;
        switch ( r ) {
        case 0:
            printf ( "Why are you playing in this difficulty? Are you testing this thing or something?\n" );
            break;
        case 1:
            printf ( "Rage. Quit. Go touch grass\n" );
            break;
        case 2:
            printf ( "You really want to beat this game on its harder difficulty\n" );
            break;
        case 3:
            printf ( "I told you this difficulty could be unbalanced, didnt I?" );
            break;
        case 4:
            printf ( "Dont try this again, is too much for you\n" );
            break;
        }
        break;
    }
}

void printWinMessages(int difficulty)
{
    int r = 0;
    printf ( "You Win!!\n" );
    system("pause");
    switch ( difficulty ) {
    case 1:
        r = rand () % 2;
        switch ( r ) {
        case 0:
            printf ( "Good job, you just beat this thing on easy modo\n" );
            break;
        case 1:
            printf ( "Try it on normal\n" );
            break;
        }
        break;
    case 2:
        r = rand () % 2;
        switch ( r ) {
        case 0:
            printf ( "Was it a hard trip?\n" );
            break;
        case 1:
            printf ( "Well done\n" );
            break;
        }
        break;
    case 3:
        r = rand () % 2;
        switch ( r ) {
        case 0:
            printf ( "You are dominating this thing, thats nice\n" );
            break;
        case 1:
            printf ( "Are you satisfied now?\n" );
            break;
        }
        break;
    case 4:
        r = rand () % 4;
        switch ( r ) {
        case 0:
            printf ( "You better be satisfied now\n" );
            break;
        case 1:
            printf ( "Congratulation, you are a LUNATIC player\n" );
            break;
        case 2:
            printf ( "Go and tell your friends what you did... sure if you have them\n" );
            break;
        case 3:
            printf ( "I bet you were really lucky to barely beat this on lunatic mode\n" );
            break;
        }
        break;
    }
    printf ( "Thank you for playing!\n" );
    system("pause");
}

void saveRunData(playerUser player)
{
    FILE * destiny = fopen(scoresFile,"ab");
    if ( destiny != NULL ) {
        fwrite(&player, sizeof(playerUser), 1, destiny);
        fclose(destiny);
        printf ( "--Data saved--\n" );
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
        printf ( "2- Player stats explained\n" );
        printf ( "0- Return\n" );
        scanf ( "%d", &input );
        switch ( input ) {
        case 1:
            system("cls");
            howToPlay();
            break;
        case 2:
            system("cls");
            explainPlayerStats();
            break;
        }
        system("cls");
    } while ( input != 0 );
}

void howToPlay()
{
    printf ( "You start by default with 100HP, with a limit of 200HP and 1 default weapon.\n" );
    system("pause");
    system("cls");
    printf ( "Each enemy has their own health, damage and damage multiplier and defense.\n" );
    system("pause");
    system("cls");
    printf ( "You can attack them or dodge or block their attacks with a chance of failing and taking damage.\n" );
    system("pause");
    system("cls");
    printf ( "You can also heal yourself with items like potions. But if you are going to use one and you don't have any healing you will lose your turn. The same if you go to 'Check Inventory'.\n" );
    system("pause");
    system("cls");
    printf ( "You have 10 slots for items and you can only discard items if you found another item.\n" );
    system("pause");
    system("cls");
}

void explainPlayerStats()
{
    printf ( "Defense: player by default starts with 0, minimal defense is -5 and max is 8, each 1 defense equals to x0.1 damage reduction.\n" );
    system("pause");
    system("cls");
    printf ( "hpMultiplier: by default x1.0, minimal is x0.5 and max is x1.5. This increases or decreases the total hp gained when the player heals.\n" );
    system("pause");
    system("cls");
    printf ( "Luck: x1 by default, minimal x0.7, max x1.3.Buffs or debuffs chances of dodging, critical hit and all that can be afected by it.\n" );
    system("pause");
    system("cls");
    printf ( "Player DMG: by default x1.0, minimal x0.5, max x1.5. This stat multiplies the damage of the weapon the player is using.\n" );
    system("pause");
    system("cls");
    printf ( "Difficulty: this afects chances of dodging, critical hit chances and enemy's stats when they spawn.\n" );
    system("pause");
}

void story()
{
    printf ( "I don't have imagination and this doesn't have story, create you own...\n" );
    system("pause");
}

void printCredits()
{
    printf ( "Project coded in 'Code::Blocks' with C\n" );
    printf ( "Game Designer\nNehuen Artaza\n\n" );
    printf ( "Game Code by\nNehuen Artaza\n\n" );
    system("pause");
}

void error()
{
    printf ( "File doesnt exist or failed at open\n" );
    system("pause");
}

