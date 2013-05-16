#include <stdio.h>
#include <stdlib.h>
#include "test.h"

/* Bibliotecas incluídas para o teste */
#include "list.h"
#include "strip.h"
#include "terrain.h"
#include "river-internal.h"

int analyse_river(int seed)
{
    printf("Análise da estrutura do Jogo:\n");
    printf("-------------------------------------------------------\n");
    printf("\n");
    printf("Configurações do rio\n");
    printf("\n");
    printf("* Fluxo: %.3f\n", Config.flux);
    printf("* Altura da tela: %d\n", Config.height);
    printf("* Largura da tela: %d\n", Config.length);
    printf("* Zona de conforto: %d\n", Config.zone);
    printf("* Probabilidade de gerar ilha: %.3f\n", Config.prob_island);
    printf("* Distância mínima para geração de ilhas: %d\n", Config.freq_island);
    
    return EXIT_SUCCESS;
}
