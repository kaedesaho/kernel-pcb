# Kernel Module: Fetch PCB & Memory Management Info
## Overview

This Linux kernel module retrieves PCB (Process Control Block) and memory management information for active processes and writes it to a text file.

The module retrieves:

- Process Name  
- Process ID (PID)  
- Page Table Pointer (PGD), if available  

## Module Architecture

The module accesses internal kernel structures in the following order:

    task_struct (Process Control Block)
            ↓
    mm_struct (Memory Descriptor)
            ↓
    pgd (Page Global Directory pointer)
            ↓
    Write output to /tmp/fetch_pcb_mm.txt

## Requirements

- Linux system
- Kernel headers installed
- Root privileges
- Tested on Linux Kernel 6.8.0

## Installation

Make sure the following files are in the same directory:

- `fetch_pcb_mm.c`
- `Makefile`

### 1. Compile the Module

```bash
make
```

This generates:

```
fetch_pcb_mm.ko
```

### 2. Load the Module

```bash
sudo insmod fetch_pcb_mm.ko
```


### 3. View Kernel Log Messages

```bash
sudo dmesg | tail
```

### 4. Access the Output File

The module writes output to:

```
/tmp/fetch_pcb_mm.txt
```

To view the file:

```bash
cat /tmp/fetch_pcb_mm.txt
```

### 5. Unload the Module

```bash
sudo rmmod fetch_pcb_mm
```

(Use the module name without `.ko`)

## Features

- Iterates through active processes
- Extracts PCB-level information
- Accesses memory management structures
- Retrieves Page Table pointer (PGD)
- Logs module load and unload events

## Libraries Used

```c
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm_types.h>
```

## Authors

Brandon Warnke  
Kaede Saho  

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
