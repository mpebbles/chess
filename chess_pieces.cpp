#include <iostream>
#include "chess_pieces.h"

Piece::Piece(char s, char t, int r, int c): isAlive(true)
{
    side = s;
    type = t;
    row = r;
    col = c;
}

King::King(char s, char t, int r, int c): Piece(s,t, r, c) {}
