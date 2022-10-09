#include "init.h"
#include "combat.h"
#include "map.h"

// add andares para a dungeon
// add criaao de mapas autonoma (gerar txt)

// loop principal
bool gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    int * mapNav,
    int * floorNumber,
    char map[][maxMapWidth],
    Mapsize mapsize,
    Tiles * mapTiles,
    int numMonsters,
    Sprites * playerImg,
    int typeMonsters,
    Sprites * trollImg,
    Sprites * bigRedImg
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

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 40.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY * display = al_create_display(displayWidth, displayHeight);
    must_init(display, "display");

    ALLEGRO_FONT * font = al_create_builtin_font();
    must_init(font, "font");

    // carrega os sprites de movimentação do player
    Sprites playerImg;
    playerImg.idle1 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_1.png");
    playerImg.idle2 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_2.png");
    playerImg.idle3 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_3.png");
    playerImg.idle4 = al_load_bitmap("./assets/characters/Wizard/wizard_idle_walk_4.png");

    // carrega os sprites de movimentação de troll
    Sprites trollImg;
    trollImg.idle1 = al_load_bitmap("./assets/characters/Troll/Troll_Idle_1.png");
    trollImg.idle2 = al_load_bitmap("./assets/characters/Troll/Troll_Idle_2.png");
    trollImg.idle3 = al_load_bitmap("./assets/characters/Troll/Troll_Idle_3.png");
    trollImg.idle4 = al_load_bitmap("./assets/characters/Troll/Troll_Idle_4.png");
    trollImg.walk1 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_1.png");
    trollImg.walk2 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_2.png");
    trollImg.walk3 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_3.png");
    trollImg.walk4 = al_load_bitmap("./assets/characters/Troll/Troll_Walk_4.png");

    Sprites bigRedImg;
    bigRedImg.idle1 = al_load_bitmap("./assets/characters/bigRed/bigRed_idle1.png");
    bigRedImg.idle2 = al_load_bitmap("./assets/characters/bigRed/bigRed_idle2.png");
    bigRedImg.idle3 = al_load_bitmap("./assets/characters/bigRed/bigRed_idle3.png");
    bigRedImg.idle4 = al_load_bitmap("./assets/characters/bigRed/bigRed_idle4.png");
    bigRedImg.walk1 = al_load_bitmap("./assets/characters/bigRed/bigRed_walk1.png");
    bigRedImg.walk2 = al_load_bitmap("./assets/characters/bigRed/bigRed_walk2.png");
    bigRedImg.walk3 = al_load_bitmap("./assets/characters/bigRed/bigRed_walk3.png");
    bigRedImg.walk4 = al_load_bitmap("./assets/characters/bigRed/bigRed_walk4.png");

    // carrega tiles para o mapa
    Tiles mapTiles;
    mapTiles.top = al_load_bitmap("./assets/tiles/wall_top.png");
    mapTiles.topSide = al_load_bitmap("./assets/tiles/wall_top_side.png");
    mapTiles.topCorner = al_load_bitmap("./assets/tiles/wall_top_corner.png");
    mapTiles.wall = al_load_bitmap("./assets/tiles/wall.png");
    mapTiles.floor1 = al_load_bitmap("./assets/tiles/floor_1.png");
    mapTiles.floor2 = al_load_bitmap("./assets/tiles/floor_2.png");
    mapTiles.floor3 = al_load_bitmap("./assets/tiles/floor_3.png");

    // tipos de evento que reagiremos no programa
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // mapa
    char map[maxMapHeight][maxMapWidth];    // matrix para armazenar o mapa
    Mapsize mapsize;
    int mapNav = 0;

    // começa o jogo
    al_start_timer(timer);
    
    int numMonsters = 0;
    int typeMonsters;
    int floorNumber = 0;
    bool gameStatus = true;    // determina se o jogo fecha ou continua rodando
    while (gameStatus) {
        // printf("mapNav: %d\n", mapNav);
        // printf("bigRed: %d\n", bigRed);
        switch (mapNav) {
            case 1:
                getMap("./maps/map1.txt", map, &mapsize);
                numMonsters = 4;
                typeMonsters = bigRed;
                mapNav = 0;
                break;
            case 2:
                getMap("./maps/map2.txt", map, &mapsize);
                numMonsters = 2;
                typeMonsters = Troll;
                mapNav = 0;
                break;
            default:
                // primeiro andar da dungeon
                getMap("./maps/map1.txt", map, &mapsize);
                numMonsters = 0;
                //typeMonsters = Troll;
                mapNav = 0;
                break;
        }
        gameStatus = gameMainLoop(
                timer,
                queue,
                font,
                &mapNav,
                &floorNumber,
                map,
                mapsize,
                &mapTiles,
                numMonsters,
                &playerImg,
                typeMonsters,
                &trollImg,
                &bigRedImg
        );
        floorNumber++;
    }

    // limpeza de recursos criados durante as inicializações
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_font(font);

    al_destroy_bitmap(playerImg.idle1);
    al_destroy_bitmap(playerImg.idle2);
    al_destroy_bitmap(playerImg.idle3);
    al_destroy_bitmap(playerImg.idle4);

    al_destroy_bitmap(trollImg.idle1);
    al_destroy_bitmap(trollImg.idle2);
    al_destroy_bitmap(trollImg.idle3);
    al_destroy_bitmap(trollImg.idle4);
    al_destroy_bitmap(trollImg.walk1);
    al_destroy_bitmap(trollImg.walk2);
    al_destroy_bitmap(trollImg.walk3);
    al_destroy_bitmap(trollImg.walk4);

    al_destroy_bitmap(bigRedImg.idle1);
    al_destroy_bitmap(bigRedImg.idle2);
    al_destroy_bitmap(bigRedImg.idle3);
    al_destroy_bitmap(bigRedImg.idle4);
    al_destroy_bitmap(bigRedImg.walk1);
    al_destroy_bitmap(bigRedImg.walk2);
    al_destroy_bitmap(bigRedImg.walk3);
    al_destroy_bitmap(bigRedImg.walk4);

    al_destroy_bitmap(mapTiles.top);
    al_destroy_bitmap(mapTiles.topSide);
    al_destroy_bitmap(mapTiles.topCorner);
    al_destroy_bitmap(mapTiles.wall);
    al_destroy_bitmap(mapTiles.floor1);
    al_destroy_bitmap(mapTiles.floor2);
    al_destroy_bitmap(mapTiles.floor3);

    return 0;
}

