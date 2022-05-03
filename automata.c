#include<stdio.h>
#include <stdlib.h>
/*
CSO Assigment #2 - Riley Brady
N13725426
rpb4838
*/

int main(int num, char *filename) {
    int initArray[5][5];
    int curArray[5][5];
    //Opening txt file
    printf("Generation 0: \n");
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s", filename);
        return 1;
    }
    //Copying txt file into array
    int curr = 0;
    for (int i=0; i<num; i++) {
        for (int j=0; j<num; j++) {
            fscanf(fp, "%d", &curr);
            initArray[i][j] = curr;
            printf("%d ", curr);
        }
        printf("\n");
    }
    printf("\n");
    //Copying array into proxy array
    for (int i=0; i<num; i++) {
        for (int j=0; j<num; j++) {
            curArray[i][j] = initArray[i][j];
        }
    }
    //STARTING THE GAME
    /*
    1. A live cell with fewer than two live neighbors dies
    2. A live cell with more than three live neighbors also dies
    3. A live cell with exactly two or three live neighbors lives
    4. A dead cell with exactly three live neighbors becomes alive
    */
    for (int gen=0; gen<num; gen++) { //Gen loop
        //Main loop
        /*
        Code takes the initArray and scans around every cell
        while storing the modifications in the curArray. 
        Then it copies curArray into initArray and repeats the loop
        */
        for (int i=0; i<num; i++) { //Vertical loop
            for (int j=0; j<num; j++) { //Horizontal loop
                int liveNeighbors = 0;
                //Live cell loop
                    int scanCol = -1;
                    for (int x=0; x<3; x++) { //Scanning initArray alive cell
                        int scanRow = -1;
                        for (int y=0; y<3; y++) {
                            if (x == 1 & y == 1) { //Skipping middle
                                scanRow++;
                                continue;
                            }
                            if (initArray[i+scanCol][j+scanRow] == 1) {
                                liveNeighbors++; //Counting live neighbors
                            }
                            scanRow++;
                        } //horizontal loop sub 3x3
                        scanCol++;
                    } //vertical loop sub 3x3
                    //Dead Cell Modifications 
                    if (initArray[i][j] == 0) {
                        if (liveNeighbors == 3) {
                            curArray[i][j] = 1;
                        }
                    }
                    //Live Cell Modifications
                    if (initArray[i][j] == 1) {
                        if (liveNeighbors == 3) {
                            curArray[i][j] = 1;
                        }
                        if (liveNeighbors == 2) {
                            curArray[i][j] = 1;
                        }
                        if (liveNeighbors > 3) {
                            curArray[i][j] = 0;
                        }
                        if (liveNeighbors < 2) {
                            curArray[i][j] = 0;
                        }
                    }
            } //horizontal loop on main 5x5
        } //vertical loop on main 5x5
        //Displaying and copying to initArray
        //Displaying
        printf("Generation %d: \n", gen+1); 
        for (int i=0; i<num; i++) { //Vertical loop
            for (int j=0; j<num; j++) { //Horizontal loop
                printf("%d", curArray[i][j]);
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");

        //Copying
        for (int i=0; i<num; i++) { //Vertical loop
            for (int j=0; j<num; j++) { //Horizontal loop
                initArray[i][j] = curArray[i][j];
            }
        } 
    } //Gen loop
    //ENDING THE GAME
    //Printing Final Array to New .txt File
    FILE *fptr;
    fptr = fopen ("output.txt", "w");
    for (int i=0; i<num; i++) { //Vertical loop
        for (int j=0; j<num; j++) { //Horizontal loop
            fprintf(fptr, "%d ", curArray[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fclose (fptr);
}