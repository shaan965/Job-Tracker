
#include "definitions.h"

struct parameters* read_parameters(struct arguments *args) {
    struct parameters* params = calloc(1, sizeof(struct parameters));

    bool valid = args->valid;
    FILE* infile = NULL;
    int n = 0, m = 1;
    
    if (valid) {

        // Read the number of workers
        if (args->workers != 0) {
            m = args->workers;
        }

        // Read the number of jobs
        struct job **jobs = NULL;

        if (args->jobs != 0) {
            // Randomly generate instance
            n = args->jobs;
            jobs = calloc(n, sizeof(struct job *));
            random_instance(n, jobs);
        }
        else {
            // Read instance from stdin or input file
            if (args->infile != NULL) {
                freopen(args->infile, "r", stdin); // Reopen the infile as stdin
            }

            // Read the values from stdin now
            valid = scanf("%d\n", &n) == 1;

            if (valid) {
                // Read the input values (at this point n should have a correct value)
                jobs = calloc(n, sizeof(struct job *));

                for (int i = 0; i < n; i++) {
                    struct job *job = calloc(1, sizeof(struct job));

                    if (scanf("%d %d", &(job->ptime), &(job->cost)) != 2) {
                        valid = false;
                    }

                    if (!inRange(job->ptime) || !inRange(job->cost)) {
                        valid = false;
                    }

                    jobs[i] = job;
                }
            }
        }

        if (valid) {
            // Set the params
            params->valid = valid;
            params->n = n;
            params->m = m;
            params->jobs = jobs;
            params->outfile = args->outfile;
        }
    }

    return params;
}


struct arguments* read_arguments(int argc, char* argv[]) {

    // The first argument is the name of the program
    /*
        *  -i infile
        *  -o outfile
        * 
        *  -n numjobs
        *  -m workers
    */

    struct arguments *args = calloc(1, sizeof(struct arguments));

    bool valid = true;
    if (argc == 1) {
        valid = true;
    }
    else if (argc > 1) {
        if ((argc-1) % 2 != 0) {
            valid = false;
        }
        else {
            // At this point argv[1] can be -i, -o, -n or -m
            bool gotInput = false;
            for (int i = 1; i < argc; i += 2) {
                if (strcmp("-i", argv[i]) == 0) {
                    if (!gotInput) {
                        args->infile = calloc(strlen(argv[i+1]) + 1, sizeof(char));
                        strcpy(args->infile, argv[i+1]);
                        gotInput = true;
                    }
                    else {
                        valid = false;
                        break;
                    }
                }
                else if (strcmp("-o", argv[i]) == 0) {
                    args->outfile = calloc(strlen(argv[i+1]) + 1, sizeof(char));
                    strcpy(args->outfile, argv[i+1]);
                }
                else if (strcmp("-n", argv[i]) == 0) {
                    if (!gotInput) {
                        args->jobs = atoi(argv[i+1]);
                        gotInput = true;
                    }
                    else {
                        valid = false;
                        break;
                    }
                }
                else if (strcmp("-m", argv[i]) == 0) {
                    args->workers = atoi(argv[i+1]);
                }
                else {
                    valid = false;
                }
            }
        }
    }
    else {
        valid = false;
    }

    args->valid = valid;

    return args;
}


void free_args(struct arguments * args) {
    if (args->infile != NULL) {
        free(args->infile);
        args->infile = NULL;
    }

    if (args->outfile != NULL) {
        free(args->outfile);
        args->outfile = NULL;
    }

    free(args);
}

void free_params(struct parameters * params) {
    if (params->outfile != NULL) {
        free(params->outfile);
        params->outfile = NULL;
    }

    for (int i = 0; i < params->n; i++) {
        if (params->jobs[i] != NULL) {
            free(params->jobs[i]);
        }
    }

    free(params);
}