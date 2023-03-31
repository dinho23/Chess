#pragma once
#include "Piece.h"


class Bishop :
    public Piece
{
private:
    static constexpr const char* def_name = "Bishop";

public:
    Bishop(bool type);

    void abstractClass();
};