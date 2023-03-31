#include "Piece.h"

Piece::Piece(const std::string& name, const bool& type)
	: m_name{ name },
	  m_type { type },
	  posX{ 0 },
	  posY {0}
{
}

void Piece::setPosition(const int& x, const int& y)
{
	posX = x;
	posY = y;
}

std::pair<int, int> Piece::getPosition()
{
	return std::pair<int, int>(posX, posY);
}

std::string Piece::getName() const
{
	return m_name;
}

std::string Piece::getShortName() const
{
	if (m_name[0] == 'K') {
		return std::string{ m_name[0],m_name[1] };
	}
	else {
		return std::string{ m_name[0] };
	}
}

bool Piece::getType() const
{
	return m_type;
}

std::ostream& operator<<(std::ostream& output, const Piece& piece)
{
	output << piece.m_name;
	return output;
}