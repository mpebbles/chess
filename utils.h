#ifndef __CHESS_UTILS__
#define __CHESS_UTILS__
#include "chess_pieces.h"
#include <vector>

extern bool is_user_turn;
extern bool computer_in_check;
extern bool user_in_check;
// location of piece putting King in check
extern int threat_row;
extern int threat_col;
extern Piece * whitePieces[16];
extern Piece * blackPieces[16];

void promotePawn(int col, Piece* board[8][8]);
void initGame(Piece* board[8][8], Piece* whitePieces[16], Piece* blackPieces[16]);
void resetGame(Piece* board[8][8], Piece* whitePieces[16], Piece* blackPieces[16]);
void printBoard(Piece* board[8][8]);
bool isCheckMate(Piece * pieces[16], Piece* board[8][8]);
void userWin(Piece * whitePieces[16], Piece* blackPieces[16], Piece* board[8][8]);
void userLoss(Piece * whitePieces[16], Piece* blackPieces[16], Piece* board[8][8]);
void gameStalemate(Piece * whitePieces[16], Piece* blackPieces[16], Piece* board[8][8]);
bool onlyKingLeft(Piece* pieces[16]);
#endif
