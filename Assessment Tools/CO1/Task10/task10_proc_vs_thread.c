#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>

#define COUNT 1000

static double diff_ms(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1000.0 + (b.tv_nsec - a.tv_nsec) / 1e6;
}

static void *thread_worker(void *arg) {
    (void)arg;
    return NULL;
}

int main(void) {
    struct timespec t0, t1;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int i = 0; i < COUNT; i++) {
        pid_t pid = fork();
        if (pid == 0) _exit(0);
        waitpid(pid, NULL, 0);
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double fork_ms = diff_ms(t0, t1);

    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int i = 0; i < COUNT; i++) {
        pthread_t tid;
        pthread_create(&tid, NULL, thread_worker, NULL);
        pthread_join(tid, NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    double thread_ms = diff_ms(t0, t1);

    printf("1,000 fork()+waitpid() processes : %7.2f ms (%.2f us/proc)\n", fork_ms, fork_ms * 1000.0 / COUNT);
    printf("1,000 pthread_create()+join()    : %7.2f ms (%.2f us/thread)\n", thread_ms, thread_ms * 1000.0 / COUNT);
    printf("Speedup Ratio (Process / Thread) : %7.2fx faster with threads\n", fork_ms / thread_ms);
    return 0;
}
