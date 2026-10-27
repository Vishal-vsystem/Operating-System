#include <stdio.h>
#define MAX 20

void show(const char *name, int n, int bt[], int wt[], int tat[]) {
    float awt = 0, atat = 0;
    printf("\n%s\n", name);
    printf("P\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
        awt += wt[i];
        atat += tat[i];
    }
    printf("Average waiting time: %.2f\n", awt / n);
    printf("Average turnaround time: %.2f\n", atat / n);
}

int main(void) {
    int n, bt[MAX], wt[MAX], tat[MAX], rem[MAX], pr[MAX], order[MAX];
    int quantum = 2;

    printf("Enter number of processes (1-%d): ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return 1;

    for (int i = 0; i < n; i++) {
        printf("Burst time for P%d: ", i + 1);
        if (scanf("%d", &bt[i]) != 1 || bt[i] < 1) return 1;
        order[i] = i;
        rem[i] = bt[i];
    }

    /* FCFS */
    wt[0] = 0;
    for (int i = 1; i < n; i++) wt[i] = wt[i-1] + bt[i-1];
    for (int i = 0; i < n; i++) tat[i] = wt[i] + bt[i];
    show("FCFS", n, bt, wt, tat);

    /* Non-preemptive SJF: sort process indexes by burst time */
    for (int i = 0; i < n; i++) order[i] = i;
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (bt[order[j]] < bt[order[i]]) {
                int tmp = order[i]; order[i] = order[j]; order[j] = tmp;
            }
    int elapsed = 0;
    for (int k = 0; k < n; k++) {
        int p = order[k];
        wt[p] = elapsed;
        tat[p] = wt[p] + bt[p];
        elapsed += bt[p];
    }
    show("SJF (non-preemptive)", n, bt, wt, tat);

    /* Round Robin with quantum = 2; all processes arrive at time 0 */
    for (int i = 0; i < n; i++) rem[i] = bt[i], wt[i] = 0;
    int time = 0, done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                done = 0;
                int run = rem[i] < quantum ? rem[i] : quantum;
                time += run;
                rem[i] -= run;
                if (rem[i] == 0) tat[i] = time;
            }
        }
    } while (!done);
    for (int i = 0; i < n; i++) wt[i] = tat[i] - bt[i];
    show("Round Robin (q = 2)", n, bt, wt, tat);

    /* Non-preemptive Priority; lower priority number = higher priority */
    for (int i = 0; i < n; i++) {
        printf("Priority for P%d (lower number = higher priority): ", i + 1);
        if (scanf("%d", &pr[i]) != 1) return 1;
        order[i] = i;
    }
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (pr[order[j]] < pr[order[i]]) {
                int tmp = order[i]; order[i] = order[j]; order[j] = tmp;
            }
    elapsed = 0;
    for (int k = 0; k < n; k++) {
        int p = order[k];
        wt[p] = elapsed;
        tat[p] = wt[p] + bt[p];
        elapsed += bt[p];
    }
    show("Priority (non-preemptive)", n, bt, wt, tat);

    return 0;
}
