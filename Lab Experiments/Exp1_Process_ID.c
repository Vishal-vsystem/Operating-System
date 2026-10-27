#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
    return 0;
}
