#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

// tamanho do display
#define displayWidth 880
#define displayHeight 660

// função para teste de inicializações
void must_init (bool testInit, const char * description) {
    if (testInit)
        return;
    printf("erro na inicialização de %s\n", description);
    exit(1);
}

// struct jogador
typedef struct {
    int x;  // cordenada x
    int y;  // cordenada y
    int speed; // velocidade de movimentação
    int direc; // direção da movimentação
    int playerAnim; // contador para estipular a velocidade da animação (transição entre sprites)
} Player;


int main () {
    printf("hello");
    // inicializações 
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "imgageAddon");

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

    // tipos de evento que reagiremos no programa
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    // player
    Player player;
    player.speed = 2;
    player.direc = 0;
    player.playerAnim = 0;
    player.x = displayWidth / 2;   // cordenadas iniciais do player
    player.y = displayHeight / 2;  // cordenadas iniciais do player

    // variáveis para o loop principal
    bool done = false;
    bool redraw = true;

    ALLEGRO_EVENT event;
    al_start_timer(timer);

    // loop principal de execução do programa
    while (!done) {
        al_wait_for_event(queue, &event); // aguarda evento acontecer para que o programa continuar

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                // game logic goes here.
                redraw = true;
                break;

            // movimentação continua
            case ALLEGRO_EVENT_KEY_CHAR:
                if (event.keyboard.repeat) {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_UP:
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

            // desenha a sprite do player
            if (player.playerAnim < 10) {
                al_draw_bitmap(playerImg1, player.x, player.y, player.direc);
                player.playerAnim++;
            }
            else if (player.playerAnim < 20) {
                al_draw_bitmap(playerImg2, player.x, player.y, player.direc);
                player.playerAnim++;
            }
            else if (player.playerAnim < 30) {
                al_draw_bitmap(playerImg3, player.x, player.y, player.direc);
                player.playerAnim++;
            }
            else {
                al_draw_bitmap(playerImg4, player.x, player.y, player.direc);
                player.playerAnim = 0;
                
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

    return 0;
}