#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player {
private:
    char game_piece; // Game piece character
    Board& board; // Reference to the game board

public:
    // Constructor
    Player(Board& board, char game_piece);

    // Place a game piece in a column
    bool put(int column);

    // Turn the board clockwise
    void turn_board();

    // Check if the player has won
    bool is_winner();

    // Get the player's game piece character
    char get_symbol();
};

#endif
