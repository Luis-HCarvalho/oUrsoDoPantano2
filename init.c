#include "init.h"

// função para teste de inicializações
void must_init (bool testInit, const char * description) {
    if (testInit)
        return;
    printf("erro na inicialização de %s\n", description);
    exit(1);
}

// inicializa player
Player initPlayer (Player player) {
    player.x = displayWidth / 2;   // cordenadas iniciais do player
    player.y = displayHeight / 2;  // cordenadas iniciais do player
    player.speed = 2;
    player.direc = 0;
    player.health = 100;
    player.level = 1;
    player.xp = 0;
    player.damage = 10;
    player.mana = 50;

    return player;
}

Monster initMonster (Monster monster, int x, int y, int rank, int type) {
    monster.x = x;  // cordenada x
    monster.y = y;  // cordenada y
    monster.direc = 0;// direção da movimentação
    monster.rank = rank;
    monster.type = type;
    monster.angry = false;
    switch (monster.rank) {
        case 1:     // golem
            monster.health = 200;
            monster.damage = 40;
            break;
        case 2:
            monster.health = 150;
            monster.damage = 20;
            break;
        case 3:
            monster.health = 100;
            monster.damage = 20;
            break;
        case 4:
            monster.health = 80;
            monster.damage = 10;
            break;
        case 5:
            monster.health = 50;
            monster.damage = 5;
            break;
    }
    return monster;
}