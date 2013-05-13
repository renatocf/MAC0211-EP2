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
#define ISLAND 0.2
#define LENGTH 100
#define LMAX   10
#define RMAX   10
#define SEED   13

/* Intervalo de tempo da animação */
#define INTERVAL 100

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                          ESTRUTURAS/MENSAGENS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* Opções da linha de comando */
typedef struct options {
    /* Opções de configuração */
    float f; /* Fluxo */
    int H;   /* Altura do rio */
    int I;   /* Probabilidade de gerar ilha */
    int L;   /* Largura do rio */
    int l;   /* Limite esquerdo */
    int r;   /* Limite direito  */
    int s;   /* Semente */
    
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
        Options args = { FLUX, HEIGHT, ISLAND, LENGTH, LMAX, RMAX, SEED };
        
    /** ARGUMENTOS ****************************************************/
        func_err = receive_arguments(argc, argv, &args);
        if(func_err) return EXIT_FAILURE;

        if(args.h == 1)
        {
            printf("\n%s\n", help);
            return EXIT_SUCCESS;
        }
        
    /** CONFIGURAÇÕES DO RIO ******************************************/
        river_config_flux    (args.f);
        river_config_size    (args.L, args.H);
        river_config_island  (args.I);
        river_config_margins (args.l, args.r);
        
    /** ANIMAÇÃO DO RIO ***********************************************/
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
    while((opt = getopt(argc, argv, "f:H:I:L:l:r:s:h")) != NONE)
    {
        switch(opt)
        {
            case 'f':
                args->f = atof(optarg); break;
            case 'H':
                args->H = atoi(optarg); break;
            case 'I':
                args->I = atof(optarg); break;
            case 'L':
                args->L = atoi(optarg); break;
            case 'l':
                args->r = atoi(optarg); break;
            case 'r':
                args->s = atoi(optarg); break;
            case 's':
                args->s = atoi(optarg); break;
            case 'h':
                args->h = 1; break;
            case '?':
                printf("Argumento -%c desconhecido\n", optopt);
                return EXIT_FAILURE;
        }
    } /* while */
    return EXIT_SUCCESS;
}
