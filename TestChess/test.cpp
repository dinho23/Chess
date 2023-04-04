#include "pch.h"

#include "../ChessLibrary/Board.h"


TEST(BoardInit, PawnInitCorrectly) {
	Board chess;

	for (int i = 0; i < 8; i++) {
		EXPECT_EQ(chess.getBoard()[1][i]->getName(), "Pawn");
		EXPECT_EQ(chess.getBoard()[6][i]->getName(), "Pawn");

		EXPECT_EQ(chess.getBoard()[1][i]->getType(), 1);
		EXPECT_EQ(chess.getBoard()[6][i]->getType(), 0);
	}
}

TEST(BoardInit, RookInitCorrectly) {
	Board chess;

	EXPECT_EQ(chess.getBoard()[0][0]->getName(), "Rook");
	EXPECT_EQ(chess.getBoard()[0][0]->getType(), 1);
	EXPECT_EQ(chess.getBoard()[0][7]->getName(), "Rook");
	EXPECT_EQ(chess.getBoard()[0][7]->getType(), 1);

	EXPECT_EQ(chess.getBoard()[7][0]->getName(), "Rook");
	EXPECT_EQ(chess.getBoard()[7][0]->getType(), 0);
	EXPECT_EQ(chess.getBoard()[7][7]->getName(), "Rook");
	EXPECT_EQ(chess.getBoard()[7][7]->getType(), 0);
}

TEST(BoardInit, KnightInitCorrectly) {
	Board chess;

	EXPECT_EQ(chess.getBoard()[0][1]->getName(), "Knight");
	EXPECT_EQ(chess.getBoard()[0][1]->getType(), 1);
	EXPECT_EQ(chess.getBoard()[0][6]->getName(), "Knight");
	EXPECT_EQ(chess.getBoard()[0][6]->getType(), 1);

	EXPECT_EQ(chess.getBoard()[7][1]->getName(), "Knight");
	EXPECT_EQ(chess.getBoard()[7][1]->getType(), 0);
	EXPECT_EQ(chess.getBoard()[7][6]->getName(), "Knight");
	EXPECT_EQ(chess.getBoard()[7][6]->getType(), 0);
}

TEST(BoardInit, BishopInitCorrectly) {
	Board chess;

	EXPECT_EQ(chess.getBoard()[0][2]->getName(), "Bishop");
	EXPECT_EQ(chess.getBoard()[0][2]->getType(), 1);
	EXPECT_EQ(chess.getBoard()[0][5]->getName(), "Bishop");
	EXPECT_EQ(chess.getBoard()[0][5]->getType(), 1);

	EXPECT_EQ(chess.getBoard()[7][2]->getName(), "Bishop");
	EXPECT_EQ(chess.getBoard()[7][2]->getType(), 0);
	EXPECT_EQ(chess.getBoard()[7][5]->getName(), "Bishop");
	EXPECT_EQ(chess.getBoard()[7][5]->getType(), 0);
}

TEST(BoardInit, QueenInitCorrectly) {
	Board chess;

	EXPECT_EQ(chess.getBoard()[0][3]->getName(), "Queen");
	EXPECT_EQ(chess.getBoard()[0][3]->getType(), 1);

	EXPECT_EQ(chess.getBoard()[7][3]->getName(), "Queen");
	EXPECT_EQ(chess.getBoard()[7][3]->getType(), 0);
}

TEST(BoardInit, KingInitCorrectly) {
	Board chess;

	EXPECT_EQ(chess.getBoard()[0][4]->getName(), "King");
	EXPECT_EQ(chess.getBoard()[0][4]->getType(), 1);

	EXPECT_EQ(chess.getBoard()[7][4]->getName(), "King");
	EXPECT_EQ(chess.getBoard()[7][4]->getType(), 0);
}

TEST(BoardInit, PiecesHaveUpdatedPossition) {
	Board chess;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (chess.getBoard()[i][j]) {
				EXPECT_EQ(chess.getBoard()[i][j]->getPosition().first, i);
				EXPECT_EQ(chess.getBoard()[i][j]->getPosition().second, j);
			}
		}
	}
}

TEST(GameOver, FoolsMateBlackWin) {
	Board chess;

	chess.movePiece(1, 6, 3, 6);
	chess.movePiece(6, 4, 5, 4);
	chess.movePiece(1, 5, 3, 5);
	chess.movePiece(7, 3, 3, 7);

	EXPECT_TRUE(chess.gameOver());
}

TEST(GameOver, FoolsMateWhiteWin) {
	Board chess;

	chess.movePiece(1, 4, 3, 4);
	chess.movePiece(6, 6, 4, 6);
	chess.movePiece(0, 1, 2, 2);
	chess.movePiece(6, 5, 4, 5);
	chess.movePiece(0, 3, 4, 7);
	chess.changeTurn();

	EXPECT_TRUE(chess.gameOver());
}

TEST(GameOver, Stalemate) {
	Board chess;

	for (int i = 0; i < 3; i++) {
		chess.getBoard()[7][i] = nullptr;
		chess.getBoard()[6][i] = nullptr;
	}
	chess.getBoard()[6][3] = nullptr;
	chess.movePiece(6, 5, 5, 5);
	chess.movePiece(6, 7, 4, 7);
	chess.movePiece(7, 3, 6, 7);
	chess.movePiece(7, 4, 6, 5);
	chess.movePiece(6, 5, 5, 6);
	chess.getBoard()[5][7] = new Rook(0);
	chess.getBoard()[5][7]->setPosition(5, 7);

	chess.movePiece(1, 7, 3, 7);
	chess.movePiece(1, 4, 2, 4);
	chess.movePiece(0, 3, 5, 4);

	chess.changeTurn();

	EXPECT_TRUE(chess.gameOver());
}

TEST(GameOver, InsufficientMaterialKnightvsKnight) {
	Board chess;

	for (int i = 0; i < 8; i++) {
		chess.getBoard()[1][i] = nullptr;
		chess.getBoard()[6][i] = nullptr;
	}

	for (int i = 0; i < 8; i++) {
		if (i != 1 && i != 4) {
			chess.getBoard()[0][i] = nullptr;
			chess.getBoard()[7][i] = nullptr;
		}
	}

	EXPECT_TRUE(chess.gameOver());
}

TEST(GameOver, InsufficientMaterialBishopvsBishop) {
	Board chess;

	for (int i = 0; i < 8; i++) {
		chess.getBoard()[1][i] = nullptr;
		chess.getBoard()[6][i] = nullptr;
	}

	for (int i = 0; i < 8; i++) {
		if (i != 2 && i != 4) {
			chess.getBoard()[0][i] = nullptr;
			chess.getBoard()[7][i] = nullptr;
		}
	}

	EXPECT_TRUE(chess.gameOver());
}

TEST(GameOver, InsufficientMaterialBishopvsKnight) {
	Board chess;

	for (int i = 0; i < 8; i++) {
		chess.getBoard()[1][i] = nullptr;
		chess.getBoard()[6][i] = nullptr;
	}

	for (int i = 0; i < 8; i++) {
		if (i != 1 && i != 2 && i != 4) {
			chess.getBoard()[0][i] = nullptr;
			chess.getBoard()[7][i] = nullptr;
		}
	}
	chess.getBoard()[0][1] = nullptr;
	chess.getBoard()[7][2] = nullptr;


	EXPECT_TRUE(chess.gameOver());
}