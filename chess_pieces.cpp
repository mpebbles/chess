#include <iostream>
#include "chess_pieces.h"

Piece::Piece(char s, char t, int r, int c)
{
    side = s;
    type = t;
    row = r;
    col = c;
}

bool Piece::move(int dest_row, int dest_col, Piece* board[8][8])
{
    //////// To Implement /////////
    // implemented in sub classes - calls here for reused parts
    // check if any pieces in the way
    // include check for side (up/down)
    // implement derived objects' methods for checking what piece can do,
    // check bounds
    if(dest_row > 7 or dest_row < 0 or dest_col > 7 or dest_col < 0)
        return false;
    return true;
    // check if spot empty, if so move
    // check if piece in place
        // check if piece on same side
        // else capture piece    
    // if move fails print why
    // if captured, delete object
    // if king verify king not in danger, move doesn't jeopardize king
    ///////////////////////////////
}
//***** King *****//
King::King(char s, int r, int c): Piece(s,'K', r, c) {}
bool King::move(int dest_row, int dest_col, Piece* board[8][8])
{
    return false;
}

//***** Queen *****//
Queen::Queen(char s, int r, int c): Piece(s,'q', r, c) {}
bool Queen::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    return false;
}

//***** Rook *****//
Rook::Rook(char s, int r, int c): Piece(s,'r', r, c) {}
bool Rook::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    return false;
}

//***** Bishop *****//
Bishop::Bishop(char s, int r, int c): Piece(s,'b', r, c) {}
bool Bishop::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    return false;
}

//***** Knight *****//
Knight::Knight(char s, int r, int c): Piece(s,'k', r, c) {}
bool Knight::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    return false;
}

//***** Pawn *****//
Pawn::Pawn(char s, int r, int c): Piece(s,'p', r, c) {}
bool Pawn::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    return false;
}
