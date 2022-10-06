#include "init.h"
#include "combat.h"
#include "map.h"

// implementar mana 
// velocidade/ limitar ataque de monstros

// loop principal
void gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    char map[][maxMapWidth],
    Mapsize mapsize,
    Tiles * mapTiles,
    Sprites * playerImg,
    Sprites * trollImg
);

// desenha o sprite do monstro na tela, recebe o monstro os srpites e o num da sprite para desenhar
void monsterAnimation (
    Monster monster, 
    int animationNum,
    Sprites * monsterImg
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
    Sprites playerImg;
    playerImg.img1 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_1.png");
    playerImg.img2 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_2.png");
    playerImg.img3 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_3.png");
    playerImg.img4 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_4.png");

    must_init(playerImg.img1, "playerImg1");
    must_init(playerImg.img2, "playerImg2");
    must_init(playerImg.img3, "playerImg3");
    must_init(playerImg.img4, "playerImg4");

    // carrega os sprites de movimentação de troll
    Sprites trollImg;
    trollImg.img1 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_1.png");
    trollImg.img2 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_2.png");
    trollImg.img3 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_3.png");
    trollImg.img4 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_4.png");

    must_init(trollImg.img1, "trollImg1");
    must_init(trollImg.img2, "trollImg2");
    must_init(trollImg.img3, "trollImg3");
    must_init(trollImg.img4, "trollImg4");

    // carrega tiles para o mapa
    Tiles map1Tiles;
    map1Tiles.wall = al_load_bitmap("./assets/tiles/brickWall.png");
    map1Tiles.floor = al_load_bitmap("./assets/tiles/tileTest.png");
    map1Tiles.floor2 = al_load_bitmap("./assets/tiles/tileTest2.png");

    must_init(map1Tiles.wall, "brickWall");
    must_init(map1Tiles.floor, "tile1");
    must_init(map1Tiles.floor2, "tile2");

    // mapa
    char map[maxMapHeight][maxMapWidth];    // matrix para armazenar o mapa
    Mapsize mapsize;
    getMap("./maps/map1.txt", map, &mapsize);  // retorna a posição dos tiles e o tamanho do mapa

    // tipos de evento que reagiremos no programa
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // começa o jogo
    al_start_timer(timer);
    gameMainLoop(
            timer,
            queue,
            font,
            map,
            mapsize,
            &map1Tiles,
            &playerImg,
            &trollImg
    );

    // limpeza de recursos criados durante as inicializações
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_font(font);

    al_destroy_bitmap(playerImg.img1);
    al_destroy_bitmap(playerImg.img2);
    al_destroy_bitmap(playerImg.img3);
    al_destroy_bitmap(playerImg.img4);

    al_destroy_bitmap(trollImg.img1);
    al_destroy_bitmap(trollImg.img2);
    al_destroy_bitmap(trollImg.img3);
    al_destroy_bitmap(trollImg.img4);

    return 0;
}

