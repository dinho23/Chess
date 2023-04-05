#pragma once
#include "Piece.h"


class Knight :
    public Piece
{
private:
    static constexpr const char* def_name = "Knight";

public:
    Knight(bool type);

    void abstractClass() const;
};