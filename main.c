#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "init.h"
#include "combat.h"
#include "map.h"

// fazer uma func para draw player 
// fazer uma func para draw monster
// fazer uma func para draw maps

// ataque com evento on keyup
// implementar mana 
// velocidade limitar ataque de monstros

int gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    char map[][maxMapWidth],
    Mapsize mapsize,
    ALLEGRO_BITMAP * tileWall,
    ALLEGRO_BITMAP * tileFloor,
    ALLEGRO_BITMAP * trollImg1,
    ALLEGRO_BITMAP * trollImg2,
    ALLEGRO_BITMAP * trollImg3,
    ALLEGRO_BITMAP * trollImg4,
    ALLEGRO_BITMAP * playerImg1,
    ALLEGRO_BITMAP * playerImg2,
    ALLEGRO_BITMAP * playerImg3,
    ALLEGRO_BITMAP * playerImg4
);

void monsterAnimation (
    Monster monster, 
    int animationNum,
    ALLEGRO_BITMAP * monsterImg1,
    ALLEGRO_BITMAP * monsterImg2,
    ALLEGRO_BITMAP * monsterImg3,
    ALLEGRO_BITMAP * monsterImg4
);

int main () {

    // inicializações 
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "imgageAddon");
    must_init(al_init_primitives_addon(), "primitives");

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY * display = al_create_display(displayWidth, displayHeight);
    must_init(display, "display");

    ALLEGRO_FONT * font = al_create_builtin_font();
    must_init(font, "font");

    // carrega os sprites de movimentação do player
    // matrix criada para possibilitar a mudança dos sprites (test)
    char * playerImgPath[4][50];
    playerImgPath[0][0] = "./assets/characters/Wizard/wizard_idle_walk_1.png";
    playerImgPath[1][0] = "./assets/characters/Wizard/wizard_idle_walk_2.png";
    playerImgPath[2][0] = "./assets/characters/Wizard/wizard_idle_walk_3.png";
    playerImgPath[3][0] = "./assets/characters/Wizard/wizard_idle_walk_4.png";
    ALLEGRO_BITMAP * playerImg1 = al_load_bitmap(playerImgPath[0][0]);
    ALLEGRO_BITMAP * playerImg2 = al_load_bitmap(playerImgPath[1][0]);
    ALLEGRO_BITMAP * playerImg3 = al_load_bitmap(playerImgPath[2][0]);
    ALLEGRO_BITMAP * playerImg4 = al_load_bitmap(playerImgPath[3][0]);

    must_init(playerImg1, "playerImg1");
    must_init(playerImg2, "playerImg2");
    must_init(playerImg3, "playerImg3");
    must_init(playerImg4, "playerImg4");

    // carrega os sprites de movimentação do troll
    ALLEGRO_BITMAP * trollImg1 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_1.png");
    ALLEGRO_BITMAP * trollImg2 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_2.png");
    ALLEGRO_BITMAP * trollImg3 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_3.png");
    ALLEGRO_BITMAP * trollImg4 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_4.png");

    must_init(trollImg1, "trollImg1");
    must_init(trollImg2, "trollImg2");
    must_init(trollImg3, "trollImg3");
    must_init(trollImg4, "trollImg4");

    // carrega tiles para o mapa
    ALLEGRO_BITMAP * tile1 = al_load_bitmap("./assets/tiles/tileTest.png");      // t
    ALLEGRO_BITMAP * tile2 = al_load_bitmap("./assets/tiles/tileTest2.png");     // b
    ALLEGRO_BITMAP * brickWall = al_load_bitmap("./assets/tiles/brickWall.png"); // w

    must_init(tile1, "tile1");
    must_init(tile2, "tile2");
    must_init(brickWall, "brickWall");

    // tipos de evento que reagiremos no programa
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // mapa
    char map[maxMapHeight][maxMapWidth];    // matrix para armazenar o mapa
    Mapsize mapsize;    // tamanho do mapa
    mapsize = getMap("./maps/map1.txt", map, mapsize);  // pega o mapa e retorna o tamanho dele (h/w)

    // mapa 1
    al_start_timer(timer);
    gameMainLoop(
            timer,
            queue,
            font,
            map,
            mapsize,
            brickWall,  // tileWall
            tile1,  // tileFloor
            trollImg1,
            trollImg2,
            trollImg3,
            trollImg4,
            playerImg1,
            playerImg2,
            playerImg3,
            playerImg4
    );

    // limpeza de recursos criados durante as inicializações
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    al_destroy_bitmap(playerImg1);
    al_destroy_bitmap(playerImg2);
    al_destroy_bitmap(playerImg3);
    al_destroy_bitmap(playerImg4);

    al_destroy_bitmap(trollImg1);
    al_destroy_bitmap(trollImg2);
    al_destroy_bitmap(trollImg3);
    al_destroy_bitmap(trollImg4);

    return 0;
}

