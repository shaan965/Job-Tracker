
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX 1000

struct arguments {
    bool valid;     // Ascertains if the arguments are valid
    int jobs;
    int workers;
    char* infile;
    char* outfile;
};

struct parameters {
    bool valid;     // Ascertains if the input is valid
    char *outfile;  // It will give the name of the output file that can be used later or NULL for printing to stdout
    int n;
    int m;
    struct job **jobs; // An array of points to struct job
};

struct job {
    int ptime;
    int cost;
};

int inRange(int v);
struct arguments* read_arguments(int argc, char* argv[]);
struct parameters* read_parameters(struct arguments *args);
void random_instance(int n, struct job **jobs);
int cmp(const void *a, const void *b);
