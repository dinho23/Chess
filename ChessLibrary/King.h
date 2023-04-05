#pragma once
#include "Piece.h"


class King :
    public Piece
{
private:
    static constexpr const char* def_name = "King";

protected:
    bool hasMoved;

public:
    King(bool type);

    bool kingCastleAvailable() const;
    void setCastleUnavailable();

    void abstractClass() const;
};