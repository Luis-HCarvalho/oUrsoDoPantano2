#include "init.h"
#include "combat.h"
#include "map.h"
#include "draw.h"

// substituir mapNav por floorNumber/profundidade e gerar monstros de acordo com a profundidade
// (consertar) level do player resetando
// implementar nivel de proeficiencia com uma escola de magia (level para as magias)
// se o player morrer ele tem que provar seus conhecimentos para o ceifador para ganhar mais chance(vida)
// fazer um modulo com funções para logica de desenho na tela

// loop principal
bool gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    Keys * keys,
    ALLEGRO_BITMAP ** spellBorder,
    int * mapNav,
    int * floorNumber,
    char map[][maxMapWidth],
    Mapsize mapsize,
    Tiles * mapTiles,
    int numMonsters,
    AllMagics * allMagics,
    Player * player,
    int typeMonsters,
    Sprites * sprites
);

int main () {
    // inicializações 
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "imgageAddon");
    must_init(al_init_primitives_addon(), "primitives");

    ALLEGRO_TIMER * timer = al_create_timer(1.0 / 50.0);  //45
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE * queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_DISPLAY * display = al_create_display(displayWidth, displayHeight);
    must_init(display, "display");

    ALLEGRO_FONT * font = al_create_builtin_font();
    must_init(font, "font");

    // carrega os sprites dos personagens
    Sprites sprites;
    sprites.player = al_load_bitmap("./assets/characters/wizard_idle_walk.png");
    sprites.princess = al_load_bitmap("./assets/characters/elfPrincess_idle_walk.png");
    sprites.fairy = al_load_bitmap("./assets/characters/fairy_idle_walk.png");
    sprites.bandit = al_load_bitmap("./assets/characters/bandit_idle_walk.png");
    sprites.wolf = al_load_bitmap("./assets/characters/wolf_idle_walk.png");
    sprites.bear = al_load_bitmap("./assets/characters/bear_idle_walk.png");
    sprites.troll = al_load_bitmap("./assets/characters/troll_idle_walk.png");
    sprites.bigRed = al_load_bitmap("./assets/characters/bigRed_idle_walk.png");
    sprites.golem = al_load_bitmap("./assets/characters/golem_idle_walk.png");
    sprites.knight = al_load_bitmap("./assets/characters/elvenKnight_idle_walk.png");
    sprites.guardian = al_load_bitmap("./assets/characters/guardian_idle_walk.png");

    // carrega sprite keys do teclado
    Keys keys;
    keys.Q = al_load_bitmap("./assets/keyboardKeys/Q.png");
    keys.W = al_load_bitmap("./assets/keyboardKeys/W.png");
    keys.E = al_load_bitmap("./assets/keyboardKeys/E.png");
    keys.R = al_load_bitmap("./assets/keyboardKeys/R.png");
    keys.ARROWUP = al_load_bitmap("./assets/keyboardKeys/ARROWUP.png");
    keys.ARROWDOWN = al_load_bitmap("./assets/keyboardKeys/ARROWDOWN.png");
    keys.ARROWLEFT = al_load_bitmap("./assets/keyboardKeys/ARROWLEFT.png");
    keys.ARROWRIGHT = al_load_bitmap("./assets/keyboardKeys/ARROWRIGHT.png");

    ALLEGRO_BITMAP * spellBorder = al_load_bitmap("./assets/borders/spellBorder.png");

    // carrega os sprites de magias
    MagicImg magicMissileImg;
    magicMissileImg.img[0] = al_load_bitmap("./assets/magic/magicMissile/magicMissile_1.png");
    magicMissileImg.img[1] = al_load_bitmap("./assets/magic/magicMissile/magicMissile_2.png");
    magicMissileImg.img[2] = al_load_bitmap("./assets/magic/magicMissile/magicMissile_3.png");
    magicMissileImg.img[3] = al_load_bitmap("./assets/magic/magicMissile/magicMissile_4.png");
    magicMissileImg.img[4] = al_load_bitmap("./assets/magic/magicMissile/magicMissile_5.png");

    MagicImg fireballImg;
    fireballImg.img[0] = al_load_bitmap("./assets/magic/fireball/fireball_1.png");
    fireballImg.img[1] = al_load_bitmap("./assets/magic/fireball/fireball_2.png");
    fireballImg.img[2] = al_load_bitmap("./assets/magic/fireball/fireball_3.png");
    fireballImg.img[3] = al_load_bitmap("./assets/magic/fireball/fireball_4.png");
    fireballImg.img[4] = al_load_bitmap("./assets/magic/fireball/fireball_5.png");
    fireballImg.img[5] = al_load_bitmap("./assets/magic/fireball/fireball_6.png");
    fireballImg.img[6] = al_load_bitmap("./assets/magic/fireball/fireball_7.png");
    fireballImg.img[7] = al_load_bitmap("./assets/magic/fireball/fireball_8.png");

    MagicImg lightningImg;
    lightningImg.img[0] = al_load_bitmap("./assets/magic/lightning/lightning_1.png");
    lightningImg.img[1] = al_load_bitmap("./assets/magic/lightning/lightning_2.png");
    lightningImg.img[2] = al_load_bitmap("./assets/magic/lightning/lightning_3.png");
    lightningImg.img[3] = al_load_bitmap("./assets/magic/lightning/lightning_4.png");
    lightningImg.img[4] = al_load_bitmap("./assets/magic/lightning/lightning_5.png");
    lightningImg.img[5] = al_load_bitmap("./assets/magic/lightning/lightning_6.png");
    lightningImg.img[6] = al_load_bitmap("./assets/magic/lightning/lightning_7.png");

    MagicImg iceshardImg;
    iceshardImg.img[0] = al_load_bitmap("./assets/magic/iceshard/iceshard_1.png");
    iceshardImg.img[1] = al_load_bitmap("./assets/magic/iceshard/iceshard_2.png");
    iceshardImg.img[2] = al_load_bitmap("./assets/magic/iceshard/iceshard_3.png");
    iceshardImg.img[3] = al_load_bitmap("./assets/magic/iceshard/iceshard_4.png");
    iceshardImg.img[4] = al_load_bitmap("./assets/magic/iceshard/iceshard_5.png");
    iceshardImg.img[5] = al_load_bitmap("./assets/magic/iceshard/iceshard_6.png");
    iceshardImg.img[6] = al_load_bitmap("./assets/magic/iceshard/iceshard_7.png");
    iceshardImg.img[7] = al_load_bitmap("./assets/magic/iceshard/iceshard_8.png");

    AllMagics allMagics;
    allMagics.spell[0] = magicMissileImg;
    allMagics.spell[1] = fireballImg;
    allMagics.spell[2] = lightningImg;
    allMagics.spell[3] = iceshardImg; 

    // carrega tiles para o mapa
    Tiles mapTiles;
    mapTiles.top = al_load_bitmap("./assets/tiles/wall_top.png");
    mapTiles.topSide = al_load_bitmap("./assets/tiles/wall_top_side.png");
    mapTiles.topCorner = al_load_bitmap("./assets/tiles/wall_top_corner.png");
    mapTiles.wall = al_load_bitmap("./assets/tiles/wall.png");
    mapTiles.floor1 = al_load_bitmap("./assets/tiles/floor_1.png");
    mapTiles.floor2 = al_load_bitmap("./assets/tiles/floor_2.png");
    mapTiles.floor3 = al_load_bitmap("./assets/tiles/floor_3.png");
    mapTiles.waterFount = al_load_bitmap("./assets/tiles/fountain.png");
    mapTiles.pillar = al_load_bitmap("./assets/tiles/pillar.png");

    // tipos de evento que reagiremos no programa
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // mapa
    char map[maxMapHeight][maxMapWidth];    // matrix para armazenar o mapa
    Mapsize mapsize;

    // começa o jogo
    al_start_timer(timer);
    
    int numMonsters = 0;
    int typeMonsters;
    int floorNumber = 0;
    int mapNav = 0;
    bool gameStatus = true;    // determina se o jogo fecha ou continua rodando
    int mapLimLeft;
    int mapLimRight;
    bool goingDown = true;
    char d, u;

    // init player
    Player player;
    initPlayer(&player);

    while (gameStatus) {
        // mapa fixo para o player comprar itens, acessar baus, etc
        if (floorNumber == 0) {
            getMap("./maps/dungeonEntrance.txt", map, &mapsize);
        }
        else {
            d = (floorNumber / 10) + '0' ; // dezena
            u = (floorNumber % 10) + '0';  // unidade

            char mapPath[] = {'.','/','m','a','p','s','/','m','a','p', d, u,'.','t','x','t', '\0'};

            if (goingDown && access(mapPath, F_OK) != 0) {
                // gera um novo mapa se o proximo andar ainda não foi criado
                mapGenerator(floorNumber);
            }

            getMap(mapPath, map, &mapsize);
        }

        // posição do player a subir ou descer os andares da dungeon
        mapLimLeft = (displayWidth -  mapsize.width * sizeTile) / 2 + 32;
        mapLimRight = displayWidth - ((displayWidth -  mapsize.width * sizeTile) / 2) - (sizeTile * 2) - 32;
        if (goingDown) {
            player.x = mapLimLeft;
        }
        else {
            player.x = mapLimRight;
        }
        player.y = displayHeight / 2;

        if (floorNumber == 0) {
            numMonsters = 0;
        }
        else {
            srand(time(NULL));
            numMonsters = rand() % (((mapsize.height * mapsize.width) / 32) / 3);
        
            if (floorNumber / 2 == 0) {
                typeMonsters = rand() %  1;
            }
            else {
                typeMonsters = rand() % (floorNumber / 2);

                if (typeMonsters > 7) {
                    typeMonsters = 0;
                }
            }
        }

        gameStatus = gameMainLoop(
                timer,
                queue,
                font,
                &keys,
                &spellBorder,
                &mapNav,
                &floorNumber,
                map,
                mapsize,
                &mapTiles,
                numMonsters,
                &allMagics,
                &player,
                typeMonsters,
                &sprites
        );

        switch (mapNav) {
            case 1:
                floorNumber++;
                mapNav = 0;
                goingDown = true;
                break;
            case 2:
                mapNav = 0;
                floorNumber--;
                goingDown = false;
                break;
        }
    
    }

    // limpeza de recursos criados durante as inicializações
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_font(font);

    al_destroy_bitmap(sprites.player);
    al_destroy_bitmap(sprites.princess);
    al_destroy_bitmap(sprites.fairy);
    al_destroy_bitmap(sprites.bandit);
    al_destroy_bitmap(sprites.wolf);
    al_destroy_bitmap(sprites.bear);
    al_destroy_bitmap(sprites.troll);
    al_destroy_bitmap(sprites.bigRed);
    al_destroy_bitmap(sprites.golem);
    al_destroy_bitmap(sprites.knight);
    al_destroy_bitmap(sprites.guardian);

    al_destroy_bitmap(keys.Q);
    al_destroy_bitmap(keys.W);
    al_destroy_bitmap(keys.E);
    al_destroy_bitmap(keys.R);
    al_destroy_bitmap(keys.ARROWUP);
    al_destroy_bitmap(keys.ARROWDOWN);
    al_destroy_bitmap(keys.ARROWLEFT);
    al_destroy_bitmap(keys.ARROWRIGHT);

    al_destroy_bitmap(spellBorder);

    for (int i = 0; i < numMagicImgs; i++) {
        al_destroy_bitmap(fireballImg.img[i]);
        al_destroy_bitmap(iceshardImg.img[i]);
        if (i < 7) {
            al_destroy_bitmap(lightningImg.img[i]);
        }
        if (i < 5) {
            al_destroy_bitmap(magicMissileImg.img[i]);
        }
    }

    al_destroy_bitmap(mapTiles.top);
    al_destroy_bitmap(mapTiles.topSide);
    al_destroy_bitmap(mapTiles.topCorner);
    al_destroy_bitmap(mapTiles.wall);
    al_destroy_bitmap(mapTiles.floor1);
    al_destroy_bitmap(mapTiles.floor2);
    al_destroy_bitmap(mapTiles.floor3);
    al_destroy_bitmap(mapTiles.waterFount);
    al_destroy_bitmap(mapTiles.pillar);

    return 0;
}

