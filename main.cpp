#include <iostream>
#include "chess_pieces.h"

int main() 
{
    // testing
    Piece * board[8][8];
    board[0][0] = new King('w','K', 0, 0);
    std::cout << board[0][0]->type << std::endl;
}
