#include <stdio.h>  // printf() & fprintf() library
#include <stdlib.h> // free() & exit() library
#include <string.h> // strstr() library
#include <pthread.h>// pthread_create() & pthread_join() library

// Color Definitions
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define NC      "\033[0m"   // No color (reset)

// Structure to pass arguments and retrieve results from threads
typedef struct {
    char *filename; // Input: File name to analyze
    size_t lines;   // Output: Total lines count
    size_t errors;  // Output: Error lines count
    int success;    // Status: 1 -> success, 0 -> failure
} FileStats;

// Thread worker function
void *analyze_file_thread(void *arg) {
    // Cast a generic void pointer back to FileStats struct
    FileStats *stats = (FileStats *)arg;

    // Initialize counters
    stats->lines = 0;
    stats->errors = 0;
    stats->success = 0;

    // Open a file for reading (standard I/O)
    FILE *fp = fopen(stats->filename, "r");
    if (fp == NULL) {
        // Print error to stderr() without exiting parallel_analyze
        fprintf(stderr, "%s[Thread Error] Cannot open file: %s%s\n", RED, stats->filename, NC);
        pthread_exit(NULL); // Terminate this thread only
    }

    char *ln = NULL;	// Line buffer
    size_t len = 0;     // Buffer size

    // Read the file line-by-line
    while (getline(&ln, &len, fp) != -1) {
        stats->lines++; // Increment line counter

        // Check if a line contains "ERROR"
        if (strstr(ln, "ERROR") != NULL) {
            stats->errors++; // Increment error counter
        }
    }

    // Clean up memory and close a file
    free(ln);
    fclose(fp);

    stats->success = 1; // Mark analysis as successful
    pthread_exit(NULL); // Exit thread
}

int main(const int argc, char *argv[]) {
    // Check if at least one file argument is provided
    if (argc < 2) {
        fprintf(stderr, "%sUsage: %s <file1> <file2> ...%s\n", YELLOW, argv[0], NC);
        return 1;   // Exit code 1
    }

    const int filesno = argc - 1;   // Number of files to process

    // Arrays to store thread IDs and their data
    pthread_t threads[filesno];
    FileStats thread_data[filesno];

    printf("%sStarting parallel analysis on %d files...%s\n\n", GREEN, filesno, NC);

    // 1. Thread creation loop
    for (int i = 0; i < filesno; i++) {
        // Assign filename to the struct
        thread_data[i].filename = argv[i + 1];

        // Create a new thread for each file
        if (pthread_create(&threads[i], NULL, analyze_file_thread, &thread_data[i]) != 0) {
            perror(RED "Error creating thread" NC);
            return 1;
        }
    }

    // Thread join loop (wait for completion)
    // Use size_t for global counters as well
    size_t total_lines = 0;
    size_t total_errors = 0;

    for (int i = 0; i < filesno; i++) {
        // Block until thread i finishes execution
        pthread_join(threads[i], NULL);

        // If the thread finished successfully, collect data
        if (thread_data[i].success) {
            // Print individual file statistics
            printf("File: %-30s | Lines: %3zu | Errors: %s%3zu%s\n",
                   thread_data[i].filename,
                   thread_data[i].lines,
                   (thread_data[i].errors > 0 ? RED : GREEN), // Red if errors exist, else Green
                   thread_data[i].errors,
                   NC);

            // Accumulate to global totals
            total_lines += thread_data[i].lines;
            total_errors += thread_data[i].errors;
        }
    }

    // Print final summary report
    printf("\t\t\tTOTAL LINES:  %zu\n", total_lines);
    printf("\t\t\tTOTAL ERRORS: %s%zu%s\n", (total_errors > 0 ? RED : GREEN), total_errors, NC);

    return 0;   // Success -> exit code 0
}