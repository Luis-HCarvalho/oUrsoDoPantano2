#ifndef COMBAT_H
#define COMBAT_H

// monstro segue o player se as cordenadas forem iguais o player leva dano
Monster monsterFollow (Monster monster, Player player);

// dano levado ao encostar em monstros
Player damageTaken (Monster monster, Player player);

#endif // COMBAT_H