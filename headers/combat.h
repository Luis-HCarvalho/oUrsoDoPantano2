#ifndef COMBAT_H
#define COMBAT_H

enum Spells {
    magicMissile = 1,
    fireball,
    lightning,
    iceSpear,
};

typedef struct {
    ALLEGRO_BITMAP * img1;
    ALLEGRO_BITMAP * img2;
    ALLEGRO_BITMAP * img3;
    ALLEGRO_BITMAP * img4;
    ALLEGRO_BITMAP * img5;
    ALLEGRO_BITMAP * img6;
    ALLEGRO_BITMAP * img7;
    ALLEGRO_BITMAP * img8;
} MagicImg;

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