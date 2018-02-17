#include "computer_side.h"

// TODO: add intelligence
bool makeMove(Piece * pieces[16], Piece * board[8][8]) 
{
    for(int i = 0; i < 16; ++i) {
        if(pieces[i]->isAlive)
            for(int a = 0; a < 8; ++a) {
                for(int b = 0; b < 8; ++b) {
                    if(pieces[i]->row != a and pieces[i]->col != b) {
                        if(pieces[i]->move(a, b, board)) {
                            std::cout << "black>move " << pieces[i]->row << pieces[i]->col
                            << " " << a << b << std::endl;
                            return true;
                        }
                    }
                }
            }
    }
    return false;
}
