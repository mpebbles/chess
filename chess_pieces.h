#ifndef __CHESS_PIECES__
#define __CHESS_PIECES__

class Piece
{
    public:
        Piece(char s, char t, int r, int c);
        // function returns true if piece moved, false if move not possible
        virtual bool move(int dest_row, int dest_col, Piece* board[8][8]);
        static bool checkBounds(int row, int col);
        // user side will always be white
        char side, type;
        int row, col;
        bool isAlive;
};

class King: public Piece 
{
    public:
        King(char s, int r, int c);
        bool move(int dest_row, int dest_col, Piece* board[8][8]);
};

class Queen: public Piece 
{   
    public:
        Queen(char s, int r, int c);
        bool move(int dest_row, int dest_col, Piece* board[8][8]);
};

class Rook: public Piece 
{   
    public:
        Rook(char s, int r, int c);
        bool move(int dest_row, int dest_col, Piece* board[8][8]);
};

class Bishop: public Piece 
{   
    public:
        Bishop(char s, int r, int c);
        bool move(int dest_row, int dest_col, Piece* board[8][8]);
};

class Knight: public Piece 
{   
    public:
        Knight(char s, int r, int c);
        bool move(int dest_row, int dest_col, Piece* board[8][8]);
};

class Pawn: public Piece 
{   
    public:
        Pawn(char s, int r, int c);
        bool move(int dest_row, int dest_col, Piece* board[8][8]);
};


#endif
