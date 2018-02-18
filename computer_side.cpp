#include "computer_side.h"

// TODO: add intelligence
bool makeMove(Piece * pieces[16], Piece * board[8][8]) 
{
    int old_row, old_col;
    for(int i = 0; i < 16; ++i) {
        if(pieces[i]->isAlive)
            for(int a = 0; a < 8; ++a) {
                for(int b = 0; b < 8; ++b) {
                    if(pieces[i]->row != a and pieces[i]->col != b) {
                        old_row = pieces[i]->row;
                        old_col = pieces[i]->col;
                        if(pieces[i]->move(a, b, board)) {
                            std::cout << "black>move " << old_col + 1 << old_row + 1
                            << " " << b + 1 << a + 1 << std::endl;
                            return true;
                        }
                    }
                }
            }
    }
    return false;
}
