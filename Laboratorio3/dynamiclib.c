//Pary Joaquin Andres 41786697
#include <string.h>
#include "cJSON/cJSON.h"
#include "cJSON/cJSON.c"

void filesystems(char* dir){
    cJSON *cJSONsavearray = cJSON_CreateArray();
    cJSON *cJSONarray = NULL;
    char *filtro = " \t\n";
    char *filtro2 = "nodev";
    char *str;
    char c[50];
    FILE *archivo;
    archivo = fopen(dir, "r");
    if(archivo == NULL){
        printf("El archivo no se pudo abrir");
    }
    int i = 0;
    while(fgets(c, sizeof c, archivo) != NULL){
        str = strtok(c, filtro);
        if(!strstr(str, filtro2)){
            cJSONarray = cJSON_CreateString(str);
            cJSON_InsertItemInArray(cJSONsavearray, i, cJSONarray);
        }
        
        str = strtok(NULL, filtro);
        if(str != NULL){
            cJSONarray = cJSON_CreateString(str);
            cJSON_InsertItemInArray(cJSONsavearray, i, cJSONarray);
        }
        
        i++;
    
    }
    char *str2 = cJSON_Print(cJSONsavearray);
    printf("%s\n", str2);
}