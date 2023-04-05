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
	EXPECT_TRUE(chess.inCheck().first);
	EXPECT_TRUE(chess.inCheck().second);
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
	EXPECT_TRUE(chess.inCheck().first);
	EXPECT_FALSE(chess.inCheck().second);
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
	EXPECT_FALSE(chess.inCheck().first);
	EXPECT_FALSE(chess.inCheck().second);
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

TEST(KingMovement, ShortCastleAvailable) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][6] = nullptr;
	chess.getBoard()[0][5] = nullptr;

	EXPECT_FALSE(chess.castleAvailable(king).first);
	EXPECT_TRUE(chess.castleAvailable(king).second);
}

TEST(KingMovement, LongCastleAvailable) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][3] = nullptr;
	chess.getBoard()[0][2] = nullptr;
	chess.getBoard()[0][1] = nullptr;

	EXPECT_TRUE(chess.castleAvailable(king).first);
	EXPECT_FALSE(chess.castleAvailable(king).second);
}

TEST(KingMovement, ShortAndLongCastleAvailable) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][6] = nullptr;
	chess.getBoard()[0][5] = nullptr;
	chess.getBoard()[0][3] = nullptr;
	chess.getBoard()[0][2] = nullptr;
	chess.getBoard()[0][1] = nullptr;

	EXPECT_TRUE(chess.castleAvailable(king).first);
	EXPECT_TRUE(chess.castleAvailable(king).second);
}

TEST(KingMovement, NoCastleAvailablePiecesInTheWay) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][6] = nullptr;
	chess.getBoard()[0][1] = nullptr;

	EXPECT_FALSE(chess.castleAvailable(king).first);
	EXPECT_FALSE(chess.castleAvailable(king).second);
}

TEST(KingMovement, NoCastleKingMoved) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][6] = nullptr;
	chess.getBoard()[0][5] = nullptr;
	chess.getBoard()[0][3] = nullptr;
	chess.getBoard()[0][2] = nullptr;
	chess.getBoard()[0][1] = nullptr;

	chess.movePiece(0, 4, 0, 5);
	chess.movePiece(0, 5, 0, 4);

	EXPECT_FALSE(chess.castleAvailable(king).first);
	EXPECT_FALSE(chess.castleAvailable(king).second);
}

TEST(KingMovement, NoCastleRooksMoved) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][6] = nullptr;
	chess.getBoard()[0][5] = nullptr;
	chess.getBoard()[0][3] = nullptr;
	chess.getBoard()[0][2] = nullptr;
	chess.getBoard()[0][1] = nullptr;

	chess.movePiece(0, 0, 0, 1);
	chess.movePiece(0, 1, 0, 0);

	chess.movePiece(0, 7, 0, 6);
	chess.movePiece(0, 6, 0, 7);

	EXPECT_FALSE(chess.castleAvailable(king).first);
	EXPECT_FALSE(chess.castleAvailable(king).second);
}

TEST(KingMovement, NoCastleThroughCheck) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][6] = nullptr;
	chess.getBoard()[0][5] = nullptr;
	chess.getBoard()[0][3] = nullptr;
	chess.getBoard()[0][2] = nullptr;
	chess.getBoard()[0][1] = nullptr;
	chess.getBoard()[1][3] = nullptr;

	chess.movePiece(7, 0, 5, 3);
	chess.movePiece(7, 1, 2, 6);

	EXPECT_EQ(chess.availableMoves(king).size(), 0);
}

TEST(KingMovement, NoCastleWhileInCheck) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][6] = nullptr;
	chess.getBoard()[0][5] = nullptr;
	chess.getBoard()[0][3] = nullptr;
	chess.getBoard()[0][2] = nullptr;
	chess.getBoard()[0][1] = nullptr;

	chess.movePiece(7, 1, 2, 5);

	EXPECT_EQ(chess.availableMoves(king).size(), 2);
}

