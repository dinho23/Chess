#pragma once
#include "Piece.h"


class Knight :
    public Piece
{
private:
    static constexpr const char* def_name = "Knight";

public:
    Knight(bool type);

    bool move(int x, int y);
};

