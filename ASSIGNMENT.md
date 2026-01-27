# Harokopio University of Athens, Informatics and Telematics Department

## Operating Systems (3<sup>rd</sup> Semester)
(Winter Semester 2025-2026)

---

## Operating Systems Lab Project - Analyzing and Processing System Events in UNIX Environment

The IT Department of an organization wants a small UNIX-based infrastructure
for event monitoring. You are invited to implement step-by-step a mini-system that:
1. Collects logs
2. Filters contents with regex
3. Combines commands with pipes & redirections
4. Manages processes to execute tasks
5. Calls utilities written in C
6. Automates the flow through shell scripts
7. Uses threads for parallel data processing

---

## I.  Environment Preparation & Basic Commands
Create a directory structure for the logging system:
```
monitor/
 raw/
 processed/
 reports 
```
1. Create the structure with one command.
2. In the monitor/raw/ directory, create three (3) log files:
- `system.log`
- `network.log`
- `security.log`
3. Add indicative lines to each one (with `echo >>`), e.g. warnings, errors,
timestamps etc., containing:
- Lines starting with a date (pattern: YYYY-MM-DD)
- Lines containing the words ERROR, FAILED, CRITICAL
- Lines containing an IPv4 address
4. Display a detailed list of the files and count how many lines in total
there are in the three (3) logs.

---

## II. Filtering logs with Regular Expressions
We want to identify events that require attention.
1. Using `grep` with regex, locate in all logs:
- Lines that start with a date (pattern: YYYY-MM-DD)
- Lines that contain either the words ERROR, FAILED, CRITICAL
- Lines that contain an IPv4 address
2. The result should be saved in the file: `monitor/processed/alerts.raw`
3. Remove duplicate lines and sort them, creating the file:
`monitor/processed/alerts.sorted`

---

## III. Combining Pipes & Redirection to create a report
Using only one pipeline command:
1. Extract from the file `monitor/processed/alerts.sorted`
- total number of alerts
- total number of lines containing the word ERROR
- total number of lines that concern a specific IP range (e.g. starts with 192.168.*)
2. The command should produce a file: `monitor/reports/daily_summary.txt` with content like:
Total Alerts: X, Errors: Y, Local Network Events: Z

---

## IV. Process Management
You will need to monitor processes related to your system.
1. Run a command that "runs in the background" and periodically writes
timestamps to a file `monitor/raw/timestamps.log`
2. Use `ps` and `grep` to find the process ID (PID)
3. Change the priority of the process (nice or renice)
4. Terminate it first with `-TERM` and, if necessary, with `-KILL`
5. Record the PIDs and what happened.

---

## V. Implementing a C program for analyzing logs
You will need to write a C program titled: `analyze.c` . The program:
1. Takes as an argument a log file name.
2. Tries to open it with `open()` .
3. If it fails → uses `errno` , `perror()` to display an error message.
4. If it opens, it reads it line by line and counts:
- total number of lines
- number of lines containing the word ERROR
- number of lines containing a number
5. Returns exit code:
- 0 -> success
- 1 -> error opening
- 2 -> empty file

The executable will be called: `analyze_log`

---

## VI. Shell Script that automates the entire system
You will need to write the script titled: run_monitor.sh. The script must:
1. Pass a logs' directory as an argument (e.g. `monitor/raw/`)
2. Check that an argument was passed (positional parameters)
3. Check if the directory exists - otherwise exit with an error message
4. Display the name of the script and the total number of arguments
5. Call the `analyze_log` program for each file in the directory
6. Collect all the results in a new file: `monitor/reports/full_report.txt`
7. Use:
- for loops
- case (for categorization, e.g. system/network/security log)
- while loop if you want iterative execution
- IFS for safe line splitting

---

## VII. Threads for parallel log analysis
You should speed up the system with threads via the program: `parallel_analyze.c`
1. The program passes more than one log file as arguments
2. It creates a thread for each file, where each thread:
- opens the file
- counts number of lines & errors (as in `analyze.c`)
- returns the results to `main()` (via struct)
3. `main()` does `pthread_join()` for all threads.
4. It prints a summary report in the format:
```
File: X.log | Lines: L | Errors: E
                ...
          TOTAL LINES: ...
          TOTAL ERRORS: ...
```