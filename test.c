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


bool test_totalEVs() {
    State aStates[10];
    int res;
    
    // Test case 1
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;
    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    // Checks if total is 38
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 12, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return false;
    }

    // Test case 2
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 15;
    aStates[6].electoralVotes = 12;
    aStates[7].electoralVotes = 8;
    aStates[8].electoralVotes = 14;
    aStates[9].electoralVotes = 13;
    printf(" Checking totalEVs() for 10 States:\n");
    res = totalEVs(aStates,10);
    // Checks if total is 100
    if (res != 100) {
        printf("  individual state EVs are 5, 8, 12, 6, 7, 15, 12, 8, 14, 13\n");
        printf("  expected total EVs = 100, actual total EVs = %d\n",res);
        return false;
    }
    // All test cases passed
    return true;
}

bool test_totalPVs() {
    State aStates[10];
    int res;

    // Test case 1
    aStates[0].popularVotes = 3;
    aStates[1].popularVotes = 25;
    aStates[2].popularVotes = 8;
    aStates[3].popularVotes = 1;
    aStates[4].popularVotes = 19;
    aStates[5].popularVotes = 5;
    printf(" Checking totalPVs() for 5 States:\n");
    res = totalPVs(aStates,5);
    // Checks if total is 56
    if (res != 56) {
        printf("  individual state PVs are 3, 25, 8, 1, 19\n");
        printf("  expected total PVs = 56, actual total PVs = %d\n",res);
        return false;
    }

    // Test case 2
    aStates[0].popularVotes = 3;
    aStates[1].popularVotes = 25;
    aStates[2].popularVotes = 8;
    aStates[3].popularVotes = 1;
    aStates[4].popularVotes = 19;
    aStates[5].popularVotes = 5;
    aStates[6].popularVotes = 13;
    aStates[7].popularVotes = 4;
    aStates[8].popularVotes = 10;
    aStates[9].popularVotes = 4;

    printf(" Checking totalPVs() for 10 States:\n");
    res = totalPVs(aStates,10);
    // Checks if total is 92
    if (res != 92) {
        printf("  individual state PVs are 3, 25, 8, 1, 19, 5, 13, 4, 10, 3\n");
        printf("  expected total PVs = 92, actual total PVs = %d\n",res);
        return false;
    }
    // All test cases passed
    return true;
}

bool test_setSettings() {
    // Test case 1: valid input
    char* argv1[] = {"app.exe", "-y", "2020", "-f", "-q"};
    int argc1 = 5;
    bool fastMode = false;
    bool quietMode = false;
    int year = 0;
    if (!setSettings(argc1, argv1, &year, &fastMode, &quietMode)) {
        printf("Test case 1 failed: setSettings returned false for valid input\n");
        return false;
    }
    if (year != 2020 || !fastMode || !quietMode) {
        printf("Test case 1 failed: incorrect settings returned for valid input\n");
        return false;
    }

    // Test case 2: valid input (missing year)
    char* argv2[] = {"app.exe", "-f", "-q"};
    int argc2 = 3;
    fastMode = false;
    quietMode = false;
    year = 0;
    if (!setSettings(argc2, argv2, &year, &fastMode, &quietMode)) {
        printf("Test case 2 failed: setSettings returned true for invalid input\n");
        return false;
    }

    // Test case 3: invalid input (invalid mode)
    char* argv3[] = {"app.exe", "-y", "2016", "-v", "-q"};
    int argc3 = 5;
    fastMode = false;
    quietMode = false;
    year = 0;
    if (setSettings(argc3, argv3, &year, &fastMode, &quietMode)) {
        printf("Test case 3 failed: setSettings returned true for invalid input\n");
        return false;
    }

    // All test cases passed
    return true;
}

bool test_inFilename() {
    // Test case 1
    int year = 2020;
    char filename[50];
    inFilename(filename, year);
    if (strcmp(filename, "data/2020.csv") != 0) {
        printf("Test case 1 failed: incorrect filename returned for valid input\n");
        return false;
    }

    // Test case 2
    year = 2016;
    char filename2[50];
    inFilename(filename2, year);
    if (strcmp(filename2, "data/2016.csv") != 0) {
        printf("Test case 2 failed: incorrect filename returned for valid input\n");
        return false;
    }

    // All test cases passed
    return true;
}

