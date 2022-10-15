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

#endif // DRAW_H