#define _POSIX_C_SOURCE 200809L
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    const char *record = "PATIENT_ID=1042;HR=78;SPO2=99;STATUS=NORMAL\n";
    char buf[128];
    int fd = open("patient_1042.rec", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) return 1;
    write(fd, record, strlen(record));
    close(fd);

    fd = open("patient_1042.rec", O_RDONLY);
    if (fd < 0) return 1;
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    if (n > 0) write(STDOUT_FILENO, buf, (size_t)n);
    close(fd);
    unlink("patient_1042.rec");
    return 0;
}
