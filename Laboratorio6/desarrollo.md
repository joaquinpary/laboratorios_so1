# Pary Joaquin Andres 41786697

## Laboratorio 6 MMAP

# Desarrollo

Se definio el **struct Data** con la variables indicadas en el **readme.md**  

```
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

```

Se obtuvo el **file descriptor** del archivo **datos** y se calcula la cantidad de muestras que tiene el archivo, para eso se define **struct stat state** una estructura que contiene una variable **st_size** que retorna el valor en bytes del archivo **datos**. **st_size** retorna 384 entonces se obtuvo que la cantidad de muestras son 3.
Posterior se utilizo **mmap** para allocar los datos del archivo en la memoria:
```
datos = mmap(NULL, state.st_size, PROT_READ , MAP_PRIVATE , fd, 0);
```
Una vez completado se cierra el file descriptor, ya que no se necesitara mas.

```
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
```
Se imprimen los datos de cada muestra que tiene el archivo

```
int buffer = 0;
int promedio;
for(int i = 0; i < cantpulse; i++){
    buffer += datos[i].validSamples;
}
promedio = buffer/cantpulse;
```
Se calcula el promedio de las 3 muestras para despues imprimirlo en pantalla.