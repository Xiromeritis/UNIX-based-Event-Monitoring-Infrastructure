# UNIX-based Event Monitoring Infrastructure

![Build Status](https://github.com/Xiromeritis/UNIX-based-Event-Monitoring-Infrastructure/actions/workflows/c-build.yml/badge.svg) ![License](https://img.shields.io/badge/license-MIT-green)

**Operating Systems University Semester Lab Work**

*Department of Informatics & Telematics,*

*Harokopio University of Athens*

---

# Description

A robust system monitoring tool designed to analyze `.log` files, filter critical events, and generate comprehensive reports. It utilizes low-level C programming for performance and bash scripting for automation.

---

# Key Features
- **Log Collection & Filtering:** Regex-based filtering for system, network, and security logs.
- **Automated Analysis:** A bash script (`run_monitor.sh`) automates the entire monitoring workflow.
- **High Performance:** Core analysis logic is written in C for efficiency.
- **Parallel Processing:** Utilizes POSIX Threads ([`pthread`](https://man.freebsd.org/cgi/man.cgi?pthread)) to analyze multiple `.log` files simultaneously, significantly reducing processing time on large datasets.

---

# Prerequisites

To build and run this project, a UNIX-based environment is required. The key prerequisites are:

- [GCC (GNU Compiler Collection)](https://gcc.gnu.org/): Required for compiling the C code. It includes the necessary system libraries ([Standard C Library](https://www.gnu.org/software/libc/)) and support for POSIX Threads ([`pthread`](https://man.freebsd.org/cgi/man.cgi?pthread)), which is essential for the parallelization part of the project.

- [Bash Shell](https://www.gnu.org/software/bash/): Necessary for executing the automation scripts (`run_monitor.sh`).

- [GNU Coreutils](https://www.gnu.org/software/coreutils/): Standard command-line utilities (such as [`grep`](https://man.freebsd.org/cgi/man.cgi?grep), [`awk`](https://man.freebsd.org/cgi/man.cgi?awk), [`find`](https://man.freebsd.org/cgi/man.cgi?find)) used for log management and filtering.

- [Git](https://git-scm.com/): Used for version control.

## Windows
[WSL (Windows Subsystem for Linux)](https://github.com/microsoft/WSL) is required because Windows isn't a UNIX-based operating system. Please refer to the [WSL installation guide](https://learn.microsoft.com/en-us/windows/wsl/install).

> **After installing WSL:** Open your Linux terminal and proceed to the **[Linux](#linux)** section below.

## macOS
If you want just the essential packages, continue with the `xcode-select` installation:
```bash
# Minimal prerequisites installation
xcode-select --install
```
Or if you have the [Homebrew](https://brew.sh/) package manager installed, continue with the [`gcc`](https://gcc.gnu.org/) and [`git`](https://git-scm.com/) installation:
```bash
# Update Homebrew
brew update

# Install GCC and Git
brew install gcc git
```
*Note: macOS uses [Clang](https://clang.llvm.org/) aliased as [GCC](https://gcc.gnu.org/) by default*

## Linux

To identify which Linux distribution you are using, you can run in your terminal:
```bash
# Distribution identification
cat /etc/os-release
```
### [**Debian-based distributions**](https://en.wikipedia.org/wiki/Category:Debian-based_distributions)
*[Debian](https://www.debian.org/), [Ubuntu](https://ubuntu.com/), [Linux Mint](https://linuxmint.com/), [Kali Linux](https://www.kali.org/), [MX Linux](https://mxlinux.org/), [Pop!_OS](https://system76.com/pop/), [Zorin OS](https://zorin.com/os/), etc.*
```bash
# Update repositories
sudo apt update

# Install required packages (GCC, Make, Git)
sudo apt install build-essential git
```

### [**RPM-based Linux distributions**](https://en.wikipedia.org/wiki/Category:RPM-based_Linux_distributions)
*[Fedora](https://www.fedoraproject.org/), [Red Hat Enterprise Linux](https://www.redhat.com/en/technologies/linux-platforms/enterprise-linux), etc.*
```bash
# Check for updates
sudo dnf check-update

# Install development tools and Git
sudo dnf groupinstall "Development Tools"
sudo dnf install git
```

### [**Arch-based distributions**](https://wiki.archlinux.org/title/Arch-based_distributions)
*[Arch Linux](https://archlinux.org/), [Manjaro](https://manjaro.org/), [EndeavourOS](https://endeavouros.com/), [Garuda Linux](https://garudalinux.org/), etc.*
```bash
# Update system
sudo pacman -Syu

# Install base-devel and Git
sudo pacman -S base-devel git
```

### [**openSUSE-based distributions**](https://www.opensuse.org/)
*[openSUSE Leap](https://get.opensuse.org/leap/), [openSUSE Tumbleweed](https://get.opensuse.org/tumbleweed/), etc.*
```bash
# Refresh repositories
sudo zypper refresh

# Install development pattern and Git
sudo zypper install -t pattern devel_basis
sudo zypper install git
```

### [**Alpine Linux**](https://www.alpinelinux.org/)
```bash
# Update repositories
sudo apk update

# Install build tools, Bash, and Git
sudo apk add build-base git bash
```

### [**Void Linux**](https://voidlinux.org/)
```bash
# Update system
sudo xbps-install -Su

# Install base-devel, Git, and Bash
sudo xbps-install base-devel git bash
```

### [**Solus**](https://getsol.us/)
```bash
# Update repositories
sudo eopkg ur

# Install component.devel and git
sudo eopkg it -c system.devel
sudo eopkg it git
```

## [BSD (Berkeley Software Distribution) Operating Systems](https://en.wikipedia.org/wiki/List_of_BSD_operating_systems)

### **FreeBSD-based distributions**
*[FreeBSD](https://www.freebsd.org/), [DragonFly BSD](https://www.dragonflybsd.org/), [GhostBSD](https://www.ghostbsd.org/), etc.*
```bash
# Update repositories
doas pkg update

# Install GCC, Bash, and Git
doas pkg install gcc bash git
```

### **NetBSD-based distributions**
*[NetBSD](https://www.netbsd.org/), etc.*
```bash
# Update database
doas pkgin update

# Install tools
doas pkgin install gcc bash git
```

### **OpenBSD-based distributions**
*[OpenBSD](https://www.openbsd.org/), etc.*
```bash
# Update packages
doas pkg_add -u

# Install tools
doas pkg_add gcc bash git
```

*Note: Some individuals may have [`doas`](https://man.freebsd.org/cgi/man.cgi?doas) instead of [`sudo`](https://man.freebsd.org/cgi/man.cgi?sudo) or the other way around.*

---

# Build

1. Go to the directory where you want the project to be:
```bash
cd path/to/your/directory/
```

2. Clone the project with [`git`](https://man.freebsd.org/cgi/man.cgi?git):
```bash
git clone https://github.com/Xiromeritis/UNIX-based-Event-Monitoring-Infrastructure.git
```

3. Go to the project's directory:
```bash
cd UNIX-based-Event-Monitoring-Infrastructure/
```

4. Compile the C programs: You need to compile both the single-file analyzer and the multithreaded version.
```bash
# Compile the main analyzer
gcc analyze.c -o analyze_log

# Compile the parallel analyzer (requires pthread library)
gcc -pthread parallel_analyze.c -o parallel_analyze_logs
```

5. Make the script executable:
```bash
chmod +x run_monitor.sh
```

---

# Project Structure

```text
.
├── analyze.c            # Source code for single-file analysis (C)
├── parallel_analyze.c   # Source code for multi-threaded analysis (C + pthreads)
├── run_monitor.sh       # Bash script for automating the monitoring process
├── README.md            # Project documentation and installation guide
└── monitor/             # Main data directory
    ├── raw/             # Input: Contains raw log files (e.g., system.log, security.log)
    └── reports/         # Output: Stores generated reports (e.g., full_report.txt)
```

---

# Usage

## Option 1: Automated Monitoring
Run the automation script by providing the directory containing your logs:
```bash
./run_monitor.sh monitor/raw/
```
This command will analyze all logs in the specified directory and generate a summary report in `monitor/reports/full_report.txt`.

## Option 2: Parallel Analysis
To demonstrate the multi-threading capabilities, you can run the parallel analyzer directly:
```bash
./parallel_analyze_logs monitor/raw/*.log
```
This will spawn a separate thread for each log file provided and output the statistics directly to the console.
### Example Output
When running the parallel analyzer, you will see output similar to this:
```text
Starting parallel analysis on 5 files...

File: monitor/raw/empty.log          | Lines:   0 | Errors:   0
File: monitor/raw/network.log        | Lines:   5 | Errors:   1
File: monitor/raw/security.log       | Lines:   5 | Errors:   0
File: monitor/raw/system.log         | Lines:   5 | Errors:   0
File: monitor/raw/timestamps.log     | Lines:  14 | Errors:   0
                        TOTAL LINES:  29
                        TOTAL ERRORS: 1
```

---

## License
This project is licensed under the MIT License – see the [LICENSE](LICENSE) file for details.
