/* legenda do mapa: 
    primeira linha -> valores de altura, largura e altura da parede nessa ordem
    t = parte de cima da parede
    l = parte de cima da parede (esquerda do mapa)
    r = parte de cima da parede (direita do mapa)
    b = parte de cima da parede (parte de baixo do mapa)
    c = parte de cima da parede, canto (esquerda do mapa)
    d = parte de cima da parede, canto (direita do mapa)
    C = parte de cima da parede, canto (parte inferior esquerda do mapa)
    D = parte de cima da parede, canto (parte inferior direita do mapa)
    w = parede
    f = piso

*/

#include <string.h>
#include "init.h"
#include "map.h"

// recebe o path para o txt do mapa e uma matrix para armazenar map[maxMapHeight][maxMapWidth]
// retorna as dimensoes w/h do mapa lido no arq txt
void getMap (char mapName[], char map[][maxMapWidth], Mapsize * mapsize) {

    // abre o arquivo
	FILE * mapFile;
	mapFile = fopen(mapName, "r");

    // pega a primeira linha do arq que contem as dimensoes
    fscanf(mapFile, "%d %d %d", &mapsize->height, &mapsize->width, &mapsize->wall);

    char row[255];
	int cont = -1; //primeira row são as dimensoes do mapa (ignorada pela matrix)

    // itera sobre todas as linhas do arquivo .txt do mapa e guarda na matrix map[][]
	while (fgets(row, sizeof(row), mapFile) != NULL) {
		if (cont >= 0)
			strcpy(map[cont], row); // copia cada linha(string) do txt para um linha da matrix
		cont++;
	}

    // fecha o arquivo do mapa
	fclose(mapFile);
}

void mapGenerator () {

    char filename[] = "./maps/map.txt";

    // open file
    FILE * mapFile = fopen(filename, "w");
    if (mapFile == NULL) {
        printf("error in %s", filename);
    }

    // define as proporções do mapa
    srand(time(NULL));
    int mapHeight = rand() % maxMapHeight;
    int mapWidth = rand() % maxMapWidth;

    if (mapHeight < 10) {
        mapHeight += 10;
    }
    if (mapWidth < 10) {
        mapWidth += 10;
    }

    // escreve no arquivo txt (construção do mapa)
    for (int line = 0; line <= mapHeight; line++) {
        if (line == 0) {
            fprintf(mapFile, "%d %d %d\n", mapHeight, mapWidth, 2);
        }
        else if (line == 1) {
            for (int tileCode = 0; tileCode < mapWidth; tileCode++) {
                if (tileCode == 0) {
                    fprintf(mapFile, "c");
                }
                else if (tileCode + 1 == mapWidth) {
                    fprintf(mapFile, "d\n");
                }
                else {
                    fprintf(mapFile, "t");
                }
            }
        }
        else if (line == 2) {
            for (int tileCode = 0; tileCode < mapWidth; tileCode++) {
                if (tileCode == 0) {
                    fprintf(mapFile, "l");
                }
                else if (tileCode + 1 == mapWidth) {
                    fprintf(mapFile, "r\n");
                }
                else {
                    fprintf(mapFile, "w");
                }
            }
        }
        else if (line  == mapHeight) {
            for (int tileCode = 0; tileCode < mapWidth; tileCode++) {
                if (tileCode == 0) {
                    fprintf(mapFile, "C");
                }
                else if (tileCode + 1 == mapWidth) {
                    fprintf(mapFile, "D");
                }
                else {
                    fprintf(mapFile, "b");
                }
            }
        }
        else {
            for (int tileCode = 0; tileCode < mapWidth; tileCode++) {
                if (tileCode == 0) {
                    fprintf(mapFile, "l");
                }
                else if (tileCode + 1 == mapWidth) {
                    fprintf(mapFile, "r\n");
                }
                else {
                    fprintf(mapFile, "f");
                }
            }
        }
    }

    fclose(mapFile);
}