// loop principal de execução do programa
bool gameMainLoop (
    ALLEGRO_TIMER * timer,
    ALLEGRO_EVENT_QUEUE * queue,
    ALLEGRO_FONT * font,
    Keys * keys,
    ALLEGRO_BITMAP ** spellBorder,
    int * mapNav,
    int * floorNumber,
    char map[][maxMapWidth],
    Mapsize mapsize,
    Tiles * mapTiles,
    int numMonsters,
    // MagicImg * fireballImg,
    // MagicImg * iceshardImg,
    AllMagics * allMagics,
    //Sprites * playerImg,
    Player * player,
    int typeMonsters,
    Sprites * sprites
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

    float borderPos[2] = {(displayWidth - ((displayWidth * 6) / 7)), displayHeight - 84};    // {x, y}
    float spellKeysPos[2] = {borderPos[0] + 6.5, borderPos[1] + 25};    // {x, y}

    int spellDistance[2];  // (x, y)
    int spellCounter = 0;
    int spellType = 0;
    int spellCasted = 0;

    int fountTimer = 0;
    int animationTimer = 0;
    int attackCooldown = 0;    // tempo de espera para ataque dos monstros
    int respawnTimer = 0;

    while (!exit && !*mapNav) {
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_wait_for_event(queue, &event);

        switch(event.type) {
            // logica do jogo

            case ALLEGRO_EVENT_TIMER:
                // mov
                if (mov.up && player->y > maplim.topBorder) {
                    player->y -= player->speed;
                }
                if (mov.down && player->y < maplim.bottomBorder) {
                    player->y += player->speed;
                }
                if (mov.left && player->x > maplim.leftBorder) {
                    player->x -= player->speed;
                    player->direc = 1;
                }
                if (mov.right && player->x < maplim.rightBorder) {
                    player->x += player->speed;
                    player->direc = 0;
                }

                // cooldown ataques dos monstros e recuperação de mana
                if (attackCooldown <= 20){
                    attackCooldown++;
                }
                else {
                    attackCooldown = 0;
                }

                // recuparação de mana
                if (player->mana < 50 && attackCooldown >= 10 && attackCooldown % 10 == 0) {
                    player->mana++;
                }
                
                // determina se um monstro esta dentro do range de combate do player
                for (int i = 0; i < numMonsters; i++) {
                    if ((combatRange = monsterAngry(&monsters[i], *player))) {
                        monsterInRange = monsters[i];
                        break;
                    }
                }

                if (!combatRange) {
                    monsterInRange.angry = false;
                }

                // determina se um monstro deve seguir o player
                for (int i = 0; i < numMonsters; i++) {
                    monsterFollow(&monsters[i], &(*player));
                    if (monsters[i].attackCooldown > 0) {
                        monsters[i].attackCooldown--;
                    }
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
                if ((player->x > maplim.rightBorder - 4) && (*floorNumber < 99)) {
                    *mapNav = 1;
                }
                else if ((player->x < maplim.leftBorder + 4) && (*floorNumber > 0)) {
                    *mapNav = 2;
                }

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
                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &(*player), magicMissile, &spellType);
                                    spellCounter = 0;
                                    break;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_W:
                        if (combatRange) {
                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &(*player), fireball, &spellType);
                                    spellCounter = 0;
                                    break;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_E:
                        if (combatRange) {
                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &(*player), lightning, &spellType);
                                    spellCounter = 0;
                                    break;
                                }
                            }
                        }
                        break;
                    case ALLEGRO_KEY_R:
                        if (combatRange) {
                            for (int i = 0; i < numMonsters; i++) {
                                if (monsterInRange.id == monsters[i].id) {
                                    castSpell(&monsters[i], &(*player), iceshard, &spellType);
                                    spellCounter = 0;
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
                else if (map[i / mapsize.width][i % mapsize.width] == '1') {
                    map[i / mapsize.width - 1][i % mapsize.width] = 's';
                }
                else if (map[i / mapsize.width][i % mapsize.width] == '2') {
                    map[i / mapsize.width - 1][i % mapsize.width] = '0';
                    map[i / mapsize.width - 2][i % mapsize.width] = 'p';
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 's') {
                    if (fountTimer < 8) {
                        al_draw_bitmap_region(mapTiles->waterFount, 0, 0, 16, 32, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                        fountTimer++;
                    }
                    else if (fountTimer < 16) {
                        al_draw_bitmap_region(mapTiles->waterFount, 16, 0, 16, 32, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                        fountTimer++;
                    }
                    else {
                        al_draw_bitmap_region(mapTiles->waterFount, 32, 0, 16, 32, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
                        fountTimer = 0;
                    }
                }
                else if (map[i / mapsize.width][i % mapsize.width] == 'p') {
                    al_draw_bitmap_region(mapTiles->pillar, 0, 0, 16, 48, ((displayWidth -  mapsize.width * sizeTile) / 2) + ((i % mapsize.width) * sizeTile), ((displayHeight -  mapsize.height * sizeTile) / 2) + ((i / mapsize.width) * sizeTile), 0);
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

            // desenha as bordas/molduras dos icones de feitiços
            al_draw_bitmap(*spellBorder, borderPos[0], borderPos[1], 0);
            al_draw_bitmap(*spellBorder, borderPos[0] + 42, borderPos[1], 0);
            al_draw_bitmap(*spellBorder, borderPos[0] + 84, borderPos[1], 0);
            al_draw_bitmap(*spellBorder, borderPos[0] + 126, borderPos[1], 0);

            // desenha os feitiçoes dentro das molduras
            al_draw_bitmap(allMagics->spell[0].img[2], borderPos[0], borderPos[1] + 6, 0);
            al_draw_bitmap(allMagics->spell[1].img[0], borderPos[0] + 50, borderPos[1] + 6, 0);
            al_draw_bitmap(allMagics->spell[2].img[3], borderPos[0] + 92, borderPos[1] + 6, 0);
            al_draw_bitmap(allMagics->spell[3].img[6], borderPos[0] + 134, borderPos[1] + 6, 0);

            // desenha as keys dos ataques
            switch (spellCasted) {
                case 0:
                    al_draw_bitmap_region(keys->Q, 0, 0, 19, 21, spellKeysPos[0], spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->W, 0, 0, 19, 21, spellKeysPos[0] + 42, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->E, 0, 0, 19, 21, spellKeysPos[0] + 84, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->R, 0, 0, 19, 21, spellKeysPos[0] + 126, spellKeysPos[1], 0);
                    break;
                case magicMissile:
                    al_draw_bitmap_region(keys->Q, 19, 0, 19, 21, spellKeysPos[0], spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->W, 0, 0, 19, 21, spellKeysPos[0] + 42, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->E, 0, 0, 19, 21, spellKeysPos[0] + 84, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->R, 0, 0, 19, 21, spellKeysPos[0] + 126, spellKeysPos[1], 0);
                    break;
                case fireball:
                    al_draw_bitmap_region(keys->Q, 0, 0, 19, 21, spellKeysPos[0], spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->W, 19, 0, 19, 21, spellKeysPos[0] + 42, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->E, 0, 0, 19, 21, spellKeysPos[0] + 84, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->R, 0, 0, 19, 21, spellKeysPos[0] + 126, spellKeysPos[1], 0);
                    break;
                case lightning:
                    al_draw_bitmap_region(keys->Q, 0, 0, 19, 21, spellKeysPos[0], spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->W, 0, 0, 19, 21, spellKeysPos[0] + 42, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->E, 19, 0, 19, 21, spellKeysPos[0] + 84, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->R, 0, 0, 19, 21, spellKeysPos[0] + 126, spellKeysPos[1], 0);
                    break;
                case iceshard:
                    al_draw_bitmap_region(keys->Q, 0, 0, 19, 21, spellKeysPos[0], spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->W, 0, 0, 19, 21, spellKeysPos[0] + 42, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->E, 0, 0, 19, 21, spellKeysPos[0] + 84, spellKeysPos[1], 0);
                    al_draw_bitmap_region(keys->R, 19, 0, 19, 21, spellKeysPos[0] + 126, spellKeysPos[1], 0);
                    break;
            }

            // desenha a sprite player e monstros
            if (animationTimer < 20) {
                al_draw_bitmap_region(sprites->player, 0, 0, 32, 32, player->x, player->y, player->direc);
                
                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Bandit) {
                        monsterAnimation(monsters[i], 1, sprites->bandit);
                    }
                    else if (monsters[i].type == Wolf) {
                        monsterAnimation(monsters[i], 1, sprites->wolf);
                    }
                    else if (monsters[i].type == Bear) {
                        monsterAnimation(monsters[i], 1, sprites->bear);
                    }
                    else if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 1, sprites->troll);
                    }
                    else if (monsters[i].type == BigRed) {
                        monsterAnimation(monsters[i], 1, sprites->bigRed);
                    }
                    else if (monsters[i].type == Golem) {
                        monsterAnimation(monsters[i], 1, sprites->golem);
                    }
                    else if (monsters[i].type == Knight) {
                        monsterAnimation(monsters[i], 1, sprites->knight);
                    }
                    else if (monsters[i].type == Guardian) {
                        monsterAnimation(monsters[i], 1, sprites->guardian);
                    }
                }

                animationTimer++;
            }
            else if (animationTimer < 40) {
                al_draw_bitmap_region(sprites->player, 33, 0, 32, 32, player->x, player->y, player->direc);

                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Bandit) {
                        monsterAnimation(monsters[i], 2, sprites->bandit);
                    }
                    else if (monsters[i].type == Wolf) {
                        monsterAnimation(monsters[i], 2, sprites->wolf);
                    }
                    else if (monsters[i].type == Bear) {
                        monsterAnimation(monsters[i], 2, sprites->bear);
                    }
                    else if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 2, sprites->troll);
                    }
                    else if (monsters[i].type == BigRed) {
                        monsterAnimation(monsters[i], 2, sprites->bigRed);
                    }
                    else if (monsters[i].type == Golem) {
                        monsterAnimation(monsters[i], 2, sprites->golem);
                    }
                    else if (monsters[i].type == Knight) {
                        monsterAnimation(monsters[i], 2, sprites->knight);
                    }
                    else if (monsters[i].type == Guardian) {
                        monsterAnimation(monsters[i], 2, sprites->guardian);
                    }
                }

                animationTimer++;
            }
            else if (animationTimer < 60) {
                al_draw_bitmap_region(sprites->player, 65, 0, 32, 32, player->x, player->y, player->direc);

                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Bandit) {
                        monsterAnimation(monsters[i], 3, sprites->bandit);
                    }
                    else if (monsters[i].type == Wolf) {
                        monsterAnimation(monsters[i], 3, sprites->wolf);
                    }
                    else if (monsters[i].type == Bear) {
                        monsterAnimation(monsters[i], 3, sprites->bear);
                    }
                    else if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 3, sprites->troll);
                    }
                    else if (monsters[i].type == BigRed) {
                        monsterAnimation(monsters[i], 3, sprites->bigRed);
                    }
                    else if (monsters[i].type == Golem) {
                        monsterAnimation(monsters[i], 3, sprites->golem);
                    }
                    else if (monsters[i].type == Knight) {
                        monsterAnimation(monsters[i], 3, sprites->knight);
                    }
                    else if (monsters[i].type == Guardian) {
                        monsterAnimation(monsters[i], 3, sprites->guardian);
                    }
                }

                animationTimer++;
            }
            else {
                al_draw_bitmap_region(sprites->player, 97, 0, 32, 32, player->x, player->y, player->direc);

                for (int i = 0; i < numMonsters; i++) {
                    if (monsters[i].type == Bandit) {
                        monsterAnimation(monsters[i], 4, sprites->bandit);
                    }
                    else if (monsters[i].type == Wolf) {
                        monsterAnimation(monsters[i], 4, sprites->wolf);
                    }
                    else if (monsters[i].type == Bear) {
                        monsterAnimation(monsters[i], 4, sprites->bear);
                    }
                    else if (monsters[i].type == Troll) {
                        monsterAnimation(monsters[i], 4, sprites->troll);
                    }
                    else if (monsters[i].type == BigRed) {
                        monsterAnimation(monsters[i], 4, sprites->bigRed);
                    }
                    else if (monsters[i].type == Golem) {
                        monsterAnimation(monsters[i], 4, sprites->golem);
                    }
                    else if (monsters[i].type == Knight) {
                        monsterAnimation(monsters[i], 4, sprites->knight);
                    }
                    else if (monsters[i].type == Guardian) {
                        monsterAnimation(monsters[i], 4, sprites->guardian);
                    }
                }

                animationTimer = 0;   
            }

            // magias
            if (spellType && player->mana > 0) {
                switch (spellType) {
                    case magicMissile:
                        spellDistance[0] = (monsterInRange.x - player->x) / 5;
                        spellDistance[1] = (monsterInRange.y - player->y) / 5;
                        break;
                    case fireball:
                        spellDistance[0] = (monsterInRange.x - player->x) / 8;
                        spellDistance[1] = (monsterInRange.y - player->y) / 8;
                        break;
                    case lightning:
                        spellDistance[0] = (monsterInRange.x - player->x) / 7;
                        spellDistance[1] = (monsterInRange.y - player->y) / 7;
                        break;
                    case iceshard:
                        spellDistance[0] = (monsterInRange.x - player->x) / 8;
                        spellDistance[1] = (monsterInRange.y - player->y) / 8;
                        break;
                }
                spellCasted = spellType;
                spellType = 0;
            }
            
            switch (spellCasted) {
                case magicMissile:
                    drawSpellAnim(&spellCasted, &allMagics->spell[0], &spellCounter, spellDistance, *player, monsterInRange);
                    break;
                case fireball:
                    drawSpellAnim(&spellCasted, &allMagics->spell[1], &spellCounter, spellDistance, *player, monsterInRange);
                    break;
                case lightning:
                    drawSpellAnim(&spellCasted, &allMagics->spell[2], &spellCounter, spellDistance, *player, monsterInRange);
                    break;
                case iceshard:
                    drawSpellAnim(&spellCasted, &allMagics->spell[3], &spellCounter, spellDistance, *player, monsterInRange);
                    break;
            }

            // algum monstro esta dentro do combatRange
            if (combatRange) {
                // mensagem que o ataque do player esta habilitado
                al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 600, 0, "MONSTRO DENTRO DO RAIO DE COMBATE");
                
                // barra de vida de monstros
                if (monsterInRange.angry) {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 5, 0, "ID %d", monsterInRange.id);
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1100, 5, 0, "VIDA %d", monsterInRange.health);
                    al_draw_filled_rectangle(1100, 20, monsterInRange.health + 1100, 30, al_map_rgba_f(255, 0, 255, 0.5));
                }
            }

            // hud player
            al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 5, 0, "LEVEL %d", player->level);
            al_draw_textf(font, al_map_rgb(255, 255, 255), 90, 5, 0, "XP %d", player->xp);

            // barra de vida
            if (player->health < 0) {
                exit = true;
            }
            else {
                al_draw_textf(font, al_map_rgb(255, 255, 255), (player->health + 30), 20, 0, "%d", player->health);
                al_draw_filled_rectangle(20, 20, (player->health + 20), 30, al_map_rgba_f(255, 0, 0, 0.5));
            }

            //barra de mana
            al_draw_textf(font, al_map_rgb(255, 255, 255), (player->mana + 30), 35, 0, "%d", player->mana);
            al_draw_filled_rectangle(20, 35, (player->mana + 20), 42, al_map_rgba_f(0, 0, 255, 0.5));

            // andar
            al_draw_textf(font, al_map_rgb(255, 255, 255), 20 , 65, 0, "Profundidade: %d", *floorNumber);

            if (*floorNumber == 0) {
                if (player->x > 662) {
                    al_draw_textf(font, al_map_rgb(239, 230, 10), 388, 450, 0, "Sequest... Salve a princesa e talvez você aprenda alguma coisa no caminho.");
                }
                else {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), player->x - 60, 440, 0, "Isso é um jogo educacional !!!");
                }
            }
            else if (*floorNumber == 1) {
                if (player->x > 848) {
                    al_draw_textf(font, al_map_rgb(255, 10, 10), 848 - 60, 500, 0, "Use fireball(W) para queimar seus inimigos");
                }
                else if (player->x > 672) {
                    al_draw_textf(font, al_map_rgb(255, 10, 10), player->x - 60, 500, 0, "Use fireball(W) para queimar seus inimigos");
                    al_draw_textf(font, al_map_rgb(255, 255, 255), player->x - 60, 510, 0, "%d %d", player->x, player->y);
                }
                else {
                    al_draw_textf(font, al_map_rgb(255, 255, 255), player->x - 60, 500, 0, "O fogo é constituído de uma mistura de gases em alta temperatura.");
                    al_draw_textf(font, al_map_rgb(255, 255, 255), player->x - 60, 510, 0, "A luminosidade vista e o calor são provenientes da reação entre o");
                    al_draw_textf(font, al_map_rgb(255, 255, 255), player->x - 60, 520, 0, "combustível (inimigos) e o comburente (oxigênio).");
                }
            }

            // quantidade de monstros no andar
            al_draw_textf(font, al_map_rgb(255, 255, 255), 20 , 75, 0, "Monstros: %d", numMonsters);

            al_flip_display();

            redraw = false;
        }
    }
    if (player->health <= 0 || exit) {
        return false;
    }
    else {
        return true;
    }
}