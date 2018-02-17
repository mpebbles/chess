#include <iostream>
#include "chess_pieces.h"
#include "utils.h"

// bad coding, I know
// checking_move is so that piece is not actually moved when
//    checkKingSafe() is testing for pieces being able to attack King
//    when true piece won't be moved
bool checking_move = false;
bool checking_move2 = false;
bool checkingKingMove = false;

Piece::Piece(char s, char t, int r, int c): isAlive(true)
{
    side = s;
    type = t;
    row = r;
    col = c;
}

bool Piece::move(int dest_row, int dest_col, Piece* board[8][8])
{ 
    if(dest_row == this->row and dest_col == this->col) return false;
    // if check is happening, don't actually move piece
    if(checking_move) return true;
    if(!checkBounds(dest_row, dest_col)) return false; 
    int old_row = this->row;
    int old_col = this->col;
    Piece * cap_piece_ref;
    if(board[dest_row][dest_col] == nullptr) {}
    // capture
    else if(board[dest_row][dest_col]->side != this->side){
        cap_piece_ref = board[dest_row][dest_col];
        cap_piece_ref->isAlive = false;
    }
    // error
    else return false;
    // move piece
    board[dest_row][dest_col] = this;
    board[old_row][old_col] = nullptr;
    this->row = dest_row;
    this->col = dest_col;
    // if piece is king, place first
    if(this->type == 'K' and !this->isSafe(board)) {
        board[old_row][old_col] = this;
        if(cap_piece_ref != nullptr) {
            board[dest_row][dest_col] = cap_piece_ref;
            cap_piece_ref->isAlive = true;
        }
        else
            board[dest_row][dest_col] = nullptr;
        this->row = old_row;
        this->col = old_col;
        return false;
    }
    // check safety of mover's king
    else if(!checkKingSafe(board)) {
        board[old_row][old_col] = this;
        if(cap_piece_ref != nullptr) {
            board[dest_row][dest_col] = cap_piece_ref;
            cap_piece_ref->isAlive = true;
        } 
        else 
            board[dest_row][dest_col] = nullptr;
        this->row = old_row;
        this->col = old_col;
        return false;
    }
    // King is able to move (not actually moving yet)
    if(checkingKingMove) {
        board[old_row][old_col] = this;
        if(cap_piece_ref != nullptr) {
            board[dest_row][dest_col] = cap_piece_ref;
            cap_piece_ref->isAlive = true;
        }
        else
            board[dest_row][dest_col] = nullptr;
        this->row = old_row;
        this->col = old_col;
        checkingKingMove = false;
        return true;
    }
    // checking piece move (2nd option)
    // for checking if valid move while in check
    if(checking_move2) {
        board[old_row][old_col] = this; 
        if(cap_piece_ref != nullptr) {
            board[dest_row][dest_col] = cap_piece_ref;
            cap_piece_ref->isAlive = true;
        }   
        else
            board[dest_row][dest_col] = nullptr;
        this->row = old_row;
        this->col = old_col;
        return true;
    }
    // if execution gets here, move is valid
   if(is_user_turn and user_in_check) user_in_check = false; 
   if(!is_user_turn and computer_in_check) computer_in_check = false;
   return true;
}

// returns std::make_pair(-1, -1) if no valid move found
std::pair<int, int> Piece::findKingMove(Piece* board[8][8])
{
    checkingKingMove = true;
    if(this->move(this->row - 1, this->col - 1, board))
        return std::make_pair(this->row - 1, this->col - 1);
    else if(this->move(this->row - 1, this->col, board))
        return std::make_pair(this->row - 1, this->col);
    else if(this->move(this->row - 1, this->col + 1, board))
        return std::make_pair(this->row - 1, this->col + 1);
    else if(this->move(this->row, this->col - 1, board))
        return std::make_pair(this->row, this->col - 1);
    else if(this->move(this->row, this->col + 1, board))
        return std::make_pair(this->row, this->col + 1);
    else if(this->move(this->row + 1, this->col - 1, board))
        return std::make_pair(this->row + 1, this->col - 1);
    else if(this->move(this->row + 1, this->col, board))
        return std::make_pair(this->row + 1, this->col);
    else if(this->move(this->row + 1, this->col + 1, board))
        return std::make_pair(this->row + 1, this->col + 1);
    else {
        checkingKingMove = false;
        return std::make_pair(-1, -1);
    }
}

