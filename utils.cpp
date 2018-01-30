#include "chess_pieces.h"

void initBoard(Piece* board[8][8]) {
    // white
    board[1][0] = new Pawn('w',1,0);
    board[1][1] = new Pawn('w',1,1);
    board[1][2] = new Pawn('w',1,2);
    board[1][3] = new Pawn('w',1,3);
    board[1][4] = new Pawn('w',1,4);
    board[1][5] = new Pawn('w',1,5);
    board[1][6] = new Pawn('w',1,6);
    board[1][7] = new Pawn('w',1,7);
    board[0][0] = new Rook('w',0,0);
    board[0][1] = new Knight('w',0,1);
    board[0][2] = new Bishop('w',0,2);
    board[0][3] = new Queen('w',0,3);
    board[0][4] = new King('w',0,4);
    board[0][5] = new Bishop('w',0,5);
    board[0][6] = new Knight('w',0,6);
    board[0][7] = new Rook('w',0,7);
    // black
    board[6][0] = new Pawn('b',6,0);
    board[6][1] = new Pawn('b',6,1);
    board[6][2] = new Pawn('b',6,2);
    board[6][3] = new Pawn('b',6,3);
    board[6][4] = new Pawn('b',6,4);
    board[6][5] = new Pawn('b',6,5);
    board[6][6] = new Pawn('b',6,6);
    board[6][7] = new Pawn('b',6,7);
    board[7][0] = new Rook('b',7,0);
    board[7][1] = new Knight('b',7,1);
    board[7][2] = new Bishop('b',7,2);
    board[7][3] = new Queen('b',7,3);
    board[7][4] = new King('b',7,4);
    board[7][5] = new Bishop('b',7,5);
    board[7][6] = new Knight('b',7,6);
    board[7][7] = new Rook('b',7,7);
}

void resetBoard(Piece* board[8][8]) {
    return; // call initBoard after deleting old pieces
}
