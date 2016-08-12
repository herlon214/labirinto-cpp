#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;
using std::cout;
using std::endl;
using std::cin;
const int LINES = 50, COLUMNS = 50;

// Functions
bool validMove(char [][ COLUMNS ], int, int );
bool validMovement(int, int, int, char[][COLUMNS]);
void printLabyrinth(char [][COLUMNS]);
int randomNumber(int);
int getMoveNumber(int mov);

int main() {
    char labyrinth[LINES][COLUMNS];
    int line, column;
    int mov = 0;
    int stop = 0;
    int startPoint, endPoint;
    int actualLine, actualColumn;
    vector<int> lineMov, columnMov;
    int totalMov = 0;
    int totalTries = 0;
    int try_n = 0;
    bool isValidMov;

    // Random functions
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);

    // Fill labyrinth with 0
    for(line = 0; line < LINES; line++) {
        for(column = 0; column < COLUMNS; column++) {
            labyrinth[line][column] = '0';
        }
    }

    // Set a start point
    startPoint = randomNumber(LINES);
    endPoint = randomNumber(COLUMNS);

    // Paint the start, end point
    labyrinth[startPoint][0] = '>';
    labyrinth[endPoint][COLUMNS -1] = '<';
    actualLine = startPoint;
    actualColumn = 0;



    // Move on the labyrinth
    while( labyrinth[endPoint][LINES - 2] != ' ') {
        mov = getMoveNumber(mov);
        isValidMov = validMovement(mov, actualLine, actualColumn, labyrinth);

        // If try 4 times back a position
        if(try_n >= 8 && lineMov.size() > 0 && columnMov.size() > 0) {
            //cout << "Reseting ... " << endl;

            // Erase actual
            labyrinth[actualLine][actualColumn] = '0';

            // Reset
            actualLine = lineMov[lineMov.size() - 1];
            actualColumn = columnMov[columnMov.size() - 1];

            lineMov.pop_back();
            columnMov.pop_back();
        }

        switch(mov) {
            // RIGHT
            case 0:
                if(isValidMov) actualColumn++;
                break;
            // DOWN
            case 1:
                if(isValidMov) actualLine++;
                break;
            // LEFT
            case 2:
                if(isValidMov) actualColumn--;
                break;
            // TOP
            case 3:
                if(isValidMov) actualLine--;
                break;
        }

        // Paint the actual position if it's valid
        if(isValidMov) {

            labyrinth[actualLine][actualColumn] = ' ';

            // Increase the movements
            totalMov++;

            // Save the new position
            lineMov.push_back(actualLine);
            columnMov.push_back(actualColumn);

            try_n = 0;

        }else {
            try_n++;
        }


        totalTries++;

        //cout << "" << endl;
        //cout << "Actual line: " << actualLine << endl;
        //cout << "Actual column: " << actualColumn << endl;
        //cout << "Start point: " << startPoint << endl;
        //cout << "End point: " << endPoint << endl;
        //cout << "Movement[" << totalMov << "][" << totalTries << "]: " << mov << endl;
    }


    // Print the labyrinth
    printLabyrinth(labyrinth);

    return 0;
}

// Return a random number with max
int randomNumber(int max) {
    return rand() % max;
}

// Return a movement number
// 0 => right
// 1 => down
// 2 => left
// 3 => up
int getMoveNumber(int mov) {
    return randomNumber(4);
}

// Check if this movement is valid
bool validMovement(int mov, int actualLine, int actualColumn, char labyrinth[][COLUMNS]) {
    // RIGHT
    if(mov == 0) {
        if(actualColumn + 1 == COLUMNS -1 ) return false;

        actualColumn++;
    }
    // DOWN
    if(mov == 1) {
        if(actualLine + 1 == LINES -1) return false;

        actualLine++;
    }

    // LEFT
    if(mov == 2) {
        if(actualColumn == 0 || (actualColumn - 1 == 0)) return false;

        actualColumn--;
    }

    // UP
    if(mov == 3) {
        if(actualLine == 0 || actualColumn == 0 || (actualLine - 1 == 0)) return false;

        actualLine--;
    }

    // CHECK IF THE MOVEMENT ISN'T DONE
    if(labyrinth[actualLine][actualColumn] == ' ') return false;


    return true;
}

void printLabyrinth(char labyrinth[][COLUMNS]) {
    int l, c;

    cout << "" << endl;

    for(l = 0; l < LINES; l++) {
        for(c = 0; c < COLUMNS; c++) {
            cout << labyrinth[l][c] << " ";
        }

        cout << endl;
    }
}
