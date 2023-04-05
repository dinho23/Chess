#pragma once
#include "Piece.h"


class Queen :
    public Piece
{
private:
    static constexpr const char* def_name = "Queen";

public:
    Queen(bool type);

    void abstractClass() const;
};