TEST(KingMovement, KingCantMoveIntoCheck) {
	Board chess;
	Piece* king = chess.getBoard()[0][4];

	chess.getBoard()[0][5] = nullptr;
	chess.getBoard()[0][3] = nullptr;
	chess.getBoard()[1][3] = nullptr;

	chess.movePiece(7, 0, 5, 3);
	chess.movePiece(7, 1, 2, 6);

	EXPECT_EQ(chess.availableMoves(king).size(), 0);
}

TEST(KingMovement, KingsCantBeNearEachother) {
	Board chess;
	Piece* whiteKing = chess.getBoard()[0][4];
	Piece* blackKing = chess.getBoard()[7][4];

	chess.movePiece(0, 4, 3, 4);
	chess.movePiece(7, 4, 6, 3);
	chess.movePiece(6, 3, 3, 2);

	EXPECT_EQ(chess.availableMoves(whiteKing).size(), 4);
	chess.changeTurn();
	EXPECT_EQ(chess.availableMoves(blackKing).size(), 3);
}

TEST(WhitePawnMovement, OneOrTwoSquaresForwardAsFirstMove) {
	Board chess;

	for (int i = 0; i < 8; i++) {
		Piece* whitePawn = chess.getBoard()[1][i];
		EXPECT_EQ(chess.whitePawnMoves(whitePawn).size(), 2);
	}
}

TEST(WhitePawnMovement, PromotionAvailable) {
	Board chess;

	Piece* whitePawn = chess.getBoard()[1][0];
	EXPECT_FALSE(dynamic_cast<Pawn*>(whitePawn)->checkPromotion());

	chess.getBoard()[6][0] = nullptr;
	chess.getBoard()[7][0] = nullptr;
	whitePawn->setPosition(7, 0);

	EXPECT_TRUE(dynamic_cast<Pawn*>(whitePawn)->checkPromotion());
}

TEST(WhitePawnMovement, CaptureLeft) {
	Board chess;

	Piece* whitePawn = chess.getBoard()[1][4];
	chess.movePiece(6, 3, 2, 3);

	EXPECT_EQ(chess.whitePawnMoves(whitePawn).size(), 3);
}

TEST(WhitePawnMovement, CaptureRight) {
	Board chess;

	Piece* whitePawn = chess.getBoard()[1][4];
	chess.movePiece(6, 5, 2, 5);

	EXPECT_EQ(chess.whitePawnMoves(whitePawn).size(), 3);
}

TEST(WhitePawnMovement, EnPassantLeft) {
	Board chess;

	Piece* whitePawn = chess.getBoard()[1][4];
	chess.movePiece(1, 4, 4, 4);
	chess.movePiece(6, 3, 4, 3);

	EXPECT_TRUE(dynamic_cast<Pawn*>(whitePawn)->getEnPassant().first);
	EXPECT_FALSE(dynamic_cast<Pawn*>(whitePawn)->getEnPassant().second);
	EXPECT_EQ(chess.whitePawnMoves(whitePawn).size(), 2);
}

TEST(WhitePawnMovement, EnPassantRight) {
	Board chess;

	Piece* whitePawn = chess.getBoard()[1][4];
	chess.movePiece(1, 4, 4, 4);
	chess.movePiece(6, 5, 4, 5);

	EXPECT_FALSE(dynamic_cast<Pawn*>(whitePawn)->getEnPassant().first);
	EXPECT_TRUE(dynamic_cast<Pawn*>(whitePawn)->getEnPassant().second);
	EXPECT_EQ(chess.whitePawnMoves(whitePawn).size(), 2);
}

TEST(BlackPawnMovement, OneOrTwoSquaresForwardAsFirstMove) {
	Board chess;

	for (int i = 0; i < 8; i++) {
		Piece* blackPawn = chess.getBoard()[6][i];
		EXPECT_EQ(chess.blackPawnMoves(blackPawn).size(), 2);
	}
}

TEST(BlackPawnMovement, PromotionAvailable) {
	Board chess;

	Piece* blackPawn = chess.getBoard()[6][0];
	EXPECT_FALSE(dynamic_cast<Pawn*>(blackPawn)->checkPromotion());

	chess.getBoard()[1][0] = nullptr;
	chess.getBoard()[0][0] = nullptr;
	blackPawn->setPosition(0, 0);

	EXPECT_TRUE(dynamic_cast<Pawn*>(blackPawn)->checkPromotion());
}

