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
    Troll,
    bigRed
};


typedef struct {
    ALLEGRO_BITMAP * idle1;
    ALLEGRO_BITMAP * idle2;
    ALLEGRO_BITMAP * idle3;
    ALLEGRO_BITMAP * idle4;
    ALLEGRO_BITMAP * walk1;
    ALLEGRO_BITMAP * walk2;
    ALLEGRO_BITMAP * walk3;
    ALLEGRO_BITMAP * walk4;
} Sprites;

typedef struct {
    ALLEGRO_BITMAP * wall;
    ALLEGRO_BITMAP * floor;
    ALLEGRO_BITMAP * floor2;
    ALLEGRO_BITMAP * trap;
} Tiles;

#endif // INIT_H