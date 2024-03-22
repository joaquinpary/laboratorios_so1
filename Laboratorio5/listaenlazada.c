//Pary Joaquin Andres 41786697
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo
{
	char *info;
	struct nodo *sig;
};

struct nodo* raiz = NULL;
struct nodo* fondo = NULL;

int empty();
void addnode(char *n);
void view();
void filter(char *in); 
const char* extraer();

int main()
{
    char in[300];
    fgets(in, sizeof in, stdin);
    filter(in);
    printf("%s\n", extraer());
    printf("%s\n", extraer());
    view();
	return 0;
}
int empty(){
    if (raiz == NULL){
        return 1;
    }
    else{
        return 0;
    }
}
void addnode (char *n){
    struct nodo *aux;
	aux = malloc(sizeof(struct nodo));
	aux -> info = n;
    aux -> sig = NULL;
    if(raiz == NULL){
        raiz = aux;
        fondo = aux;
    }
    else{
        fondo -> sig = aux;
        fondo = aux;
    }
	printf("Se agrego: %s\n",n);
}

void view(){
	struct nodo *recorrido = raiz;
    printf("\nImpimiendo\n");
    while (recorrido!=NULL)
    {
        printf("%s\n",recorrido -> info);
        recorrido = recorrido -> sig;
    }
    printf("\n");
}

void filter(char* in){
    char *aux;
    aux = strtok(in, "\n ");
    while(aux != NULL){
        addnode(aux);
        aux = strtok(NULL, "\n ");
    }
}

const char* extraer(){
    if (!empty())
    {
        char* informacion = raiz->info;
        struct nodo *bor = raiz;
        if (raiz == fondo)
        {
            raiz = NULL;
            fondo = NULL;
        }
        else
        {
            raiz = raiz->sig;
        }
        free(bor);
        return informacion;
    }
    else{
        return NULL;
    }
}
/*
void firstnode(){
    struct nodo *recorrido
}*/