TEST(BlackPawnMovement, CaptureLeft) {
	Board chess;

	Piece* blackPawn = chess.getBoard()[6][4];
	chess.movePiece(1, 3, 5, 3);

	EXPECT_EQ(chess.blackPawnMoves(blackPawn).size(), 3);
}

TEST(BlackPawnMovement, CaptureRight) {
	Board chess;

	Piece* blackPawn = chess.getBoard()[6][4];
	chess.movePiece(1, 5, 5, 5);

	EXPECT_EQ(chess.blackPawnMoves(blackPawn).size(), 3);
}

TEST(BlackPawnMovement, EnPassantLeft) {
	Board chess;

	Piece* blackPawn = chess.getBoard()[6][4];
	chess.movePiece(6, 4, 3, 4);
	chess.movePiece(1, 3, 3, 3);

	EXPECT_TRUE(dynamic_cast<Pawn*>(blackPawn)->getEnPassant().first);
	EXPECT_FALSE(dynamic_cast<Pawn*>(blackPawn)->getEnPassant().second);
	EXPECT_EQ(chess.blackPawnMoves(blackPawn).size(), 2);
}

TEST(BlackPawnMovement, EnPassantRight) {
	Board chess;

	Piece* blackPawn = chess.getBoard()[6][4];
	chess.movePiece(6, 4, 3, 4);
	chess.movePiece(1, 5, 3, 5);

	EXPECT_FALSE(dynamic_cast<Pawn*>(blackPawn)->getEnPassant().first);
	EXPECT_TRUE(dynamic_cast<Pawn*>(blackPawn)->getEnPassant().second);
	EXPECT_EQ(chess.blackPawnMoves(blackPawn).size(), 2);
}

TEST(GeneralPieceMovement, PieceCantMoveOutOfPin) {
	Board chess;
	
	Piece* knight = chess.getBoard()[0][6];

	chess.movePiece(0, 6, 1, 4);
	chess.movePiece(7, 0, 2, 4);

	EXPECT_EQ(chess.availableMoves(knight).size(), 0);
}

TEST(GeneralPieceMovement, PinnedPieceCanCapture) {
	Board chess;

	Piece* rook = chess.getBoard()[0][7];

	chess.movePiece(0, 7, 1, 4);
	chess.movePiece(7, 0, 2, 4);

	EXPECT_EQ(chess.availableMoves(rook).size(), 1);
}

TEST(GeneralPieceMovement, PinnedPieceCanMoveKeepingPin) {
	Board chess;

	Piece* rook = chess.getBoard()[0][7];

	chess.movePiece(0, 7, 1, 4);
	chess.movePiece(7, 0, 3, 4);

	EXPECT_EQ(chess.availableMoves(rook).size(), 2);
}

TEST(GeneralPieceMovement, QueenMovement) {
	Board chess;

	Piece* queen = chess.getBoard()[0][3];

	chess.movePiece(0, 3, 2, 3);

	EXPECT_EQ(chess.availableMoves(queen).size(), 18);
}

TEST(GeneralPieceMovement, RookMovement) {
	Board chess;

	Piece* rook = chess.getBoard()[0][0];
	EXPECT_EQ(chess.availableMoves(rook).size(), 0);

	chess.movePiece(0, 0, 3, 3);

	EXPECT_EQ(chess.availableMoves(rook).size(), 11);
}

TEST(GeneralPieceMovement, KnightMovement) {
	Board chess;

	Piece* knight = chess.getBoard()[0][1];
	EXPECT_EQ(chess.availableMoves(knight).size(), 2);

	chess.movePiece(0, 1, 5, 2);

	EXPECT_EQ(chess.availableMoves(knight).size(), 8);
}

TEST(GeneralPieceMovement, BishopMovement) {
	Board chess;

	Piece* bishop = chess.getBoard()[0][2];
	EXPECT_EQ(chess.availableMoves(bishop).size(), 0);

	chess.movePiece(0, 2, 4, 2);

	EXPECT_EQ(chess.availableMoves(bishop).size(), 8);
}