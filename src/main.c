/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                              BIBLIOTECAS     
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
#include<stdio.h>
#include<stdlib.h>

#include "river.h"
#include "getopt.h"

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
    int L;   /* Largura do rio */
    int l;   /* Limite esquerdo */
    int r;   /* Limite direito  */
    int s;   /* Semente */
    
    /* Opções booleanas */
    int h;   /* Ajuda */
} Options;

#define FLUX   
#define HEIGHT 30
#define LENGTH 100
#define LMAX   10
#define RMAX   10
#define SEED   13

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

        /* Struct com argumentos da linha de comando */
       Options args = { 0, PI, 0.4 };

    /** ARGUMENTOS ****************************************************/
        func_err = receive_arguments(argc, argv, &args);
        if(func_err) return EXIT_FAILURE;

        if(args.h == 1)
        {
            printf("\n%s\n", help);
            return EXIT_SUCCESS;
        }

        /*
         *
         * Área para o restante do nosso main
         *
         */

   /* return EXIT_SUCCESS;*/
   return 0;
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
    while((opt = getopt(argc, argv, "h")) != NONE)
    {
        switch(opt)
        {
            case 'f';
                args->f = atof(optarg); break;
            case 'H';
                args->H = atoi(optarg); break;
            case 'L';
                args->L = atoi(optarg); break;
            case 'l';
                args->r = atoi(optarg); break;
            case 'r';
                args->s = atoi(optarg); break;
            case 's';
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
