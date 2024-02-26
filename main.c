/**
 * This is a basix skeleton code for Assignment 1
 * 
 * It includes the required functions for the assignment. You may want to 
 * create additional help functions, especially for memory allocation
 * 
 * The program should compile via gcc -g -Wall -Werror main.c -o main.o
 * Execute via ./main.o
 * 
 * @author David Vasquez
 * @version 02/16/2024
 **/

/* Don't forget to add any additional required include files! */
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execute_cmd(size_t num_args, char *args[]) {
// Creating child process.
pid_t pid = fork();
    if (pid == -1) {
        // Fork failed.
        perror("fork failed");
        exit(EXIT_FAILURE);

    } else if (pid == 0) {
        // Successful fork
        execvp(args[0], args);
        // Invalid command.
        perror("Command failed");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
}

void parse_cmd(char *input) {
    // Initializing capacity.
    size_t capacity = 20; 

    // Initializing tokens.
    size_t size = 0; 

    char **tokens = malloc(capacity * sizeof(char *));

    // Checking memory allocation.
    if (tokens == NULL) {
       fprintf(stderr, "ERROR Memory allocation failed\n");
       exit(EXIT_FAILURE);
    }
    // create tokens
     char *token = strtok(input," ");

    // While token has a command to process.
    while (token != NULL) {

        // Resize token array.
        if (size >= capacity) {
            // Double capacity.
            capacity *= 2;
            // Temporary token pointer.
            char **temp = realloc(tokens, capacity * sizeof(char *));

            // Error if reallocation fails.
            if (temp == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
            // Tokens new resized array.
            tokens = temp;
        }

         // Allocate memory for token.
        tokens[size] = malloc((strlen(token) + 1) * sizeof(char));
        // Check for errors.
        if (tokens[size] == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        // Add token.
        strcpy(tokens[size], token);
        //move to next token.
        token = strtok(NULL, " ");
        //increase size.
        size++;
    }

    // Pass tokens commands to execute_cmd.
    execute_cmd(size, tokens);

    // Free memory.
    for (size_t i = 0; i < size; i++) {
        free(tokens[i]);
    }
    free(tokens);

}


int main(void){
   char input[LINE_MAX]; 

   printf("*****************************COMMAND SHELL*****************************\n");
    
    //loop to get user inputs(shell).
    while (1) {
        printf("_______________________________________________________________________\n" );
        printf("Enter a command (to exit input: exit):");
        
        // fgets for input.
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Error reading command\n");
            exit(EXIT_FAILURE);
        }
        
        // Deleting trailing.
        input[strcspn(input, "\n")] = '\0';
        
        // Check if the user wants to quit
        if (strcmp(input, "exit") == 0) {
            printf("Leaving...\n");
            printf("_______________________________________________________________________\n" );
            break;
        }
        
        // Calling parsing function with user's command.
        parse_cmd(input);
    }
    printf("***********************************************************************\n");
  return 0;
}
int main(void) {
    
  return 0;
}
