#include "definitions.h"

int inRange(int v) { return (1 <= v) && (v <= MAX);}

void random_instance(int n, struct job **jobs) {
    // Generates a random instance and stores it in the array jobs.

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int t = rand() % MAX + 1;
        int c = rand() % MAX + 1;

        struct job *job = calloc(1, sizeof(struct job));
        job->ptime = t;
        job->cost = c;

        jobs[i] = job;
    }
}

int cmp(const void *a, const void *b) {
    // a & b would be pointers to elements of the jobs array
    // However, the jobs array contains pointer to struct job
    // so a & b will be pointer to a pointer to struct job.
    struct job *j1 = *(struct job **) (a);
    struct job *j2 = *(struct job **) (b);

    return j1->ptime - j2->ptime;
}
