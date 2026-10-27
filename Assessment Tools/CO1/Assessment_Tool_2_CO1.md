# SIMATS ENGINEERING
## ASSESSMENT TOOL 2 — CONCEPT MAPPING

**COURSE NAME:** Operating Systems  
**COURSE CODE:** CSA04  
**COURSE OUTCOME COVERED:** CO1: Apply the concepts of Operating System types, structures, and system calls to demonstrate their functions in various computing environments. (BL2, BL3)  
**QUESTIONS:** 1 (5 Comprehensive Concept Maps) | **Total Marks:** 100 | **Marks Scored:** 95/100  
**Submitted by:** Vishal Balaji J | **Register Number:** 192525014  
**Annexure A:** Concept Mapping  

---

### Code of Conduct
*I Vishal Balaji J (192525014) certify that this submission is my original work and that I have adhered to the guidelines specified for this assessment. I understand that any violation of academic integrity rules will result in disciplinary action.*  
**Signature of the student:** Vishal Balaji J  

---

## Question 1: Multi-Level Concept Map Integrating OS Types, Structures, System Calls, and Functions (BL2)

```mermaid
graph TD
    OS["Operating System<br><i>Manages hardware resources and provides services to applications</i>"]
    
    %% Branch 1: OS Types
    OS -->|"Can be classified into"| Types["Operating System Types"]
    Types --- T1["• Batch OS"]
    Types --- T2["• Time-Sharing OS"]
    Types --- T3["• Distributed OS"]
    Types --- T4["• Real-Time OS (RTOS)"]
    Types --- T5["• Network OS"]
    Types --- T6["• Embedded / Mobile OS"]

    %% Branch 2: OS Structures
    OS -->|"Implemented using"| Struct["OS Structures"]
    Struct --- S1["• Monolithic Structure"]
    Struct --- S2["• Layered Structure"]
    Struct --- S3["• Microkernel Architecture"]
    Struct --- S4["• Modular / Hybrid Kernel"]

    %% Branch 3: Interfaces
    OS -->|"Provides programmatic interface"| SC["System Calls"]
    SC --- SC1["• Process Control (fork, exec, exit)"]
    SC --- SC2["• File Management (open, read, write)"]
    SC --- SC3["• Device Management (ioctl, read, write)"]
    SC --- SC4["• Information & Communication (pipe, socket)"]

    %% Branch 4: OS Functions
    OS -->|"Executes core"| Func["OS Functions"]
    Func --- F1["• Process & Thread Management"]
    Func --- F2["• Memory & Virtual Memory Management"]
    Func --- F3["• File System & Storage Management"]
    Func --- F4["• I/O System Management & Buffering"]
    Func --- F5["• Protection, Security & Error Detection"]
    Func --- F6["• Accounting & Performance Monitoring"]

    %% Cross-links
    Struct -.->|"Defines call dispatching"| SC
    SC -.->|"Invokes kernel services for"| Func
```

---

## Question 2: Comprehensive Interdependency Concept Map for Core Subsystems (BL3)

```mermaid
graph TD
    subgraph ProcessMgr ["Process Management Subsystem"]
        PCB["Process Control Block (PCB)"]
        Sched["CPU Scheduler (Short/Long term)"]
        Sync["Process Synchronization (Mutex/Semaphores)"]
        SC_P["Calls: fork(), exec(), exit(), wait(), kill()"]
    end

    subgraph MemoryMgr ["Memory Management Subsystem"]
        MMU["Page Tables / MMU Translation"]
        Alloc["Dynamic Allocator (brk/sbrk/malloc)"]
        VM["Virtual Memory & Page Replacement (FIFO/LRU)"]
        SC_M["Calls: brk(), sbrk(), mmap(), munmap()"]
    end

    subgraph FileSys ["File System Subsystem"]
        VFS["Virtual File System (VFS) Layer"]
        Inodes["Inode Table & Directory Trees"]
        BufCache["Buffer Cache & Page Cache"]
        SC_F["Calls: open(), read(), write(), close(), unlink()"]
    end

    subgraph IOSubsys ["I/O Subsystem"]
        DevDrivers["Device Drivers (Char/Block)"]
        DevQueue["Device Queues & Interrupt Handlers"]
        DMA["DMA Controllers & Spooling"]
        SC_D["Calls: ioctl(), read(), write(), select()"]
    end

    %% Interdependencies
    ProcessMgr -->|"Requests memory space for stack & heap"| MemoryMgr
    ProcessMgr -->|"Loads binary executables & writes logs"| FileSys
    ProcessMgr -->|"Blocks on I/O wait / Dispatches I/O request"| IOSubsys

    MemoryMgr -->|"Backs virtual memory pages to swap file"| FileSys
    MemoryMgr -->|"Performs DMA transfers to/from RAM"| IOSubsys

    FileSys -->|"Sends block read/write commands"| IOSubsys
    IOSubsys -->|"Signals completion via interrupts"| ProcessMgr
```

---

## Question 3: Comparative Concept Map — OS Paradigms (BL2)

