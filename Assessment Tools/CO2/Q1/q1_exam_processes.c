#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static void inspect_proc_status(pid_t pid, const char *role) {
    char path[64], line[256];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) return;
    printf("--- /proc/%d/status (%s) ---\n", pid, role);
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Name:", 5) == 0 || strncmp(line, "State:", 6) == 0 ||
            strncmp(line, "Pid:", 4) == 0  || strncmp(line, "PPid:", 5) == 0  ||
            strncmp(line, "VmRSS:", 6) == 0 || strncmp(line, "voluntary_ctxt", 14) == 0) {
            fputs("  ", stdout);
            fputs(line, stdout);
        }
    }
    fclose(fp);
}

int main(void) {
    const char *roles[3] = {"exam_session", "autosave_worker", "video_proctor"};
    pid_t pids[3];
    printf("Parent Exam Server PID: %d\n", getpid());
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            usleep(300000);
            _exit(0);
        }
    }
    for (int i = 0; i < 3; i++) inspect_proc_status(pids[i], roles[i]);
    for (int i = 0; i < 3; i++) waitpid(pids[i], NULL, 0);
    return 0;
}
