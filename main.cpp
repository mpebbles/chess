#include <iostream>
#include "chess_pieces.h"
#include "utils.h"
#include <ctype.h>

int main() 
{
    is_user_turn = true;
    computer_in_check = false;
    user_in_check = false;
    bool game_reset = false;
    Piece * board[8][8] = {};
    // for checking stalemate
    int k_move_row;
    int k_move_col;
    // whitePieces/blackPieces ordered by importance (high -> low) 
    //    -for easy implementation,
    //    -not literal importance in game
    //    
    //    Order: K q r r b b k k p p p p p p p p 

    Piece * whitePieces[16];
    Piece * blackPieces[16];
    initGame(board, whitePieces, blackPieces);
    std::cout << "********************************************" << std::endl;
    std::cout << "Welcome! Enter 'help' for info and commands." << std::endl; 

    printBoard(board);
    bool print_board;
    std::string user_in;
    while(true)
    {  
       if(!is_user_turn) {
           // ...
           std::cout << "Computer moves here..." << std::endl;
           is_user_turn = true;
           printBoard(board);
       }
       else {
            print_board = true;
            std::cout << "white>";
            std::getline(std::cin, user_in);
            if(user_in == "help") {
                print_board = false;
                std::cout << "\nImplemented by Mitchell Pebbles (2018).\n" 
                          << "To move a piece enter: 'move x1y1 x2y2' with x1y1\n"
                          << "    being the piece's current position, and x2y2 being\n"
                          << "    the desired destination.\n"
                          << "To exit enter 'exit'.\n"
                          << "To reset game enter 'reset'.\n" << std::endl;
            }
            // move 12,34
            else if(user_in.find("move") != std::string::npos and 
                    user_in.length() > 9 and isdigit(user_in.at(5)) and 
                    isdigit(user_in.at(6)) and isdigit(user_in.at(8)) 
                    and isdigit(user_in.at(9))) {
                // get moving coors and convert to ints
                // and swap row/col, subtract 1 from each
                int row = user_in.at(6) - '0' - 1;
                int col = user_in.at(5) - '0' - 1;
                int dest_row = user_in.at(9) - '0' - 1;
                int dest_col = user_in.at(8) - '0' - 1;
                if(board[row][col] == nullptr or
                   board[row][col]->side == 'b')
                   std::cout << "Invalid move." << std::endl;
                else {
                    if(!board[row][col]->move(dest_row, dest_col, board)) {
                        std::cout << "Invalid move." << std::endl;
                        is_user_turn = true;
                    }
                    else is_user_turn = false;
                }
            }
            else if(user_in == "exit") {
                std::cout << "Thank you for playing." << std::endl;
                exit(0);
            }
            else if(user_in == "reset") {
                game_reset = true;
                resetGame(board, whitePieces, blackPieces);
            }
            else {
                print_board = false;
                std::cout << "Invalid input. Enter 'help' for info and commands." << std::endl;
            }
            if(print_board)
                printBoard(board);
        }
        // !is_user_turn is side that just went, check following before turn given
        // check for check, checkmate, stalemate
        if(!game_reset) {
            if(is_user_turn and print_board) {
                if(!whitePieces[0]->isSafe(board)) {
                    // if exececution here, threat_row and threat_col have current vals
                    // Check for checkmate
                    // if checkmate reset game -- remember extra DS when implemented for piece swap
                    if(isCheckMate(whitePieces, board)) {
                        userLoss(whitePieces, blackPieces, board);
                    } else {
                        // if not checkmate
                        user_in_check = true;
                        // move function will check king safety -- move is invalid unless King safe
                        std::cout << "Your King is in check. You must resolve this." << std::endl;
                    }
                }
                // check for stalemate
                if(onlyKingLeft(whitePieces)) {
                    std::tie(k_move_row, k_move_col) = whitePieces[0]->findKingMove(board);
                    if(k_move_row == -1 and k_move_col == -1)
                        gameStalemate(whitePieces, blackPieces, board);
                }
            }
            // check black side
            else {
            // use logic from above, change needed vars/actions
            }
        } else { game_reset = false; is_user_turn = true; }
    }
}