bool Piece::checkKingSafe(Piece* board[8][8])
{
    int k_row, k_col;
    // get king coors
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j) {
            if(board[i][j] != nullptr and
               board[i][j]->type == 'K' and
               board[i][j]->side == this->side) {
               k_row = i; k_col = j;
               break;
            }
        }
    return board[k_row][k_col]->isSafe(board);
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

bool Piece::checkDiag(int dest_row, int dest_col, Piece* board[8][8])
{
    // if not diag move
    if(abs(this->row - dest_row) != abs(this->col - dest_col)) return false;
    if(!checkBounds(dest_row, dest_col)) return false;
    // check no pieces blocking
    // up right
    if(this->row < dest_row and this->col < dest_col) {
        for(int i = 1; i + this->row < dest_row; ++i)
            if(board[this->row + i][this->col + i] != nullptr)
                return false;
    }
    // up left
    else if(this->row < dest_row and this->col > dest_col) {
        for(int i = 1; i + this->row < dest_row; ++i)
            if(board[this->row + i][this->col - i] != nullptr)
                return false;
    }
    // down right
    else if(this->row > dest_row and this->col < dest_col) {
        for(int i = 1; i + this->col < dest_col; ++i)
            if(board[this->row - i][this->col + i] != nullptr)
                return false;
    }
    // down left
    else if(this->row > dest_row and this->col > dest_col) {
        for(int i = -1; i + this->row > dest_row; --i)
            if(board[this->row + i][this->col + i] != nullptr)
                return false;
    }
    else {return false;}
    return true;
}

bool Piece::checkUpDownLeftRight(int dest_row, int dest_col, Piece* board[8][8])
{
    if(!checkBounds(dest_row, dest_col)) return false;
    // left or right
    if(this->row == dest_row and this->col != dest_col) {
        // left
        if(this->col < dest_col) {
            for(int i = 1; i + this->col < dest_col; ++i)
                if(board[this->row][i + this->col] != nullptr) {
                    return false;
                }
        }
        // right
        else if(this->col > dest_col) {
            for(int i = -1; i + this->col > dest_col; --i)
                if(board[this->row][i+this->col] != nullptr)
                    return false;
        }
    }
    // up or down
    else if(this->row != dest_row and this->col == dest_col) {
        //up
        if(this->row < dest_row) {
            for(int i = 1; i + this->row < dest_row; ++i)
                if(board[this->row + i][this->col] != nullptr)
                    return false;
        }
        // down
        else if(this->row > dest_row) {
            for(int i = -1; i + this->row > dest_row; --i)
                if(board[this->row + i][this->col] != nullptr)
                    return false;
        }
    }
    else {return false;}
    return true;
}

// assumes this is King
bool Piece::isSafe(Piece* board[8][8])
{
    // check if opposing pieces can attack king
    checking_move = true;
    for(int i = 0; i < 7; ++i)
        for(int j = 0; j < 7; ++j) {
            if(board[i][j] != nullptr and
               board[i][j]->side != this->side) {
                // to make moving King 2 from enemy pawn valid move
                if(board[i][j]->type == 'p' and abs(board[i][j]->row - this->row) == 2) {}
                else if(board[i][j]->move(this->row, this->col, board)) {
                    checking_move = false;
                    // extern vars
                    threat_row = i;
                    threat_col = j;
                    // invalid move, king in jeopardy
                    return false;
                }   
            }   
        }  
    checking_move = false;
    return true;
}

