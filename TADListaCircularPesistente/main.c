#include "ListaCircularPersistente.h"

void tela(){
    system("cls");// comando para ambiente Windows
    printf("Lista Encadeada Circular Persistente\n");
    printf("comandos:\n");
    printf("A - anterior\n");
    printf("P - proximo\n");
    printf("I - insere\n");
    printf("R - remove o corrente\n");
    printf("F - finaliza\n\n");
    lcp_exibeListaCircular();
}

int menu(){
    Mercadoria m;
    tela();
    char opcao = getchar();
    if (toupper(opcao) == 'F'){ // F ou f
        return FALSE;
    } else if (toupper(opcao) == 'P'){
        int ok = lcp_proximo(); // torna corrente o proximo item
        if (ok){
            lcp_corrente(&m);
            printf("nome: %s qte: %i preco: %lf\ntecle algo", m.nome, m.quantidade, m.preco);
            getchar();//getcharr();
        }
    } else if (toupper(opcao) == 'R'){
        int ok = lcp_corrente(&m);
        if (ok){
            printf("Remove(s/n) nome: %s qte: %i preco: %lf ?\n", m.nome, m.quantidade, m.preco);
            char tecla = getchar();
            if (toupper(tecla) == 'S'){
                printf("vai remover ... ");
                lcp_remove();
                printf("... removido!\n");
            }
            ok = lcp_corrente(&m);
            if (ok){
                printf("nome: %s qte: %i preco: %lf\ntecle algo", m.nome, m.quantidade, m.preco);
                getchar();
            }
        }
    } else if (toupper(opcao) == 'I'){
        printf("Digite nome, quantidade e preco: \n");
        scanf("%s%i%lf", m.nome, &m.quantidade, &m.preco);
        lcp_insere(m);
        lcp_corrente(&m);
        printf("nome: %s qte: %i preco: %lf\ntecle algo", m.nome, m.quantidade, m.preco);
        getchar();
    }else if (toupper(opcao) == 'A'){
        int ok = lcp_anterior(); // torna corrente o proximo item
        if (ok){
            lcp_corrente(&m);
            printf("nome: %s qte: %i preco: %lf\ntecle algo", m.nome, m.quantidade, m.preco);
            getchar();//getcharr();
        }
    }
    return TRUE;
}

int main(){
    lcp_cria();
    while (menu());
    lcp_finaliza();
    printf("bye!\n");
    return 0;
}
