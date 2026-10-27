#include <stdio.h>

int main(void) {
    int pages[] = {1, 2, 3, 2, 1, 4, 2, 5, 1};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames[3] = {-1, -1, -1};
    int next = 0, hits = 0, faults = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < 3; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (found) {
            hits++;
        } else {
            frames[next] = pages[i];
            next = (next + 1) % 3;
            faults++;
        }
        printf("Page %d: ", pages[i]);
        for (int j = 0; j < 3; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total page hits: %d\n", hits);
    printf("Total page faults: %d\n", faults);
    return 0;
}
