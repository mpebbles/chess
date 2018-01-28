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

class King: public Piece {
    public:
        King(char s, char t, int r, int c);
};


#endif