```mermaid
graph LR
    subgraph Batch ["Batch Operating System"]
        B_Goal["Goal: Maximize CPU Utilization"]
        B_Char["Jobs grouped in batches; No user interaction"]
        B_Adv["High throughput for repetitive scientific tasks"]
        B_Lim["Zero debugging interaction; high turnaround time"]
    end

    subgraph TimeShare ["Time-Sharing Operating System"]
        TS_Goal["Goal: Minimize User Response Time"]
        TS_Char["Preemptive Round Robin time-slicing across multiple users"]
        TS_Adv["Interactive sessions; fair CPU sharing"]
        TS_Lim["High context-switch overhead; complex scheduling"]
    end

    subgraph Distributed ["Distributed Operating System"]
        D_Goal["Goal: Resource Sharing & Transparency"]
        D_Char["Multiple autonomous nodes communicating via network"]
        D_Adv["Scalability, fault tolerance, high resource availability"]
        D_Lim["Network latency, synchronization complexity, security"]
    end

    subgraph RTOS ["Real-Time Operating System"]
        R_Goal["Goal: Strict Deterministic Deadlines"]
        R_Char["Fixed priority preemption, bounded interrupt latency"]
        R_Adv["Guaranteed deadlines for mission-critical hardware"]
        R_Lim["Limited throughput, simple scheduling, high cost"]
    end
```

---

## Question 4: Dynamic Execution Flow — User Program to Hardware & Response (BL3)

```mermaid
sequenceDiagram
    autonumber
    actor User as User Application
    participant Lib as Standard Library / API (glibc)
    participant Trap as System Call Interface (TRAP / SYSENTER)
    participant Kernel as OS Kernel Subsystem
    participant Driver as Device Driver / Controller
    participant HW as Hardware Device

    User->>Lib: Call library wrapper (e.g., read(fd, buf, count))
    Lib->>Trap: Load system call number into register & execute trap / syscall
    Note over Trap: CPU switches from User Mode (Ring 3) to Kernel Mode (Ring 0)
    Trap->>Kernel: Lookup dispatch table & invoke sys_read()
    Kernel->>Kernel: Validate pointers, permissions, and file descriptors
    
    alt Data in Kernel Buffer Cache
        Kernel-->>User: Copy data to user buffer & return byte count
    else Data requires Hardware Fetch
        Kernel->>Driver: Issue device read command
        Driver->>HW: Start DMA transfer / Read sectors
        Note over Kernel: Put calling process to SLEEP (Wait state)
        HW-->>Driver: Raise Hardware Interrupt (I/O Complete)
        Driver-->>Kernel: Interrupt handler wakes up waiting process
        Kernel->>Kernel: Copy data into User Program address space
        Kernel-->>Trap: Return status code / bytes read
        Trap-->>Lib: Return from kernel mode to user mode
        Lib-->>User: Return to User Application
    end
```

---

## Question 5: Hierarchical & Functional Taxonomy of System Calls (BL3)

```mermaid
graph TD
    SC["System Calls Classification"]

    %% Class 1: Process Control
    SC --> P["1. Process Control"]
    P --- P1["fork() : Create child process"]
    P --- P2["exec() : Load program into address space"]
    P --- P3["exit() : Terminate process"]
    P --- P4["wait() : Wait for child termination"]
    P --- P5["kill() : Send signal to process"]
    P -.->|"Maps to"| Srv_P["OS Process Scheduler & Dispatcher"]

    %% Class 2: File Management
    SC --> F["2. File Management"]
    F --- F1["open() : Allocate file descriptor"]
    F --- F2["read() : Fetch bytes from file"]
    F --- F3["write() : Write bytes to file"]
    F --- F4["lseek() : Reposition offset pointer"]
    F --- F5["close() : Release file descriptor"]
    F -.->|"Maps to"| Srv_F["VFS & File System Block Allocator"]

    %% Class 3: Device Management
    SC --> D["3. Device Management"]
    D --- D1["ioctl() : Device-specific I/O control"]
    D --- D2["read() / write() : Read/write device stream"]
    D --- D3["select() / poll() : Synchronous I/O multiplexing"]
    D -.->|"Maps to"| Srv_D["Device Drivers & Interrupt Service Routines"]

    %% Class 4: Information & Maintenance
    SC --> I["4. Information & Maintenance"]
    I --- I1["getpid() / getppid() : Query process identifiers"]
    I --- I2["time() : Get system wall clock"]
    I --- I3["sysinfo() : System memory and load stats"]
    I -.->|"Maps to"| Srv_I["Kernel Accounting & Performance Subsystems"]

    %% Class 5: Memory Management
    SC --> M["5. Memory Management"]
    M --- M1["brk() / sbrk() : Adjust process heap break"]
    M --- M2["mmap() : Map file/anonymous pages into virtual memory"]
    M --- M3["munmap() : Unmap virtual memory range"]
    M -.->|"Maps to"| Srv_M["Virtual Memory Manager & MMU Page Tables"]
```