//***** King *****//
King::King(char s, int r, int c): Piece(s,'K', r, c) {}
bool King::move(int dest_row, int dest_col, Piece* board[8][8])
{
    //if(!checkBounds(dest_row, dest_col)) return false;
    // TODO structure like knight
    // check valid direction    
    if(this->row + 1 == dest_row and this->col == dest_col) {}
    // down
    else if(this->row - 1 == dest_row and this->col == dest_col) {}
    // right
    else if(this->row == dest_row and this->col + 1 == dest_col) {}
    // left
    else if(this->row == dest_row and this->col - 1 == dest_col) {}
    // up-left
    else if(this->row + 1 == dest_row and this->col - 1 == dest_col) {}
    // up-right
    else if(this->row + 1 == dest_row and this->col + 1 == dest_col) {}
    // down-left
    else if(this->row - 1 == dest_row and this->col - 1 == dest_col) {}
    // down-right
    else if(this->row - 1 == dest_row and this->col + 1 == dest_col) {}
    else return false;

    // call parent
    if(!Piece::move(dest_row, dest_col, board)) return false;
    return true;
}

//***** Queen *****//
Queen::Queen(char s, int r, int c): Piece(s,'q', r, c) {}
bool Queen::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    // check that move is in valid direction
    if(!Piece::checkDiag(dest_row, dest_col, board) and
       !Piece::checkUpDownLeftRight(dest_row, dest_col, board))
       return false;
    // call parent
    if(!Piece::move(dest_row, dest_col, board)) return false;
    return true;
}

//***** Rook *****//
Rook::Rook(char s, int r, int c): Piece(s,'r', r, c) {}
bool Rook::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    if(!Piece::checkUpDownLeftRight(dest_row, dest_col, board)) return false;
    // call parent
    if(!Piece::move(dest_row, dest_col, board)) return false;
    return true;
}

//***** Bishop *****//
Bishop::Bishop(char s, int r, int c): Piece(s,'b', r, c) {}
bool Bishop::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    if(!Piece::checkDiag(dest_row, dest_col, board)) return false;
    // call parent
    if(!Piece::move(dest_row, dest_col, board)) return false;
    return true;
}

//***** Knight *****//
Knight::Knight(char s, int r, int c): Piece(s,'k', r, c) {}
bool Knight::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    //if(!checkBounds(dest_row, dest_col)) return false;
    // check valid direction
    if(!(
         // up 2, right one
         (this->row + 2 == dest_row and this->col + 1 == dest_col) or 
         // up 2, left one
         (this->row + 2 == dest_row and this->col - 1 == dest_col) or
         // up 1, right 2
         (this->row + 1 == dest_row and this->col + 2 == dest_col) or
         // up 1, left 2
         (this->row + 1 == dest_row and this->col - 2 == dest_col) or
         // down 2, right one
         (this->row - 2 == dest_row and this->col + 1 == dest_col) or
         // down 2, left one
         (this->row - 2 == dest_row and this->col - 1 == dest_col) or
         // down 1, right 2
         (this->row - 1 == dest_row and this->col + 2 == dest_col) or
         // down 1, left 2
         (this->row - 1 == dest_row and this->col - 2 == dest_col)
      )) return false;
    // call parent
    if(!Piece::move(dest_row, dest_col, board)) return false;
    return true;
}

//***** Pawn *****//
Pawn::Pawn(char s, int r, int c): Piece(s,'p', r, c) {}
bool Pawn::move(int dest_row, int dest_col, Piece* board[8][8]) 
{
    // check bounds included so that below won't break when board coors accessed
    // TODO: put checking of board for nulltpr/opposite team into parent
    if(!checkBounds(dest_row, dest_col)) return false;
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
        else if(this->col == dest_col - 1 or this->col == dest_col + 1) {
            // check that row - 1 only and piece white
            if(this->row - 1 != dest_row or 
               board[dest_row][dest_col] == nullptr 
               or board[dest_row][dest_col]->side=='b')
                return false;
        }
        // not forward or diag
        else {return false;}
        // TODO: implement for black
        if(dest_row == 0)
            std::cout << "Piece promotion not implemented yet" << std::endl;
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
        else if(this->col == dest_col - 1 or this->col == dest_col + 1) {
            // check that row + 1 only and piece black 
            if(this->row + 1 != dest_row or 
               board[dest_row][dest_col] == nullptr
               or board[dest_row][dest_col]->side=='w')
                return false;
        }
        // not forward or diag
        else {return false;}
       
        // TODO: implement for white
        if(dest_row == 7)
            std::cout << "Piece promotion not implemented yet" << std::endl;
    }
    // call parent
    if(!Piece::move(dest_row, dest_col, board)) return false;
    return true;
}
