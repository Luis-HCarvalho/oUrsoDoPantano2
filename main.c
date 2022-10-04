#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "init.h"
#include "combat.h"

// tamanho mapa (quantidade de tiles)
#define mapWidth 60
#define mapHeight 20
#define sizeTile 32 // tamanho em px dos tiles

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
    ALLEGRO_BITMAP * playerImg1 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_1.png");
    ALLEGRO_BITMAP * playerImg2 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_2.png");
    ALLEGRO_BITMAP * playerImg3 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_3.png");
    ALLEGRO_BITMAP * playerImg4 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_4.png");

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

    // mapa
    int map[mapHeight][mapWidth] = {
        'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
        'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
        'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
        'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
        't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't', 't',
    };

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
    
    // player
    Player player;
    player = initPlayer(player);

    // troll
    Monster troll;
    troll = initMonster(troll, 100, 100, 5);

    // variáveis para o loop principal
    bool done = false;
    bool redraw = true;
    bool combat = false;
    bool attack = false;

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    // loop principal de execução do programa
    while (!done) {
        al_wait_for_event(queue, &event); // aguarda evento acontecer para que o programa continuar

        switch(event.type) {
            // logica do jogo
            case ALLEGRO_EVENT_TIMER:
                if (troll.health <= 0) {
                    player = killMonster(troll, player);
                }
                if (attack) {
                    troll = monsterFollow(troll, player);
                }

                if ((( (player.x - troll.x) < 64 ) && ( (player.x - troll.x) > -64 )) && (((player.y - troll.y) < 64) && ((player.y - troll.y) > -64))) {
                    combat = true; // combate habilitado
                    attack = true;
                }
                else {
                    combat = false;
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
                    case ALLEGRO_KEY_X: // nao esta funcionando
                        if (combat) {
                            troll = castSpell(troll, player);

                        }
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        done = true;
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
            // limpa a tela
            al_clear_to_color(al_map_rgb(0, 0, 0));


            // construção do mapa (coloca os tiles no lugar)
            for (int i = 0; i < mapHeight; i++) {
                for (int j = 0; j < mapWidth; j++) {
                    if (map[i][j] == 'w') {
                        al_draw_bitmap(brickWall, (j * sizeTile),  (i * sizeTile), 0);
                    }
                    else if (map[i][j] == 't') {
                        al_draw_bitmap(tile1, (j * sizeTile),  (i * sizeTile), 0);
                    }
                }
            }

            // desenha a sprite do player
            if (player.playerAnim < 10) {
                al_draw_bitmap(playerImg1, player.x, player.y, player.direc);
                al_draw_bitmap(trollImg1, troll.x, troll.y, 0); //troll
                player.playerAnim++;
            }
            else if (player.playerAnim < 20) {
                al_draw_bitmap(playerImg2, player.x, player.y, player.direc);
                al_draw_bitmap(trollImg2, troll.x, troll.y, 0);  //troll
                player.playerAnim++;
            }
            else if (player.playerAnim < 30) {
                al_draw_bitmap(playerImg3, player.x, player.y, player.direc);
                al_draw_bitmap(trollImg3, troll.x, troll.y, 0);  //troll
                player.playerAnim++;
            }
            else {
                al_draw_bitmap(playerImg4, player.x, player.y, player.direc);
                al_draw_bitmap(trollImg4, troll.x, troll.y, 0);  //troll
                player.playerAnim = 0;
                
            }
            if (combat) {
                al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 600, 0, "APERTE X PARA ATACAR");
            }

            if (attack) {
                if (troll.health < 0) {
                    //done = true;
                    troll.health = 50;
                }
                else {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1100, 5, 0, "VIDA %d", troll.health);
                    al_draw_filled_rectangle(1100, 20, troll.health + 1100, 30, al_map_rgba_f(255, 0, 0, 0.5));
                }
            }

            // hud player
            al_draw_textf(font, al_map_rgb(255, 255, 255), 5, 5, 0, "LEVEL %d", player.level);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 80, 5, 0, "XP %d", player.xp);
            
            // se for pego pelo monstro leva dano
            player = damageTaken (troll, player);

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