/*Author: Muhammad Safwan Hossain*/
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
    for (int i; i < jobCount; i++){
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

int rejectedtotalCost(int jobCount, int rejCost[]){
    int totalCost = 0, length = (jobCount/2);

    for (int i = 0; i < length; i++){
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
    
    char filename[50];
    int jobCount, jobPosition = 0;
    int totalList[jobCount * 2];
    int rejCost[jobCount], neededTime[jobCount];
    int completeCount = 0, rejectCount = 0;
    bool wrongInput;

    int indexRand[jobCount];
    int timeCalc = 0, totalTime = 0;
    int numberofselectedjobs = 0;

    srand(time(NULL));

    // reading the file 
    scanf("%s", filename);

    FILE *openFile = fopen(filename, "r");

    if (openFile == NULL){
        printf("invalid instance.\n");
        return 1;
    }

    int errorCheck = fscanf(openFile, "%d", &jobCount);

    if (jobCount <= 0){ // also need to check if input is not int 
        printf("invalid instance.\n");
    }  

    while (!feof(openFile)){
        

         // Read Numbers Using scanf and for Loop.
        for (int i = 0; i < 10; i++){
            scanf("%d", &totalList[i]);     //check if the jobCount is 
                                            // stored differently or not
        }

        // Adding numbers to specific lists Using for Loop.
        for (int i = 0; i < 10; i++){
            if (i % 2 != 0){
                neededTime[completeCount] = totalList[i];
                completeCount++;
            }
        else{
                rejCost[rejectCount] = totalList[i];
                rejectCount++;
            }
        }

        // checking if the value of each condition is correct or not
        wrongInput = checkValidity(jobCount, neededTime, rejCost);
        }

        

    // close file
    fclose(openFile);

    // closing file for wrong input
    if (!wrongInput){
        printf("invalid instance.\n");
        exit(1);
    }

    // program run
    displayscreen(jobCount, neededTime, rejCost);

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

    orderedJobs(numberofselectedjobs, sTime, sCost);
    
    //getting total time
    totalTime = addTime(numberofselectedjobs, sTime);

    //calculating the rejection cost
    int sumCost[numberofselectedjobs];

    for (int i = 0; i < jobCount; i++){
        if(sCost[i] != rejCost[i]){
           sumCost[i] = rejCost[i]; 
        }
    }

    int rejectionCost = rejectedtotalCost(numberofselectedjobs, sumCost);

    printjobs(numberofselectedjobs, sTime, sCost);
    finalPrint(totalTime, rejectionCost);

}   
