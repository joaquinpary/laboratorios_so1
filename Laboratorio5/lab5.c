#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define CLC "\033[H\033[J"

int job = 0;
pid_t child_pid;

void prompt(char **user, char **host);
void *openfile(char* direccion, FILE **archivo);
void printprompt(char *user, char *host, char *path);
int intcommands(char *command, char **arglist, char *oldpath, int flagdir, int flagamp);
void echo(char *text);
int programinv(char* command, char **arglist, int flagamp);
int programinvrel(char* command, char *commandrel, char **arglist, int flagamp);
void handler(int sig);
void handler_sigchld(int sig);
int listcommands(char *in, char *oldpath, int flagdir, int flagamp);
void pipelist(char *in);
void pipefunction(char* command1, char** arglist1, char *command2, char **arglist2);
void callpipe(char *in1, char *in2);
void ioredirlist(char *in, char *file);
void ioredir(char *command, char **arglist, char *file, int flagin, int flagout);

int main(int argc, char *argv[]){
    signal(SIGINT, handler);
    signal(SIGTSTP, handler);
    signal(SIGQUIT, handler);
    signal(SIGCHLD, handler_sigchld);
    int flagdir = 0;
    int flagamp = 0;
    char *user;
    char *host;
    char *oldpath;
    char *path;
    prompt(&user, &host);
    char in[300];
    
    if(argc > 1){
        FILE *archivo = NULL;
        char dir[300];
        char dirrel[300];
        sprintf(dir, "%s", argv[1]);
        sprintf(dirrel, "%s/%s", getenv("PWD"), argv[1]);
        memmove(dir, dir+1, strlen(dir));
        memmove(dirrel, dirrel+1, strlen(dirrel));
        openfile(strtok(dir," \n"), &archivo);
        char c[300];
        
        if(archivo != NULL){
            while(fgets(c, sizeof c, archivo) != NULL){
                if(strstr(c, "&")){
                    flagamp = 1;
                }
  
                if(flagdir == 1){
                    oldpath = strdup(path);
                    flagdir = 0;
                }
                path = getcwd(NULL, 0);
                printprompt(user, host, path);
                if(strstr(c, "|")){
                    pipelist(c);
                }
                else if((strstr(c, "<")) || strstr(c, ">")){
                    char *redirin = strdup(c);
                    ioredirlist(strtok(c, "<>"), redirin);
                }
                else{
                    flagdir = listcommands(c, oldpath, flagdir, flagamp);
                }          
                flagamp = 0;
            }
            fclose(archivo);
            exit(EXIT_SUCCESS);
        }
        else{
            openfile(strtok(dirrel," \n"),&archivo);
            while(fgets(c, sizeof c, archivo) != NULL){
                if(strstr(c, "&")){
                    flagamp = 1;
                }
                if(flagdir == 1){
                    oldpath = strdup(path);
                    flagdir = 0;
                }
                path = getcwd(NULL, 0);
                printprompt(user, host, path);
                if(strstr(c, "|")){
                    pipelist(c);
                }
                else if((strstr(c, "<")) || strstr(c, ">")){
                    char *redirin = strdup(c);
                    ioredirlist(strtok(c, "<>"), redirin);
                }   
                else{
                    flagdir = listcommands(c, oldpath, flagdir, flagamp);
                }       
                flagamp = 0;
            }
            fclose(archivo);
            exit(EXIT_SUCCESS);  
        }     
    }
    
    while(1){
        if(flagdir == 1){
            oldpath = strdup(path);
            flagdir = 0;
        }
        path = getcwd(NULL, 0);
        printprompt(user, host, path);

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
    }
}
/*se encarga de recibir la cadena de string ingresado por el teclado o
mediante un archivo de texto, creando un array dinamico y mandandolo a otra funcion
que se encargara de la ejecucion de los comandos*/

