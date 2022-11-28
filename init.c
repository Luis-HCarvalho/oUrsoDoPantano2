#include "init.h"
// função para teste de inicializações
void must_init (bool testInit, const char * description) {
    if (testInit)
        return;
    printf("erro na inicialização de %s\n", description);
    exit(1);
}

// inicializa player
void initPlayer (Player * player) {
    player->x = displayWidth / 2;   // cordenadas iniciais do player
    player->y = displayHeight / 2;  // cordenadas iniciais do player
    player->speed = 2;
    player->direc = 0;
    player->health = 100;
    player->level = 1;
    player->xp = 0;
    player->damage = 10;
    player->mana = 50;
}

Monster initMonster (int type, int id, Maplimits maplim) {
    Monster monster;
    monster.type = type;
    monster.id = id;
    monster.angry = false;
    monster.attackCooldown = 0;
    
    srand(rand() + id + time(NULL));
    monster.x = (rand() % (maplim.rightBorder - maplim.leftBorder)) + maplim.leftBorder;
    monster.y = (rand() % (maplim.bottomBorder - maplim.topBorder)) + maplim.topBorder;
    monster.direc = rand() % 2;  // direção da movimentação

    switch (type) {
        case Bandit:
            monster.rank = 1;
            break;
        case Wolf:
            monster.rank = 1;
            break;
        case Bear:
            monster.rank = 2;
            break;
        case Troll:
            monster.rank = 3;
            break;
        case BigRed:
            monster.rank = 4;
            break;
        case Golem:
            monster.rank = 5;
            break;
        case Knight:
            monster.rank = 6;
            break;
        case Guardian:
            monster.rank = 7;
            break;
    }

    monster.health = monster.rank * 50;
    monster.damage = monster.rank * 10;

    return monster;
}