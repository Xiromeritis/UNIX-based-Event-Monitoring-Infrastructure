#include <stdio.h>  // printf(), fprintf() & perror() library
#include <stdlib.h> // free() library
#include <string.h> // strstr() library
#include <fcntl.h>  // open() & O_RDONLY library
#include <unistd.h> // close() library
#include <ctype.h>  // isdigit() library

// Colors
#define RED     "\033[0;31m"
#define YELLOW  "\033[1;33m"
#define NC   "\033[0m"   // No color (reset)

int main(const int argc, char *argv[]) {
    // Check if filename argument is provided
    if (argc != 2) {
        fprintf(stderr, "%sUsage: %s <filename>%s\n", YELLOW, argv[0], NC);
        return 1;   // Error opening -> exit code 1
    }

    // Open file using system call (w/ reading only flag)
    const int fd = open(argv[1], O_RDONLY);   // File descriptor

    // Check for open() error
    if (fd == -1) {
        perror(RED "Error opening file");
        return 1;   // Error opening -> exit code 1
    }

    // Convert file descriptor to stream for getline() w/ read permission
    FILE *fp = fdopen(fd, "r");     // File pointer
    if (fp == NULL) {
        perror(RED "Error converting file descriptor");
        close(fd);  // Close file
        return 1;   // Error converting -> exit code 1
    }

    char *ln = NULL;    // Line buffer
    size_t len = 0;     // Buffer allocation size
    ssize_t read;       // Characters read counter

    size_t sumln = 0;  // Lines read counter
    size_t errln = 0;  // "ERROR"-containing lines counter
    size_t noln = 0;   // Digit-containing lines counter

    // Read file line-by-line
    while ((read = getline(&ln, &len, fp)) != -1) {
        sumln++;    // Increment line counter

        // Increment "ERROR"-containing line counter
        if (strstr(ln, "ERROR") != NULL) {
            errln++;
        }

        // Increment digit-containing line counter
        for (int i = 0; i < read; i++) {
            if (isdigit(ln[i])) {
                noln++;
                break;  // Stop checking the line if a number is found
            }
        }
    }

    free(ln);   // Cleanup memory
    fclose(fp); // Close file

    // Empty file -> exit code 2
    if (sumln == 0) {
        fprintf(stderr, "%sEmpty file warning: %s%s\n", YELLOW, argv[1], NC);
        return 2;
    }

    // Print statistics
    printf("File: %s | Lines: %zu | Errors: %zu | Numeric Lines: %zu\n", argv[1], sumln, errln, noln);

    return 0;   // Success -> exit code 0
}