#ifndef COMBAT_H
#define COMBAT_H

// entrou no campo de visão do monstro
bool monsterAngry (Monster * monster, Player player);

// monstro segue o player se as cordenadas forem iguais o player leva dano
void monsterFollow (Monster * monster, Player * player);

// lançar magia
void castSpell (Monster * monster, Player * player);

// matou um monstro
void killMonster (Monster * monster, Player * player);

// determina se o player level up
void levelUp (Player * player);

#endif // COMBAT_H