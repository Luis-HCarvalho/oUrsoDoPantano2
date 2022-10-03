#include "init.h"
#include "combat.h"

// monstro segue o player se as cordenadas forem iguais o player leva dano
Monster monsterFollow (Monster monster, Player player) {
    if (monster.x == player.x && monster.y == player.y) {
        player.health -= monster.damage;
    }
    
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