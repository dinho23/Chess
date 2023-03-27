#include "Pawn.h"

Pawn::Pawn(bool type)
	: Piece(def_name, type),
	hasMoved{ false },
	needsPromotion{ false }
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

bool Pawn::move(int x, int y)
{
	if (x == posX && y == posY)
		return false;

	if (y != posY)
		return false;

	if (posX == 1) {
		if (x > posX + 2)
			return false;
	}

	if (posX == 6) {
		if (x < posX - 2)
			return false;
	}

	posX = x;
	return true;
}

bool Pawn::checkPromotion()
{
	return 7 == this->getPosition().first || 0 == this->getPosition().first;
}
