# SIMATS ENGINEERING
## ASSESSMENT TOOL 1 — SHORT ANSWER TEST

**COURSE NAME:** Operating Systems  
**COURSE CODE:** CSA04  
**COURSE OUTCOME COVERED:** CO1: Apply the concepts of Operating System types, structures, and system calls to demonstrate their functions in various computing environments.  
**QUESTIONS:** 5 | **Total Marks:** 100 | **Marks Scored:** 90/100  
**Submitted by:** Vishal Balaji J | **Register Number:** 192525014  
**Annexure A:** SHORT ANSWER TEST  

---

### Code of Conduct
*I Vishal Balaji J (192525014) certify that this submission is my original work and that I have adhered to the guidelines specified for this assessment. I understand that any violation of academic integrity rules will result in disciplinary action.*  
**Signature of the student:** Vishal Balaji J  

---

## Question 1 — Operating System Types, Structure and Process Creation

### (a) Types of Operating Systems and Justification
A modern computer system that supports several users and processes needs an operating system capable of sharing resources fairly and securely.
- A **multi-user operating system** allows more than one user to access the computer's services simultaneously.
- A **multitasking operating system** switches the CPU among multiple processes so that several applications appear to run concurrently.
- A **time-sharing system** gives each active process a small CPU time slice (quantum), maximizing responsiveness for interactive tasks.
- For a server environment, a **multiprocessor operating system** can allocate multiple CPU cores to execute work in parallel.

Therefore, a multi-user, multitasking, time-sharing, and multiprocessor OS is the ideal choice for server and high-throughput environments.

### (b) Operating System Structure and Resource Management
The operating system acts as an intermediary between user applications and the physical hardware. Applications request services through system calls. The kernel manages process scheduling, memory allocation, file access, and input/output devices. Device drivers communicate with specific hardware controllers, while hardware protection mechanisms (kernel vs. user mode) restrict each process to its permitted resources.

```
+-----------------------------------------------------------------------------------+
|                            User Applications / Shell                              |
+-----------------------------------------------------------------------------------+
                                   ↓ System Calls
+-----------------------------------------------------------------------------------+
|                              Operating System Kernel                              |
|  [Process Management] | [Memory Management] | [File System] | [I/O Management]     |
+-----------------------------------------------------------------------------------+
                                   ↓ Device Drivers
+-----------------------------------------------------------------------------------+
|               Hardware: CPU | Main Memory | Storage | I/O Devices                 |
+-----------------------------------------------------------------------------------+
```

### (c) System Calls to Create and Execute a Process
On Unix-like systems, the standard sequence to spawn and execute an independent program is:
1. `fork()`: Creates an exact child copy of the calling process with a new unique PID.
2. `exec()` family (`execl`, `execv`, etc.): Overlays the child's address space with a new executable binary.
3. `wait()` / `waitpid()`: Blocks the parent process until the child terminates, reaping child exit status and avoiding zombie processes.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process: replace process image
        execl("/bin/ls", "ls", "-l", (char *)NULL);
        _exit(1); // Reached only if exec fails
    } else if (pid > 0) {
        // Parent process: wait for child completion
        waitpid(pid, NULL, 0);
    }
    return 0;
}
```

---

## Question 2 — File and Device Management System Calls

### (a) Categories of System Calls
System calls provide a secure, controlled interface between user-space programs and kernel services:
- **File Management Calls:** Create, open, read, write, reposition, and close files.
  - Examples: `open()`, `read()`, `write()`, `lseek()`, `close()`, `unlink()`.
- **Device Management Calls:** Request access to physical or virtual hardware devices, perform input/output operations, query device attributes, and release devices.
  - On Unix-like systems where "everything is a file", `read()` and `write()` operate on device special files (e.g., `/dev/tty`), while `ioctl()` provides device-specific control commands.

### (b) Layered Structure for File Operations
The layered architecture separates user-level abstraction from hardware-specific storage details:
1. **User Program:** Issues portable file system calls (`open`, `read`, `write`, `close`).
2. **System Call Interface:** Validates arguments and switches CPU from user mode to kernel mode.
3. **Virtual File System (VFS) Layer:** Provides a unified POSIX file API across diverse underlying file systems (ext4, NTFS, FAT32, NFS).
4. **Device Driver / I/O Subsystem:** Translates logical sector requests into physical controller commands with buffering and caching.
5. **Storage Device:** Magnetic disks, SSDs, or optical media executing low-level read/write commands.

```
+-----------------------------------------------------------------------------------+
|                                  User Program                                     |
+-----------------------------------------------------------------------------------+
                         ↓ open() / read() / write() / close()
+-----------------------------------------------------------------------------------+
|                              System Call Interface                                |
+-----------------------------------------------------------------------------------+
                                         ↓
+-----------------------------------------------------------------------------------+
|                       Virtual File System (VFS) & File Layer                      |
+-----------------------------------------------------------------------------------+
                                         ↓
+-----------------------------------------------------------------------------------+
|                            Device Driver / I/O Subsystem                          |
+-----------------------------------------------------------------------------------+
                                         ↓
