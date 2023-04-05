#include "pch.h"
#include "King.h"


King::King(bool type)
	: Piece(def_name, type),
	hasMoved{ false }
{
}

bool King::kingCastleAvailable() const
{
	return !hasMoved;
}

void King::setCastleUnavailable()
{
	hasMoved = true;
}

void King::abstractClass() const
{
	return;
}