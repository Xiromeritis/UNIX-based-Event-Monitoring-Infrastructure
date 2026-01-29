# Harokopio University of Athens, Informatics and Telematics Department

## Operating Systems (3<sup>rd</sup> Semester)
(Winter Semester 2025-2026)

---

## Operating Systems Lab Project - Analyzing and Processing System Events in UNIX Environment

---

## I.  Environment Preparation & Basic Commands
1. `monitor` directory with `/raw`, `/processed` & `/reports` subdirectories creation:
```shell
mkdir -p monitor/{raw,processed,reports}
```
![I-1](screenshots/I-1.png)

2. `system.log`, `network.log` & `security.log` files creation in the `/monitor/raw` directory:
```shell
touch monitor/raw/system.log monitor/raw/network.log monitor/raw/security.log
```
![I-2](screenshots/I-2.png)
3. Redirect and append (`>>`) the following strings ([FreeBSD](https://www.freebsd.org/)-based mock logs), that contain: YYYY-MM-DD pattern, "ERROR", "FAILED", "CRITICAL" & IPv4 address

For `monitor/raw/system.log`:
```
"2025-10-25 08:00:15 freebsd-srv kernel: Copyright (c) 1992-2025 The FreeBSD Project."
"2025-10-25 08:00:18 freebsd-srv kernel: CRITICAL event: da0: READ_DMA failure - Check cables."
"2025-10-25 12:30:05 freebsd-srv cron[1055]: (root) CMD (/usr/libexec/atrun)"
"2025-10-26 09:15:00 freebsd-srv syslogd: kernel boot file is /boot/kernel/kernel"
"INFO: User logged in from 192.168.1.15 via sshd[22]"
```
For `monitor/raw/network.log`:
```
"2025-10-25 14:20:00 freebsd-srv sshd[8022]: Accepted publickey for admin from 192.168.1.20 port 55122 ssh2"
"FAILED: Connection timed out to 10.0.0.5 during pkg update"
"2025-10-26 03:00:11 freebsd-srv ipfw: 100 Deny TCP 192.168.1.20:5342 192.168.1.1:80 in via em0"
"ERROR: Network unreachable: route to 8.8.8.8 is down via interface em0"
"2025-10-26 15:45:22 freebsd-srv named[662]: client @0x802345678 192.168.1.45#4321: query: google.com IN A + (192.168.1.1)"
```
For `monitor/raw/system.log`:
```
"2025-10-25 10:00:01 freebsd-srv su: admin to root on /dev/pts/0"
"WARNING: Failed login attempt from 192.168.1.100 user=root"
"CRITICAL: Firewall breach detected on port 22 (Brute Force)"
"2025-10-26 18:20:55 freebsd-srv sudo: admin : TTY=pts/1 ; PWD=/home/admin ; USER=root ; COMMAND=/usr/sbin/service apache24 restart"
"2025-10-26 18:21:05 freebsd-srv kernel: pid 4321 (apache24), jid 0, uid 0: exited on signal 11 (core dumped)”
```
```shell
(
echo "2025-10-25 08:00:15 freebsd-srv kernel: Copyright (c) 1992-2025 The FreeBSD Project."
echo "2025-10-25 08:00:18 freebsd-srv kernel: CRITICAL event: da0: READ_DMA failure - Check cables."
echo "2025-10-25 12:30:05 freebsd-srv cron[1055]: (root) CMD (/usr/libexec/atrun)"
echo "2025-10-26 09:15:00 freebsd-srv syslogd: kernel boot file is /boot/kernel/kernel"
echo "INFO: User logged in from 192.168.1.15 via sshd[22]"
) >> monitor/raw/system.log
```
```shell
(
echo "2025-10-25 14:20:00 freebsd-srv sshd[8022]: Accepted publickey for admin from 192.168.1.20 port 55122 ssh2"
echo "FAILED: Connection timed out to 10.0.0.5 during pkg update"
echo "2025-10-26 03:00:11 freebsd-srv ipfw: 100 Deny TCP 192.168.1.20:5342 192.168.1.1:80 in via em0"
echo "ERROR: Network unreachable: route to 8.8.8.8 is down via interface em0"
echo "2025-10-26 15:45:22 freebsd-srv named[662]: client @0x802345678 192.168.1.45#4321: query: google.com IN A + (192.168.1.1)"
) >> monitor/raw/network.log
```
```shell
(
echo "2025-10-25 10:00:01 freebsd-srv su: admin to root on /dev/pts/0"
echo "WARNING: Failed login attempt from 192.168.1.100 user=root"
echo "CRITICAL: Firewall breach detected on port 22 (Brute Force)"
echo "2025-10-26 18:20:55 freebsd-srv sudo: admin : TTY=pts/1 ; PWD=/home/admin ; USER=root ; COMMAND=/usr/sbin/service apache24 restart"
echo "2025-10-26 18:21:05 freebsd-srv kernel: pid 4321 (apache24), jid 0, uid 0: exited on signal 11 (core dumped)"
) >> monitor/raw/security.log
```
![I-3](screenshots/I-3.png)

4. Display a detailed list of each line with [ls](https://man.freebsd.org/cgi/man.cgi?ls) (standing for "list") and the "line" flag `-l`:
```shell
ls -l monitor/raw/
```
and use [wc](https://man.freebsd.org/cgi/man.cgi?wc) (standing for "word count") with the "line" flag `-l` to count total lines in the 3 `.log` files:
```shell
wc -l monitor/raw/*.log
```
![I-4](screenshots/I-4.png)

---

## II. Filtering logs with Regular Expressions
1. Use of [`grep`](https://man.freebsd.org/cgi/man.cgi?grep) with extended regex (`-E`) to locate lines starting with YYYY-MM-DD pattern, lines containing "ERROR", "FAILED", "CRITICAL" & IPv4 address:
```shell
grep -E "^[0-9]{4}-[0-9]{2}-[0-9]{2}|ERROR|FAILED|CRITICAL|([0-9]{1,3}\.){3}[0-9]{1,3}" monitor/raw/*.log
```
![II-1](screenshots/II-1.png)
2. Redirect and overwrite (`>`) [`grep`](https://man.freebsd.org/cgi/man.cgi?grep) result in `monitor/processed/alerts.raw`:
```shell
grep -E "^[0-9]{4}-[0-9]{2}-[0-9]{2}|ERROR|FAILED|CRITICAL|([0-9]{1,3}\.){3}[0-9]{1,3}" monitor/raw/*.log > monitor/processed/alerts.raw
```
![II-2](screenshots/II-2.png)
3. Remove duplicate lines with [`uniq`](https://man.freebsd.org/cgi/man.cgi?uniq) and [`sort`](https://man.freebsd.org/cgi/man.cgi?sort) them, creating the `monitor/processed/alerts.sorted` file with pipe (`|`) and redirect & overwrite (`>`):
```shell
sort monitor/processed/alerts.raw | uniq > monitor/processed/alerts.sorted
```
![II-3](screenshots/II-3.png)

---

## III. Combining Pipes & Redirection to create a report
1. [`cat`](https://man.freebsd.org/cgi/man.cgi?cat) redirects `monitor/processed/alerts.sorted`'s contents via pipe (`|`) to [`awk`](https://man.freebsd.org/cgi/man.cgi?awk) which is executed separately for each of the file's line, allowing us to define local variables (counters) and print the output:
```shell
cat monitor/processed/alerts.sorted | awk '{
    # Increase total alert counter for every line read
    count++; 

    # If the line contains "ERROR", increase error counter
    if ($0 ~ /ERROR/) error++; 

    # If the line contains a local IP (192.168.*), increase ip counter
    if ($0 ~ /192\.168\./) ip++; 
} 
END { 
    # Print final summary
    print "Total Alerts: " count ", Errors: " error ", Local Network Events: " ip 
}'
```
![III-1](screenshots/III-1.png)
2. Redirect and overwrite (`>`) the output of the [`cat`](https://man.freebsd.org/cgi/man.cgi?cat) pipe (`|`) with [`awk`](https://man.freebsd.org/cgi/man.cgi?awk) in the `monitor/reports/daily_summary.txt` file with:
```shell
cat monitor/processed/alerts.sorted | awk '{
    # Increase total alert counter for every line read
    count++; 

    # If the line contains "ERROR", increase error counter
    if ($0 ~ /ERROR/) error++; 

    # If the line contains a local IP (192.168.*), increase ip counter
    if ($0 ~ /192\.168\./) ip++; 
} 
END { 
    # Print final summary
    print "Total Alerts: " count ", Errors: " error ", Local Network Events: " ip 
}' > monitor/reports/daily_summary.txt
```
![III-2](screenshots/III-2.png)

---

## IV. Process Management
1. Run background process (`&`) that records timestamps every 2 seconds ([`sleep`](https://man.freebsd.org/cgi/man.cgi?sleep) 2) via a while loop in the `monitor/raw/timestamps.log` file with:
```shell
(while true; do date >> monitor/raw/timestamps.log; sleep 2; done) &
```
2. Identification of the process' ID (PID) that runs in the background (`&`), using [`ps`](https://man.freebsd.org/cgi/man.cgi?ps) for viewing processes (with the "every" flag `-e`, to show every system process (user-independent) and with the "full format" flag `-f`, to show additional information for every process)) and [`grep`](https://man.freebsd.org/cgi/man.cgi?grep) for filtering with:
```shell
ps -ef | grep sleep
```
![IV-2](screenshots/IV-2.png)
3. Use of [`renice`](https://man.freebsd.org/cgi/man.cgi?renice) to the process whose `PID = 931`, to change the process' priority (niceness) to 10 (lowest process) (sudo privileges required) with:
```shell
sudo renice -n 10 -p 931
```
![IV-3](screenshots/IV-3.png)
4. Process termination with `-TERM` (`SIGTERM`) [signal](https://man.freebsd.org/cgi/man.cgi?query=signal) via [`kill`](https://man.freebsd.org/cgi/man.cgi?kill) to the process whose `PID = 931` with:
```shell
kill -TERM 931
```
![IV-4](screenshots/IV-4.png)
5. The process was found running with `PID = 931`. Initially, its priority was reduced with [`renice`](https://man.freebsd.org/cgi/man.cgi?renice) and then the process was permanently terminated via [`kill`](https://man.freebsd.org/cgi/man.cgi?kill). The `monitor/raw/timestamps.log` file confirms that logging stopped after the process was terminated.
```shell
cat monitor/raw/timestamps.log
```
![IV-5](screenshots/IV-5.png)

---

## V. Implementing a C program for analyzing logs
1. Receive `.log` file's name as an argument and check if not received.
```c
int main(int argc, char *argv[]) {
    // Check if filename argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;   // Error opening -> exit code 1
    }
}
```
2. Attempt to [`open()`](https://man.freebsd.org/cgi/man.cgi?open) the file via system call with the "open for reading only" flag O_RDONLY and returning [`open()`](https://man.freebsd.org/cgi/man.cgi?open)'s value to an integer holding the file descriptor's ID.
```c
// Open file using system call (with reading only flag)
int fd = open(argv[1], O_RDONLY);   // File descriptor
```
3. If [`open()`](https://man.freebsd.org/cgi/man.cgi?open) returns `-1`, the file failed to open and [`perror()`](https://man.freebsd.org/cgi/man.cgi?perror) is used to print error message.
```c
// Check for open() error
if (fd == -1) {
    perror("Error opening file");
    return 1;   // Error opening -> exit code 1
}
```
4. If the file opens, [`getline()`](https://man.freebsd.org/cgi/man.cgi?getline) reads, inside an infinite loop, each of the `fp`'s (file pointer's) line until it returns `-1`, meaning end of file (`EOF`). The variables that are defined are:
- total lines read from the use of [`getline()`](https://man.freebsd.org/cgi/man.cgi?getline) counter
- "ERROR" string-containing lines from the use of [`strstr()`](https://man.freebsd.org/cgi/man.cgi?strstr) counter
- digit-containing lines from the use of [`isdigit`](https://man.freebsd.org/cgi/man.cgi?isdigit) in a loop counter
```c
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
```
5. If the file is successfully read, [`main()`](https://man.freebsd.org/cgi/man.cgi?main) returns exit code `0`, else if an opening file error exists, [`main()`](https://man.freebsd.org/cgi/man.cgi?main) returns exit code `1` and exit code `2` if file is empty.
```c
// Check if filename argument is provided
if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return 1;   // Error opening -> exit code 1
}
       
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
       
// Empty file -> exit code 2
if (sumln == 0) {
    return 2;
}

return 0;   // Success -> exit code 0
```

Finally, with the use of [`gcc`](https://gcc.gnu.org/) and the output flag `-o`, we compile `analyze.c` into the executable `analyze_log` with:
```shell
gcc analyze.c -o analyze_log
```

---

## VI. Shell Script that automates the entire system
1. Pass a logs' directory as an argument:
```shell
# Assign first argument to variable
LOG_D=$1
```
2. Check if an argument was passed (positional parameters) by checking if total arguments number `$#` is not equal `-ne` to `1`. If `true`, then print an [`echo`](https://man.freebsd.org/cgi/man.cgi?echo) message and [`exit`](https://man.freebsd.org/cgi/man.cgi?exit) with exit code `1`.
```shell
# Check if more than one argument is being passed
if [ "$#" -ne 1 ]; then
    echo -e "${YELLOW}USAGE: $0 /path/to/logs/${NC}"
    exit 1
fi
```
3. Check if the passed `LOG_D` argument is NOT `!` a directory `-d` (therefore, checking if it also exists) and if `true` then [`echo`](https://man.freebsd.org/cgi/man.cgi?echo) an error message and [`exit`](https://man.freebsd.org/cgi/man.cgi?exit) with exit code `1`.
```shell
# Check if path exists & is NOT a directory
if [ ! -d "$LOG_D" ]; then
    echo -e "${RED}ERROR: Directory '$LOG_D' does not exist.${NC}"
    exit 1
fi
```
4. Display with [`echo`](https://man.freebsd.org/cgi/man.cgi?echo) the name of the script `$0` and the total number of arguments `$#`:
```shell
# Script info
echo -e "${GREEN}SCRIPT: $0 running with $# argument${NC}"
```
5. Check if the executable exists and is executable with `-x`, then call the `ANALYZER_EXEC="./analyze_log"` program for each file in the directory as a `file` argument. Else, if the executable is missing, [`echo`](https://man.freebsd.org/cgi/man.cgi?echo) an error message and [`exit`](https://man.freebsd.org/cgi/man.cgi?exit) with exit code `1`.
```shell
ANALYZER_EXEC="./analyze_log"

        # Check if executable exists and is executable
        if [ -x "$ANALYZER_EXEC" ]; then
            # Run executable w/ the file as argument & append its output to report file
            "$ANALYZER_EXEC" "$file" >> "$RPT_F"
        else
            # Exit if executable missing
            echo -e "${RED}ERROR: '$ANALYZER_EXEC' not found!${NC}"
            exit 1
        fi
```
6. Define a report file variable `RPT_F` holding the string value of its path `monitor/reports/full_report.txt`. Then, initialize/overwrite (`>`) the file with [`echo`](https://man.freebsd.org/cgi/man.cgi?echo)-ing a header. After that, [`echo`](https://man.freebsd.org/cgi/man.cgi?echo) the `$(date)` when the script is run and append (`>>`) it to the report file `RPT_F`. Then again, [`echo`](https://man.freebsd.org/cgi/man.cgi?echo) the `CATEGORY` and the `filename` of the `file` and append (`>>`) it to the report file `RPT_F`. And finally, run the `ANALYZER_EXEC="./analyze_log"` executable with the `file` argument and append (`>>`) its output (`stdout`) to the report file `RPT_F`. A full report will be available in `monitor/reports/full_report.txt`.
```shell
# Report file path
RPT_F="monitor/reports/full_report.txt"

# Initialize (overwrite) report file
echo "--- SYSTEM MONITOR FULL REPORT ---" > "$RPT_F"
echo "Run @ $(date)" >> "$RPT_F"
echo "----------------------------------" >> "$RPT_F"

# Append separator and file header to report
echo "" >> "$RPT_F"
echo "=== $CATEGORY: $filename ===" >> "$RPT_F"   

# Run executable w/ the file as argument & append its output to report file
"$ANALYZER_EXEC" "$file" >> "$RPT_F" 
```

*Note: The enable color `-e` flag in [`echo`](https://man.freebsd.org/cgi/man.cgi?echo) is used for a <span style="color:red"> *colored output*</span>.*