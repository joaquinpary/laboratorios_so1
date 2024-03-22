//Pary Joaquin Andres 41786697
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    char *memt = "MemTotal";
    char *memf = "MemFree";
    char *mema = "MemAvailable";
    char *swapf = "SwapFree";
    char cantswapf[30];
    char cantmemt[30];
    char cantmemf[30];
    char cantmema[30];
    int cantmemT, cantmemF, cantmemA, cantswapF;
    
    FILE *archivo;
    char c[500];

    archivo = fopen("/proc/meminfo", "r");
    if (archivo == NULL){
        printf("No se pudo abrir el archivo");
        return 1;
    }
    
    while (fgets(c, sizeof c, archivo) != NULL){
        //printf ("%s", c);
        if(strstr(c, memt)){
            strcpy(cantmemt, c);
        }
        else if(strstr(c, memf)){
            strcpy(cantmemf, c);
        }
        else if(strstr(c, mema)){
            strcpy(cantmema, c);
        }
        else if(strstr(c, swapf)){
            strcpy(cantswapf, c);
        }
    } 
    char aux[20], aux1[20], aux2[20], aux3[20];
    int t = 0;
    int f = 0;
    int a = 0;
    int s = 0;
    for(int i = 0; i <= sizeof cantmemt; i++){
        if(cantmemt[i] > 47 && cantmemt[i] < 58){
            aux[t] = cantmemt[i];
            t++;
        }
        if(cantmemf[i] > 47 && cantmemf[i] < 58){
            aux1[f] = cantmemf[i];
            f++;
        }
        if(cantmema[i] > 47 && cantmema[i] < 58){
            aux2[a] = cantmema[i];
            a++;
        }
        if(cantswapf[i] > 47 && cantswapf[i] < 58){
            aux3[s] = cantswapf[i];
            s++;
        }
    }
    cantmemT = atoi(aux)/1000;
    cantmemF = atoi(aux1)/1000;
    cantmemA = atoi(aux2)/1000;
    cantswapF = atoi(aux3);
    
    printf("Memoria Ram Total: %d MB\n", cantmemT);
    printf("Memoria Ram Libre: %d MB\n", cantmemF);
    printf("Memoria Ram Disponible: %d MB\n", cantmemA);
    printf("Memoria Swap Ocupada: %d KB\n", cantswapF);
    
    fclose(archivo);
    
    char *cpumodel = "model name";
    char *cores = "cpu cores";
    char *threads = "siblings";
    char cpu[100];
    char core[100];
    char thread[100];

    archivo = fopen("/proc/cpuinfo", "r");
    if (archivo == NULL){
        printf("No se pudo abrir el archivo");
        return 1;
    }
    while (fgets(c, sizeof c, archivo) != NULL){
        //printf ("%s", c);
        if(strstr(c, cpumodel)){
            strcpy(cpu, c);
        }
        else if(strstr(c, cores)){
            strcpy(core, c);
        }
        else if(strstr(c, threads)){
            strcpy(thread, c);
        }
    }

    char cpumodelaux[100], coreaux[100], threadaux[100]; 
    int x;
    for(int i = 0; i <= sizeof cpu; i++){
        if(cpu[i] == ':'){
            x = i;
        }
    }
    int j = 0;
    for(int i = x; i <= sizeof cpu; i++){
        cpumodelaux[j] = cpu[i+2];
        coreaux[j] = core[i+1];
        threadaux[j] = thread[i];
        j++;
    }

    printf("Modelo de la CPU: %s", cpumodelaux);
    printf("Cantidad de Cores: %d\n", atoi(coreaux));
    printf("Cantidad de Hilos por Core: %d\n", atoi(threadaux)/atoi(coreaux));

    fclose(archivo);
}
