#pragma once
#include "Piece.h"


class Pawn :
    public Piece
{
private:
    static constexpr const char* def_name = "Pawn";
protected:
    bool hasMoved;
    bool needsPromotion;
public:
    Pawn(bool type);

    bool getHasMoved() const;
    void setHasMovedTrue();

    bool move(int x, int y);
    bool checkPromotion();
};

