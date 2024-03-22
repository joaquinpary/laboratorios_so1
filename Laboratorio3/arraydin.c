//Pary Joaquin Andres 41786697
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void mayuscula(char* srt);

int main(){
    //FILE *archivo;
    char c[500];
    char **arraydin = NULL;
    char *array;
    char *filtro = " ";

    FILE *archivo;
    archivo = fopen("/proc/version", "r");
    if (archivo == NULL){
        printf("No se pudo abrir el archivo");
        return 1;
    }
    //Obtiene la cadena de caracteres hasta que haya un "\n" y luego lo copia a una variable
    fgets(c, sizeof c, archivo);
    //Retorna la cadena de caracteres hasta que encuentre uno de los caracteres que se asigno en "filtro"
    array = strtok(c, filtro);
    //printf("%s",array);
    int p = 0;
    while(array != NULL){
        p++;
        arraydin = (char**) realloc(arraydin, p*sizeof(array));
        arraydin[p-1] = array;
        array = strtok(NULL, filtro);
    }

    for(int i = 0; i < p; i++){
        mayuscula(arraydin[i]);  
    }
    for(int i = 0; i <= p-1; i++){
        printf("%s ", arraydin[i]);
    }  
    free(arraydin); 
    fclose(archivo);
}

void mayuscula(char *str){
    int i = 0;
    while(str[i]){
        if(str[i] >= 'a' && str[i] <= 'z'){
            str[i]-=32;
        }
        i++;
    }
}
