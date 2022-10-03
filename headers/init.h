#ifndef INIT_H
#define INIT_H

// bibliotecas
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// tamanho do display
#define displayWidth 880
#define displayHeight 660

// função para teste de inicializações
void must_init (bool testInit, const char * description);

// struct jogador
typedef struct {
    int x;  // cordenada x
    int y;  // cordenada y
    int speed; // velocidade de movimentação
    int direc; // direção da movimentação
    int playerAnim; // contador para estipular a velocidade da animação (transição entre sprites)
    int health;
    int level;
    int xp;
    int damage;
} Player;

// struct mob
typedef struct {
    int x;  // cordenada x
    int y;  // cordenada y
    int direc; // direção da movimentação
    int health;
    int damage;
} Monster;

// inicializa player
Player initPlayer (Player player);

// init Monster
Monster initMonster (Monster monster, int x, int y, int rank);

#endif // INIT_H