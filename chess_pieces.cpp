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
    // implement check king safety here
    // move piece, make former space nullptr,
    // keep former coors, check for king problem

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
    // remember to make former board spot nullptr
    // computer final move default to moving pawns up?
    ///////////////////////////////

    return true;
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
    // still need to do white, check blocking pieces, check if at other side
    // check right direction from starting point
    // black
    if(this->side=='b') {
        // forward 1 or 2 if same col
        if(this->col == dest_col) {
            if(this->row - 1 != dest_row and this->row - 2 != dest_row)
                return false;
            if(this->row - 1 == dest_row and 
               board[dest_row][dest_col] != nullptr)
               return false;
            if(this->row == 6 and this->row - 2 == dest_row and 
                    (board[dest_row - 1][dest_col] != nullptr
                     or board[dest_row -2][dest_col] !=nullptr))
                return false;          
        }
        // if diag by one check for opposite team's piece
        else if(this->col == dest_col - 1 or this->col == dest_col + 1)
            // check that row - 1 only and piece white
            if(this->row - 1 != dest_row or 
               board[dest_row][dest_col] == nullptr 
               or board[dest_row][dest_col]->side=='b')
                return false;
        // not forward or diag
        else return false;
        // TODO: implement for white
        if(dest_row == 0)
            std::cout << "Piece Swapping Not Implemented Yet" << std::endl;
    }
    // white
    else {
        if(this->col == dest_col) {
            if(this->row + 1 != dest_row and this->row + 2 != dest_row)
                return false;
            if(this->row + 1 == dest_row and
               board[dest_row][dest_col] != nullptr)
               return false;
            if(this->row == 1 and this->row + 2 == dest_row and 
                    (board[dest_row + 1][dest_col] != nullptr
                     or board[dest_row +2][dest_col] !=nullptr))
                return false;          
        }
        // if diag by one check for opposite team's piece
        else if(this->col == dest_col - 1 or this->col == dest_col + 1)
            // check that row + 1 only and piece black 
            if(this->row + 1 != dest_row or 
               board[dest_row][dest_col] == nullptr
               or board[dest_row][dest_col]->side=='w')
                return false;
        // not forward or diag
        else return false;
       
        // TODO: implement for white
        if(dest_row == 7)
            std::cout << "Piece Swapping Not Implemented Yet" << std::endl;
    }
    // call parent
    if(!Piece::move(dest_row, dest_col, board)) return false;
    return true;
}
