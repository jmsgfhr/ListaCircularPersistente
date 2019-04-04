#include "ListaCircularPersistente.h"

// ATENCAO: a estrutura Node que permite a lista encadeada
// nao esta´ disponivel
// para o programador que vai usar a TAD
typedef struct node {
    Mercadoria m;
    struct node *proximo;
    struct node *anterior;
} Node;

Node *corrente;

// ATENCAO: as funcoes para persistencia usando arquivos
// nao estao disponiveis
// para o programador que vai usar a TAD
void recupera(char *filename);
void grava(char *filename);

int lcp_cria(){
    corrente=NULL;
    recupera("lcp.bin");
    return TRUE;
}

int lcp_exibeListaCircular(){
    if (corrente == NULL) {printf("vazia\n"); return FALSE;}
    Node * p1 = corrente;
    Node * p2 = corrente->proximo;
    printf("corrente: %s->", corrente->m.nome);
    while (p2 != corrente){
        p1 = p2;
        printf("%s->", p2->m.nome);
        p2 = p1->proximo;
    }
    printf("\n");
    return TRUE;
}


int lcp_proximo(){
    if (corrente == NULL) {printf("vazia"); return FALSE;}
    corrente = corrente->proximo;
    return TRUE;
}

int lcp_anterior(){
    if (corrente == NULL) {printf("vazia"); return FALSE;}
    corrente = corrente->anterior;
    return TRUE;
}

int lcp_corrente(Mercadoria *m){
    if (corrente == NULL) {printf("vazia"); return FALSE;}
    *m = corrente->m;
    return TRUE;
}

int lcp_remove(){
    if (corrente == NULL) {printf("vazia"); return FALSE;}
    // ultimo elemento
    if (corrente->proximo == corrente){
        free(corrente);
        corrente = NULL;
        return TRUE;
    }
    // percorro toda a lista circular para encontrar o anterior     Node *anterior = corrente;
    Node * p1 = corrente->proximo;
    /*Node * p2 = corrente->proximo;
    while (p2 != corrente){
        p1 = p2;
        p2 = p1->proximo;
    }
    p1->proximo = corrente->proximo;*/
    corrente->anterior->proximo=corrente->proximo;
    corrente->proximo->anterior=corrente->anterior;
    free(corrente);
    corrente = p1;
    return TRUE;
}

int lcp_insere(Mercadoria m){
    Node *nd = (Node *) malloc(sizeof(Node));
    nd->m = m;
    // favor alterar para inserir ordenadamente
    // por enquanto nao

    if (corrente == NULL){
        nd->proximo = nd;
        nd->anterior=nd;
        corrente = nd;
        return TRUE;
    }
    // funciona para 1,2 ou N elementos (ja fiz o desenho)
    Node *aux = corrente->proximo ;
    nd->anterior=corrente;
    corrente->proximo = nd;
    nd->proximo = aux;
    corrente = nd;
    corrente->proximo->anterior=nd;//define que o ultimo->prox(que é o primeiro)->anterior= ao ultimo(primeiro->anterior=ultimo)

    return TRUE;

}



// observe que estas duas funcoes a seguir nao sao disponibilizadas pelo TAD
void liberaMemoria(Node *cur);
void liberaMemoriaRecursivamente(Node *cur, Node *prox);

int lcp_finaliza(){
    // grava a lista atual
    grava("lcp.bin");
    // libera memoria
    if(corrente == NULL) return TRUE;
    //liberaMemoria(corrente);
    liberaMemoriaRecursivamente(corrente, corrente->proximo);
    corrente=NULL;
    return TRUE;
}






void liberaMemoria(Node *cur){
    Node * p1 = cur;
    Node * p2 = cur->proximo;
    while (p2 != cur){
        //p1 = p2;
        Node *aux = p2->proximo;
        printf("libera %s\n", p2->m.nome);
        free(p2);
        p1->proximo = aux;
        p2 = p1->proximo;
    }
    printf("libera corrente %s\n", p2->m.nome);
    free(p2);
}

void liberaMemoriaRecursivamente(Node *cur, Node *prox){
    //printf("debug %s %s\n", cur->m.nome, prox->m.nome);
    if (prox == cur){
        printf("libera corrente %s\n", cur->m.nome);
        free(cur);
    } else {
        liberaMemoriaRecursivamente(cur, prox->proximo);
        printf("libera %s\n", prox->m.nome);
        free(prox);
    }
}









void grava(char *filename){
    if (corrente == NULL) {printf("vazia"); return;}
    FILE *fp;
    fp = fopen(filename, "w");// abre para "write"
    Node *aux = corrente->proximo; // para que o ultimo seja o corrente
    while (aux != corrente){
        fwrite(&aux->m , sizeof(Mercadoria) , 1 , fp );
        /*fprintf(fp, "%s %i %lf\n", aux->m.nome, aux->m.quantidade, aux->m.preco);*/
        aux = aux->proximo;
    }
    // grava o corrente
    fwrite(&aux->m , sizeof(Mercadoria) , 1 , fp );
    fclose(fp);
}

void recupera(char *filename){
    Mercadoria m;
    FILE *fp;
    if((fp = fopen(filename, "r"))==NULL)
       return 0;// abre para "read"
    while (!feof(fp)){
        int item=fread(&m , sizeof(Mercadoria) , 1 , fp);
        if(item>0)
            lcp_insere(m);
    }
    fclose(fp);
}


