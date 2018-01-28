#ifndef __CHESS_PIECES__
#define __CHESS_PIECES__

class Piece
{
    public:
        Piece(char s, char t, int r, int c);
        char side, type;
        int row, col;
        bool isAlive;
};

class King: public Piece 
{
    public:
        King(char s, int r, int c);
};

class Queen: public Piece 
{   
    public:
        Queen(char s, int r, int c);
};

class Rook: public Piece 
{   
    public:
        Rook(char s, int r, int c);
};

class Bishop: public Piece 
{   
    public:
        Bishop(char s, int r, int c);
};

class Knight: public Piece 
{   
    public:
        Knight(char s, int r, int c);
};

class Pawn: public Piece 
{   
    public:
        Pawn(char s, int r, int c);
};

#endif
