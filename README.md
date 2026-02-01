# Installation

## Windows
[WSL (Windows Subsystem for Linux)](https://github.com/microsoft/WSL) is required because Windows isn't a UNIX-based operating system. Please refer to the [WSL installation guide](https://learn.microsoft.com/en-us/windows/wsl/install).

## macOS
If you want just the essential packages, continue with the `xcode-select` installation:
```bash
# Minimal prerequisites installation
xcode-select --install
```
Or if you have the [Homebrew](https://brew.sh/) package manager installed, continue with the [`gcc`](https://gcc.gnu.org/) and [`git`](https://git-scm.com/) installation:
```bash
brew install gcc git
```
*Note: macOS uses [Clang](https://clang.llvm.org/) aliased as [gcc](https://gcc.gnu.org/) by default*

## Linux

To identify which Linux distribution you are using, you can run in your terminal:
```bash
# Distribution identification
cat /etc/os-release
```
### [Debian-based distributions](https://distrowatch.com/search.php?basedon=Debian) ([Debian](https://www.debian.org/), [Ubuntu](https://ubuntu.com/), [Linux Mint](https://linuxmint.com/), [Kali Linux](https://www.kali.org/), [MX Linux](https://mxlinux.org/), [Pop!_OS](https://system76.com/pop/), etc.)
```bash
# Update the package manager
sudo apt update
# Install required packages
sudo apt install build-essential git
```