// two player connect four

// draw board on screen
// make array for board
// get user input (user will just pick column)
// update array acordingly
// check for winning combo

#include <iostream>
using namespace std;
#include <stdlib.h> // for rand
#include <windows.h>

// constant macro
#define height 6
#define width 7

int board_arr[height][width] = {{0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0},
                                {0,0,0,0,0,0,0}};

// last moves
int prevX, prevY;

// method to print board to command line
void drawBoard() {
    cout << endl; // inserts new line

    // iterating through array printing X and O for each player
    for (int y=0; y<height; y++) {
        for (int x=0; x<width; x++) {
            cout << "| ";
            // 0 == neither player so " "
            // 1 == player 1 so "X"
            // 2 == player 2 so "O"
            if (board_arr[y][x] == 0) cout << " ";
            else if (board_arr[y][x] == 1) cout << "X";
            else if (board_arr[y][x] == 2) cout << "O";
        }
        // split up each row
        cout << "\n---------------------" << endl;
    }
}


// player turn method
void playerMove(int player) {
    int choice;
    cout << "\nPlayer" << player << ", please select a number from 1 - 7: ";
    cin >> choice;

    // error checks
    if (cin.fail()) {
        cout << "Error!";
        exit(1);
    } 

    while (choice>width || choice<=0) {
        cout << "\nPlease select again: ";
        cin >> choice;
    }

    // player must select again if the column they picked is full
    int number=0;
    while (board_arr[(height-1)-number][(choice-1)] != 0) {
        number++;
        if (number>(height-1)) {
            cout << "\nPlease select again: ";
            cin >> choice;
            number=0; //resetting number for players new choice
        }
    };

    // entering players number into their chosen column
    board_arr[(height-1)-number][choice-1] = player; 
    prevX = choice-1;
    prevY = (height-1)-number;
}

// checking for diagonal / win
bool checkDiagSWtoNE(int x, int y, int player) {
    int score = 1;
    int count = 1;

    while((y-count >= 0) && (x+count < width)) {
        if (board_arr[y-count][x+count] == player) {
            // checking from SW to NE first
            score++;
            count++;
        }
        // if no combo detected then exit loop
        else break;
    }

    count = 1;
    while((y+count < height) && (x-count >= 0)) {
        if (board_arr[y+count][x-count] == player) {
            // checking NE to SW
            score++;
            count++;
        }
        else break;
    }
    
    if (score == 4) return true;
    else return false;
}

// checking for diagonal \ win
bool checkDiagNWtoSE(int x, int y, int player) {
    int score = 1;
    int count = 1;
   
   while((y+count >= 0) && (x+count < width)) {
      if (board_arr[y+count][x+count] == player) {
        // checking NW to SE
         score++;
         count++;
      }
      else break;
   }

   count = 1;
   while((y-count < height) && (x-count >=0)) {
      if (board_arr[y-count][x-count] == player) {
        // checking SE to NW
         score++;
         count++;
      }   
      else break;
   }
   
   if (score == 4) return true;
   else return false;
}

// checking for a vertical win
bool checkVertical(int x, int y, int player) {
    int score = 1;
    int count = 1;
    
    while(y+count>=0 && y+count<height) {
        if (board_arr[y+count][x] == player) {
            // only need to check downwards
            // as starting position is players most recent move
            score++;
            count++;
        }
        else break;
    }
    if (score == 4) return true;
    else return false;
}

// checking for horizontal win
bool checkHorizontal(int x, int y, int player) {
    int score = 1;
    int count = 1;

    while((x+count>=0) && (x+count<width)) {
        if (board_arr[y][x+count] == player) {
            // checking left
            score++;
            count++;
        }
        else break;
    }

    count = 1;
    while((x-count<width) && (x-count>=0)) {
        if (board_arr[y][x-count] == player) {
            // checking right
            score++;
            count++;
        }
        else break;
    }
    if (score == 4) return true;
    else return false;
}


// method to check for a winner
bool checkForWin(int x, int y, int player) {
    bool winner;

    // running through checks for each direction
    if (checkDiagSWtoNE(x, y, player)) return true;
    else if (checkDiagNWtoSE(x, y, player)) return true;
    else if (checkVertical(x, y, player)) return true;
    else if (checkHorizontal(x, y, player)) return true;
    else return false;
}


// driver function 
int main() {
    int counter = 0;
    bool winner = false;

    // setting random time
    srand(GetTickCount());
    cout << "Please select a number from 1-7" << endl;
    cout << "| 1| 2| 3| 4| 5| 6| 7" << endl;
    cout << "---------------------";
    drawBoard();

    for (int i=0; i<21; i++) {
        playerMove(1);
        drawBoard();
        winner = checkForWin(prevX, prevY, 1);
        if (winner) {

            cout << "\nYou win!" << endl;
            break;
        }

        playerMove(2);
        drawBoard();
        winner = checkForWin(prevX, prevY, 2);
        if (winner) {
            cout << "\nYou win!" << endl;
            break;
        }
    }

    system("PAUSE");
    return 0;
}