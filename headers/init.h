#ifndef INIT_H
#define INIT_H

// bibliotecas
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// tamanho do display
#define displayWidth 1280 // 40x32 tiles
#define displayHeight 640 // 20x32 tiles

// função para teste de inicializações
void must_init (bool testInit, const char * description);

// struct jogador
typedef struct {
    int x;  // cordenada x
    int y;  // cordenada y
    int speed; // velocidade de movimentação
    int direc; // direção da movimentação
    int health;
    int level;
    int xp;
    int damage;
    int mana;
} Player;

// struct monstro
typedef struct {
    int x;  // cordenada x
    int y;  // cordenada y
    int direc; // direção da movimentação
    int health;
    int damage;
    int rank;
    int type;
    bool angry;  // se o player entrar no seu compo de visão ele ira atacar
} Monster;

// inicializa player
Player initPlayer (Player player);

// init Monster
Monster initMonster (Monster monster, int x, int y, int rank, int type);

// tipos de monstros
enum monstertype {
    Slime = 0,
    Troll
};

#endif // INIT_H