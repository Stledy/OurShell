#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <ctype.h>
#include <time.h>

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
void myone();  // System information command
void set_shell_env();
char* generate_screenshot_filename();

// Global for shell path
char shell_path[MAX_INPUT];

// Main Function
int main() {
    // Set the shell environment variable
    if (getcwd(shell_path, sizeof(shell_path)) != NULL) {
        strcat(shell_path, "/OurShell");
        setenv("shell", shell_path, 1);
    }
    
    shell_loop();
    return 0;
}

// Shell Loop with current directory in prompt
void shell_loop() {
    char input[MAX_INPUT];
    char cwd[MAX_INPUT];

    while (1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("OurShell [%s]> ", cwd);
        } else {
            printf("OurShell> ");
        }

        if (fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\nExiting...\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;  // Remove newline
        if (strlen(input) > 0) {
            // Convert to lowercase
            for (int i = 0; input[i]; i++) {
                input[i] = tolower((unsigned char)input[i]);
            }
            
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

// Generate unique screenshot filename with timestamp
char* generate_screenshot_filename() {
    static char filename[50];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    strftime(filename, sizeof(filename), "system_info_%Y%m%d_%H%M%S.png", t);
    return filename;
}

// Custom Command: System Information Display
void myone() {
    printf("\n=== System Information ===\n");
    
    // 1. Disk Usage (Memory Space)
    printf("\n💾 Disk Usage:\n");
    system("df -h --output=source,size,used,avail,pcent,target | grep -E 'Filesystem|/$'");
    
    // 2. RAM Information
    printf("\n🧠 RAM Usage:\n");
    system("free -h | awk 'NR==1 || NR==2 {print}'");
    
    // 3. Battery Information
    printf("\n🔋 Battery Status:\n");
    int battery_result = system("upower -i $(upower -e | grep battery) 2>/dev/null | grep -E 'state|time|percentage'");
    if (battery_result != 0) {
        printf("No battery information available\n");
    }
    
    // 4. Take screenshot
    char screenshot_cmd[100];
    char* filename = generate_screenshot_filename();
    snprintf(screenshot_cmd, sizeof(screenshot_cmd), "scrot -d 1 '%s'", filename);
    
    printf("\n📸 Saving screenshot as %s...\n", filename);
    if (system(screenshot_cmd) == 0) {
        printf("Screenshot saved successfully\n");
    } else {
        printf("Failed to take screenshot. Is scrot installed?\n");
    }
    
    printf("\n=== Information display completed ===\n");
}