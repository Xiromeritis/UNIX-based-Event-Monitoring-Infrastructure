#include <stdio.h>  // printf(), fprintf() & perror() library
#include <stdlib.h> // free() library
#include <string.h> // strstr() library
#include <fcntl.h>  // open() & O_RDONLY library
#include <unistd.h> // close() library
#include <errno.h>  // errno library
#include <ctype.h>  // isdigit() library

int main(int argc, char *argv[]) {
    // Check if filename argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;   // Error opening -> exit code 1
    }

    // Open file using system call (with reading only flag)
    int fd = open(argv[1], O_RDONLY);   // File descriptor

    // Check for open() error
    if (fd == -1) {
        perror("Error opening file");
        return 1;   // Error opening -> exit code 1
    }

    // Convert file descriptor to stream for getline() with read permission
    FILE *fp = fdopen(fd, "r");     // File pointer
    if (fp == NULL) {
        perror("Error converting file descriptor");
        close(fd);  // Close file
        return 1;   // Error converting -> exit code 1
    }

    char *ln = NULL;    // Line's text
    size_t len = 0;     // Buffer allocation size
    ssize_t read;       // Characters read counter

    int sumln = 0;  // Lines read counter
    int errln = 0;  // "ERROR"-containing lines counter
    int noln = 0;   // Digit-containing lines counter

    // Read file line-by-line
    while ((read = getline(&ln, &len, fp)) != -1) {
        sumln++;    // Increment line counter

        // Increment "ERROR"-containing line counter
        if (strstr(line, "ERROR") != NULL) {
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
        return 2;
    }

    return 0;   // Success -> exit code 0
}