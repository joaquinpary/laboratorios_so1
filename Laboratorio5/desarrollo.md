# Pary Joaquin Andres 41786697

## Laboratorio 5 MyShellAdvance

### Desarrollo
Cuando se inicia el programa lo primero que hara sera imprimir el prompt, para eso se utiliza **prompt(&user, &host)** que obtiene el usuario y el host para luego imprimirlo con **printprompt(user, host, path)**. Si se ingresa un argumento al ejecutar el programa se podra utilizar comandos desde un archivo de texto, el resto de la implementaciones se utilizan para ambas partes:

```
int listcommands(char *in, char *oldpath, int flagdir, int flagamp);
```
Se encarga de procesar la entrada ya sea por teclado o por el archivo creando un array dinamico e invocar la siguente funcion:
```
int intcommands(char *command, char **arglist, char *oldpath, int flagdir, int flagamp);
```
Recibe los parametros pasados de la funcion anterior y soporta los siguientes comando:
* cd **arg**
* cd-
* clr
* echo **text**
* quit
* **command** **arg1** **arg2**
* **command** **arg1** **arg2** **&**

Tambien soporta paths relativos y absolutos en caso de requerirlos para ejecutar comandos que no estan implementados, para ello se utiliza:
```
int programinv(char* command, char **arglist, int flagamp);
int programinvrel(char* command, char *commandrel, char **arglist, int flagamp);
```
#### Implementaciones Lab5
Si se quiere finalizar un proceso en ejecucion se podra con **Ctrl+C**, **Ctrl+Z**, **Ctrl+\**. Correspondido al siguente codigo:
```
signal(SIGINT, handler);
signal(SIGTSTP, handler);
signal(SIGQUIT, handler);
signal(SIGCHLD, handler_sigchld);
```
Que se encargara de mandar invocar la funcion handler:
```
void handler(int sig){
    if (child_pid == 0)
    {
        return;
    }
    else{
        kill(child_pid, sig);
    }
}

void handler_sigchld(int sig){
    if (sig != SIGCHLD){
        return;
    }
    waitpid(-1, NULL, WNOHANG); // clean zombies
}
```
Estan funciones se encargaran de mandar seniales para terminar el proceso y eliminar procesos zombies.

El **pipe** o **i/o redirection** sera ejecutado de manera diferente:
```
if(strtok(fgets(in, 300, stdin),"\n") != NULL){

    if(strstr(in, "&")){
        flagamp = 1;
    }
    if(strstr(in, "|")){
        pipelist(in);
    }
    else if((strstr(in, "<")) || strstr(in, ">")){
        char *redirin = strdup(in);
        ioredirlist(strtok(in, "<>"), redirin);
    }
    else{
        flagdir = listcommands(in, oldpath, flagdir, flagamp);
    }    
    flagamp = 0;
}
```
Si se reconoce que en la entrada hay un **|** o **<>** llamara a funciones diferentes que se encargaran de separar la entrada por comandos-argumentos y eliminar el simbolos **|<>** respectivamente
```
void callpipe(char *in1, char *in2);
void ioredir(char *command, char **arglist, char *file, int flagin, int flagout);
```
Cada una de la opciones tendra su funcion por separado para realizar su implementacion

#### Cambios respecto al Laboratorio4

Se corrigio el error que no permitia no ingresar un comando, mandando un coredump. Se cambio el **execl** por un **execvp** para permitir el ingreso de varios argumentos, para eso tambien se cambio el array estatico por uno dinamico.

#### Respuesta

El mecanismo de pipe se encuentra en /proc, en los procesos que se estan comunicando. 