#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int src, dest;
    ssize_t n;
    char buffer[100];

    src = open("source.txt", O_RDONLY);
    if (src < 0) {
        perror("Cannot open source.txt");
        return 1;
    }

    dest = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Cannot open destination.txt");
        close(src);
        return 1;
    }

    while ((n = read(src, buffer, sizeof(buffer))) > 0) {
        ssize_t written = 0;
        while (written < n) {
            ssize_t w = write(dest, buffer + written, n - written);
            if (w < 0) {
                perror("Write failed");
                close(src);
                close(dest);
                return 1;
            }
            written += w;
        }
    }

    if (n < 0) {
        perror("Read failed");
        close(src);
        close(dest);
        return 1;
    }

    close(src);
    close(dest);
    printf("File copied successfully.\n");
    return 0;
}
