#include "init.h"

// função para teste de inicializações
void must_init (bool testInit, const char * description) {
    if (testInit)
        return;
    printf("erro na inicialização de %s\n", description);
    exit(1);
}