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

4. Display a detailed [list](https://man.freebsd.org/cgi/man.cgi?ls) with:
```shell
ls -l monitor/raw/
```
and [count](https://man.freebsd.org/cgi/man.cgi?wc) total lines in the 3 `.log` files with:
```shell
wc -l monitor/raw/*.log
```
![I-4](screenshots/I-4.png)

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