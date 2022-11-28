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
void monsterFollow (Monster * monster, Player * player) {
    if (monster->angry && monster->health > 0) {
        if (monster->x == player->x && monster->y == player->y) {
            if (monster->attackCooldown == 0) {
                player->health -= monster->damage;
                monster->attackCooldown = 10;
            }
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
    player->xp += monster->rank * 10;

    if (levelUp(player) && player->damage < 55) {
        player->damage += 5;
        player->health += 10;
    }
}

bool levelUp (Player * player) {
    if (player->xp > (player->level * (20 + player->level))) {
        player->level++;
        return true;
    }
    return false;
}