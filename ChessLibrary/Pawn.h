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
    std::pair<bool, bool> enPassant; // first - left; second right
    int totalPawnsMoved;

public:
    Pawn(bool type);

    bool getHasMoved() const;
    void setHasMovedTrue();
    bool checkPromotion() const;

    std::pair<bool, bool> getEnPassant() const;
    void enPassantActive(bool left);
    void enPassantInactive();

    void setTotalPawnsMoved(int totalPawnsMoved);
    int getTotalPawnsMoved() const;

    void abstractClass() const;
};