#pragma once
#include "Piece.h"


class Queen :
    public Piece
{
private:
    static constexpr const char* def_name = "Queen";

public:
    Queen(bool type);

    bool move(int x, int y);
};

