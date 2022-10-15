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
                al_draw_bitmap(magicImg->img[0], monsterInRange.x, monsterInRange.y, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 4) {
                al_draw_bitmap(magicImg->img[1], monsterInRange.x, monsterInRange.y, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 6) {
                al_draw_bitmap(magicImg->img[2], monsterInRange.x, monsterInRange.y, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 8) {
                al_draw_bitmap(magicImg->img[3], monsterInRange.x, monsterInRange.y, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 10) {
                al_draw_bitmap(magicImg->img[4], monsterInRange.x, monsterInRange.y, 0);
                (*spellCounter)++;
            }
            else if ((*spellCounter) < 12) {
                al_draw_bitmap(magicImg->img[5], monsterInRange.x, monsterInRange.y, 0);
                (*spellCounter)++;
            }
            else {
                al_draw_bitmap(magicImg->img[6], monsterInRange.x, monsterInRange.y, 0);
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