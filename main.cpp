#include <iostream>
#include "chess_pieces.h"
#include "utils.h"
#include <ctype.h>

int main() 
{
    is_user_turn = false;
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
        print_board = true;
        std::cout << "white>";
        std::string user_in;
        std::getline(std::cin, user_in);
        if(user_in == "help") {
            print_board = false;
            // To implement
        }
        else if(user_in.find("move") != std::string::npos and 
                user_in.length() > 7 and isdigit(user_in.at(5)) and 
                isdigit(user_in.at(7))) {
            // check if move valid, if so make and print board
            // To implement
        }
        else if(user_in == "exit") {
            // To implement
            exit(0);
        }
        else if(user_in == "reset") {
            resetGame(board, whitePieces, blackPieces);
        }
        else {
            print_board = false;
            std::cout << "Invalid input. Enter 'help' for info and commands." << std::endl;
        }
        if(print_board) printBoard(board);
    }
    /////// Plan ////
    // generate move function (using piece arrays)
         // Make note - dumb move function for now
           //1. Doesn’t harm king
           //2. Can capture best piece
           //3. Just make valid move if needed
    // check that user selected their own piece, not nullptr or computer's piece
    // call move on piece
    // print board
    // computer moves
    // print out computer's move
    // alternate
    // check for win each time
    // print x,y grid for user, swap coors for logic

    // have prompt, interface for commands (help, move x y, exit)
}
