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