int listcommands(char *in, char *oldpath, int flagdir, int flagamp){
    char **commands = NULL;
    char *ins, *command;
    ins = strtok(in, "\n ");
    command = strdup(ins);
    int p = 0;
    while(ins != NULL){
        p++;  
        commands = (char**) realloc(commands, p*sizeof(ins));
        commands[p-1] = ins;
        ins = strtok(NULL, "\n ");
        
    }
    if(flagamp){
        commands[p-1] = NULL;
    }
    else{
        p++;
        commands = (char**) realloc(commands, p*sizeof(ins));
        commands[p-1] = NULL;       
    }
    flagdir = intcommands(command, commands, oldpath, flagdir, flagamp);
    free(commands);
    return flagdir;
}
/*procesa la informacion necesaria para poder imprimir el prompt*/
void prompt(char **user, char **host){
    FILE *archivo;
    openfile("/proc/sys/kernel/hostname", &archivo);
    char c[30];
    fgets(c, sizeof c, archivo);
    char *filtro = strtok(c, "\n");
    fclose(archivo);
    *host = strdup(filtro);
    *user = getlogin();
}

void *openfile(char* direccion, FILE **archivo){
    if((*archivo = fopen(direccion,"r")) == NULL){ 
        printf("No se pudo abrir el archivo");
    }
}
/*imprime el prompt*/
void printprompt(char *user, char *host, char *path){
    printf("\n");
    printf("╭─");
    printf(RED);
    printf("%s@%s~$", user, host);
    printf(WHITE);
    printf("%s\n", path);
    printf("\033[0m");
    printf("╰─$ ");
}
/*funcion que se encarga de ejecutar los comandos ingresados*/
int intcommands(char *command, char **arglist, char *oldpath, int flagdir, int flagamp){
    if(flagamp == 1){
        //printf("\n pre flagback = %d\n",flagamp);
        char altcommand[500];
        char altcommandrel[500];
        sprintf(altcommandrel,"%s/bin/%s", getenv("PWD"), command);
        sprintf(altcommand, "/bin/%s",command);
        if(strstr(command ,"./")){   
            programinv(command, arglist, flagamp);
            printf("[%d] %d\n",job ,getpid());
            job--;
        }
        else{
            programinvrel(strtok(altcommand," \n"), strtok(altcommandrel," \n"), arglist, flagamp);
            printf("[%d] %d\n",job ,getpid());
            job--;
            }  
    }
    
    else{
    if(strcmp(command, "cd") == 0){
        //printf("en cd\n");
        if(chdir(arglist[1]) == 0){
            flagdir = 1;
            return flagdir;
        }
        else{
            printf("La direccion ingresada es incorrecta\n");
        }    
    }
    else if(strstr(command, "clr")){
        //printf("en clc\n");
        printf(CLC);
    }
    else if(strstr(command, "echo")){
        //printf("en echo\n");
        echo(strtok(arglist[1], "\n"));
    }
    else if(strstr(command, "quit")){
        //printf("en quit\n");
        exit(EXIT_SUCCESS);
    }
    else if(strstr(command, "cd-")){
        chdir(strtok(oldpath, "\n"));
        //printf("en cd-\n");
        //printf("%s",oldpath);
    }
    else{       
        //printf("en execl\n");
        int status;
        char altcommand[500];
        char altcommandrel[500];
        sprintf(altcommandrel,"%s/bin/%s", getenv("PWD"), command);
        sprintf(altcommand, "/bin/%s",command);
        
        if(strstr(command ,"./")){
            programinv(command, arglist, flagamp);
            waitpid(child_pid, &status, WUNTRACED);
        }
        else{
            programinvrel(strtok(altcommand," \n"), strtok(altcommandrel," \n"), arglist, flagamp);
            waitpid(child_pid, &status, WUNTRACED);
        }
        }
    }
    return 0;
}
void echo(char *text){
    for(int i = 0; i < strlen(text); i++)
    {
        if(*(text+i) != ' ' || *(text+i+1) != ' ')
        {
            printf("%c", *(text+i));
        }
    }
    printf("\n");
}

int programinv(char* command, char** arglist, int flagamp){
    //printf("\n flagback = %d\n",flagamp);
    if(flagamp){job++;}
	//pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0) {
		return child_pid;
	}
	else {     
		execvp(command, arglist);
        fprintf (stderr, "Ocurrio un error en execvp\n");
		exit(0);
	}
}

int programinvrel(char* command, char *commandrel, char** arglist, int flagamp){
    //printf("\n flagback = %d\n",flagamp);
    if(flagamp){job++;}
	//pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0) {
		return child_pid;
	}
	else {   
		if(execvp(command, arglist) && 
        execvp(commandrel, arglist) != 0){
            fprintf (stderr, "Ocurrio un error en execvp\n");
        }
		exit(0);
	}
}

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

