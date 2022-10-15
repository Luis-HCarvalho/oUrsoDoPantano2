#ifndef COMBAT_H
#define COMBAT_H

#define numMagicImgs 8

enum Spells {
    magicMissile = 1,
    fireball,
    lightning,
    iceshard,
};

typedef struct {
    ALLEGRO_BITMAP * img[numMagicImgs];
} MagicImg;

typedef struct {
    MagicImg spell[4];
} AllMagics;

// entrou no campo de visão do monstro
bool monsterAngry (Monster * monster, Player player);

// monstro segue o player se as cordenadas forem iguais o player leva dano
void monsterFollow (Monster * monster, Player * player, int attackCooldown);

// lançar magia
void castSpell (Monster * monster, Player * player, int spell, int * spellType);

// matou um monstro
void killMonster (Monster * monster, Player * player);

// determina se o player level up
void levelUp (Player * player);

#endif // COMBAT_H