#include <iostream>
#include "chess_pieces.h"
#include "utils.h"
#include <ctype.h>

int main() 
{
    is_user_turn = true;
    Piece * board[8][8] = {};

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
            std::string user_in;
            std::getline(std::cin, user_in);
            if(user_in == "help") {
                print_board = false;
                // To implement
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
                    if(!board[row][col]->move(dest_row, dest_col, board))
                        std::cout << "Invalid move." << std::endl;
                }
            }
            else if(user_in == "exit") {
                std::cout << "Thank you for playing." << std::endl;
                exit(0);
            }
            else if(user_in == "reset") {
                resetGame(board, whitePieces, blackPieces);
            }
            else {
                print_board = false;
                std::cout << "Invalid input. Enter 'help' for info and commands." << std::endl;
            }
            if(print_board) { 
                printBoard(board);
                // user moved
                is_user_turn = false;
            }
        }
        // !is_user_turn is side that just went
        // check for check
        // ...
        // check for checkmate
        // ...
        // check for stalemate
        // ...
    }
    /////// Plan ////
    // generate move function (using piece arrays)
         // Make note - dumb move function for now
           //1. Doesn’t harm king
           //2. Can capture best piece
           //3. Just make valid move if needed
    // call move on piece
    // print board
    // computer moves
    // print out computer's move
    // alternate
    // check for win each time

    // have prompt, interface for commands (help, move x y, exit)
}