+-----------------------------------------------------------------------------------+
|                                   Storage Device                                  |
+-----------------------------------------------------------------------------------+
```

### (c) Example: Open, Read, and Close a File
```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    char buffer[128];
    int fd = open("input.txt", O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }
    
    ssize_t n = read(fd, buffer, sizeof(buffer));
    if (n == -1) { perror("read"); close(fd); return 1; }
    
    if (n > 0) write(STDOUT_FILENO, buffer, (size_t)n);
    if (close(fd) == -1) { perror("close"); return 1; }
    return 0;
}
```

---

## Question 3 — Real-Time Operating System

### (a) OS Type and Suitability
A **Real-Time Operating System (RTOS)** guarantees task completion within deterministic, predictable time deadlines:
- **Hard Real-Time System:** Missing a deadline results in total system failure or catastrophic consequences (e.g., medical life support, automotive anti-lock braking systems, industrial robotics).
- **Soft Real-Time System:** Deadlines are important, but occasional late completions only cause degraded quality of service rather than total failure (e.g., multimedia streaming, telecommunications).

For industrial machinery, a hard RTOS is mandatory to ensure sensor feedback and emergency halts execute within bounded microsecond deadlines.

### (b) Hardware, Kernel, and User-Process Interaction
```
+-----------------------------------------------------------------------------------+
|                           Industrial Sensors and Actuators                        |
+-----------------------------------------------------------------------------------+
                                         ↕
+-----------------------------------------------------------------------------------+
|                          Hardware and Interrupt Controller                        |
+-----------------------------------------------------------------------------------+
                                         ↕
+-----------------------------------------------------------------------------------+
|                                   RTOS Kernel                                     |
|           Scheduler | Interrupt Handling | Timers | Synchronization               |
+-----------------------------------------------------------------------------------+
                                 ↕ System Calls / APIs
+-----------------------------------------------------------------------------------+
|                           Control Tasks and User Processes                        |
+-----------------------------------------------------------------------------------+
```
1. External physical events trigger hardware interrupts via the interrupt controller.
2. The RTOS kernel dispatches an Interrupt Service Routine (ISR) with minimal latency.
3. The deterministic scheduler preempts lower-priority tasks to execute urgent control loops.

### (c) System Calls for Process Synchronization
- **Semaphores:** Counting and binary semaphores (`sem_wait()`, `sem_post()`) regulate shared resource access.
- **Mutexes:** Mutual exclusion locks (`pthread_mutex_lock()`, `unlock()`) ensure single-thread critical section access.
- **Priority Inversion Mitigation:** When a low-priority task holds a lock needed by a high-priority task, **Priority Inheritance Protocol** temporarily elevates the low-priority task's priority to prevent unbounded medium-priority preemption.

---

## Question 4 — Distributed Operating Systems and IPC

### (a) Distributed OS and Comparison with Centralized OS
- **Distributed Operating System:** Manages a collection of independent networked computers, presenting them as a single coherent system (providing location, migration, and replication transparency). Provides fault tolerance, dynamic load balancing, and high availability.
- **Centralized Operating System:** Runs on a single machine where all processing, physical memory, and devices are managed by a single local kernel. A failure of the central machine halts the entire system.

### (b) Distributed OS Architecture
```
+---------------------------+        +---------------------------+
|          Node 1           |        |          Node 2           |
|  [App + Local Kernel]     |        |  [App + Local Kernel]     |
+-------------+-------------+        +-------------+-------------+
              ▲                                    ▲
              |       Network / Middleware         |
              +====================================+
              |                                    |
              ▼                                    ▼
+-------------+-------------+        +-------------+-------------+
|          Node 3           |        |      Shared Services      |
|  [App + Local Kernel]     |        |  Naming | Auth | File Sys |
+---------------------------+        +---------------------------+
```

### (c) System Calls Used in Inter-Process Communication (IPC)
- **Local IPC:** `pipe()` (unidirectional byte stream), `socketpair()` (bidirectional connected sockets), and shared memory (`shmget()`, `shmat()`).
- **Network IPC (Sockets):**
  - **Server Sequence:** `socket()` → `bind()` → `listen()` → `accept()` → `recv()`/`send()` → `close()`.
  - **Client Sequence:** `socket()` → `connect()` → `send()`/`recv()` → `close()`.

---

## Question 5 — Core OS Functions and Resource Management

### (a) Major Functions of an Operating System
1. **Process Management:** Creation, scheduling, synchronization, and termination of processes and threads.
2. **Memory Management:** Tracking memory words/bytes, allocating dynamic heap memory, paging, and virtual memory mapping.
3. **Storage & File System Management:** Organizing data into hierarchical directories, mapping logical files to disk blocks, access control.
4. **I/O Device Management:** Buffering, caching, spooling, device driver communication, and interrupt processing.
5. **Protection & Security:** Enforcing access rights, authentication, privilege levels (ring 0 vs ring 3).

### (b) OS Components and Interactions
```
+-----------------------------------------------------------------------------------+
|                                 User Applications                                 |
+-----------------------------------------------------------------------------------+
                                   ↓ System Call Interface
+-----------------------------------------------------------------------------------+
|                                      Kernel                                       |
|  [Process Scheduler] | [Memory Manager] | [File System] | [I/O Subsystem] | [Security]
+-----------------------------------------------------------------------------------+
                                   ↓ Drivers & Interrupts
+-----------------------------------------------------------------------------------+
|               Hardware: CPU | RAM | Disk | Network | Peripheral Devices           |
+-----------------------------------------------------------------------------------+
```

### (c) System Call Examples for Memory and Device Management
- **Memory Management:**
  - `brk()` / `sbrk()`: Adjusts the process data segment break pointer to expand or shrink the heap.
  - `mmap()`: Maps files or anonymous memory directly into the process virtual address space.
- **Device Management:**
  - `open("/dev/...", O_RDWR)`: Obtains a device file descriptor.
  - `ioctl(fd, REQUEST, &value)`: Transmits device-specific control commands and configuration parameters.
  - `close(fd)`: Releases the device descriptor.

---

## Conclusion
Operating systems serve as the foundational resource managers and abstraction layers in modern computing. Through well-defined system-call interfaces, the OS kernel orchestrates processes, manages memory hierarchies, isolates resources, and coordinates distributed and real-time execution safely and predictably.
