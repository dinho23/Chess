#include "pch.h"
#include "Pawn.h"


Pawn::Pawn(bool type)
	: Piece(def_name, type),
	hasMoved{ false },
	needsPromotion{ false },
	enPassant{ false, false },
	totalPawnsMoved{ 0 }
{
}

bool Pawn::getHasMoved() const
{
	return hasMoved;
}

void Pawn::setHasMovedTrue()
{
	hasMoved = true;
}

bool Pawn::checkPromotion() const
{
	return 7 == this->getPosition().first || 0 == this->getPosition().first;
}

std::pair<bool, bool> Pawn::getEnPassant() const
{
	return enPassant;
}

void Pawn::enPassantActive(bool left)
{
	if (left) {
		enPassant = { 1, 0 };
	}
	else {
		enPassant = { 0, 1 };
	}
}

void Pawn::enPassantInactive()
{
	enPassant = { 0, 0 };
}

void Pawn::setTotalPawnsMoved(int totalPawnsMoved)
{
	this->totalPawnsMoved = totalPawnsMoved;
}

int Pawn::getTotalPawnsMoved() const
{
	return totalPawnsMoved;
}

void Pawn::abstractClass() const
{
	return;
}