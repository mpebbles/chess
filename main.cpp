#include <iostream>
#include "chess_pieces.h"
#include "utils.h"

int main() 
{
    is_user_turn = false;
    Piece * board[8][8] = {};

    // whitePieces/blackPieces ordered by importance (high -> low) 
    //    -for easy implementation,
    //    -not literal importance in game
    //    
    //    Order: K q r r b b k k p p p p p p p p 

    Piece * whitePieces[16];
    Piece * blackPieces[16];
    initGame(board, whitePieces, blackPieces);
    printBoard(board);

    /////// Plan ////
    // generate move function (using piece arrays)
         // Make note - dumb move function for now
           //1. Doesn’t harm king
           //2. Can capture best piece
           //3. Just make valid move if needed
    // check that user selected their own piece, not nullptr or computer's piece
    // call move on piece
    // print board
    // computer moves
    // alternate
    // check for win each time
    // print x,y grid for user, swap coors for logic

    // have prompt, interface for commands (help, move x y, exit)
    //while(true) {

    //}
}
