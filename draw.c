#include "draw.h"

void drawSpellAnim (
    int * spellCasted, 
    MagicImg * magicImg, 
    int * spellCounter,
    int spellDistance[],
    Player player,
    Monster monsterInRange
) {

    switch (*spellCasted) {
        case magicMissile:
            if ((*spellCounter) < 2) {
                al_draw_bitmap(magicImg->img[0], player.x, player.y, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 4) {
                al_draw_bitmap(magicImg->img[1], (spellDistance[0] * (*spellCounter) + player.x), (spellDistance[1] * (*spellCounter) + player.y), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 6) {
                al_draw_bitmap(magicImg->img[2], (spellDistance[0] * (*spellCounter) + player.x), (spellDistance[1] * (*spellCounter) + player.y), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 8) {
                al_draw_bitmap(magicImg->img[3], (spellDistance[0] * (*spellCounter) + player.x), (spellDistance[1] * (*spellCounter) + player.y), monsterInRange.direc);
                (*spellCounter)++;
            }
            else {
                al_draw_bitmap(magicImg->img[4], monsterInRange.x, monsterInRange.y, monsterInRange.direc);
                (*spellCounter)--;
                *spellCasted = 0;
            }
            break;
        case fireball:
            if ((*spellCounter) < 2) {
                al_draw_bitmap(magicImg->img[0], player.x + 16, player.y + 16, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 4) {
                al_draw_bitmap(magicImg->img[1], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 6) {
                al_draw_bitmap(magicImg->img[2], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 8) {
                al_draw_bitmap(magicImg->img[3], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 10) {
                al_draw_bitmap(magicImg->img[4], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 12) {
                al_draw_bitmap(magicImg->img[5], (spellDistance[0] * (*spellCounter) + player.x +16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 14) {
                al_draw_bitmap(magicImg->img[6], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else {
                al_draw_bitmap(magicImg->img[7], monsterInRange.x + 16, monsterInRange.y + 16, monsterInRange.direc);
                (*spellCounter)--;
                *spellCasted = 0;
            }
            break;
        case lightning:
            if ((*spellCounter) < 2) {
                al_draw_bitmap(magicImg->img[0], monsterInRange.x - 16, monsterInRange.y - 32, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 4) {
                al_draw_bitmap(magicImg->img[1], monsterInRange.x - 16, monsterInRange.y - 32, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 6) {
                al_draw_bitmap(magicImg->img[2], monsterInRange.x - 16, monsterInRange.y - 32, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 8) {
                al_draw_bitmap(magicImg->img[3], monsterInRange.x - 16, monsterInRange.y - 32, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 10) {
                al_draw_bitmap(magicImg->img[4], monsterInRange.x - 16, monsterInRange.y - 32, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 12) {
                al_draw_bitmap(magicImg->img[5], monsterInRange.x - 16, monsterInRange.y - 32, 0);
                (*spellCounter)++;
            }
            else {
                al_draw_bitmap(magicImg->img[6], monsterInRange.x - 16, monsterInRange.y - 32, 0);
                (*spellCounter)--;
                *spellCasted = 0;
            }
            break;
        case iceshard:
            if ((*spellCounter) < 2) {
                al_draw_bitmap(magicImg->img[0], player.x + 16, player.y + 16, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 4) {
                al_draw_bitmap(magicImg->img[1], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 6) {
                al_draw_bitmap(magicImg->img[2], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 8) {
                al_draw_bitmap(magicImg->img[3], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 10) {
                al_draw_bitmap(magicImg->img[4], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 12) {
                al_draw_bitmap(magicImg->img[5], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 14) {
                al_draw_bitmap(magicImg->img[6], (spellDistance[0] * (*spellCounter) + player.x + 16), (spellDistance[1] * (*spellCounter) + player.y + 16), monsterInRange.direc);
                (*spellCounter)++;
            }
            else {
                al_draw_bitmap(magicImg->img[7], monsterInRange.x + 16, monsterInRange.y + 16, monsterInRange.direc);
                (*spellCounter)--;
                *spellCasted = 0;
            }
            break;
    }
}

void monsterAnimation (
    Monster monster,
    int animationNum,
    ALLEGRO_BITMAP * monsterImg
) {
    if (monster.health > 0) {
        switch (animationNum) {
            case 1:
                if (monster.angry) {
                    al_draw_bitmap_region(monsterImg, (32 * 5), 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap_region(monsterImg, 0, 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                break;
            case 2:
                if (monster.angry) {
                    al_draw_bitmap_region(monsterImg, (32 * 6), 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap_region(monsterImg, (32), 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                break;
            case 3:
                if (monster.angry) {
                    al_draw_bitmap_region(monsterImg, (32 * 7), 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap_region(monsterImg, (32 * 2), 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                break;
            case 4:
                if (monster.angry) {
                    al_draw_bitmap_region(monsterImg, (32 * 8), 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap_region(monsterImg, (32 * 3), 0, 32, 32, monster.x, monster.y, monster.direc);
                }
                break;
        }
    }
}