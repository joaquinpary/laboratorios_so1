//Pary Joaquin Andres 41786697
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/io.h>
#include <unistd.h>
#include <stdbool.h>

struct Data{
    unsigned short version;
    unsigned short drxVersion;
    char res1[3];
    double initCW;
    float azimuth;
    float elevation;
    unsigned short idVolumen;
    unsigned short idBarrido;
    unsigned short idCnjunto;
    unsigned short idGrupo;
    unsigned short idPulso;
    bool iniBarrido;
    bool finBarrido;
    bool finGrupo;
    bool inhibido;
    unsigned short validSamples;
    unsigned short nroAdquisicion;
    char res2[1];
    unsigned int nroSecuencia;
    unsigned int readTime_high;
    unsigned long readTime_low;
    char res3[63];
}typedef Data;


int main(int argc, char *argv[]){
    struct stat state;
    Data *datos;
    int fd = open(argv[1], O_RDONLY);
    if(fstat(fd, &state) == -1){
        perror("No se puede obtener el tamanio del archivo\n");
    }
    //cantidad de muestras(pulsos)
    int cantpulse = state.st_size/sizeof(Data);
    datos = mmap(NULL, state.st_size, PROT_READ , MAP_PRIVATE , fd, 0);
    close(fd);
    for(int i = 0; i < cantpulse; i++){
        printf("\nPULSO (%d)\n",i+1);
        printf("version: %d\n", datos[i].version);
        printf("drxVersion; %d\n", datos[i].drxVersion);
        printf("res1: %s\n", datos[i].res1);
        printf("initCW: %f\n", datos[i].initCW);
        printf("azimuth: %f\n", datos[i].azimuth);
        printf("elevation: %f\n", datos[i].elevation);
        printf("idVolumen; %d\n", datos[i].idVolumen);
        printf("idBarrido: %d\n", datos[i].idBarrido);
        printf("idCnjunto: %d\n", datos[i].idCnjunto);
        printf("idGrupo: %d\n", datos[i].idGrupo);
        printf("idPulso: %d\n", datos[i].idPulso);
        printf("iniBarrido; %d\n", datos[i].iniBarrido);
        printf("finBarrido: %d\n", datos[i].finBarrido);
        printf("finGrupo: %d\n", datos[i].finGrupo);
        printf("inhibido: %d\n", datos[i].inhibido);
        printf("validSamples: %d\n", datos[i].validSamples);
        printf("nroAdquisicion; %d\n", datos[i].nroAdquisicion);
        printf("res2: %s\n", datos[i].res2);
        printf("nroSecuencia: %u\n", datos[i].nroSecuencia);
        printf("readTime_high: %u\n", datos[i].readTime_high);
        printf("readTime_low: %lu\n", datos[i].readTime_low);
        printf("res3: %s\n", datos[i].res3);
    }
    int buffer = 0;
    int promedio;
    for(int i = 0; i < cantpulse; i++){
        buffer += datos[i].validSamples;
    }
    promedio = buffer/cantpulse;

    printf("\nCantidad de instancias de muestra: %d\n", cantpulse);
    printf("Promedio de 'validSamples': %d\n", promedio);

    munmap(datos, state.st_size);
    return 0;
}

