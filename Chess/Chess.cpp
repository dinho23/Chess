#include <iostream>

#include "Piece.h"
#include "Pawn.h"
#include "Player.h"
#include "Board.h"

void intro(std::string& input) {
    std::cout << "Would you like to play a game? (y/n):";
    std::cin >> input;

    for (auto& c : input) {
        c = toupper(c);
    }
}

bool isValid(std::string input) {
    if (input == "Q" || input == "QUIT" || input == "N" || input == "NO")
        return false;

    return true;
}

int main()
{
    std::string input{};
    intro(input);

    while (isValid(input)) {
        Board chess;
        chess.startGame();
        intro(input);
    }
    std::cout << ":(\n";
}