// loop principal de execução do programa
// return flag para mudar o mapa e monstros
int gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    char map[][maxMapWidth],
    Mapsize mapsize,
    ALLEGRO_BITMAP * tileWall,
    ALLEGRO_BITMAP * tileFloor,
    ALLEGRO_BITMAP * trollImg1,
    ALLEGRO_BITMAP * trollImg2,
    ALLEGRO_BITMAP * trollImg3,
    ALLEGRO_BITMAP * trollImg4,
    ALLEGRO_BITMAP * playerImg1,
    ALLEGRO_BITMAP * playerImg2,
    ALLEGRO_BITMAP * playerImg3,
    ALLEGRO_BITMAP * playerImg4
) {

    ALLEGRO_EVENT event;

    // player
    Player player;
    player = initPlayer(player);

    // trolls
    Monster troll;
    troll = initMonster(troll, 100, 100, 5, Troll, 0);

    Monster troll2;
    troll2 = initMonster(troll2, 300, 300, 5, Troll, 1);

    // variáveis para o loop principal
    bool done = false;
    bool redraw = true;
    bool combatRange = false;
    Monster monsterInRange;  // qual monstro esta no range de combate do player
    bool spell = false;

    // animação do player e monstros
    int animationTimer = 0;

    // monstros >> colocar uma funcçao de criação de monstro 

    while (!done) {

        // limpa a tela
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_wait_for_event(queue, &event); // aguarda evento acontecer para que o programa continuar

        switch(event.type) {
            // logica do jogo
            case ALLEGRO_EVENT_TIMER:
                if (troll.angry && troll.health > 0) {
                    monsterFollow(&troll, &player);
                }

                if (troll2.angry && troll2.health > 0) {
                    monsterFollow(&troll2, &player);
                }

                combatRange = monsterAngry(&troll, player);
                if (combatRange) {
                    monsterInRange = troll;
                }
                combatRange = monsterAngry(&troll2, player);
                if (combatRange) {
                    monsterInRange = troll2;
                }

                redraw = true;
                break;

            // movimentação continua
            case ALLEGRO_EVENT_KEY_CHAR:
                if (event.keyboard.repeat) {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_UP:
                            if (player.y > 42)
                                player.y  -= player.speed;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            player.y += player.speed;
                            break;
                        case ALLEGRO_KEY_LEFT:
                            player.x -= player.speed;
                            player.direc = 1;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            player.x += player.speed;
                            player.direc = 0;
                            break;
                    }
                }
            // movimentação por tecla pressionada
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        if (player.y > 42) {
                            player.y  -= player.speed;
                        }
                        break;
                    case ALLEGRO_KEY_DOWN:
                        player.y += player.speed;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        player.x -= player.speed;
                        player.direc = 1;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        player.x += player.speed;
                        player.direc = 0;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        done = true;
                        break;
                }
                break;

            // magias (ataques do player)
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_X:
                        if (combatRange) {
                            spell = true;
                            switch (monsterInRange.id) {
                                case 0:
                                    castSpell(&troll, player);
                                    break;
                                case 1:
                                    castSpell(&troll2, player);
                                    break;

                            }
                            //castSpell(&monsterInRange, player);
                            if (monsterInRange.health <= 0) {
                                player = killMonster(&monsterInRange, player);
                            }
                        }
                        break;
                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue)) {

            // construção do mapa (coloca os tiles no lugar)
            for (int i = 0; i < mapsize.height; i++) {
                for (int j = 0; j < mapsize.width; j++) {
                    if (map[i][j] == 'w') {
                        al_draw_bitmap(tileWall, (j * sizeTile),  (i * sizeTile), 0);
                    }
                    else if (map[i][j] == 't') {
                        al_draw_bitmap(tileFloor, (j * sizeTile),  (i * sizeTile), 0);
                    }
                }
            }

            if (spell) {
                al_draw_line(player.x + 16, player.y + 16, monsterInRange.x + 16, monsterInRange.y + 16, al_map_rgb_f(255, 255, 255), 2);
                spell = false;
            }

            // desenha a sprite (animação) player e monstros
            if (animationTimer < 10) {
                al_draw_bitmap(playerImg1, player.x, player.y, player.direc);
                
                monsterAnimation(troll, 1, trollImg1, trollImg2, trollImg3, trollImg4);
                monsterAnimation(troll2, 1, trollImg1, trollImg2, trollImg3, trollImg4);
                animationTimer++;
            }
            else if (animationTimer < 20) {
                al_draw_bitmap(playerImg2, player.x, player.y, player.direc);

                monsterAnimation(troll, 2, trollImg1, trollImg2, trollImg3, trollImg4);
                monsterAnimation(troll2, 2, trollImg1, trollImg2, trollImg3, trollImg4);

                animationTimer++;
            }
            else if (animationTimer < 30) {
                al_draw_bitmap(playerImg3, player.x, player.y, player.direc);

                monsterAnimation(troll, 3, trollImg1, trollImg2, trollImg3, trollImg4);
                monsterAnimation(troll2, 3, trollImg1, trollImg2, trollImg3, trollImg4);

                animationTimer++;
            }
            else {
                al_draw_bitmap(playerImg4, player.x, player.y, player.direc);

                monsterAnimation(troll, 4, trollImg1, trollImg2, trollImg3, trollImg4);
                monsterAnimation(troll2, 4, trollImg1, trollImg2, trollImg3, trollImg4);

                animationTimer = 0;   
            }

            if (combatRange) {
                al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 600, 0, "APERTE X PARA ATACAR");
            }

            if (monsterInRange.angry) {
                if (monsterInRange.health < 0) {
                    //done = true;

                    //implementar loop para checar monstros mortos e imple=mentar mecanica de morte
                    monsterInRange.health = 50;
                }
                else {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1100, 5, 0, "VIDA %d", monsterInRange.health);
                    al_draw_filled_rectangle(1100, 20, monsterInRange.health + 1100, 30, al_map_rgba_f(255, 0, 255, 0.5));
                }
            }

            // hud player
            al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, 0, "LEVEL %d", player.level);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 80, 5, 0, "XP %d", player.xp);
            
            // se for pego pelo monstro leva dano
            //player = damageTaken (troll, player);

            // barra de vida
            if (player.health < 0) {
                done = true;
            }
            else {
                al_draw_filled_rectangle(10, 20, player.health, 30, al_map_rgba_f(255, 0, 0, 0.5));
            }

            al_flip_display();

            redraw = false;
        }
    }
}

// recebe um monstro (futuramente mais) e o num da sprite para ser desenhada na tela
void monsterAnimation (
    Monster monster,
    int animationNum,
    ALLEGRO_BITMAP * monsterImg1,
    ALLEGRO_BITMAP * monsterImg2,
    ALLEGRO_BITMAP * monsterImg3,
    ALLEGRO_BITMAP * monsterImg4
) {

    if (monster.health > 0) {
        switch (animationNum) {
            case 1:
                al_draw_bitmap(monsterImg1, monster.x, monster.y, 0);
                break;
            case 2:
                al_draw_bitmap(monsterImg2, monster.x, monster.y, 0);
                break;
            case 3:
                al_draw_bitmap(monsterImg3, monster.x, monster.y, 0);
                break;
            case 4:
                al_draw_bitmap(monsterImg4, monster.x, monster.y, 0);
                break;
        }
    }
}