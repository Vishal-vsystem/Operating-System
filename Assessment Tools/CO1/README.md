# Course Outcome 1 (CO1) — Assessment Tools

**SIMATS ENGINEERING — SAVEETHA INSTITUTE OF MEDICAL AND TECHNICAL SCIENCES**  
**Department of Computer Science and Engineering**

- **Course:** CSA04 — Operating Systems
- **Course Outcome:** **CO1** — *Apply the concepts of Operating System types, structures, and system calls to demonstrate their functions in various computing environments.*
- **Student Name:** Vishal Balaji J
- **Register Number:** 192525014

---

## 📑 Assessment Submissions Index

| Assessment Tool | Theme / Type | Total Marks | Marks Scored | Documentation (.md) | Scanned Script (.pdf) | Status |
|:---:|:---|:---:|:---:|:---:|:---:|:---:|
| **Assessment Tool 1** | Short Answer Test | 100 | **90 / 100** | [View Markdown](Assessment_Tool_1_CO1.md) | [📥 Download PDF](Assesment%20tool-1%20Operating%20system.pdf) | ✅ Evaluated |
| **Assessment Tool 2** | Concept Mapping | 100 | **95 / 100** | [View Markdown](Assessment_Tool_2_CO1.md) | [📥 Download PDF](Assesment%20tool-2%20operating%20system.pdf) | ✅ Evaluated |
| **Assessment Tool 3** | Technical Presentation | 100 | **95 / 100** | [View Markdown](Assessment_Tool_3_CO1.md) | [📥 Download PDF](Assessment%20tool-3%20Operating%20system%20(1).pdf) | ✅ Evaluated |

---

## 📌 Assessment Tool 1 Overview (Short Answer Test)
- **Question 1:** Operating System Types, Multi-user / Time-sharing / Multiprocessor justifications, and `fork()`, `exec()`, `waitpid()` process lifecycle.
- **Question 2:** File and Device Management System Calls, POSIX layered architecture (`VFS` and device drivers), and working C implementation of `open()`, `read()`, `write()`, `close()`.
- **Question 3:** Real-Time Operating Systems (Hard vs. Soft RTOS), hardware interrupt handling, synchronization primitives (Semaphores, Mutexes), and Priority Inversion / Priority Inheritance.
- **Question 4:** Distributed Operating Systems vs. Centralized OS, distributed node architecture, and inter-process communication (`pipe()`, `socketpair()`, sockets API).
- **Question 5:** Core OS Functions (Process, Memory, File, I/O, Protection), kernel subsystem interactions, and memory management calls (`brk()`, `sbrk()`, `mmap()`).

📖 [Read Full Assessment Tool 1 Solutions](Assessment_Tool_1_CO1.md)

---

## 📌 Assessment Tool 2 Overview (Concept Mapping)
- **Question 1:** Multi-level concept map integrating OS Types $\to$ OS Structures $\to$ System Calls $\to$ OS Functions.
- **Question 2:** Comprehensive subsystem interdependency map for Process Management, Memory Management, File System, and I/O Subsystem.
- **Question 3:** Comparative concept map contrasting Batch OS, Time-Sharing OS, Distributed OS, and Real-Time OS.
- **Question 4:** Dynamic end-to-end execution flow: User Program $\to$ API $\to$ System Call Interface (TRAP) $\to$ Kernel $\to$ Hardware $\to$ Response.
- **Question 5:** Hierarchical and functional taxonomy of system calls (Process, File, Device, Information, and Memory).

📖 [Read Full Assessment Tool 2 Concept Maps](Assessment_Tool_2_CO1.md)

---

## 📌 Assessment Tool 3 Overview (Technical Presentation)
- **Slide Deck:** Architecture, System Calls, and Paradigms in Modern Operating Systems.
- **Core Topics:** Monolithic vs. Microkernel vs. Hybrid architectures, system call trapping and dual-mode CPU switching, MMU page translation, RTOS priority inheritance, and modern trends in kernel development (Rust, microservices, containerization).

📖 [Read Full Assessment Tool 3 Presentation](Assessment_Tool_3_CO1.md)


---

## 🏥 Assignment 1 — Evaluate and Justify the Operating-System Design of a Smart Hospital (50 Marks, K5)

- **Student Name:** Vishalbalaji J (`192525014`)
- **Word Report (.docx):**
  - [📥 Download `CSA04_192525014_Vishalbalaji_J_Assignment1.docx`](CSA04_192525014_Vishalbalaji_J_Assignment1.docx)
  - [📥 Download `CSA04_OS_Assignment_1_Smart_Hospital.docx`](CSA04_OS_Assignment_1_Smart_Hospital.docx)
- **Execution Environment:** `Ubuntu 22.04.4 LTS (Kernel 6.5.0-x86_64)` | `gcc 13.2.0 (-std=c11 -Wall -Wextra -pthread)`
- **Task Folders (`Task01` – `Task12`):**
  - [`Task01/`](Task01/) — Evaluate the Requirements of Each Computing Environment
  - [`Task02/`](Task02/) — Judge the Type of Operating System for Each Environment
  - [`Task03/`](Task03/) — Evaluate Operating-System Structures
  - [`Task04/`](Task04/) — Evaluate the Services an Operating System Must Provide
  - [`Task05/`](Task05/) — Examine System Calls (`task05_patient_read.c` & `strace`)
  - [`Task06/`](Task06/) — Evaluate the Cost of System Calls (`task06_copy_syscalls.c` & `strace -c`)
  - [`Task07/`](Task07/) — Evaluate Process Control System Calls (`task07_shell_jobs.c`)
  - [`Task08/`](Task08/) — Evaluate CPU States and Protection
  - [`Task09/`](Task09/) — Evaluate the Memory Hierarchy and I/O Systems
  - [`Task10/`](Task10/) — Measure and Compare (`task10_proc_vs_thread.c` benchmark)
  - [`Task11/`](Task11/) — Recommend and Defend the Operating-System Plan
  - [`Task12/`](Task12/) — Day-4 Design Challenge: Hybrid Cloud-Edge OS Adaptation
