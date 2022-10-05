#include "init.h"
#include "combat.h"
#include <time.h>

// entrou no campo de visão do monstro
bool monsterAngry (Monster  * monster, Player player) {
    if ((( (player.x - monster->x) < 64 ) && ( (player.x - monster->x) > -64 )) && (((player.y - monster->y) < 64) && ((player.y - monster->y) > -64))) {
        monster->angry = true;
        return true;
    }
    return false;
}

// monstro segue o player se as cordenadas forem iguais o player leva dano
Monster monsterFollow (Monster monster, Player player) {
    if (monster.x > player.x) {
        monster.x--;
    }
    else if (monster.x < player.x) {
        monster.x++;
    }
    
    if (monster.y > player.y) {
        monster.y--;
    }
    else if (monster.y < player.y) {
        monster.y++;
    }
    return monster;
}

// dano levado ao encostar em monstros
Player damageTaken (Monster monster, Player player) {
    if (monster.x == player.x && monster.y == player.y) {
        player.health -= monster.damage;
    }
    return player;
}

// matou um monstro
Player killMonster (Monster monster, Player player) {
    switch (monster.rank) {
        case 1:
            player.xp += 70;
            break;
        case 2:
            player.xp += 40;
            break;
        case 3:
            player.xp += 20;
            break;
        case 4:
            player.xp += 10;
            break;
        case 5:
            player.xp += 5;
            break;
    }

    // level Up
    if (player.xp > 260) {
        player.level = 10;
        player.speed = 3;
        player.health = 280;
        player.damage = 55;
    }
    else if (player.xp > 210) {
        player.level = 9;
        player.health = 260;
        player.damage = 50;
    }
    else if (player.xp > 165) {
        player.level = 8;
        player.health = 240;
        player.damage = 45;
    }
    else if (player.xp > 130) {
        player.level = 7;
        player.health = 220;
        player.damage = 40;
    }
    else if (player.xp > 100) {
        player.level = 6;
        player.health = 200;
        player.damage = 35;
    }
    else if (player.xp > 75) {
        player.level = 5;
        player.health = 180;
        player.damage = 30;
    }
    else if (player.xp > 50) {
        player.level = 4;
        player.health = 160;
        player.damage = 25;
    }
    else if (player.xp > 30) {
        player.level = 3;
        player.health = 140;
        player.damage = 20;
    }
    else if (player.xp > 15) {
        player.level = 2;
        player.health = 120;
        player.damage = 15;
    }

    return player;
}

// lança magia
Monster castSpell (Monster monster, Player player) {
    srand(time(NULL));
    int damage = rand() % player.damage + 1;
    
    monster.health -= damage;

    return monster;
    
}