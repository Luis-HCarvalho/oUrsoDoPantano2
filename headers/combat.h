#ifndef COMBAT_H
#define COMBAT_H

// entrou no campo de visão do monstro
bool monsterAngry (Monster * monster, Player player);

// monstro segue o player se as cordenadas forem iguais o player leva dano
void monsterFollow (Monster * monster, Player * player);

// dano levado ao encostar em monstros
Player damageTaken (Monster monster, Player player);

// matou um monstro
Player killMonster (Monster * monster, Player player);

// lançar magia
void castSpell (Monster * monster, Player player);

#endif // COMBAT_H