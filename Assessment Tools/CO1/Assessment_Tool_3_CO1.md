# SIMATS ENGINEERING
## ASSESSMENT TOOL 3 — TECHNICAL PRESENTATION

**COURSE NAME:** Operating Systems  
**COURSE CODE:** CSA04  
**COURSE OUTCOME COVERED:** CO1: Apply the concepts of Operating System types, structures, and system calls to demonstrate their functions in various computing environments.  
**QUESTIONS:** 1 (Technical Seminar Presentation) | **Total Marks:** 100 | **Marks Scored:** 95/100  
**Submitted by:** Vishal Balaji J | **Register Number:** 192525014  
**Annexure A:** Technical Presentation  

---

### Code of Conduct
*I Vishal Balaji J (192525014) certify that this submission is my original work and that I have adhered to the guidelines specified for this assessment. I understand that any violation of academic integrity rules will result in disciplinary action.*  
**Signature of the student:** Vishal Balaji J  

---

## Technical Presentation: Architecture, System Calls, and Paradigms in Modern Operating Systems

### Slide 1: Title & Overview
- **Title:** Modern Operating System Paradigms: From Monolithic Kernels to Distributed & Real-Time Architectures
- **Presenter:** Vishal Balaji J (Reg. No: 192525014)
- **Institution:** SIMATS Engineering, Saveetha Institute of Medical and Technical Sciences
- **Course Outcome (CO1):** Apply the concepts of Operating System types, structures, and system calls to demonstrate their functions in various computing environments.

---

### Slide 2: The Evolution of Operating System Paradigms
- **First Generation:** Bare-metal programming, manual plugboards, no OS abstraction.
- **Batch Processing:** Job scheduling without interactive control; IBM OS/360; maximizing hardware duty cycles.
- **Time-Sharing Systems:** Multiprogramming with preemptive Round Robin scheduling (CTSS, MULTICS, Unix).
- **Distributed & Cloud Systems:** Geographically distributed compute nodes presenting single-system illusion.
- **Embedded & RTOS:** Ultra-low footprint, zero-tolerance deadline adherence for automotive, aerospace, and medical devices.

---

### Slide 3: Operating System Architectural Models
1. **Monolithic Architecture:**
   - Entire kernel runs in a single address space in privileged mode (Ring 0).
   - High performance due to direct in-kernel function invocation (e.g., Linux, FreeBSD).
   - Drawback: Single driver bug can cause kernel panic / crash.
2. **Microkernel Architecture:**
   - Only minimal essential mechanisms (IPC, low-level scheduling, basic memory mapping) remain in kernel mode.
   - Servers (VFS, device drivers, networking) run in user mode (e.g., Minix, QNX, seL4).
   - Benefit: Unmatched fault isolation and formal verifiability.
3. **Hybrid Architecture:**
   - Blends monolithic speed with microkernel subsystem separation (e.g., Windows NT, macOS XNU).

---

### Slide 4: Anatomy of a System Call & Context Switching
- Dual-mode CPU operation: **User Mode (Ring 3)** vs **Kernel Mode (Ring 0)**.
- System call transition mechanism:
  1. User invokes standard library API (e.g., `open()`, `fork()`).
  2. Library puts syscall number into CPU register (`%eax` / `%rax`) and triggers software interrupt (`int 0x80` or `syscall`/`sysenter`).
  3. Hardware switches privilege levels, saves program counter and stack pointer to kernel stack.
  4. System Call Dispatcher invokes corresponding kernel handler.
  5. Result code returned, CPU switched back to Ring 3.

---

### Slide 5: Memory Management & Virtualization
- **Paging & Segmentation:** Linear virtual address spaces translated via Memory Management Unit (MMU) and Multi-level Page Tables.
- **Translation Lookaside Buffer (TLB):** Hardware cache accelerating address translation.
- **Demand Paging & Page Replacement:** FIFO, LRU, and Clock algorithms balancing hit ratios and page fault penalties.

---

### Slide 6: Real-Time Operating Systems (RTOS) in Mission-Critical Systems
- Comparison of Determinism vs Throughput:
  - General Purpose OS (GPOS): Optimizes average throughput and human interactivity.
  - RTOS: Optimizes bounded worst-case execution time (WCET).
- Priority Inversion Problem:
  - Scenario where high-priority task $T_{high}$ is blocked by low-priority task $T_{low}$, which is preempted by medium task $T_{med}$.
  - Solution: **Priority Inheritance Protocol** dynamically raises $T_{low}$ to $T_{high}$'s priority until the critical lock is released.

---

### Slide 7: Distributed Operating Systems & Scalable IPC
- Key IPC Mechanisms:
  - Local pipes and named FIFOs.
  - Shared memory primitives (`mmap`, POSIX `shm_open`).
  - Network communication: Stream sockets (TCP) vs Datagram sockets (UDP).
- RPC & Microservice Communication: Remote Procedure Calls abstracting network transport into local function calls.

---

### Slide 8: Summary & Research Outlook
- Future Operating Systems are shifting towards:
  - Memory-safe systems programming languages (Rust in Linux and Windows kernels).
  - Unikernels and containerized lightweight execution environments.
  - Heterogeneous computing kernels scheduling across CPUs, GPUs, TPUs, and neuromorphic accelerators.

---

## 📎 Attached Submissions
- Scanned physical assessment paper and verified evaluation sheet available in:  
  [`Assessment tool-3 Operating system (1).pdf`](Assessment%20tool-3%20Operating%20system%20(1).pdf)
