/*
 * Author: Muhammad Safwan Hossain
 * Collaborators: None
 */

#include "definitions.h"

int main(int argc, char* argv[]) {

    struct arguments *args = read_arguments(argc, argv); // Reads arguments

    if (!args->valid) {
        printf("Invalid Arguments\n");
    }
    else {
        struct parameters* params = read_parameters(args);   // Reads instance
        printf("Valid: %d\n", params->n);

        if (params->valid) {
            // Sort it in SPT order
            qsort(params->jobs, params->n, sizeof(struct job*), cmp);

            for (int i = 0; i < params->n; i++) {
                printf("%d %d\n", params->jobs[i]->ptime, params->jobs[i]->cost);
            }
        }
        else {
            printf("invalid instance\n");
        }
    }

    return 0;
}



