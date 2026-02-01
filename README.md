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
# Update Homebrew
brew update

# Install GCC and Git
brew install gcc git
```
*Note: macOS uses [Clang](https://clang.llvm.org/) aliased as [gcc](https://gcc.gnu.org/) by default*

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