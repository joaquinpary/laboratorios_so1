3.1)
Para utilizar el typedef junto a un struct primero debo declara un typedef y declarar al lado el struct,testo nos ayuda a reducir la cantidad de codigot escrito y dejar un codigo mas limpio.
Puedo usarlo de dos formas:

-------Ejemplo1

#include<stdio.h>

struct Point{
  int x;
  int y;
};
typedef struct Point Point;
int main() {
    Point p1;
    p1.x = 1;
    p1.y = 3;
    printf("%d \n", p1.x);
    printf("%d \n", p1.y);
    return 0;
}


-------Ejemplo2

#include<stdio.h>

typedef struct Point{
  int x;
  int y;
} Point;
int main() {
    Point p1;
    p1.x = 1;
    p1.y = 3;
    printf("%d \n", p1.x);
    printf("%d \n", p1.y);
    return 0;
}

Padding es la insercion de bits en una estructura a la hora de almacenarla en la memoria, tiene
como fin reducir el tiempo necesario para leerla y una desventaja que consume mas memoria

Packing es lo contrario al Padding, es decir la omision de los bits de padding. Las Estructuras en este caso no estan alineadas, sino que estan empaquetadas para reducir al maximo de consumo de espacion en la memoria, su desventaja es la perdida de rendimiento

3.2)

Es el espacio en Bytes que ocupa esa estructura en la memoria:
BaseData: esta estructura tiene 20 Bytes de los cuales en 14 se utilizan para almacenar informacion y 6 de padding
-3 char de 1 Bytes = 3 Bytes
-2 unsignded short int de 2 Bytes = 4 Bytes
-1 int de 4 Bytes = 4 Bytes
-1 string de 3 Bytes = 3 Bytes

ReorderData: esta estructura ocupa 16 Bytes porque esta mejor ordenado, la asignacion de memoria se hace secuencial por lo que si tengo agrupadas las variables del mismo tipo se reducida el espacio que ocupa una estructura, tiene 14 Bytes y 2 Bytes de padding
-3 char de 1 Bytes = 3 Bytes
-2 unsignded short int de 2 Bytes = 4 Bytes
-1 int de 4 Bytes = 4 Bytes
-1 string de 3 Bytes = 3 Bytes

ExtendedData: esta estructura tiene 24 Bytes asignados de los cuales 20 tiene datos y 4 de padding
-3 char de 1 Bytes = 3 Bytes
-3 unsignded short int de 2 Bytes = 6 Bytes
-1 int de 4 Bytes = 4 Bytes
-1 string de 3 Bytes = 3 Bytes
-1 long unsigned int de 4 Bytes = 4 Bytes

BaseDataPacked: en esta estructura al estar empaquetada consume los 14 Bytes de datos y ninguno de padding
-3 char de 1 Bytes = 3 Bytes
-2 unsignded short int de 2 Bytes = 4 Bytes
-1 int de 4 Bytes = 4 Bytes
-1 string de 3 Bytes = 3 Bytes


limit y limit_aux son expresiones similares para asignacion de la posicion a los punteros en 
limit obtiene la direccion de data y le suma 20 que es el tamanio en Bytes de la estructura
y en limit_aux obtiene la direccion de data mas un data mas

Obtiene los valores en hexa de cada Byte de la esctructura data:
-byte 00	char a
-byte 01	char b
-byte 02	padding
-byte 03	padding
-byte 04	int x
-byte 05	int x
-byte 06	int x
-byte 07	int x
-byte 08	unsigned short int y
-byte 09	unsigned short int y
-byte 10	char c
-byte 11	padding
-byte 12	unsigned short int z
-byte 13	unsigned short int z
-byte 14	char d[0]
-byte 15	char d[1]
-byte 16	char d[2]
-byte 17	padding
-byte 18	padding
-byte 19	padding