#ifndef MAP_H
#define MAP_H

// tamanho mapa (quantidade de tiles)
#define maxMapHeight 20
#define maxMapWidth 60
#define sizeTile 16 // tamanho em px dos tiles

// dimensoes do mapa
typedef struct {
    int width;
    int height;
    int wall;
} Mapsize;

// substituir posteriormente pelo nome dos mapas
enum MapNavigation {
    room0 = 0,
    room1,
    room2,
    room3,
};

// recebe o path para o txt do mapa e uma matrix para armazenar map[maxMapHeight][maxMapWidth]
void getMap (char mapName[], char map[][maxMapWidth], Mapsize * mapsize);

void mapGenerator();

#endif // MAP_H