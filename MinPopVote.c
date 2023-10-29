/*-------------------------------------------
Program 4: Popular Vote Minimizer
Course: CS 211, Fall 2023, UIC
System: Advanced zyLab
Author: Eric Mai
------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MinPopVote.h"

// This function sets the program settings based on the command line arguments passed to the program.
// Parameters:
// - argc: The number of command line arguments passed to the program.
// = argv: The array of command line arguments passed to the program.
// = year: A pointer to an integer that will be set to the year specified by the command line arguments.
// returns bool 
bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    // Set the default values
    *year = 0;
    *fastMode = false;
    *quietMode = false;
    bool valid = true;

    // Loop through the command line arguments and set the program settings
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            *fastMode = true;
        } 
        else if (strcmp(argv[i], "-q") == 0) {
            *quietMode = true;
        } 
        else if ((strcmp(argv[i], "-y") == 0) && (i + 1 < argc)) {
            // Check if the year is valid
            int numyear = atoi(argv[i + 1]);
            if ((numyear % 4 == 0) && (numyear >= 1828) && (numyear <= 2020)) {
                *year = numyear;
            } 
            i++;
        }
        else {
            valid = false;
        }
    }
    return valid;
}

// This function makes the usage message for the program.
// Parameters:
// - filename: The name of the file
// - year: The year specified by the command line arguments.
// returns void
void inFilename(char* filename, int year) {
    sprintf(filename, "data/%d.csv", year);
    return;
}

// This function makes the output name for the program.
// Parameters:
// - filename: The name of the file
// - year: The year specified by the command line arguments.
// returns void
void outFilename(char* filename, int year) {
    sprintf(filename, "toWin/%d_win.csv", year);
    return;
}

// This function parses a line of input from the election data file and stores the relevant information in a State struct.
// Parameters:
// - line: The line of input from the election data file.
// - myState: A pointer to a State struct that will be filled with the relevant information from the line of input.
// returns bool
bool parseLine(char* line, State* myState) {
    char* token = strtok(line, ","); // Get the first token
    if (token == NULL) {
        return false;
    }
    strcpy(myState->name, token);

    token = strtok(NULL, ","); // Get the next token
    if (token == NULL) {
        return false;
    }
    strcpy(myState->postalCode, token);

    token = strtok(NULL, ","); // Get the next token
    if (token == NULL) {
        return false;
    }
    myState->electoralVotes = atoi(token);

    token = strtok(NULL, ","); // Get the next token
    if (token == NULL) {
        return false;
    }
    myState->popularVotes = atoi(token);

    return true;
}

// Reads election data from a file and stores it in an array of State structs.
// Parameters:
// - filename: The name of the file to read from.
// - allStates: A pointer to an array of State structs that will be filled with the election data.
// - nStates: A pointer to an integer that will be set to the number of states read from the file.
// returns bool
bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0;
    // Check if the filename is NULL
    if(filename == NULL){
        return false;
    }

    FILE* file = fopen(filename, "r");
    // Check if the file is NULL
    if(file == NULL){
        return false;
    }
    // Read the file line by line and parse each line
    while(!feof(file)){
        char line[100];
        fgets(line, 100, file);
        if(parseLine(line, &allStates[*nStates])){
            (*nStates)++;
        }

    }
    fclose(file);

    return true;
}

// This function returns the total electoral votes
// Parameters:
// - states: A pointer to an array of State structs that will be filled with the election data.
// - szStates: The number of states in the array.
// returns int
int totalEVs(State* states, int szStates) {
    int evTotal = 0;
    // Loop through all the states and add up the electoral votes
    for(int i = 0; i < szStates; i++){
        evTotal += states[i].electoralVotes;
    }
    return evTotal; 
}

// This function returns the total popular votes
// Parameters:
// - states: A pointer to an array of State structs that will be filled with the election data.
// - szStates: The number of states in the array.
// returns int
int totalPVs(State* states, int szStates) {
    int pvTotal = 0;
    // Loop through all the states and add up the popular votes
    for(int i = 0; i < szStates; i++){
        pvTotal += states[i].popularVotes;
    }
    return pvTotal; 
}

// This function returns the minimum popular votes to win the election
// Parameters:
// - states: A pointer to an array of State structs that will be filled with the election data.
// - szStates: The number of states in the array.
// - start: The starting index of the array.
// - EVs: The number of electoral votes.
// returns MinInfo
MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    MinInfo withState, withoutState;
    // Base cases
    if (EVs <= 0){
        withState.szSomeStates = 0;
        withState.subsetPVs = 0;
        withState.sufficientEVs = true;
        return withState;
    }
    if (szStates == start){
        withState.szSomeStates = 0;
        withState.subsetPVs = 0;
        withState.sufficientEVs = false;
        return withState;
    }
    // Recursive case
    withState = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes);
    // Add the current state to the subset
    withState.someStates[withState.szSomeStates++] = states[start];
    // Add the popular votes of the current state to the subset
    withState.subsetPVs += ((states[start].popularVotes)/2) + 1;
    // Calculate the subset without the current state
    withoutState = minPopVoteAtLeast(states, szStates, start + 1, EVs);

    // Choose the better result
    if ((withState.subsetPVs > withoutState.subsetPVs) && withoutState.sufficientEVs) {
        return withoutState;
    } else {
        return withState;
    }
}

// This function returns the minimum popular votes to win the election
// Parameters:
// - states: A pointer to an array of State structs that will be filled with the election data.
// - szStates: The number of states in the array.
// returns minInfo
MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

// This function returns the minimum popular votes to win the election in more optimized approach
// Parameters:
// - states: A pointer to an array of State structs that will be filled with the election data.
// - szStates: The number of states in the array.
// - start: The starting index of the array.
// - EVs: The number of electoral votes.
// - memo: A pointer to an array of MinInfo structs that will be filled with the election data.
// returns MinInfo
MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    MinInfo withState, withoutState;
    // Base cases
    if (EVs <= 0){
        withState.szSomeStates = 0;
        withState.subsetPVs = 0;
        withState.sufficientEVs = true;
        return withState;
    }
    if (szStates == start){
        withState.szSomeStates = 0;
        withState.subsetPVs = 0;
        withState.sufficientEVs = false;
        return withState;
    }

    // Check if the result is already calculated
    if (memo[start][EVs].subsetPVs != -1) {
        return memo[start][EVs];
    }

    // Recursive case
    withState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo);
    withState.someStates[withState.szSomeStates++] = states[start];
    withState.subsetPVs += ((states[start].popularVotes) / 2) + 1;
    withoutState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo);
    MinInfo result;
    // Choose the better result
    if (withState.subsetPVs > withoutState.subsetPVs && withoutState.sufficientEVs) {
        result = withoutState;
    } else {
        result = withState;
    }

    // Save the result in the memo table
    memo[start][EVs] = result;

    return result;
}

// This function returns the minimum popular votes to win the election in more optimized approach
// Parameters:
// - states: A pointer to an array of State structs that will be filled with the election data.
// - szStates: The number of states in the array.
// returns MinInfo
MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    
    // Free the memo table
    for (int i = 0; i < szStates+1; ++i) {
        free(memo[i]);
    }
    free(memo);

    return res;
}

// This function writes the subset of states that minimizes the popular vote to a file.
// Parameters:
// - filenameW: The name of the file to write to.
// - totEVs: The total number of electoral votes.
// - totPVs: The total number of popular votes.
// - wonEVs: The number of electoral votes needed to win the election.
// - toWin: A MinInfo struct that contains the subset of states that minimizes the popular vote.
// returns bool
bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    FILE* file = fopen(filenameW, "w");
    if (file == NULL) {
        return false;  // Return false if the file couldn't be opened for writing
    }

    // Write the first line of the output file
    fprintf(file, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs);

    // Write individual State details
    for (int i = toWin.szSomeStates - 1; i >= 0; i--) {
        fprintf(file, "%s,%s,%d,%d\n", toWin.someStates[i].name, toWin.someStates[i].postalCode, toWin.someStates[i].electoralVotes, (toWin.someStates[i].popularVotes / 2) + 1);
    }

    fclose(file);
    return true;
}