// loop principal de execução do programa
void gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    char map[][maxMapWidth],
    Mapsize mapsize,
    Tiles * mapTiles,
    Sprites * playerImg,
    Sprites * trollImg
) {
    
    ALLEGRO_EVENT event;
    
    // animação do player e monstros
    int animationTimer = 0;

    // player
    Player player;
    initPlayer(&player);

    // trolls
    Monster troll;
    initMonster(&troll, 100, 100, 5, Troll, 0);

    Monster troll2;
    initMonster(&troll2, 300, 300, 5, Troll, 1);

    // o monstro esta no range de combate do player
    Monster monsterInRange;

    // variáveis para o loop principal
    bool done = false;
    bool redraw = true;
    bool combatRange = false;
    bool spell = false;

    // limites do mapa
    int leftBorder = (displayWidth -  mapsize.width * sizeTile) / 2;
    int rightBorder = displayWidth - leftBorder - 32;
    int topBorder = (mapsize.wall * 32 - 22)+ (displayHeight -  mapsize.height * sizeTile) / 2; //limite do chao 
    int bottomBorder = displayHeight - ((displayHeight -  mapsize.height * sizeTile) / 2) - 36;

    while (!done) {
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_wait_for_event(queue, &event);

        switch(event.type) {
            // logica do jogo
            case ALLEGRO_EVENT_TIMER:
                if (combatRange = monsterAngry(&troll, player)) {
                    monsterInRange = troll;
                }
                else if (combatRange = monsterAngry(&troll2, player)) {
                    monsterInRange = troll2;
                }
                else {
                    // quando um monstro morre e não há outro no range essa instrução garante que a barra de vida de monstros desapareça
                    monsterInRange.angry = false;
                }

                monsterFollow(&troll, &player);
                monsterFollow(&troll2, &player);

                redraw = true;
                break;

            // movimentação continua
            case ALLEGRO_EVENT_KEY_CHAR:
                if (event.keyboard.repeat) {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_UP:
                            if (player.y > topBorder) {
                                player.y -= player.speed;
                            }
                            break;
                        case ALLEGRO_KEY_DOWN:
                            if (player.y < bottomBorder) {
                                player.y += player.speed;
                            }
                            break;
                        case ALLEGRO_KEY_LEFT:
                            if (player.x > leftBorder) {
                                player.x -= player.speed;
                                player.direc = 1;
                            }
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            if (player.x < rightBorder) {
                                player.x += player.speed;
                                player.direc = 0;
                            }
                            break;
                    }
                }
            // movimentação por tecla pressionada
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        if (player.y > topBorder) {
                            player.y  -= player.speed;
                        }
                        break;
                    case ALLEGRO_KEY_DOWN:
                        if (player.y < bottomBorder) {
                            player.y += player.speed;
                        }
                        break;
                    case ALLEGRO_KEY_LEFT:
                        if (player.x > leftBorder) {
                            player.x -= player.speed;
                            player.direc = 1;
                        }
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        if (player.x < rightBorder) {
                            player.x += player.speed;
                            player.direc = 0;
                        }
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
                                // determina em qual monstro vai o ataque
                                case 0:
                                    castSpell(&troll, &player);
                                    break;
                                case 1:
                                    castSpell(&troll2, &player);
                                    break;

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
                    // desenha os tiles do mapa centralizados
                    if (map[i][j] == 'w') {
                        al_draw_bitmap(mapTiles->wall, ((displayWidth -  mapsize.width * sizeTile) / 2) + (j * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + (i * sizeTile), 0);
                    }
                    else if (map[i][j] == 't') {
                        al_draw_bitmap(mapTiles->floor, ((displayWidth -  mapsize.width * sizeTile) / 2) + (j * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + (i * sizeTile), 0);
                    }
                }
            }

            if (spell) {
                al_draw_line(player.x + 16, player.y + 16, monsterInRange.x + 16, monsterInRange.y + 16, al_map_rgb_f(255, 255, 255), 2);
                spell = false;
            }

            // desenha a sprite player e monstros
            if (animationTimer < 10) {
                al_draw_bitmap(playerImg->img1, player.x, player.y, player.direc);
                
                monsterAnimation(troll, 1, trollImg);
                monsterAnimation(troll2, 1, trollImg);

                animationTimer++;
            }
            else if (animationTimer < 20) {
                al_draw_bitmap(playerImg->img2, player.x, player.y, player.direc);

                monsterAnimation(troll, 2, trollImg);
                monsterAnimation(troll2, 2, trollImg);

                animationTimer++;
            }
            else if (animationTimer < 30) {
                al_draw_bitmap(playerImg->img3, player.x, player.y, player.direc);

                monsterAnimation(troll, 3, trollImg);
                monsterAnimation(troll2, 3, trollImg);

                animationTimer++;
            }
            else {
                al_draw_bitmap(playerImg->img4, player.x, player.y, player.direc);

                monsterAnimation(troll, 4, trollImg);
                monsterAnimation(troll2, 4, trollImg);

                animationTimer = 0;   
            }

            // algum monstro esta dentro do combatRange
            if (combatRange) {
                // mensagem que o ataque do player esta habilitado
                al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 600, 0, "APERTE X PARA ATACAR");
                
                // barra de vida de monstros
                if (monsterInRange.angry) {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1100, 5, 0, "VIDA %d", monsterInRange.health);
                    al_draw_filled_rectangle(1100, 20, monsterInRange.health + 1100, 30, al_map_rgba_f(255, 0, 255, 0.5));
                }
            }

            // hud player
            al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, 0, "LEVEL %d", player.level);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 80, 5, 0, "XP %d", player.xp);

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

// recebe um monstro e o num da sprite para ser desenhada na tela
void monsterAnimation (
    Monster monster,
    int animationNum,
    Sprites * monsterImg
) {

    if (monster.health > 0) {
        switch (animationNum) {
            case 1:
                al_draw_bitmap(monsterImg->img1, monster.x, monster.y, 0);
                break;
            case 2:
                al_draw_bitmap(monsterImg->img2, monster.x, monster.y, 0);
                break;
            case 3:
                al_draw_bitmap(monsterImg->img3, monster.x, monster.y, 0);
                break;
            case 4:
                al_draw_bitmap(monsterImg->img4, monster.x, monster.y, 0);
                break;
        }
    }
}