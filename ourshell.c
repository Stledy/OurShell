#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

#define MAX_INPUT 1024

// Function Prototypes
void shell_loop();
void execute_command(char *input);
void mycd(char *dir);
void myclr();
void mydir(char *dir);
void myenviron();
void myecho(char *message);
void myhelp();
void mypause();
void myone();  // Custom Command

// Main Function
int main() {
    shell_loop();
    return 0;
}

// Shell Loop
void shell_loop() {
    char input[MAX_INPUT];

    while (1) {
        printf("OurShell> ");  // Display shell prompt
        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\nExiting...\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;  // Remove newline character
        if (strlen(input) > 0) {
            execute_command(input);
        }
    }
}

// Execute commands
void execute_command(char *input) {
    if (strncmp(input, "mycd", 4) == 0) {
        mycd(input + 5);
    } else if (strcmp(input, "myclr") == 0) {
        myclr();
    } else if (strncmp(input, "mydir", 5) == 0) {
        mydir(input + 6);
    } else if (strcmp(input, "myenviron") == 0) {
        myenviron();
    } else if (strncmp(input, "myecho", 6) == 0) {
        myecho(input + 7);
    } else if (strcmp(input, "myhelp") == 0) {
        myhelp();
    } else if (strcmp(input, "mypause") == 0) {
        mypause();
    } else if (strcmp(input, "myone") == 0) {
        myone();
    } else if (strcmp(input, "myquit") == 0) {
        printf("Exiting OurShell...\n");
        exit(0);
    } else {
        printf("Command not recognized: %s\n", input);
    }
}

// Internal Command Implementations

void mycd(char *dir) {
    if (dir == NULL || strlen(dir) == 0) {
        printf("%s\n", getcwd(NULL, 0));
    } else if (chdir(dir) != 0) {
        perror("mycd");
    }
}

void myclr() {
    printf("\033[H\033[J"); // ANSI escape sequence to clear screen
}

void mydir(char *dir) {
    if (dir == NULL || strlen(dir) == 0) {
        dir = ".";
    }

    DIR *dp = opendir(dir);
    if (!dp) {
        perror("mydir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL) {
        printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(dp);
}

void myenviron() {
    extern char **environ;
    for (int i = 0; environ[i]; i++) {
        printf("%s\n", environ[i]);
    }
}

void myecho(char *message) {
    printf("%s\n", message);
}

void myhelp() {
    system("more help.txt");
}

void mypause() {
    printf("Press Enter to continue...");
    getchar();
}

// Custom Command: Counts Running Processes
void myone() {
    system("ps -e | wc -l");
}
