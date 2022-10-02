#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "drawMap.h"

int drawMap (char mapName[]) {

    // abre o arquivo
	FILE * mapFile;
	mapFile = fopen(mapName, "r");
	
    // dimensoes do mapa
	int mapWidth;
	int mapHeight;

    // pega a primeira linha do arq que contem as dimensoes
    fscanf(mapFile, "%d %d", &mapHeight, &mapWidth);
    
    char * mapArr[mapHeight];
    char row[255];

    //aloca endereços de espaços de mem para cada indice de mapArr[]
	for (int i = 0; i < mapHeight; i += 1 ) {
		mapArr[i] = (char*)malloc((mapWidth * sizeof(char)) + 1);
	}

    // itera sobre todas as linhas do arquivo .txt do mapa e guarda uma str para cada indice de mapArr[] em mapArr[]
	int cont = -1;
	while (fgets(row, sizeof(row), mapFile) != NULL) {
		if (cont >= 0)
			strcpy(mapArr[cont], row);
		cont++;
	}

    // print para test
    for (int i = 0; i < mapHeight; i++) {
        printf("%s", mapArr[i]);
    }

    // libera espaços da memoria (alocados na chamada do malloc)
	for (int i = 0; i < mapHeight; i++) {
		free(mapArr[i]);
	}
	
    // fecha o arquivo do mapa
	fclose(mapFile);

    return 0;

}
