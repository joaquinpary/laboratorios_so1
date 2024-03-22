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

void prompt(char **user, char **host);
void *openfile(char* direccion, FILE **archivo);
void print_prompt(char *user, char *host, char *path);
int intcommands(char *command, char *instruccion, char *instruccion2, char *oldpath, char *in, int flag, int flagamp);
void echo(char *text);
int programinv(char* command, char *arg, char *arg2, int flagamp);
int programinvrel(char* command, char *commandrel, char *arg, char *arg2, int flagamp);

int main(int argc, char *argv[]){
    int flag = 0;
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
                if(strstr(in, "&")){
                    flagamp = 1;
                }
                char *caux;
                caux = strdup(c);
                char *txtargs[3];
                txtargs[0] = strtok(c, " \n");
                txtargs[0] = strtok(NULL, " \n");
                txtargs[1] = strtok(NULL, " \n");
                txtargs[2] = strtok(NULL, " \n");
         
                char *txtcommand = strtok(c, " \n");    
                if(flag == 1){
                    oldpath = strdup(path);
                    flag = 0;
                }
                path = getcwd(NULL, 0);
                print_prompt(user, host, path);
                flag = intcommands(txtcommand,txtargs[0], txtargs[1], oldpath, caux, flag, flagamp);
                flagamp = 0;
            }
            fclose(archivo);
            exit(EXIT_SUCCESS);
        }
        else{
            openfile(strtok(dirrel," \n"),&archivo);
            while(fgets(c, sizeof c, archivo) != NULL){
                if(strstr(in, "&")){
                    flagamp = 1;
                }
                char *caux;
                caux = strdup(c);
                char *txtargs[3];
                txtargs[0] = strtok(c, " \n");
                txtargs[0] = strtok(NULL, " \n");
                txtargs[1] = strtok(NULL, " \n");
                txtargs[2] = strtok(NULL, " \n");
                char *txtcommand = strtok(c, " \n");    
                if(flag == 1){
                    oldpath = strdup(path);
                    flag = 0;
                }
                path = getcwd(NULL, 0);
                print_prompt(user, host, path);
                flag = intcommands(txtcommand,txtargs[0], txtargs[1], oldpath, caux, flag, flagamp);
                flagamp = 0;
            }
            fclose(archivo);
            exit(EXIT_SUCCESS);  
        }     
    }
    
    while(1){
        if(flag == 1){
            oldpath = strdup(path);
            flag = 0;
        }
        path = getcwd(NULL, 0);
        print_prompt(user, host, path);
        if(fgets(in, 300, stdin) != NULL){
            char *inaux;
            inaux = strdup(in);
            if(strstr(in, "&")){
                flagamp = 1;
            }
            char *args[3];
            args[0] = strtok(in, " \n");
            args[0] = strtok(NULL, " \n");
            args[1] = strtok(NULL, " \n");
            args[2] = strtok(NULL, " \n");

            char *command = strtok(in, " \n");
            //printf("\nC: %s\nI1: %s\nI2: %s\n",command,args[0],args[1]);
            flag = intcommands(command, args[0],args[1], oldpath, inaux, flag, flagamp);
            flagamp = 0;
        }
    }
}

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
    *archivo = fopen(direccion, "r");
    if(archivo == NULL){ 
        printf("No se pudo abrir el archivo");
        }
    return NULL;
}

void print_prompt(char *user, char *host, char *path){
    printf("\n");
    printf("╭─");
    printf(RED);
    printf("%s@%s~$", user, host);
    printf(WHITE);
    printf("%s\n", path);
    printf("\033[0m");
    printf("╰─$ ");
}

int intcommands(char *command, char *instruccion, char *instruccion2, char *oldpath, char *in, int flag, int flagamp){
    
    if(flagamp == 1){
        char altcommand[500];
        char altcommandrel[500];
        sprintf(altcommandrel,"%s/bin/%s", getenv("PWD"), in);
        sprintf(altcommand, "/bin/%s",in);
        if(strstr(in ,"./")){
            if(strstr(instruccion, "&")){
                programinv(command, NULL, NULL, flagamp);
            }
            else if(strstr(instruccion2, "&")){
                programinv(command, instruccion, NULL, flagamp);
            }
            else{
                programinv(command, instruccion, instruccion2, flagamp);
            }
        }
        else{
            if(strstr(instruccion, "&")){
                programinvrel(strtok(altcommand," \n"), strtok(altcommandrel," \n"), NULL,NULL, flagamp);
            }
            else if(strstr(instruccion2, "&")){
                programinvrel(strtok(altcommand," \n"), strtok(altcommandrel," \n"), instruccion,NULL, flagamp);
            }
            else{
                programinvrel(strtok(altcommand," \n"), strtok(altcommandrel," \n"), instruccion,instruccion2, flagamp);
            }
        }
    }
    
    else{
    if(strcmp(command, "cd") == 0){
        if(chdir(strtok(instruccion, "\n")) == 0){
            flag = 1;
            return flag;
        }
        else{
            printf("La direccion ingresada es incorrecta\n");
        }    
    }
    else if(strstr(command, "clr")){
        printf(CLC);
    }
    else if(strstr(command, "echo")){
        echo(strtok(instruccion, "\n"));
    }
    else if(strstr(command, "quit")){
        exit(EXIT_SUCCESS);
    }
    else if(strstr(command, "cd-")){
        printf("%s",oldpath);
    }
    else{
        
        int status;
        char altcommand[500];
        char altcommandrel[500];
        sprintf(altcommandrel,"%s/bin/%s", getenv("PWD"), in);
        sprintf(altcommand, "/bin/%s",in);
        
        if(strstr(in ,"./")){
            programinv(command, instruccion, instruccion2, flagamp);
            wait(&status);
        }
        else{
            programinvrel(strtok(altcommand," \n"), strtok(altcommandrel," \n"), instruccion, instruccion2, flagamp);
            wait(&status);
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

int programinv(char* command, char* arg, char *arg2, int flagamp){
    if(flagamp){job++;}
	pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0) {
		return child_pid;
	}
	else {
        if(flagamp){
            printf("[%d] %d\n",job ,getpid());
            job--;
        }
		execl(command, command, arg ,arg2, NULL);
        fprintf (stderr, "Ocurrio un error en execl\n");
		abort ();
	}
}

int programinvrel(char* command, char *commandrel, char* arg, char *arg2, int flagamp){
    if(flagamp){job++;}
	pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0) {
		return child_pid;
	}
	else {   
        if(flagamp){
            printf("[%d] %d\n",job ,getpid());
            job--;
        } 
		if(execl(command, command, arg , arg2, NULL) && 
        execl(commandrel, commandrel, arg , arg2, NULL) != 0){
            fprintf (stderr, "Ocurrio un error en execl\n");
        }
		abort ();
	}
}