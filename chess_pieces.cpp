#include <iostream>
#include "chess_pieces.h"
#include "utils.h"

Piece::Piece(char s, char t, int r, int c): isAlive(true)
{
    side = s;
    type = t;
    row = r;
    col = c;
}

bool Piece::move(int dest_row, int dest_col, Piece* board[8][8])
{   
    if(!checkBounds(dest_row, dest_col)) return false;
    

    //////// To Implement /////////
    // implemented in sub classes - calls here for reused parts
    // check if any pieces in the way
    // include check for side (up/down)
    // implement derived objects' methods for checking what piece can do,
    // check if spot empty, if so move
    // check if piece in place
        // check if piece on same side
        // else capture piece    
    // if user move (not computer) fails print why - can tell by piece being moved
        // before above check that user is moving valid piece..(new function)
    // if captured, remove object from board, isAlive = false
    // verify king not in danger, move doesn't jeopardize king
 
    ///////////////////////////////

    return false;
}

bool Piece::checkBounds(int row, int col)
{
    if(row > 7 or row < 0 or col > 7 or col < 0) {
        if(is_user_turn)
            std::cout << "Invalid move. Move out of bounds." << std::endl;
        return false;
    }
    return true;
}

//***** King *****//
King::King(char s, int r, int c): Piece(s,'K', r, c) {}
bool King::move(int dest_row, int dest_col, Piece* board[8][8])
{
    // TO BE IMPLEMENTED
    return false;
}

//***** Queen *****//
Queen::Queen(char s, int r, int c): Piece(s,'q', r, c) {}
bool Queen::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    // TO BE IMPLEMENTED
    return false;
}

//***** Rook *****//
Rook::Rook(char s, int r, int c): Piece(s,'r', r, c) {}
bool Rook::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    // TO BE IMPLEMENTED
    return false;
}

//***** Bishop *****//
Bishop::Bishop(char s, int r, int c): Piece(s,'b', r, c) {}
bool Bishop::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    // TO BE IMPLEMENTED
    return false;
}

//***** Knight *****//
Knight::Knight(char s, int r, int c): Piece(s,'k', r, c) {}
bool Knight::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    // TO BE IMPLEMENTED
    return false;
}

//***** Pawn *****//
Pawn::Pawn(char s, int r, int c): Piece(s,'p', r, c) {}
bool Pawn::move(int dest_row, int dest_col, Piece* board[8][8]) 
{   // TO BE IMPLEMENTED
    
    return true;
}
