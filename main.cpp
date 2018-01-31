#include <iostream>
#include "chess_pieces.h"
#include "utils.h"

int main() 
{
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
    //while(true) {

    //}
}
