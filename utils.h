#ifndef __CHESS_UTILS__
#define __CHESS_UTILS__
#include "chess_pieces.h"

void initGame(Piece* board[8][8], Piece* whitePieces[16], Piece* blackPieces[16]);
void resetGame(Piece* board[8][8], Piece* whitePieces[16], Piece* blackPieces[16]);
void printBoard(Piece* board[8][8]);
#endif
