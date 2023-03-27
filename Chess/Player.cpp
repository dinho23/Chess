#include "Player.h"

Player::Player(bool white)
	: white {white}
{
	pieces.resize(16);
	for (size_t i = 0; i < 8; i++) {
		pieces.at(i) = new Pawn(white);
	}

	for (size_t i = 8; i < 10; i++) {
		pieces.at(i) = new Rook(white);
	}

	for (size_t i = 10; i < 12; i++) {
		pieces.at(i) = new Knight(white);
	}

	for (size_t i = 12; i < 14; i++) {
		pieces.at(i) = new Bishop(white);
	}

	pieces.at(14) = new Queen(white);
	pieces.at(15) = new King(white);
}

Player::~Player()
{
	for (auto ptr : pieces) {
		delete ptr;
	}
	pieces.clear();
}

void Player::insertPiece(Piece* piece)
{
	pieces.push_back(piece);
}

std::vector<Piece*> Player::getPieces()
{
	return pieces;
}
