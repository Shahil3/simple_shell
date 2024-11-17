#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *history[MAX_HISTORY];
int history_count = 0;

// Add a command to the history
void add_to_history(char *command) {
    // If we have reached the max history limit, remove the oldest entry
    if (history_count >= MAX_HISTORY) {
        free(history[0]);  // Free the oldest command
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i];  // Shift history up
        }
        history_count--;
    }

    // Allocate memory and store the new command in history
    history[history_count] = strdup(command);  // Duplicate the command string
    history_count++;
}

// Print the command history
void print_history(void) {
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

// Save the history to a file
void save_history(void) {
    FILE *history_file = fopen(".simple_shell_history", "w");  // Open history file

    if (history_file == NULL) {
        perror("Unable to save history");
        return;
    }

    for (int i = 0; i < history_count; i++) {
        fprintf(history_file, "%s\n", history[i]);
    }

    fclose(history_file);  // Close the file after writing
}

// Load the history from a file
void load_history(void) {
    FILE *history_file = fopen(".simple_shell_history", "r");  // Open history file for reading

    if (history_file == NULL) {
        return;  // No history file found, nothing to load
    }

    char line[1024];
    while (fgets(line, sizeof(line), history_file) != NULL) {
        line[strcspn(line, "\n")] = 0;  // Remove newline character
        add_to_history(line);  // Add each line to history
    }

    fclose(history_file);  // Close the file after reading
}