// loop principal de execução do programa
bool gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    int * mapNav,
    int * floorNumber,
    char map[][maxMapWidth],
    Mapsize mapsize,
    Tiles * mapTiles,
    int numMonsters,
    Sprites * playerImg,
    int typeMonsters,
    Sprites * trollImg,
    Sprites * bigRedImg
) {
    
    ALLEGRO_EVENT event;

    // limites do mapa
    Maplimits maplim;
    maplim.leftBorder = (displayWidth -  mapsize.width * sizeTile) / 2;
    maplim.rightBorder = displayWidth - maplim.leftBorder - (sizeTile * 2);
    maplim.topBorder = (mapsize.wall * sizeTile - 22)+ (displayHeight -  mapsize.height * sizeTile) / 2; //limite do chao 
    maplim.bottomBorder = displayHeight - ((displayHeight -  mapsize.height * sizeTile) / 2) - (sizeTile * 3);

    // determina uma ordem aleatória dos tiles de piso no mapa
    int tilesOrder[maxMapHeight * maxMapWidth];
    for (int i = 0; i < mapsize.height * mapsize.width; i++) {
        srand(rand() + i + time(NULL));
        tilesOrder[i] = rand() % 3 + 1;
    }

    // player
    Player player;
    initPlayer(&player);

    PlayerMov mov;
    mov.up = 0;
    mov.down = 0;
    mov.right = 0;
    mov.left = 0;

    // o monstro que esta no range de combate do player
    Monster monsterInRange;

    // init monstros
    Monster monsters[maxNumMonsters];
    for (int i = 0; i < numMonsters; i++) {
        monsters[i] = initMonster(typeMonsters, i, maplim);
    }

    // variáveis para o loop principal
    bool exit = false;
    bool redraw = true;
    bool combatRange = false;
    bool spell = false;
    int animationTimer = 0;    // animação do player e monstros
    int attackCooldown = 0;    // tempo de espera para ataque dos monstros
    int respawnTimer = 0;

    while (!exit && !*mapNav) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_wait_for_event(queue, &event);

        switch(event.type) {
            // logica do jogo
            case ALLEGRO_EVENT_TIMER:

                // mov
                if (mov.up && player.y > maplim.topBorder) {
                    player.y -= player.speed;
                }
                if (mov.down && player.y < maplim.bottomBorder) {
                    player.y += player.speed;
                }
                if (mov.left && player.x > maplim.leftBorder) {
                    player.x -= player.speed;
                    player.direc = 1;
                }
                if (mov.right && player.x < maplim.rightBorder) {
                    player.x += player.speed;
                    player.direc = 0;
                }

                // cooldown ataques dos monstros e recuperação de mana
                if (attackCooldown <= 20){
                    attackCooldown++;
                }
                else {
                    attackCooldown = 0;
                }

                // recuparação de mana
                if (player.mana < 50 && attackCooldown >= 10 && attackCooldown % 10 == 0) {
                    player.mana++;
                }
                
                // determina se um monstro esta dentro do range de combate do player
                for (int i = 0; i < numMonsters; i++) {
                    if ((combatRange = monsterAngry(&monsters[i], player))) {
                        monsterInRange = monsters[i];
                        break;
                    }
                }

                if (!combatRange) {
                    monsterInRange.angry = false;
                }

                // determina se um monstro deve seguir o player
                for (int i = 0; i < numMonsters; i++) {
                    monsterFollow(&monsters[i], &player, attackCooldown);
                }

                // respawn de monstros
                respawnTimer++;
                if (respawnTimer == 200) {
                    respawnTimer = 0;
                    for (int i = 0; i < numMonsters; i++) {
                        if (monsters[i].health <= 0) {
                            monsters[i] = initMonster(monsters[i].type, monsters[i].id, maplim);
                        }
                    }
                }

                // navegação entre mapas
                if (player.x > maplim.rightBorder - 4) {
                    printf("rightB\n");
                    *mapNav = 1;
                }
                else if (player.x < maplim.leftBorder + 4) {
                    *mapNav = 2;
                }
                // else if (player.y > maplim.bottomBorder - 4) {
                //     *mapNav = 1;
                // }

                redraw = true;
                break;

            // movimentação por tecla pressionada
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        mov.up = 1;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        mov.down =  1;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        mov.left = 1;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        mov.right = 1;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        exit = true;
                        break;
                }
                break;

            // magias (ataques do player)
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        mov.up = 0;
                        break;
                    case ALLEGRO_KEY_DOWN:
                        mov.down =  0;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        mov.left = 0;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        mov.right = 0;
                        break;

                    case ALLEGRO_KEY_Q:
                        if (combatRange) {
                            spell = true;

                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &player, magicMissile);
                                    printf("%dvida: %d\n", i,monsters[i].health);
                                    break;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_W:
                        if (combatRange) {
                            spell = true;

                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &player, fireBall);
                                    printf("%dvida: %d\n", i,monsters[i].health);
                                    break;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_E:
                        if (combatRange) {
                            spell = true;

                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &player, lightning);
                                    printf("%dvida: %d\n", i,monsters[i].health);
                                    break;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_R:
                        if (combatRange) {
                            spell = true;

                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &player, iceSpear);
                                    printf("%dvida: %d\n", i,monsters[i].health);
                                    break;
                                }
                            }
                        }
                        break;

                }
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                exit = true;
                break;
        }

        if(exit)
            break;

        if(redraw && al_is_event_queue_empty(queue)) {

            // construção do mapa (coloca os tiles no lugar)
            for (int i = 0; i < mapsize.height * mapsize.width; i++) {
                // (i / mapsize.width) == linha, (i % mapsize.width) == coluna
                if (map[i / mapsize.width][i % mapsize.width] == 't') {
                    al_draw_bitmap(mapTiles->top, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'l') {
                    al_draw_bitmap(mapTiles->topSide, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'r') {
                    al_draw_bitmap(mapTiles->topSide, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), ALLEGRO_FLIP_HORIZONTAL);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'b') {
                    al_draw_bitmap(mapTiles->top, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), ALLEGRO_FLIP_VERTICAL);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'c') {
                    al_draw_bitmap(mapTiles->topCorner, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'd') {
                    al_draw_bitmap(mapTiles->topCorner, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), ALLEGRO_FLIP_HORIZONTAL);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'C') {
                    al_draw_bitmap(mapTiles->topCorner, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), ALLEGRO_FLIP_VERTICAL);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'D') {
                    al_draw_bitmap(mapTiles->topCorner, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), ALLEGRO_FLIP_HORIZONTAL + ALLEGRO_FLIP_VERTICAL);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'w') {
                    al_draw_bitmap(mapTiles->wall, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'f') {
                    switch(tilesOrder[i]) {
                        case 1:
                            al_draw_bitmap(mapTiles->floor1, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                            break;
                        case 2:
                            al_draw_bitmap(mapTiles->floor1, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                            break;
                        case 3:
                            al_draw_bitmap(mapTiles->floor3, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                            break;
                    }
                }
            }

            if (spell && player.mana > 0) {
                al_draw_line(player.x + 16, player.y + 16, monsterInRange.x + 16, monsterInRange.y + 16, al_map_rgb_f(255, 255, 255), 2);
                spell = false;
            }

            // desenha a sprite player e monstros
            if (animationTimer < 20) {
                al_draw_bitmap(playerImg->idle1, player.x, player.y, player.direc);
                
                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 1, trollImg);
                    }
                    else if (monsters[i].type == bigRed) {
                        monsterAnimation(monsters[i], 1, bigRedImg);
                    }
                }

                animationTimer++;
            }
            else if (animationTimer < 40) {
                al_draw_bitmap(playerImg->idle2, player.x, player.y, player.direc);

                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 2, trollImg);
                    }
                    else if (monsters[i].type == bigRed) {
                        monsterAnimation(monsters[i], 2, bigRedImg);
                    }
                }

                animationTimer++;
            }
            else if (animationTimer < 60) {
                al_draw_bitmap(playerImg->idle3, player.x, player.y, player.direc);

                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 3, trollImg);
                    }
                    else if (monsters[i].type == bigRed) {
                        monsterAnimation(monsters[i], 3, bigRedImg);
                    }
                }

                animationTimer++;
            }
            else {
                al_draw_bitmap(playerImg->idle4, player.x, player.y, player.direc);

                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 4, trollImg);
                    }
                    else if (monsters[i].type == bigRed) {
                        monsterAnimation(monsters[i], 4, bigRedImg);
                    }
                }

                animationTimer = 0;   
            }

            // algum monstro esta dentro do combatRange
            if (combatRange) {
                // mensagem que o ataque do player esta habilitado
                al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 600, 0, "APERTE X PARA ATACAR");
                
                // barra de vida de monstros
                if (monsterInRange.angry) {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 5, 0, "ID %d", monsterInRange.id);
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1100, 5, 0, "VIDA %d", monsterInRange.health);
                    al_draw_filled_rectangle(1100, 20, monsterInRange.health + 1100, 30, al_map_rgba_f(255, 0, 255, 0.5));
                }
            }

            // hud player
            al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 5, 0, "LEVEL %d", player.level);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 90, 5, 0, "XP %d", player.xp);

            // barra de vida
            if (player.health < 0) {
                exit = true;
            }
            else {
                al_draw_textf(font, al_map_rgb(255, 255, 255), (player.health + 30), 20, 0, "%d", player.health);
                al_draw_filled_rectangle(20, 20, (player.health + 20), 30, al_map_rgba_f(255, 0, 0, 0.5));
            }

            //barra de mana
            al_draw_textf(font, al_map_rgb(255, 255, 255), (player.mana + 30), 35, 0, "%d", player.mana);
            al_draw_filled_rectangle(20, 35, (player.mana + 20), 42, al_map_rgba_f(0, 0, 255, 0.5));

            // andar
            al_draw_textf(font, al_map_rgb(255, 255, 255), 20 , 65, 0, "Profundidade: %d", *floorNumber);

            al_flip_display();

            redraw = false;
        }
    }
    if (player.health <= 0 || exit) {
        return false;
    }
    else {
        return true;
    }
    printf("fim do loop principal do jogo\n");
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
                if (monster.angry) {
                    al_draw_bitmap(monsterImg->walk1, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap(monsterImg->idle1, monster.x, monster.y, monster.direc);
                }
                break;
            case 2:
                if (monster.angry) {
                    al_draw_bitmap(monsterImg->walk2, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap(monsterImg->idle2, monster.x, monster.y, monster.direc);
                }
                break;
            case 3:
                if (monster.angry) {
                    al_draw_bitmap(monsterImg->walk3, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap(monsterImg->idle3, monster.x, monster.y, monster.direc);
                }
                break;
            case 4:
                if (monster.angry) {
                    al_draw_bitmap(monsterImg->walk4, monster.x, monster.y, monster.direc);
                }
                else {
                    al_draw_bitmap(monsterImg->idle4, monster.x, monster.y, monster.direc);
                }
                break;
        }
    }
}