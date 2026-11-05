#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_CAMERAS 64
#define WORK_ITERS  500000

static int next_cam = 0;
static long plates_unprotected = 0;
static long plates_protected   = 0;
static pthread_mutex_t queue_mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t count_mtx = PTHREAD_MUTEX_INITIALIZER;

static void simulate_ocr_frame(int cam_id, int protect_flag) {
    volatile double acc = cam_id * 1.001;
    for (int i = 0; i < WORK_ITERS; i++) acc += (i ^ cam_id) * 0.000001;
    for (int k = 0; k < 1000; k++) {
        if (protect_flag) {
            pthread_mutex_lock(&count_mtx);
            plates_protected++;
            pthread_mutex_unlock(&count_mtx);
        } else {
            plates_unprotected++;
        }
    }
}

static void *pool_worker(void *arg) {
    int protect_flag = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&queue_mtx);
        int cam = next_cam++;
        pthread_mutex_unlock(&queue_mtx);
        if (cam >= NUM_CAMERAS) break;
        simulate_ocr_frame(cam, protect_flag);
    }
    return NULL;
}

int main(void) {
    int protect = 1;
    pthread_t tids[16];
    for (int i = 0; i < 16; i++) pthread_create(&tids[i], NULL, pool_worker, &protect);
    for (int i = 0; i < 16; i++) pthread_join(tids[i], NULL);
    printf("Protected Counter: %ld (Expected 64000)\n", plates_protected);
    return 0;
}
