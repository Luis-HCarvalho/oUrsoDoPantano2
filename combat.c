#include "init.h"
#include "combat.h"

// recebe ponteiro de um monstro e avalia se ele esta no alcance de combate do player
// se sim o monstro fica bravo e começa a atacar o player; retorna o monstro
bool monsterAngry (Monster  * monster, Player player) {
    if (((player.x - monster->x < 64 ) && (player.x - monster->x > -64)) && ((player.y - monster->y < 64) && (player.y - monster->y > -64))) {
        monster->angry = true;
        return true;
    }
    return false;
}

// monstro segue o player se as cordenadas forem iguais o player leva dano
void monsterFollow (Monster * monster, Player * player, int attackCooldown) {
    if (monster->angry && monster->health > 0) {
        if (monster->x == player->x && monster->y == player->y) {
            if (attackCooldown > 10 && attackCooldown % 10 == 0)
                player->health -= monster->damage;
        }
        else if (monster->x > player->x) {
            monster->x--;
            monster->direc = 1;
        }
        else if (monster->x < player->x) {
            monster->x++;
            monster->direc = 0;
        }
        
        if (monster->y > player->y) {
            monster->y--;
        }
        else if (monster->y < player->y) {
            monster->y++;
        }
    }
}

// lança magia
void castSpell (Monster * monster, Player * player, int spell, int * spellType) {
    if (player->mana > 0) {
        srand(time(NULL));
        int damage = rand() % player->damage + 1;
        
        switch (spell) {
            case magicMissile:
                if (player->mana > 5) {
                    player->mana -= 5;
                    monster->health -= damage;
                    *spellType = magicMissile;
                }
                break;
            case fireball:
                if (player->mana > 10) {
                    player->mana -= 10;
                    monster->health -= (damage + 10);
                    *spellType = fireball;
                }
                break;
            case lightning:
                if (player->mana > 15) {
                    player->mana -= 15;
                    monster->health -= (damage + 15);
                    *spellType = lightning;
                }
                break;
            case iceshard:
                if (player->mana > 15) {
                    player->mana -= 15;
                    monster->health -= (damage + 15);
                    *spellType = iceshard;
                }
                break;
        } 

        if (monster->health <= 0) {
            killMonster(monster, player);
        }
    }
}

// matou um monstro
void killMonster (Monster * monster, Player * player) {
    // monster death
    monster->x = -100;
    monster->y = -100;
    monster->angry = false;

    // xp
    switch (monster->rank) {
        case 1:
            player->xp += 70;
            break;
        case 2:
            player->xp += 40;
            break;
        case 3:
            player->xp += 20;
            break;
        case 4:
            player->xp += 10;
            break;
        case 5:
            player->xp += 5;
            break;
    }

    levelUp(player);
}

void levelUp (Player * player) {

    if (player->xp > (player->level * (20 + player->level))) {
        player->level++;
    }

    // if (player->xp > 260 && player->level == 9) {
    //     player->level = 10;
    //     player->speed = 3;
    //     player->health = 190;
    //     player->damage = 55;
    // }
    // else if (player->xp > 210 && player->level == 8) {
    //     player->level = 9;
    //     player->health = 180;
    //     player->damage = 50;
    // }
    // else if (player->xp > 210 && player->level == 8) {
    //     player->level = 9;
    //     player->health = 180;
    //     player->damage = 50;
    // }
    // else if (player->xp > 210 && player->level == 8) {
    //     player->level = 9;
    //     player->health = 180;
    //     player->damage = 50;
    // }
    // else if (player->xp > 165 && player->level == 7) {
    //     player->level = 8;
    //     player->health = 170;
    //     player->damage = 45;
    // }
    // else if (player->xp > 130 && player->level == 6) {
    //     player->level = 7;
    //     player->health = 160;
    //     player->damage = 40;
    // }
    // else if (player->xp > 100 && player->level == 5) {
    //     player->level = 6;
    //     player->health = 150;
    //     player->damage = 35;
    // }
    // else if (player->xp > 75 && player->level == 4) {
    //     player->level = 5;
    //     player->health = 140;
    //     player->damage = 30;
    // }
    // else if (player->xp > 50 && player->level == 3) {
    //     player->level = 4;
    //     player->health = 130;
    //     player->damage = 25;
    // }
    // else if (player->xp > 30 && player->level == 2) {
    //     player->level = 3;
    //     player->health = 120;
    //     player->damage = 20;
    // }
    // else if (player->xp > 15 && player->level == 1) {
    //     player->level = 2;
    //     player->health = 110;
    //     player->damage = 15;
    // }
}