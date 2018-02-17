#include <iostream>
#include "chess_pieces.h"
#include "utils.h"

bool is_user_turn;
bool computer_in_check;
bool user_in_check;
int threat_row, threat_col;

bool isCheckMate(Piece * pieces[16], Piece* board[8][8])
{
    // since calls may change values of threat_row and threat_col
    int threat_row1 = threat_row; 
    int threat_col1 = threat_col;
    checking_move2 = true;
    // 1. check if threat can be taken out
    for(int i = 0; i < 16; ++i) {
        // if threat can be taken out
        if(pieces[i]->move(threat_row1, threat_col1, board)) {
            checking_move2 = false;
            return false;
        }
    }
    checking_move2 = false;
    // 2. check if King can move
    int temp_k_move_row, temp_k_move_col;
    std::tie(temp_k_move_row, temp_k_move_col) = pieces[0]->findKingMove(board);
    // king can move out of check
    if(temp_k_move_row != -1 or temp_k_move_col != - 1) return false;

    // 3. piece can block check?
    if(board[threat_row1][threat_col1]->type != 'k' and
       board[threat_row1][threat_col1]->type != 'K' and
       board[threat_row1][threat_col1]->type !='p') {
        checking_move2 = true;
        // +/-1's used since this is for blocking -- there must be a space between
        // check up left diag
        if(threat_row1 > pieces[0]->row + 1 and threat_col1 > pieces[0]->col - 1) {
            for(int i = 1; i + pieces[0]->row + 1 < threat_row; ++i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row + i,pieces[0]->col - i, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        }
        // check up
        else if(threat_row1 > pieces[0]->row + 1 and threat_col1 == pieces[0]->col) {
            for(int i = 1; i + pieces[0]->row + 1 < threat_row; ++i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row + i,pieces[0]->col, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        }
        // check up right diag
        else if(threat_row1 > pieces[0]->row + 1 and threat_col1 > pieces[0]->col + 1) {
            for(int i = 1; i + pieces[0]->row + 1 < threat_row; ++i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row + i,pieces[0]->col + i, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        }
        // check left
        else if(threat_row1 == pieces[0]->row and threat_col1 < pieces[0]->col - 1) {
            for(int i = -1; i + pieces[0]->col > threat_row + 1; --i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row,pieces[0]->col + i, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        }
        // check right
        else if(threat_row1 == pieces[0]->row and threat_col1 > pieces[0]->col + 1) {
            for(int i = 1; i + pieces[0]->col + 1 < threat_col; ++i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row,pieces[0]->col + i, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        }
        // check diag down left
        else if(threat_row1 < pieces[0]->row - 1 and threat_col1 < pieces[0]->col - 1) {
            for(int i = -1; i + pieces[0]->col > threat_col + 1; --i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row + i,pieces[0]->col + i, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        }
        // check down
        else if(threat_row1 < pieces[0]->row - 1 and threat_col1 == pieces[0]->col) {
            for(int i = -1; i + pieces[0]->row > threat_row + 1; --i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row + i,pieces[0]->col, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        }
        // check diag down right
        else if(threat_row1 < pieces[0]->row - 1 and threat_col1 > pieces[0]->col + 1) {
            for(int i = -1; i + pieces[0]->row > threat_row + 1; --i) {
                for(int j = 1; j < 16; ++j) {
                    if(pieces[j]->move(pieces[0]->row + i,pieces[0]->col - i, board)) {
                        checking_move2 = false;
                        return false;
                    }
                }
            }
        } 
    } 
    return true;
}

bool onlyKingLeft(Piece * pieces[16])
{
    for(int i = 1; i < 16; ++i)
        if(pieces[i]->isAlive)
            return false;
    return true;
}

void getAnswer(Piece* whitePieces[16], Piece* blackPieces[16], Piece* board[8][8])
{
    std::string user_ans;
    std::getline(std::cin, user_ans);
    if(user_ans.find("y") != std::string::npos)
        resetGame(board, whitePieces, blackPieces);
    else {
        std::cout << "Thank you for playing." << std::endl;
        exit(0);
    }
    printBoard(board);
}

void userWin(Piece * whitePieces[16], Piece* blackPieces[16], Piece* board[8][8]) 
{
    std::cout << "You won! Play again? (y/n): ";
    getAnswer(whitePieces, blackPieces, board);
}

void userLoss(Piece * whitePieces[16], Piece* blackPieces[16], Piece* board[8][8]) 
{
    std::cout << "The computer won. Play again? (y/n): ";
    getAnswer(whitePieces, blackPieces, board);
}

void gameStalemate(Piece * whitePieces[16], Piece* blackPieces[16], Piece* board[8][8])
{   
    std::cout << "It's a stalemate. Play again? (y/n): ";
    getAnswer(whitePieces, blackPieces, board);
}

void initGame(Piece* board[8][8], Piece* whitePieces[16], Piece* blackPieces[16])
{
    // white
    board[1][0] = new Pawn('w',1,0);
    whitePieces[15] = board[1][0];
    board[1][1] = new Pawn('w',1,1);
    whitePieces[14] = board[1][1];
    board[1][2] = new Pawn('w',1,2);
    whitePieces[13] = board[1][2];
    board[1][3] = new Pawn('w',1,3);
    whitePieces[12] = board[1][3];
    board[1][4] = new Pawn('w',1,4);
    whitePieces[11] = board[1][4];
    board[1][5] = new Pawn('w',1,5);
    whitePieces[10] = board[1][5];
    board[1][6] = new Pawn('w',1,6);
    whitePieces[9] = board[1][6];
    board[1][7] = new Pawn('w',1,7);
    whitePieces[8] = board[1][7];
    
    board[0][0] = new Rook('w',0,0);
    whitePieces[2] = board[0][0];
    board[0][1] = new Knight('w',0,1);
    whitePieces[6] = board[0][1];
    board[0][2] = new Bishop('w',0,2);
    whitePieces[4] = board[0][2];
    board[0][3] = new Queen('w',0,3);
    whitePieces[1] = board[0][3];
    board[0][4] = new King('w',0,4);
    whitePieces[0] = board[0][4];
    board[0][5] = new Bishop('w',0,5);
    whitePieces[5] = board[0][5];
    board[0][6] = new Knight('w',0,6);
    whitePieces[7] = board[0][6];
    board[0][7] = new Rook('w',0,7);
    whitePieces[3] = board[0][7];

    // black
    board[6][0] = new Pawn('b',6,0);
    blackPieces[15] = board[6][0];
    board[6][1] = new Pawn('b',6,1);
    blackPieces[14] = board[6][1];
    board[6][2] = new Pawn('b',6,2);
    blackPieces[13] = board[6][2];
    board[6][3] = new Pawn('b',6,3);
    blackPieces[12] = board[6][3];
    board[6][4] = new Pawn('b',6,4);
    blackPieces[11] = board[6][4];
    board[6][5] = new Pawn('b',6,5);
    blackPieces[10] = board[6][5];
    board[6][6] = new Pawn('b',6,6);
    blackPieces[9] = board[6][6];
    board[6][7] = new Pawn('b',6,7);
    blackPieces[8] = board[6][7];

    board[7][0] = new Rook('b',7,0);
    blackPieces[2] = board[7][0];
    board[7][1] = new Knight('b',7,1);
    blackPieces[6] = board[7][1];
    board[7][2] = new Bishop('b',7,2);
    blackPieces[4] = board[7][2];
    board[7][3] = new Queen('b',7,3);
    blackPieces[1] = board[7][3];
    board[7][4] = new King('b',7,4);
    blackPieces[0] = board[7][4];
    board[7][5] = new Bishop('b',7,5);
    blackPieces[5] = board[7][5];
    board[7][6] = new Knight('b',7,6);
    blackPieces[7] = board[7][6];
    board[7][7] = new Rook('b',7,7);
    blackPieces[3] = board[7][7];

}

void resetGame(Piece* board[8][8], Piece* whitePieces[16], Piece* blackPieces[16])
{
    for(int i = 0; i < 8; ++i)
        for(int j = 0; j < 8; ++j)
            board[i][j] = nullptr;

    // white

    board[1][0] = whitePieces[15];
    board[1][0]->row = 1; board[1][0]->col = 0; board[1][0]->isAlive = true;
    board[1][1] = whitePieces[14];
    board[1][1]->row = 1; board[1][1]->col = 1; board[1][1]->isAlive = true;
    board[1][2] = whitePieces[13];
    board[1][2]->row = 1; board[1][2]->col = 2; board[1][2]->isAlive = true;
    board[1][3] = whitePieces[12];
    board[1][3]->row = 1; board[1][3]->col = 3; board[1][3]->isAlive = true;
    board[1][4] = whitePieces[11];
    board[1][4]->row = 1; board[1][4]->col = 4; board[1][4]->isAlive = true;
    board[1][5] = whitePieces[10];
    board[1][5]->row = 1; board[1][5]->col = 5; board[1][5]->isAlive = true;
    board[1][6] = whitePieces[9];
    board[1][6]->row = 1; board[1][6]->col = 6; board[1][6]->isAlive = true;
    board[1][7] = whitePieces[8];
    board[1][7]->row = 1; board[1][7]->col = 7; board[1][7]->isAlive = true;

    board[0][0] = whitePieces[2];
    board[0][0]->row = 0; board[0][0]->col = 0; board[0][0]->isAlive = true;
    board[0][1] = whitePieces[6];
    board[0][1]->row = 0; board[0][1]->col = 1; board[0][1]->isAlive = true;
    board[0][2] = whitePieces[4];
    board[0][2]->row = 0; board[0][2]->col = 2; board[0][2]->isAlive = true;
    board[0][3] = whitePieces[1];
    board[0][3]->row = 0; board[0][3]->col = 3; board[0][3]->isAlive = true;
    board[0][4] = whitePieces[0];
    board[0][4]->row = 0; board[0][4]->col = 4; board[0][4]->isAlive = true;
    board[0][5] = whitePieces[5];
    board[0][5]->row = 0; board[0][5]->col = 5; board[0][5]->isAlive = true;
    board[0][6] = whitePieces[7];
    board[0][6]->row = 0; board[0][6]->col = 6; board[0][6]->isAlive = true;
    board[0][7] = whitePieces[3];
    board[0][7]->row = 0; board[0][7]->col = 7; board[0][7]->isAlive = true;
    
    // black
    board[6][0] = blackPieces[15];
    board[6][0]->row = 1; board[1][0]->col = 0; board[1][0]->isAlive = true;
    board[6][1] = blackPieces[14];
    board[6][1]->row = 1; board[1][1]->col = 1; board[1][1]->isAlive = true;
    board[6][2] = blackPieces[13];
    board[6][2]->row = 1; board[1][2]->col = 2; board[1][2]->isAlive = true;
    board[6][3] = blackPieces[12];
    board[6][3]->row = 1; board[1][3]->col = 3; board[1][3]->isAlive = true;
    board[6][4] = blackPieces[11];
    board[6][4]->row = 1; board[1][4]->col = 4; board[1][4]->isAlive = true;
    board[6][5] = blackPieces[10];
    board[6][5]->row = 1; board[1][5]->col = 5; board[1][5]->isAlive = true;
    board[6][6] = blackPieces[9];
    board[6][6]->row = 1; board[1][6]->col = 6; board[1][6]->isAlive = true;
    board[6][7] = blackPieces[8];
    board[6][7]->row = 1; board[1][7]->col = 7; board[1][7]->isAlive = true;

    board[7][0] = blackPieces[2];
    board[7][0]->row = 0; board[0][0]->col = 0; board[0][0]->isAlive = true;
    board[7][1] = blackPieces[6];
    board[7][1]->row = 0; board[0][1]->col = 1; board[0][1]->isAlive = true;
    board[7][2] = blackPieces[4];
    board[7][2]->row = 0; board[0][2]->col = 2; board[0][2]->isAlive = true;
    board[7][3] = blackPieces[1];
    board[7][3]->row = 0; board[0][3]->col = 3; board[0][3]->isAlive = true;
    board[7][4] = blackPieces[0];
    board[7][4]->row = 0; board[0][4]->col = 4; board[0][4]->isAlive = true;
    board[7][5] = blackPieces[5];
    board[7][5]->row = 0; board[0][5]->col = 5; board[0][5]->isAlive = true;
    board[7][6] = blackPieces[7];
    board[7][6]->row = 0; board[0][6]->col = 6; board[0][6]->isAlive = true;
    board[7][7] = blackPieces[3];
    board[7][7]->row = 0; board[0][7]->col = 7; board[0][7]->isAlive = true;

}

void printBoard(Piece* board[8][8])
{
    std::cout << std::endl;
    for(int i = 7; i >= 0; --i) {
        std::string color;
 
        std::cout << "\033[30m  " << i + 1 << "|";
        for(int j = 0; j < 8; ++j) {
            if(i%2==0) {
                if(j%2==0)
                    // cyan
                    color = "\033[36m";
                else
                    // blue
                    color = "\033[34m";
            }
            else {
                if(j%2==0)
                    // blue
                    color = "\033[34m";
                else
                    // cyan
                    color = "\033[36m";
            }
               
            if(board[i][j] == nullptr)
                std::cout << color << "    *";
            else {
                if(board[i][j]->side == 'b')
                    color = "\033[30m";
                else
                    color = "\033[37m";
                std::cout << color << "    " << board[i][j]->type;
            }
        }
        // change font color back to black and skip line
        std::cout << std::endl << "\033[30m   |" << std::endl;
    }
    std::cout << "   ------------------------------------------" << std::endl;
    std::cout << "        1    2    3    4    5    6    7    8";
    std::cout << std::endl;
}
