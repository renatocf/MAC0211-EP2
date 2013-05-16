/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                              BIBLIOTECAS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "river.h"
#include "strip.h"
#include "getopt.h"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                 MACROS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* Padrões para a gerar o rio */
#define FLUX   73.54
#define HEIGHT 30
#define ISLAND 0.4
#define LENGTH 100
#define LMAX   40
#define RMAX   80
#define SEED   13
#define FREQ   5

/* Intervalo de tempo da animação */
#define INTERVAL 1.4*10e3

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                          ESTRUTURAS/MENSAGENS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* Opções da linha de comando */
typedef struct options
{
    /* Opções de configuração */
    float F; /* Fluxo */
    int H;   /* Altura do rio */
    float i; /* Probabilidade de gerar ilha */
    int L;   /* Largura do rio */
    int l;   /* Limite esquerdo */
    int r;   /* Limite direito  */
    int s;   /* Semente */
    int f;   /* Frequencia com que as ilhas aparecem(em numero de linhas) */

    /* Opções booleanas */
    int h;   /* Ajuda */
} Options;

/* Mensagens */
char help[] = "Ops, ainda não fiz a mensagem de ajuda...\n";

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                               PROTÓTIPOS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
int receive_arguments (int argc, char **argv, Options *args);


/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                  MAIN
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
int main(int argc, char **argv)
{
    /** VARIÁVEIS *****************************************************/
    int func_err;
    clock_t init, end;

    /* Struct com argumentos da linha de comando */
    Options args = { FLUX, HEIGHT, ISLAND, LENGTH, LMAX, RMAX, SEED, FREQ };

    /** ARGUMENTOS ****************************************************/
    func_err = receive_arguments(argc, argv, &args);
    if(func_err) return EXIT_FAILURE;

    if(args.h == 1)
    {
        printf("\n%s\n", help);
        return EXIT_SUCCESS;
    }

    /** CONFIGURAÇÕES DO RIO ******************************************/
    river_config_flux    (args.F);
    river_config_size    (args.L, args.H);
    river_config_island  (args.i, args.f);
    river_config_margins (args.l, args.r);

    /** ANIMAÇÃO DO RIO ***********************************************/
    /* first_line = tstrip_generate(args.L, args.l, args.r, args.f, NO_BASE); */
    river_animation_generate(args.s);

    while(1)
    {
        for(end = init = clock(); end-init < INTERVAL; end = clock());
        system("clear || cls");
        river_animation_iterate();
    }

    /** LIBERAÇÃO DE MEMÓRIA ******************************************/
    river_animation_finish();

    return EXIT_SUCCESS;
}


/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                                 FUNÇÕES
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
int receive_arguments(int argc, char **argv, Options *args)
/* Recebe os argumentos da linha de comando e os
 * armazena na struct correspondente */
{
    char opt; /* int i = 0; */
    while((opt = getopt(argc, argv, "F:H:i:L:l:r:s:f:h")) != NONE)
    {
        switch(opt)
        {
        case 'F':
            args->F = atof(optarg);
            break;
        case 'H':
            args->H = atoi(optarg);
            break;
        case 'i':
            args->i = atof(optarg);
            break;
        case 'L':
            args->L = atoi(optarg);
            break;
        case 'l':
            args->l = atoi(optarg);
            break;
        case 'r':
            args->r = atoi(optarg);
            break;
        case 's':
            args->s = atoi(optarg);
            break;
        case 'f':
            args->f = atoi(optarg);
        case 'h':
            args->h = 1;
            break;
        case '?':
            printf("Argumento -%c desconhecido\n", optopt);
            return EXIT_FAILURE;
        }
    } /* while */
    return EXIT_SUCCESS;
}
