#ifndef DRAW_H
#define DRAW_H

#include "init.h"
#include "combat.h"

void drawSpellAnim (
    int * spellCasted, 
    MagicImg * magicImg, 
    int * spellCounter,
    int spellDistance[],
    Player player,
    Monster monsterInRange
);

// desenha o sprite do monstro na tela, recebe o monstro os srpites e o num da sprite para desenhar
void monsterAnimation (
    Monster monster, 
    int animationNum,
    ALLEGRO_BITMAP * monsterImg
);


typedef struct {
    ALLEGRO_BITMAP * player;
    ALLEGRO_BITMAP * princess;
    ALLEGRO_BITMAP * fairy;

    ALLEGRO_BITMAP * bandit;
    ALLEGRO_BITMAP * wolf;
    ALLEGRO_BITMAP * bear;

    ALLEGRO_BITMAP * troll;
    ALLEGRO_BITMAP * bigRed;

    ALLEGRO_BITMAP * golem;
    
    ALLEGRO_BITMAP * knight;
    ALLEGRO_BITMAP * guardian;
} Sprites;

#endif // DRAW_H