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
    player.playerAnim = 0;
    player.health = 100;
    player.level = 1;
    player.xp = 0;
    player.damage = 10;

    return player;
}