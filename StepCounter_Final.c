#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Global variables for filename and FITNESS_DATA array
char filename[256];
FITNESS_DATA *fitnessDataArray = NULL;
int totalRecords = 0;

// Function prototypes
int importFile();
void displayTotalRecords();
void findFewestSteps();
void findLargestSteps();
void findMeanStepCount();
void findLongestPeriodAbove500Steps();

int main() {
    char choice;

    do {
        // Display menu
        printf("\nMenu:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the data and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Exit\n");

        // Get user input
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
                if (importFile() == 1) {
                    printf("Error: could not open file\n");
                    return 1;
                }
                break;
            case 'B':
                displayTotalRecords();
                break;
            case 'C':
                findFewestSteps();
                break;
            case 'D':
                findLargestSteps();
                break;
            case 'E':
                findMeanStepCount();
                break;
            case 'F':
                findLongestPeriodAbove500Steps();
                break;
            case 'Q':
                // Free allocated memory before exiting
                free(fitnessDataArray);
                printf("Program returns 0 & exits\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'Q');

    return 0;
}

int importFile() {
    FILE *file;

    // Get filename from user
    printf("Input filename: ");
    scanf("%s", filename);

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        return 1; // File could not be opened
    }

    // Read the total number of records from the file
    fscanf(file, "%d", &totalRecords);

    // Allocate memory for the FITNESS_DATA array
    fitnessDataArray = (FITNESS_DATA *)malloc(totalRecords * sizeof(FITNESS_DATA));

    // Read data into the array
    for (int i = 0; i < totalRecords; i++) {
        char record[256];
        fscanf(file, " %[^\n]", record);
        tokeniseRecord(record, ",", fitnessDataArray[i].date, fitnessDataArray[i].time, fitnessDataArray[i].steps);
    }

    // Close the file
    fclose(file);

    return 0; // File imported successfully
}

void displayTotalRecords() {
    printf("Total records: %d\n", totalRecords);
}

void findFewestSteps() {
    int minSteps = fitnessDataArray[0].steps;
    char minDate[11];
    char minTime[6];

    for (int i = 1; i < totalRecords; i++) {
        if (fitnessDataArray[i].steps < minSteps) {
            minSteps = fitnessDataArray[i].steps;
            strcpy(minDate, fitnessDataArray[i].date);
            strcpy(minTime, fitnessDataArray[i].time);
        }
    }

    printf("Fewest steps: %s %s\n", minDate, minTime);
}

void findLargestSteps() {
    int maxSteps = fitnessDataArray[0].steps;
    char maxDate[11];
    char maxTime[6];

    for (int i = 1; i < totalRecords; i++) {
        if (fitnessDataArray[i].steps > maxSteps) {
            maxSteps = fitnessDataArray[i].steps;
            strcpy(maxDate, fitnessDataArray[i].date);
            strcpy(maxTime, fitnessDataArray[i].time);
        }
    }

    printf("Largest steps: %s %s\n", maxDate, maxTime);
}

void findMeanStepCount() {
    int sum = 0;

    for (int i = 0; i < totalRecords; i++) {
        sum += fitnessDataArray[i].steps;
    }

    int mean = sum / totalRecords;
    printf("Mean step count: %d\n", mean);
}

void findLongestPeriodAbove500Steps() {
    int start = -1;
    int end = -1;
    int currentStart = -1;
    int currentEnd = -1;

    for (int i = 0; i < totalRecords; i++) {
        if (fitnessDataArray[i].steps > 500) {
            if (currentStart == -1) {
                currentStart = i;
            }
            currentEnd = i;
        } else {
            currentStart = -1;
            currentEnd = -1;
        }

        if (currentEnd - currentStart > end - start) {
            start = currentStart;
            end = currentEnd;
        }
    }

    printf("Longest period start: %s %s\n", fitnessDataArray[start].date, fitnessDataArray[start].time);
    printf("Longest period end: %s %s\n", fitnessDataArray[end].date, fitnessDataArray[end].time);
}











