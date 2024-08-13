#include "Player.h"

Player::Player(Board& board, char game_piece) : board(board), game_piece(game_piece) {

}

bool Player::put(int column) {
    return board.put_piece(game_piece, column);
}


void Player::turn_board() {
    board.turn_board_clockwise();
}

bool Player::is_winner() {
    char status = board.get_game_status();
    return (status == game_piece);
}

char Player::get_symbol() {
    return game_piece;
}
