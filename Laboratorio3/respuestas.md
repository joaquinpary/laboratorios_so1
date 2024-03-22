# Pary Joaquin Andres 41786697 

## 4.1. ¿Cuáles son los tipos de file descriptors que podemos encontrar en /proc//fd?

Un file descriptor es un numero que identifica de forma unica un archivo abierto por el sistema. Describe el dato de un recurso y como se puede acceder a ese recurso.

Cuando un proceso realiza una solicitud exitosa para abrir un archivo, el kernel devuelve un file descriptor que apunta a una entrada en la tabla de archivos global del kernel.

En linux, los primeros 3 files descriptor por defecto son:
* "0" Standard Input (stdin)
* "1" Standard Output (stdout)
* "2" Standard Error (stderr)

## 4.2. Suponiendo que un usuario está ejecutando el proceso pid 1212, ¿Es válida la ejecución del siguiente comando desde una terminal nueva? % echo “Hello, world.” >> /proc/1212/fd/1

Si porque cuando se realiza echo "Hello, world", esta intentando imprimir en la Standard Output ("1") del proceso 1212

## 4.3. Qué diferencia hay entre hard y soft limits?

El Hard Limit es el tope para el SoftLimit. El SoftLimit es lo que realmente se aplica para una sesión o proceso. Esto permite al administrador (o usuario) establecer el HardLimit para el uso máximo que desea permitir. Otros usuarios y procesos pueden usar el Soft Limit para autolimitar su uso de recursos a niveles aún más bajos si así lo desean.