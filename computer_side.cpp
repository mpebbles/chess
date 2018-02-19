#include "computer_side.h"
#include <random>

// TODO: add intelligence
// For now function just looks for piece to attack, defaults to valid move
bool makeMove(Piece * pieces[16], Piece * board[8][8]) 
{
    //int old_row, old_col;
    // loop through board looking for piece that can attack piece
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j) {
            if(board[i][j] != nullptr and board[i][j]->side == 'b') {
                for(int a = 0; a < 8; ++a)
                    for(int b = 0; b < 8; ++b) {
                        if(!(a == i and b == j) and board[a][b] != nullptr
                           and board[a][b]->side == 'w') {
                            //old_row = i; old_col = j;
                            if(board[i][j]->move(a, b, board)) {
                                std::cout << "black>move " << j + 1 << i + 1
                                << " " << b + 1 << a + 1 << std::endl;
                                return true;
                            }
                        }
                    }
            }
        }
     // if execution gets here, a move to attack a piece wasn't found
    
    // get random index [0, 16]
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 16);
    int rand_start_index = distr(eng);
    int old_row, old_col;
    // start index to 16
    for(int i = rand_start_index; i < 16; ++i) {
        if(pieces[i]->isAlive)
            for(int a = 0; a < 8; ++a) {
                for(int b = 0; b < 8; ++b) {
                    if(!(pieces[i]->row == a and pieces[i]->col == b)) {
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
    // 0 to start index
    for(int i = 0; i < rand_start_index; ++i) {
        if(pieces[i]->isAlive) 
            for(int a = 0; a < 8; ++a) {
                for(int b = 0; b < 8; ++b) {
                    if(!(pieces[i]->row == a and pieces[i]->col == b)) {
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
