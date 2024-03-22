Laboratorio N3
# GNU Toolchain y Linux Software
### SOI - FCEFyN - UNC - 2022


## Objetivo
Sentar las bases del diseño e implementación de librerías estáticas y dinámicas.


## Duración
COn el material dado en clase, este laboratorio está diseñado para resolverse entre 8 y 10 horas.


## Actividades
#### 1. Command line arguments


Se debe diseñar e implementar un programa en lengiaje C que al ejecutarse reciba por argumentos:

  1. Si se ejecuta con la opción _-s_ debe ejecutar el ejercicio 1 del Laboratorio 2.

  1. Si se ejecuta con la opción _-a_ debe ejecutar el ejercicio 2 del Laboratorio 2.



#### 2. Static Library

Implementar en el proyecto la librería cJSON, que permita:

  2.1. Si se agrega, junto a las opciones del **punto 1**, la opción _-j_, se debe utilizar la librería estática **cJSON** [1] y mostrar el resultado en dicho formato.
  
#### 3. Dynamic Library

Se debe diseñar e implementar una librería dinámica que actúe como _plugin_, extendiendo las opciones y que permita lo siguiente:

  3.1. Se debe cargar dinámicamente al ejecutarse con la opción -d
  
  3.2. Debe mostrar, utilizando la librería cJSON del punto 2, la información sobre los filesystems soportado por el kernel en uso: /proc/filesystems.
  
#### 4. Cuestionario

  4.1. ¿Cuáles son los tipos de _type descriptors_ que podemos encontrar en _/proc/<id>/fd_?
  
  4.2. Suponiendo que un usuario está ejecutando el proceso _pid 1212_, ¿Es válida la ejecución del siguiente comando desde una terminal nueva?
_% echo “Hello, world.” >> /proc/1212/fd/1_
  
  4.3. Qué diferencia hay entre _hard_ y _soft limits_?



## ¿Qué entregar?
- Se debe trabajar en GitHub Classroom. Es necesario subir los archivos de código en C y generar y subir un archivo markdown (.md) para las respuestas.
- Se debe compilar utilizando *gcc -Wall -Werror -Pedantic*.
- Se debe proveer un Makefile para el construir el proyecto. Ademas, se debe proveer de un target clean para eliminar archivos generados.
- Aclaración: No subir binarios ni archivos de proyectos (eg: Eclipse). Solo archivos .h y .c.
- Se recomienda ir haciendo git push incrementales al repositorio a medida que se desarrolla el trabajo.

## Referencias
[1] cJSON, https://github.com/DaveGamble/cJSON
