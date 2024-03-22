//Pary Joaquin Andres 41786697
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>
#include "cJSON/cJSON.h"
#include "cJSON/cJSON.c"

void *openfile(char* direccion, FILE **archivo);

int main(int argc, char *argv[]){
    int flag_a = 0;
    int flag_s = 0;
    int flag_j = 0;
    int flag_d = 0;
    FILE *archivo = NULL;
    char buffer[BUFSIZ + 1];
    int char_reads;
    char *filtro = ":\n";
    char *str;
    cJSON *cJSONsave = cJSON_CreateObject();
    cJSON *cJSONsavearray =cJSON_CreateArray();
    while(1){
        int option;
        option = getopt(argc, argv, "sajd");
        if (option == -1){
            break;
        }      
        switch(option){
            case 's':
                flag_s = 1;
                break;
            case 'a':
                flag_a = 1;
                break;
            case 'j':
                flag_j = 1;
                break;
            case 'd':
                flag_d = 1;
                break;
        }
    }
    if(flag_s == 1){
        archivo = popen("./string", "r");
        char_reads = fread(buffer, sizeof(char), BUFSIZ, archivo);
        if(char_reads > 0 && flag_j == 0){
            printf("\n%s\n", buffer);
        }
        if(flag_j == 1 && flag_d == 0){
            cJSON *cJSONdata = NULL;
            str = strtok(buffer, filtro); 
            str = strtok(NULL, filtro);
            cJSONdata = cJSON_CreateString(str);          
            cJSON_AddItemToObject(cJSONsave, "Memoria Ram Total", cJSONdata);
            str = strtok(NULL, filtro); 
            str = strtok(NULL, filtro);
            cJSONdata = cJSON_CreateString(str);
            cJSON_AddItemToObject(cJSONsave, "Memoria Ram Libre", cJSONdata);
            str = strtok(NULL, filtro); 
            str = strtok(NULL, filtro);
            cJSONdata = cJSON_CreateString(str);
            cJSON_AddItemToObject(cJSONsave, "Memoria Ram Disponible", cJSONdata);
            str = strtok(NULL, filtro); 
            str = strtok(NULL, filtro);
            cJSONdata = cJSON_CreateString(str);
            cJSON_AddItemToObject(cJSONsave, "Memoria Swap Ocupada", cJSONdata);
            str = strtok(NULL, filtro); 
            str = strtok(NULL, filtro);
            cJSONdata = cJSON_CreateString(str);
            cJSON_AddItemToObject(cJSONsave, "Cpu Model", cJSONdata);
            str = strtok(NULL, filtro); 
            str = strtok(NULL, filtro);
            cJSONdata = cJSON_CreateString(str);
            cJSON_AddItemToObject(cJSONsave, "Cores", cJSONdata);
            str = strtok(NULL, filtro); 
            str = strtok(NULL, filtro);
            cJSONdata = cJSON_CreateString(str);
            cJSON_AddItemToObject(cJSONsave, "Threads por Core", cJSONdata);
            char *str1 = cJSON_Print(cJSONsave);
            printf("%s\n", str1);
        }
    }

    if(flag_a == 1){
        archivo = popen("./arraydin", "r");
        char_reads = fread(buffer, sizeof(char), BUFSIZ, archivo);
        if(char_reads > 0 && flag_j == 0){
            printf("\n%s\n", buffer);
        }
        if(flag_j == 1){
            cJSON *cJSONarray = NULL;
            filtro = " ";
            str = strtok(buffer, filtro);
            cJSONarray = cJSON_CreateString(str); 
            cJSON_InsertItemInArray(cJSONsavearray, 0, cJSONarray);
            int i = 1;
            while(str != NULL){
                str = strtok(NULL, filtro);
                cJSONarray = cJSON_CreateString(str); 
                cJSON_InsertItemInArray(cJSONsavearray, i, cJSONarray);
                i++;
            }
            char *str2 = cJSON_Print(cJSONsavearray);
            printf("%s\n", str2);
        }
    }

    if(flag_d == 1 && flag_j == 0){
        char *dir = "/proc/filesystems";
        void *handle;
        void (*f_filesystems)(const char*);
        handle = dlopen("./dynamiclib.so", RTLD_LAZY);
        if(!handle){
            fprintf(stderr, "Error: %s\n", dlerror());
            exit(EXIT_FAILURE);
        }
        *(void **) (&f_filesystems) = dlsym(handle, "filesystems");
        if(!f_filesystems){
            fprintf(stderr, "Error: %s\n", dlerror());
            dlclose(handle);
        }
        f_filesystems(dir);
        dlclose(handle);
    }
    return 0;
}