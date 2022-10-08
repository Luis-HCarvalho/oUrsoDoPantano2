#ifndef INIT_H
#define INIT_H

// bibliotecas
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

typedef struct {
    int rightBorder;
    int leftBorder;
    int bottomBorder;
    int topBorder;
} Maplimits;

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
    int type;  // talvez não precise
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
    Slime = 0,
    Troll
};


typedef struct {
    ALLEGRO_BITMAP * img1;
    ALLEGRO_BITMAP * img2;
    ALLEGRO_BITMAP * img3;
    ALLEGRO_BITMAP * img4;
} Sprites;

typedef struct {
    ALLEGRO_BITMAP * wall;
    ALLEGRO_BITMAP * floor;
    ALLEGRO_BITMAP * floor2;
    ALLEGRO_BITMAP * trap;
} Tiles;

#endif // INIT_H