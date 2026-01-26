#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>  // open() library
#include <unistd.h> // close() library
#include <errno.h>  // errno library
#include <ctype.h>  // isdigit() library

int main(int argc, char *argv[]) {
    // Check if filename argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file using system call
    int fd = open(argv[1], O_RDONLY);

    // Check for open() error
    if (fd == -1) {
        perror("Error opening file");
        return 1; // Error opening -> exit code 1
    }

    // Convert file descriptor to stream for getline()
    FILE *fp = fdopen(fd, "r");
    if (fp == NULL) {
        perror("Error converting file descriptor");
        close(fd); // Close file
        return 1; // Error converting -> exit code 1
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int total_lines = 0;
    int error_lines = 0;
    int number_lines = 0;

    // Read file line-by-line
    while ((read = getline(&line, &len, fp)) != -1) {
        total_lines++; // Increment line counter

        // "ERROR"-containing line counter
        if (strstr(line, "ERROR") != NULL) {
            error_lines++;
        }

        // Digit-containing line counter
        for (int i = 0; i < read; i++) {
            if (isdigit(line[i])) {
                number_lines++;
                break; // Stop checking this line if a number is found
            }
        }
    }

    free(line); // Cleanup memory
    fclose(fp); // Close file

    // Empty file -> exit code 2
    if (total_lines == 0) {
        return 2;
    }

    // Print final statistics
    printf("File: %s\n", argv[1]);
    printf("Total Lines: %d\n", total_lines);
    printf("Error Lines: %d\n", error_lines);
    printf("Lines with Numbers: %d\n", number_lines);

    return 0; // Success -> exit code 0
}