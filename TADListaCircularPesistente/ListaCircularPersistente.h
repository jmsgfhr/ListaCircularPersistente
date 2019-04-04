#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#ifndef LISTACIRCULARPERSISTENTE_H_INCLUDED
#define LISTACIRCULARPERSISTENTE_H_INCLUDED

#define TRUE 1
#define FALSE 0

typedef struct mercadoria {
    char nome[40];
    int quantidade;
    double preco;
} Mercadoria;

int lcp_proximo(); // torna corrente o proximo item
int lcp_anterior();
int lcp_corrente(Mercadoria *m); // obtem a mercadoria corrente
int lcp_remove(); // remove o item corrente
int lcp_insere(Mercadoria m);
int lcp_cria();
int lcp_finaliza();
int lcp_exibeListaCircular();


#endif // LISTACIRCULARPERSISTENTE_H_INCLUDED
