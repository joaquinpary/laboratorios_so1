//Pary Joaquin Andres 41786697
#include <stdio.h>
#include <stdlib.h>

struct nodo
{
	char *info;
	struct nodo *sig;
};

struct nodo* raiz = NULL;
struct nodo* fondo = NULL;

void agregarnodo(char *n);
void mostrar();

int main()
{
    agregarnodo("primer elemento");
    agregarnodo("segundo elemento");
    agregarnodo("tercer elemento");
    agregarnodo("cuarto elemento");
    mostrar();
	return 0;
}

void agregarnodo (char *n){
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

void mostrar(){
	struct nodo *recorrido = raiz;
    printf("\nImpimiendo\n");
    while (recorrido!=NULL)
    {
        printf("%s\n",recorrido -> info);
        recorrido = recorrido -> sig;
    }
    printf("\n");
}