bool test_outFilename() {
    // Test case 1
    int year = 2020;
    char filename[50];
    outFilename(filename, year);
    if (strcmp(filename, "toWin/2020_win.csv") != 0) {
        printf("Test case 1 failed: incorrect filename returned for valid input\n");
        return false;
    }

    // Test case 2
    year = 2016;
    char filename2[50];
    outFilename(filename2, year);
    if (strcmp(filename2, "toWin/2016_win.csv") != 0) {
        printf("Test case 2 failed: incorrect filename returned for valid input\n");
        return false;
    }
    // All test cases passed
    return true; 
}

bool test_parseLine() {
    // Test case 1: valid input
    State state;
    char line[100] = "Illinois,IL,20,6033744";
    if (!parseLine(line, &state)) {
        printf("Test case 1 failed: parseLine returned false for valid input\n");
        return false;
    }

    // Test case 2: valid input
    State state2;
    char line2[100] = "Illinois,IL,20,6033744\n";
    if (!parseLine(line2, &state2)) {
        printf("Test case 2 failed: parseLine returned false for valid input\n");
        return false;
    }
    
    // Test case 3: invalid input
    State state3;
    char line3[100] = "Illinois,IL,20";
    if (parseLine(line3, &state3)) {
        printf("Test case 3 failed: parseLine returned true for invalid input\n");
        return false;
    }

    // All test cases passed
    return true; 
}

bool test_readElectionData() {
    State allStates[51];
    int nStates = 0;

    // Test case 1: valid input
    char filename1[] = "data/1832.csv";
    if (!readElectionData(filename1, allStates, &nStates)) {
        printf("Test case 1 failed: readElectionData returned false for valid input\n");
        return false;
    }
    if ((nStates != 24) || (strcmp(allStates[0].name, "Alabama") != 0) ||
        (strcmp(allStates[1].name, "Connecticut") != 0) || (strcmp(allStates[2].name, "Delaware") != 0)) {        
        printf("Test case 1 failed: incorrect state data returned for valid input\n");
        return false;
    }

    // Test case 2: invalid input
    char filename2[] = "nonexistent_file.txt";
    if (readElectionData(filename2, allStates, &nStates)) {
        printf("Test case 2 failed: readElectionData returned true for invalid input\n");
        return false;
    }

    // All test cases passed
    return true;
}

bool test_minPVsSlow() {
    // Test case 1: valid input
    State allStates[51];
    int nStates = 0;

    char filename1[] = "data/1916.csv";
    if (!readElectionData(filename1, allStates, &nStates)) {
        printf("Test case 1 failed: readElectionData returned false for valid input\n");
        return false;
    }
    MinInfo minPVs = minPopVoteToWinFast(allStates, nStates);
    if (!minPVs.sufficientEVs) {
        printf("Test case 1 failed: incorrect minimum popular votes returned for valid input\n");
        return false;
    }

    // Test case 2: valid input
    char filename2[] = "data/1828.csv";
    if (!readElectionData(filename2, allStates, &nStates)) {
        printf("Test case 2 failed: readElectionData returned true for invalid input\n");
        return false;
    }
    MinInfo minPVs2 = minPopVoteToWinFast(allStates, nStates);
    if (!minPVs2.sufficientEVs) {
        printf("Test case 2 failed: incorrect minimum popular votes returned for valid input\n");
        return false;
    }

    // All test cases passed
    return true;
}

bool test_minPVsFast() {
    // Test case 1: valid input
    char filename1[] = "data/1916.csv";
    State allStates[51];
    int nStates = 0;
    if (!readElectionData(filename1, allStates, &nStates)) {
        printf("Test case 1 failed: readElectionData returned false for valid input\n");
        return false;
    }
    MinInfo minPVs = minPopVoteToWinFast(allStates, nStates);
    if (!minPVs.sufficientEVs) {
        printf("Test case 1 failed: incorrect minimum popular votes returned for valid input\n");
        return false;
    }

    // Test case 2: valid input
    char filename2[] = "data/1828.csv";
    if (!readElectionData(filename2, allStates, &nStates)) {
        printf("Test case 2 failed: readElectionData returned true for invalid input\n");
        return false;
    }
    MinInfo minPVs2 = minPopVoteToWinFast(allStates, nStates);
    if (!minPVs2.sufficientEVs) {
        printf("Test case 2 failed: incorrect minimum popular votes returned for valid input\n");
        return false;
    }
    // All test cases passed
    return true;
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
