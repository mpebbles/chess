#include <iostream>
#include "chess_pieces.h"

Piece::Piece(char s, char t, int r, int c): isAlive(true)
{
    side = s;
    type = t;
    row = r;
    col = c;
}

King::King(char s, int r, int c): Piece(s,'K', r, c) {}
Queen::Queen(char s, int r, int c): Piece(s,'q', r, c) {}
Rook::Rook(char s, int r, int c): Piece(s,'r', r, c) {}
Bishop::Bishop(char s, int r, int c): Piece(s,'b', r, c) {}
Knight::Knight(char s, int r, int c): Piece(s,'k', r, c) {}
Pawn::Pawn(char s, int r, int c): Piece(s,'p', r, c) {}
