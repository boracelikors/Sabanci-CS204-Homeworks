#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    char** matrix; // Dynamic matrix representing the board
    int Size{}; // Size of the board (number of rows/columns)
    int N; // Number of pieces needed to win

public:
    // Constructor
    Board(int size, int n);

    // Destructor
    ~Board();

    // Print the current state of the board
    void print_board();

    // Add a game piece to the board
    bool put_piece(char piece, int column);

    // Rotate the board 90 degrees clockwise
    void turn_board_clockwise();

    // Check game status (winner, draw, or ongoing)
    char get_game_status();

    // Helper function for get_game_status
    bool check_winner(char piece);
};

#endif
