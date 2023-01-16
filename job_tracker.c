/*References: https://www.learnc.net/c-tutorial/c-read-text-file/*/ //www.geeksforgeeks.org/bubble-sort/ https://www.codespeedy.com/generate-a-random-array-in-c-or-cpp/

#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include <stdlib.h>

void printjobs(int jobCount, int neededTime[jobCount], int rejCost[jobCount]);
void orderedJobs(int jobNumber, int neededTime[jobNumber], int rejCost[jobNumber]);
int addTime(int numberofJobs, int neededTime[]);
int rejectedtotalCost(int jobCount, int rejCost[]);
void displayscreen(int jobCount, int neededTime[jobCount], int rejCost[jobCount]);
bool checkValidity(int jobCount, int neededTime[jobCount], int rejCost[jobCount]);
void finalPrint(int totalTime, int totalCost);



void printjobs(int jobCount, int neededTime[jobCount], int rejCost[jobCount]){
    for (int i = 0; i < jobCount; i++){
        printf("%d %d\n", neededTime[i], rejCost[i]);
    }
}

void orderedJobs(int jobNumber, int neededTime[jobNumber], int rejCost[jobNumber]){  // put completion time list
    for (int i = 0; i < jobNumber; i++){
        for (int j = 0; j < jobNumber - 1; j++){
            if (neededTime[j] > neededTime[j+1]){
                int temp1 = neededTime[j];
                int temp2 = rejCost[j];
                neededTime[j] = neededTime[j+1];
                rejCost[j] = rejCost[j+1];
                neededTime[j+1] = temp1;
                rejCost[j+1] = temp2;
            }
        }
    }
}

int addTime(int numberofJobs, int neededTime[]){
    int timeCalc = 0, totalTime = 0;
    for (int i = 0; i < numberofJobs; i++){
        // get index value from neededTime using the value of randomTimeIdx
        // and sum the total needed time
        timeCalc += neededTime[i];
        totalTime += timeCalc;
    } 
    return totalTime;
}

int rejectedtotalCost(int jobCount, int rejCost[jobCount]){
    int totalCost = 0;

    for (int i = 0; i < jobCount; i++){
        totalCost += rejCost[i];
    }
    return totalCost; 
}


void displayscreen(int jobCount, int neededTime[jobCount], int rejCost[jobCount]){

    printf("%d\n", jobCount);

    printjobs(jobCount, neededTime, rejCost);

    printf("\n\n");

    printf("The accepted jobs in SPT order: \n");
}

bool checkValidity(int jobCount, int neededTime[jobCount], int rejCost[jobCount]){
    bool wrongInput = false;
    // checking if the value of each condition is correct or not
    for (int i; i < jobCount; i++){
        if (neededTime[i] < 1 || neededTime[i] > 1000){
            wrongInput = true;
            break;
        }

        if (rejCost[i] < 1 || rejCost[i] > 1000){
            wrongInput = true;
            break;
        }
    }
    return wrongInput;
}

void finalPrint(int totalTime, int totalCost){
    int objective = totalCost + totalTime;

    printf("total completion time = %d\n", totalTime);
    printf("total rejection cost = %d\n", totalCost);
    printf("objective = %d\n", objective);
}

int main(void){
    
    int jobCount, totalTime = 0, numberofselectedjobs = 0;

    bool wrongInput;


    srand(time(NULL));
    
    scanf("%d", &jobCount);
    int rejCost[jobCount], neededTime[jobCount], indexRand[jobCount];

    
    if (jobCount <= 0 || jobCount > 1000){ // also need to check if input is not int 
        printf("invalid instance.\n");
	exit(1);
    }  
  
    // Read Numbers Using scanf and for Loop.
    for (int i = 0; i < jobCount; i++){
        scanf("%d %d", &neededTime[i], &rejCost[i]);     //check if the jobCount is stored differently or not
    }

    // checking if there is all jobs are in the list
    if ((jobCount != (sizeof(neededTime)/sizeof(neededTime[0]))) || (jobCount != (sizeof(rejCost)/sizeof(rejCost[0])))){
	printf("invalid instance.\n");
	exit(1);	
    }

    // checking if the value of each condition is correct or not
    wrongInput = checkValidity(jobCount, neededTime, rejCost);

    // closing file for wrong input
    if (wrongInput == 1){
        printf("invalid instance.\n");
        exit(1);
    }

    printf("%d\n", jobCount);

    printjobs(jobCount, neededTime, rejCost);

    printf("\n");

    printf("The accepted jobs in SPT order: \n");

    // program run

    for (int i = 0; i < jobCount; i++){
        if (rand() % 2 == 0){       // 50% chance of each being selected
            indexRand[numberofselectedjobs] = i;
            numberofselectedjobs++;
        }
    } 

    // list according to the random index
    int sTime[numberofselectedjobs], sCost[numberofselectedjobs];

    for (int i = 0; i < numberofselectedjobs; i++) {
        sTime[i] = neededTime[indexRand[i]];
        sCost[i] = rejCost[indexRand[i]];
    }

    
    // ordering the lists according to the time of jobs
    orderedJobs(numberofselectedjobs, sTime, sCost);
    
    for (int i = 0; i < numberofselectedjobs; i++) {
	    printf("%d %d\n", sTime[i], sCost[i]);
    }
 
    int rejTotal = 0;
    for (int i = 0; i < jobCount; i++) {
	int flag = 1;
	for (int k = 0; k < numberofselectedjobs; k++) {
		if (i == indexRand[k]) {
			flag = 0;
			break;
		}
	}
	if (flag) {
		rejTotal += rejCost[i];
	}
    }
	
    totalTime = addTime(numberofselectedjobs, sTime);
    finalPrint(totalTime, rejTotal);
    
}   