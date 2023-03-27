#pragma once

#include <iostream>
#include <string>


class Piece
{
	
protected:
	std::string m_name;
	bool m_type;
	int posX, posY;

public:
	Piece(const std::string &name, const bool &type);

	void setPosition(int x, int y);
	std::pair<int,int> getPosition();
	std::string getName() const;
	std::string getShortName() const;
	bool getType() const;
	virtual bool move(int x, int y) = 0;

	friend std::ostream& operator<<(std::ostream& output, const Piece& piece);
};

