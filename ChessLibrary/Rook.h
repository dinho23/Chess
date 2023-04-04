#pragma once
#include "Piece.h"


class Rook :
    public Piece
{
private:
    static constexpr const char* def_name = "Rook";

protected:
    bool hasMoved;

public:
    Rook(bool type);

    bool rookHasMoved();
    void setRookHasMoved();

    void abstractClass();
};

