#include "Board.h"
#include "iostream"
using namespace std;
// Constructor
Board::Board(int size, int n) {
    Size = size;
    matrix = new char* [Size];
    for (int i = 0; i<Size; i++){
        matrix[i] = new char[Size];
        for (int j = 0; j < Size; j++)
            matrix[i][j] = '-';

    }
    N = n;


}


// Destructor
Board::~Board() {
    for (int i = 0; i< Size; i++)
        delete [] matrix[i];
    delete [] matrix;

}

// Print the current state of the board
void Board::print_board() {
    cout << endl;
    for (int i = 0; i<Size; i++) {

        for (int j = 0; j < Size; j++) { cout << matrix[i][j]; }
        cout << endl;
    }
    cout << endl;

}

// Add a game piece to the board
bool Board::put_piece(char piece, int column) {
    if(column>=Size){return false;}
    else {
        for (int i = Size - 1; i >= 0; i--) {
            if (matrix[i][column] == '-') {
                matrix[i][column] = piece;
                return true;
            }

        }
        return false;
    }
}

// Rotate the board 90 degrees clockwise
void Board::turn_board_clockwise() {
    // Create a temporary matrix to store the rotated board
    char** new_matrix = new char*[Size];
    for (int i = 0; i < Size; ++i) {
        new_matrix[i] = new char[Size];
    }

    // Rotate the board 90 degrees clockwise
    for (int row = 0; row < Size; ++row) {
        for (int col = 0; col < Size; ++col) {
            new_matrix[col][Size - 1 - row] = matrix[row][col];
        }
    }

    // Apply gravity to the board
    for (int col = 0; col < Size; ++col) {
        int row = Size - 1;
        for (int i = Size - 1; i >= 0; --i) {
            if (new_matrix[i][col] != '-') {
                new_matrix[row--][col] = new_matrix[i][col];
            }
        }
        while (row >= 0) {
            new_matrix[row--][col] = '-';
        }
    }

    // Update the original matrix with the rotated matrix
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            matrix[i][j] = new_matrix[i][j];
        }
    }

    // Deallocate memory for the temporary matrix
    for (int i = 0; i < Size; ++i) {
        delete[] new_matrix[i];
    }
    delete[] new_matrix;
}



// Function to check if a specific player has won
bool Board::check_winner(char piece) {
    // Check rows
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j <= Size - N; ++j) {
            bool win = true;
            for (int k = 0; k < N; ++k) {
                if (matrix[i][j + k] != piece) {
                    win = false;
                }
            }
            if (win) return true;
        }
    }

    // Check columns
    for (int j = 0; j < Size; ++j) {
        for (int i = 0; i <= Size - N; ++i) {
            bool win = true;
            for (int k = 0; k < N; ++k) {
                if (matrix[i + k][j] != piece) {
                    win = false;
                }
            }
            if (win) return true;
        }
    }

    // Check diagonals
    for (int i = 0; i <= Size - N; ++i) {
        for (int j = 0; j <= Size - N; ++j) {
            bool win = true;
            for (int k = 0; k < N; ++k) {
                if (matrix[i + k][j + k] != piece) {
                    win = false;
                }
            }
            if (win) return true;
        }
    }
    for (int i = N - 1; i < Size; ++i) {
        for (int j = 0; j <= Size - N; ++j) {
            bool win = true;
            for (int k = 0; k < N; ++k) {
                if (matrix[i - k][j + k] != piece) {
                    win = false;
                }
            }
            if (win) return true;
        }
    }

    return false;
}

// Implementation of get_game_status function
char Board::get_game_status() {
    bool x_wins = check_winner('X');
    bool o_wins = check_winner('O');

    // Both players win simultaneously
    if (x_wins && o_wins) {
        return 'D';
    }

    // Check if player 'X' wins
    if (x_wins) {
        return 'X';
    }

    // Check if player 'O' wins
    if (o_wins) {
        return 'O';
    }

    // Check if the board is full (draw condition)
    bool full = true;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            if (matrix[i][j] == '-') {
                full = false;
            }
        }
    }
    if (full) {
        return 'D';
    }


    return '-';
}
