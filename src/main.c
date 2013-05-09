#include<stdio.h>
#include<stdlib.h>
#include "getopt.h"
#include "list.h"
/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                          ESTRUTURAS/MENSAGENS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

/* Opções da linha de comando */
typedef struct options {
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
    List lista;
    Link nova = malloc(sizeof(Link));
    nova = malloc(sizeof(Link));
    lista = list_init(2);

    printf("\n %d \n", list_empty(lista));


list_insert(lista, nova);
printf("%d\n", list_empty(lista));

list_remove(lista, nova);
printf("@\n");

list_free(lista);
printf("-----");
printf("%d\n", list_empty(lista));






    /** VARIÁVEIS *****************************************************/
/*        int func_err;*/

        /* Struct com argumentos da linha de comando */
/*        Options args = { 0 };*/

    /** ARGUMENTOS ****************************************************/
/*        func_err = receive_arguments(argc, argv, &args);
        if(func_err) return EXIT_FAILURE;

        if(args.h == 1)
        {
            printf("\n%s\n", help);
            return EXIT_SUCCESS;
        }
   */
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
            case 'h':
                args->h = 1; break;
            case '?':
                printf("Argumento -%c desconhecido\n", optopt);
                return EXIT_FAILURE;
        }
    } /* while */
    return EXIT_SUCCESS;
}
