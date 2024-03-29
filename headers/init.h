#ifndef INIT_H
#define INIT_H

// bibliotecas
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

// tamanho do display
#define displayWidth 1280 // 40x32 tiles
#define displayHeight 640 // 20x32 tiles
#define maxNumMonsters 10

// função para teste de inicializações
void must_init (bool testInit, const char * description);

// limites do mapa
typedef struct {
    int rightBorder;
    int leftBorder;
    int bottomBorder;
    int topBorder;
} Maplimits;

// movimentação do player
typedef struct {
    int up;
    int down;
    int left;
    int right;
} PlayerMov;

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
    int id;
    int attackCooldown;
} Monster;

// inicializa player
void initPlayer (Player * player);

// init Monster
Monster initMonster (int type, int id, Maplimits maplim);

// tipos de monstros
enum monstertype {
    Bandit = 0,
    Wolf,
    Bear,
    Troll,
    BigRed,
    Golem,
    Knight,
    Guardian,
};

typedef struct {
    ALLEGRO_BITMAP * top;
    ALLEGRO_BITMAP * topSide;
    ALLEGRO_BITMAP * topCorner;
    ALLEGRO_BITMAP * wall;
    ALLEGRO_BITMAP * floor1;
    ALLEGRO_BITMAP * floor2;
    ALLEGRO_BITMAP * floor3;
    ALLEGRO_BITMAP * trap;
    ALLEGRO_BITMAP * waterFount;
    ALLEGRO_BITMAP * pillar;
} Tiles;

typedef struct {
    ALLEGRO_BITMAP * Q;
    ALLEGRO_BITMAP * W;
    ALLEGRO_BITMAP * E;
    ALLEGRO_BITMAP * R;
    ALLEGRO_BITMAP * ARROWUP;
    ALLEGRO_BITMAP * ARROWDOWN;
    ALLEGRO_BITMAP * ARROWLEFT;
    ALLEGRO_BITMAP * ARROWRIGHT;
} Keys;


#endif // INIT_H