void pipelist(char *in){
    //int pipecount = 0;
    char **pipecommands = NULL;
    char *inaux;
    inaux = strtok(in, "|\n");
    int p = 0;
    while(inaux != NULL){
        //printf("en while\n");
        p++;
        pipecommands = (char**) realloc(pipecommands, p*sizeof(inaux));
        pipecommands[p-1] = inaux;
        if(p >= 2){
            memmove(pipecommands[p-1], pipecommands[p-1]+1, strlen(pipecommands[p-1]));
        }
        inaux = strtok(NULL, "|\n");
    }
    callpipe(pipecommands[0], pipecommands[1]);
}

void callpipe(char *in1, char *in2){
    printf("%s\n%s\n",in1,in2);
    char **commands1 = NULL;
    char *ins1, *command1;
    ins1 = strtok(in1, "\n ");
    command1 = strdup(ins1);
    int p = 0;
    while(ins1 != NULL){
        p++;  
        commands1 = (char**) realloc(commands1, p*sizeof(ins1));
        commands1[p-1] = ins1;
        ins1 = strtok(NULL, "\n ");
        
    }
    p++;
    commands1 = (char**) realloc(commands1, p*sizeof(ins1));
    commands1[p-1] = NULL;       

    char **commands2 = NULL;
    char *ins2, *command2;
    ins2 = strtok(in2, "\n ");
    command2 = strdup(ins2);
    p = 0;
    while(ins2 != NULL){
        p++;  
        commands2 = (char**) realloc(commands2, p*sizeof(ins2));
        commands2[p-1] = ins2;
        ins2 = strtok(NULL, "\n ");
        
    }
    p++;
    commands2 = (char**) realloc(commands2, p*sizeof(ins2));
    commands2[p-1] = NULL;       
    pipefunction(command1, commands1, command2, commands2);
    free(commands1);
    free(commands2);
}

void pipefunction(char* command1, char** arglist1, char *command2, char **arglist2){
    int pipefd[2];
    if(pipe(pipefd) == -1){
        perror("Error en pipe");
        exit(1);
    }
    if(fork() == 0){
        close(STDOUT_FILENO);
        dup(pipefd[1]);
        close(pipefd[0]);
        close(pipefd[1]);

        execvp(command1, arglist1);
        perror("Ocurrio un error en execvp");
        exit(1);
    }
    if(fork() == 0){
        close(STDIN_FILENO);
        dup(pipefd[0]);
        close(pipefd[1]);
        close(pipefd[0]);

        execvp(command2, arglist2);
        perror("Ocurrio un error en execvp");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(0);
    wait(0);
}

void ioredirlist(char *in, char *file){
    int flagin = 0;
    int flagout = 0;
    if(strstr(file, "<")){flagin = 1;}
    if(strstr(file, ">")){flagout = 1;}
    char **commands = NULL;
    char *ins, *command;
    ins = strtok(in, "\n ");
    command = strdup(ins);
    int p = 0;
    while(ins != NULL){
        p++;  
        commands = (char**) realloc(commands, p*sizeof(ins));
        commands[p-1] = ins;
        ins = strtok(NULL, "\n ");
        
    }
    p++;
    commands = (char**) realloc(commands, p*sizeof(ins));
    commands[p-1] = NULL;
    
    char *fileio = strtok(file, "<>");
    fileio = strtok(NULL, "\n");
    ioredir(command, commands, fileio, flagin, flagout);
}

void ioredir(char *command, char **arglist, char *file, int flagin, int flagout){
    printf("ioredir\n");
    memmove(file, file+1, strlen(file));
    int status;
    if((child_pid = fork()) < 0){
        perror("Error en fork");
    }
    else if(child_pid == 0){
        if(flagin){
            int fd0 = open(file, O_RDONLY, 0);
            if(fd0 == -1){
                fprintf(stderr, "Error al abrir %s\n", file);
                exit(1);
            }
            dup2(fd0, STDIN_FILENO);
            close(fd0);
            }
        if(flagout){
            int fd1 = creat(file, 0644); // 0644 = rw-rw-rw-
            if(fd1 == -1){
                fprintf(stderr, "Error opening %s\n", file);
                exit(1);
            }
            dup2(fd1, STDOUT_FILENO); // stdout
            close(fd1);
        }

        execvp(command, arglist);
        exit(1);
    }
    else{
        wait(&status);
    }
}