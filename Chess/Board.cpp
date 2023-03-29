#include "Board.h"


Board::Board()
	: white(1),
	  black(0),
	  whitesTurn{true},
	  pawnMoves { 0 },
	  lastMovePawn { false }
{
	board.resize(8);

	for (size_t i = 0; i < 8; i++) {
		board.at(i).resize(8);
	}
	
	//Populate with Pawns
	for (size_t i = 0; i < 8; i++) {
		board.at(1).at(i) = white.getPieces().at(i);
		board.at(6).at(i) = black.getPieces().at(i);
	}

	//Populate with Rooks
	board.at(0).at(0) = white.getPieces().at(8);
	board.at(0).at(7) = white.getPieces().at(9);
	board.at(7).at(0) = black.getPieces().at(8);
	board.at(7).at(7) = black.getPieces().at(9);

	//Populate with Knights
	board.at(0).at(1) = white.getPieces().at(10);
	board.at(0).at(6) = white.getPieces().at(11);
	board.at(7).at(1) = black.getPieces().at(10);
	board.at(7).at(6) = black.getPieces().at(11);

	//Populate with Bishops
	board.at(0).at(2) = white.getPieces().at(12);
	board.at(0).at(5) = white.getPieces().at(13);
	board.at(7).at(2) = black.getPieces().at(12);
	board.at(7).at(5) = black.getPieces().at(13);

	//Populate with Queens
	board.at(0).at(3) = white.getPieces().at(14);
	board.at(7).at(3) = black.getPieces().at(14);

	//Populate with Kings
	board.at(0).at(4) = white.getPieces().at(15);
	board.at(7).at(4) = black.getPieces().at(15);

	setPiecePosition();

}

void Board::setPiecePosition()
{
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if(board[i][j])
				board.at(i).at(j)->setPosition(i, j);
		}
	}
}

void Board::takeInput()
{
	std::string input{};

	while (!gameOver()) {
		print();

		if (inCheck().first) {
			if (whitesTurn) {
				std::cout << "White is in check!!!!!\n";
			}
			else {
				std::cout << "Black is in check!!!!!\n";
			}
		}

		if (whitesTurn) {
			std::cout << "White's turn.\n";
		}
		else {
			std::cout << "Black's turn.\n";
		}

		std::cout << "Enter the position of the piece that you want to move(ex: d2): ";
		std::cin >> input;
		if (checkInput(input) && checkCorrectPiece(input)) {
			int iOld = input.at(1) - '0' - 1;
			int jOld = toupper(input.at(0)) - 'A';

			std::vector<std::pair<int, int>> availableMovesForPiece{ availableMoves(board[iOld][jOld]) };

			if (availableMovesForPiece.size() == 0) {
				std::cout << "\n\nNo available moves for this piece\n";
			}
			else {
				print();

				std::cout << "\nAvailable positions: ";
				for (int i = 0; i < availableMovesForPiece.size(); i++) {
					std::cout << static_cast<char>('A' + availableMovesForPiece.at(i).second) << availableMovesForPiece.at(i).first + 1;
					if (i != availableMovesForPiece.size() - 1) {
						std::cout << ", ";
					}
					else {
						std::cout << "\n";
					}
				}

				while (true) {
					std::cout << "\nTIP: Enter q to chose another piece\n";
					std::cout << "Enter new position:";
					std::cin >> input;
					if (input[0] == 'q' || input[0] == 'Q') {
						break;
					}
					while (!checkInput(input)) {
						std::cout << "Please enter valid input: ";
						std::cin >> input;
					}

					int iNew = input.at(1) - '0' - 1;
					int jNew = toupper(input.at(0)) - 'A';

					std::pair<int, int> isValidMove{ iNew, jNew };
					if (std::find(availableMovesForPiece.begin(), availableMovesForPiece.end(), isValidMove) != availableMovesForPiece.end()) {
						movePiece(iOld, jOld, iNew, jNew);
						break;
					}
				}
				if (input[0] != 'q' && input[0] != 'Q') {
					whitesTurn = !whitesTurn;
				}
			}
		}
		else {
			std::cout << "Please enter a valid position!\n";
		}

	}

	print();
	if (inCheck().first) {
		std::cout << "Checkmate!!!\n";
		if (inCheck().second) {
			std::cout << "Black has won!\n";
		}
		else {
			std::cout << "White has won!\n";
		}
	}
	else {
		std::cout << "Stalemate! -_-\n";
	}
}

bool Board::checkInput(std::string& input) {
	if (input.size() != 2)
		return false;

	input.at(0) = toupper(input.at(0));
	if (input.at(0) < 'A' || input.at(0) > 'H')
		return false;

	if (!isdigit(input.at(1)))
		return false;

	if (input.at(1) == '9' || input.at(1) == '0')
		return false;

	return true;
}

bool Board::checkCorrectPiece(std::string& input)
{
	int i = input.at(1) - '0' - 1;
	int j = toupper(input.at(0)) - 'A';

	if (!board[i][j])
		return false;

	
	if (whitesTurn) {
		for (const auto &piece : white.getPieces()) {
			if (piece == board.at(i).at(j)) {
				return true;
			}
		}
		return false;
	}
	else {
		for (const auto& piece : black.getPieces()) {
			if (piece == board.at(i).at(j)) {
				return true;
			}
		}
		return false;
	}
}

void Board::movePiece(int iOld, int jOld, int i, int j)
{
	board[i][j] = board[iOld][jOld];
	board[i][j]->setPosition(i, j);

	if (dynamic_cast<Pawn*>(board[i][j])) {

		if (dynamic_cast<Pawn*>(board[i][j])->getEnPassant().first || dynamic_cast<Pawn*>(board[i][j])->getEnPassant().second) {
			dynamic_cast<Pawn*>(board[i][j])->enPassantInactive();

			if (j != jOld) {
				board[iOld][j] = nullptr;
			}

		}

		pawnMoves++;
		lastMovePawn = true;
	}
	else {
		lastMovePawn = false;
	}

	if (dynamic_cast<Pawn*>(board[i][j]) && !dynamic_cast<Pawn*>(board[i][j])->getHasMoved()) {
		dynamic_cast<Pawn*>(board[i][j])->setHasMovedTrue();

		if (abs(iOld - i) == 2) {
			if (j+1 < 8 && board[i][j + 1]) {
				if (typeid(*board[i][j + 1]) == typeid(Pawn)) {
					dynamic_cast<Pawn*>(board[i][j + 1])->enPassantActive(1);
					dynamic_cast<Pawn*>(board[i][j + 1])->setTotalPawnsMoved(pawnMoves);
				}
			}
			if (j - 1 >= 0 && board[i][j - 1]) {
				if (typeid(*board[i][j - 1]) == typeid(Pawn)) {
					dynamic_cast<Pawn*>(board[i][j - 1])->enPassantActive(0);
					dynamic_cast<Pawn*>(board[i][j - 1])->setTotalPawnsMoved(pawnMoves);
				}
			}
		}
	}

	if (dynamic_cast<Pawn*>(board[i][j]) && dynamic_cast<Pawn*>(board[i][j])->checkPromotion()) {
		promotePawn(board[i][j]);
	}

	

	if (dynamic_cast<Rook*>(board[i][j]) && !dynamic_cast<Rook*>(board[i][j])->rookHasMoved()) {
		dynamic_cast<Rook*>(board[i][j])->setRookHasMoved();
	}
	if (dynamic_cast<King*>(board[i][j]) && dynamic_cast<King*>(board[i][j])->kingCastleAvailable()) {
		if (abs(j - jOld) == 2) {
			if (j > jOld) {
				board[i][j - 1] = board[i][7];
				board[i][j - 1]->setPosition(i, j - 1);
				board[i][7] = nullptr;
			}
			else {
				board[i][j + 1] = board[i][0];
				board[i][j + 1]->setPosition(i, j + 1);
				board[i][0] = nullptr;
			}
		}
		dynamic_cast<King*>(board[i][j])->setCastleUnavailable();
	}
	
	board[iOld][jOld] = nullptr;
	
}

std::vector<std::pair<int, int>> Board::availableMoves(Piece* piece)
{
	std::vector<std::pair<int, int>> availableMoves{};

	if (typeid(*piece) == typeid(Pawn) && whitesTurn) {
		availableMoves = whitePawnMoves(piece);
	}
	else if (typeid(*piece) == typeid(Pawn)) {
		availableMoves = blackPawnMoves(piece);
	}
	else if (typeid(*piece) == typeid(Rook)) {
		availableMoves = rookMoves(piece);
	}
	else if (typeid(*piece) == typeid(Knight)) {
		availableMoves = knightMoves(piece);
	}
	else if (typeid(*piece) == typeid(Bishop)) {
		availableMoves = bishopMoves(piece);
	}
	else if (typeid(*piece) == typeid(Queen)) {
		availableMoves =  bishopMoves(piece);
		std::vector<std::pair<int, int>> availableRookMoves{ rookMoves(piece) };
		availableMoves.insert(availableMoves.end(), availableRookMoves.begin(), availableRookMoves.end());
	}
	else if (typeid(*piece) == typeid(King)) {
		availableMoves = kingMoves(piece);
	}

	removeIlegalMoves(availableMoves, piece);
	if (typeid(*piece) == typeid(King)) {
		removeIlegalCastle(availableMoves, piece);
	}
	return availableMoves;
}

std::vector<std::pair<int, int>> Board::whitePawnMoves(Piece* piece) {
	std::vector<std::pair<int, int>> allMoves{};

	if (piece->getPosition().first + 1 < 8 && !board[piece->getPosition().first+1][piece->getPosition().second]) {
		allMoves.push_back({ piece->getPosition().first + 1, piece->getPosition().second });
		if (!dynamic_cast<Pawn*>(piece)->getHasMoved() && piece->getPosition().first + 2 < 8 && !board[piece->getPosition().first + 2][piece->getPosition().second]) {
			allMoves.push_back({ piece->getPosition().first + 2, piece->getPosition().second });
		}
	}
	if (piece->getPosition().first + 1 < 8 && piece->getPosition().second + 1 < 8 && 
		board[piece->getPosition().first + 1][piece->getPosition().second + 1] && 
		board[piece->getPosition().first + 1][piece->getPosition().second + 1]->getType() != piece->getType()) {
		allMoves.push_back({ piece->getPosition().first + 1, piece->getPosition().second + 1 });
	}
	if (piece->getPosition().first + 1 < 8 && piece->getPosition().second - 1 >= 0 && 
		board[piece->getPosition().first + 1][piece->getPosition().second - 1] &&
		board[piece->getPosition().first + 1][piece->getPosition().second - 1]->getType() != piece->getType()) {
		allMoves.push_back({ piece->getPosition().first + 1, piece->getPosition().second - 1 });
	}

	if (lastMovePawn && dynamic_cast<Pawn*>(piece) && dynamic_cast<Pawn*>(piece)->getEnPassant().first) {
		if (dynamic_cast<Pawn*>(piece)->getTotalPawnsMoved() == pawnMoves) {
			allMoves.push_back({ piece->getPosition().first + 1, piece->getPosition().second - 1 });
		}
	}

	if (lastMovePawn && dynamic_cast<Pawn*>(piece) && dynamic_cast<Pawn*>(piece)->getEnPassant().second) {
		if (dynamic_cast<Pawn*>(piece)->getTotalPawnsMoved() == pawnMoves) {
			allMoves.push_back({ piece->getPosition().first + 1, piece->getPosition().second + 1 });
		}
	}

	return allMoves;
}

std::vector<std::pair<int, int>> Board::blackPawnMoves(Piece* piece) {
	std::vector<std::pair<int, int>> allMoves{};

	if (piece->getPosition().first - 1 >= 0 && !board[piece->getPosition().first - 1][piece->getPosition().second]) {
		allMoves.push_back({ piece->getPosition().first - 1, piece->getPosition().second });
		if (!dynamic_cast<Pawn*>(piece)->getHasMoved() && piece->getPosition().first - 2 >= 0 && !board[piece->getPosition().first - 2][piece->getPosition().second]) {
			allMoves.push_back({ piece->getPosition().first - 2, piece->getPosition().second });
		}
	}
	if (piece->getPosition().first - 1 >= 0 && piece->getPosition().second + 1 < 8 && 
		board[piece->getPosition().first - 1][piece->getPosition().second + 1] &&
		board[piece->getPosition().first - 1][piece->getPosition().second + 1]->getType() != piece->getType()) {
		allMoves.push_back({ piece->getPosition().first - 1, piece->getPosition().second + 1 });
	}
	if (piece->getPosition().first - 1 >= 0 && piece->getPosition().second - 1 >= 0 && 
		board[piece->getPosition().first - 1][piece->getPosition().second - 1] &&
		board[piece->getPosition().first - 1][piece->getPosition().second - 1]->getType() != piece->getType()) {
		allMoves.push_back({ piece->getPosition().first - 1, piece->getPosition().second - 1 });
	}

	if (dynamic_cast<Pawn*>(piece) && dynamic_cast<Pawn*>(piece)->getEnPassant().first) {
		if (dynamic_cast<Pawn*>(piece)->getTotalPawnsMoved() == pawnMoves) {
			allMoves.push_back({ piece->getPosition().first - 1, piece->getPosition().second - 1 });
		}
	}

	if (dynamic_cast<Pawn*>(piece) && dynamic_cast<Pawn*>(piece)->getEnPassant().second) {
		if (dynamic_cast<Pawn*>(piece)->getTotalPawnsMoved() == pawnMoves) {
			allMoves.push_back({ piece->getPosition().first - 1, piece->getPosition().second + 1 });
		}
	}

	return allMoves;
}

std::vector<std::pair<int, int>> Board::rookMoves(Piece* piece)
{
	std::vector<std::pair<int, int>> availableMoves{};

	for (int i = piece->getPosition().first + 1; i < 8; i++) {
		if (!board[i][piece->getPosition().second]) {
			availableMoves.push_back({ i, piece->getPosition().second });
		}
		else {
			if (board[i][piece->getPosition().second]->getType() == piece->getType()) {
				break;
			}
			availableMoves.push_back({ i, piece->getPosition().second });
			break;
		}
	}

	for (int i = piece->getPosition().first - 1; i >= 0 ; i--) {
		if (!board[i][piece->getPosition().second]) {
			availableMoves.push_back({ i, piece->getPosition().second });
		}
		else {
			if (board[i][piece->getPosition().second]->getType() == piece->getType()) {
				break;
			}
			availableMoves.push_back({ i, piece->getPosition().second });
			break;
		}
	}

	for (int j = piece->getPosition().second + 1; j < 8; j++) {
		if (!board[piece->getPosition().first][j]) {
			availableMoves.push_back({ piece->getPosition().first, j });
		}
		else {
			if (board[piece->getPosition().first][j]->getType() == piece->getType()) {
				break;
			}
			availableMoves.push_back({ piece->getPosition().first, j });
			break;
		}
	}

	for (int j = piece->getPosition().second - 1; j >= 0; j--) {
		if (!board[piece->getPosition().first][j]) {
			availableMoves.push_back({ piece->getPosition().first, j });
		}
		else {
			if (board[piece->getPosition().first][j]->getType() == piece->getType()) {
				break;
			}
			availableMoves.push_back({ piece->getPosition().first, j });
			break;
		}
	}

	return availableMoves;
}

std::vector<std::pair<int, int>> Board::knightMoves(Piece* piece)
{
	std::vector<std::pair<int, int>> availableMoves{};

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* temp = nullptr;
			if (i == piece->getPosition().first - 2 && j == piece->getPosition().second + 1) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}
			else if (i == piece->getPosition().first - 2 && j == piece->getPosition().second - 1) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}
			else if (i == piece->getPosition().first + 2 && j == piece->getPosition().second + 1) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}
			else if (i == piece->getPosition().first + 2 && j == piece->getPosition().second - 1) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}
			else if (i == piece->getPosition().first - 1 && j == piece->getPosition().second + 2) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}
			else if (i == piece->getPosition().first + 1 && j == piece->getPosition().second + 2) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}
			else if (i == piece->getPosition().first - 1 && j == piece->getPosition().second - 2) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}

			else if (i == piece->getPosition().first + 1 && j == piece->getPosition().second - 2) {
				temp = board[i][j];
				if (!temp || temp->getType() != piece->getType()) {
					availableMoves.push_back({ i, j });
				}
			}
		}
	}

	return availableMoves;
}

std::vector<std::pair<int, int>> Board::bishopMoves(Piece* piece)
{
	std::vector<std::pair<int, int>> availableMoves{};

	int i{ piece->getPosition().first + 1};
	int j{ piece->getPosition().second + 1};

	while(i < 8 && j < 8) {
		if (!board[i][j]) {
			availableMoves.push_back({ i,j });
		}
		else {
			if (board[i][j]->getType() != piece->getType()) {
				availableMoves.push_back({ i,j });
			}
			break;
		}
		i++;
		j++;
	}

	i = piece->getPosition().first - 1;
	j = piece->getPosition().second - 1;
	while (i >= 0 && j >= 0) {
		if (!board[i][j]) {
			availableMoves.push_back({ i,j });
		}
		else {
			if (board[i][j]->getType() != piece->getType()) {
				availableMoves.push_back({ i,j });
			}
			break;
		}
		i--;
		j--;
	}

	i = piece->getPosition().first - 1;
	j = piece->getPosition().second + 1;
	while (i >= 0 && j < 8) {
		if (!board[i][j]) {
			availableMoves.push_back({ i,j });
		}
		else {
			if (board[i][j]->getType() != piece->getType()) {
				availableMoves.push_back({ i,j });
			}
			break;
		}
		i--;
		j++;
	}

	i = piece->getPosition().first + 1;
	j = piece->getPosition().second - 1;
	while (i < 8 && j >= 0) {
		if (!board[i][j]) {
			availableMoves.push_back({ i,j });
		}
		else {
			if (board[i][j]->getType() != piece->getType()) {
				availableMoves.push_back({ i,j });
			}
			break;
		}
		i++;
		j--;
	}


	return availableMoves;
}

std::vector<std::pair<int, int>> Board::kingMoves(Piece* piece)
{
	std::vector<std::pair<int, int>> allMoves{};

	if (castleAvailable(piece).first) {
		allMoves.push_back({ piece->getPosition().first, 2 });
	}

	if (castleAvailable(piece).second) {
		allMoves.push_back({ piece->getPosition().first, 6 });
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i >= piece->getPosition().first - 1 && i <= piece->getPosition().first + 1 &&
				j >= piece->getPosition().second - 1 && j <= piece->getPosition().second + 1) {
				if (!board[i][j]) {
					allMoves.push_back({ i, j });
				} 
				else if (board[i][j]->getType() != piece->getType()) {
					allMoves.push_back({ i, j });
				}
			}
		}
	}


	return allMoves;
}

std::vector<std::pair<int, int>> Board::pawnChecks(Piece* piece)
{
	std::vector<std::pair<int, int>> pawnChecks;

	if (piece->getType()) {
		if (piece->getPosition().first + 1 < 8 && piece->getPosition().second + 1 < 8 &&
			board[piece->getPosition().first + 1][piece->getPosition().second + 1] &&
			board[piece->getPosition().first + 1][piece->getPosition().second + 1]->getType() != piece->getType())
			pawnChecks.push_back({ piece->getPosition().first + 1, piece->getPosition().second + 1 });
		if (piece->getPosition().first + 1 < 8 && piece->getPosition().second - 1 >= 0 &&
			board[piece->getPosition().first + 1][piece->getPosition().second - 1] &&
			board[piece->getPosition().first + 1][piece->getPosition().second - 1]->getType() != piece->getType()) {
			pawnChecks.push_back({ piece->getPosition().first + 1, piece->getPosition().second - 1 });
		}
	}
	else {
		if (piece->getPosition().first - 1 >= 0 && piece->getPosition().second + 1 < 8 &&
			board[piece->getPosition().first - 1][piece->getPosition().second + 1] &&
			board[piece->getPosition().first - 1][piece->getPosition().second + 1]->getType() != piece->getType())
			pawnChecks.push_back({ piece->getPosition().first - 1, piece->getPosition().second + 1 });
		if (piece->getPosition().first - 1 >= 0 && piece->getPosition().second - 1 >= 0 &&
			board[piece->getPosition().first - 1][piece->getPosition().second - 1] &&
			board[piece->getPosition().first - 1][piece->getPosition().second - 1]->getType() != piece->getType()) {
			pawnChecks.push_back({ piece->getPosition().first - 1, piece->getPosition().second - 1 });
		}
	}

	return pawnChecks;
}

bool Board::isIllegalMove(Piece* piece, int newI, int newJ)
{
	int tempI = piece->getPosition().first;
	int tempJ = piece->getPosition().second;
	bool illegal{};

	Piece* savedPiece = board[newI][newJ];
	board[newI][newJ] = board[tempI][tempJ];
	board[newI][newJ]->setPosition(newI, newJ);
	board[tempI][tempJ] = nullptr;

	if (inCheck().first) {
		illegal = true;
	}

	board[tempI][tempJ] = board[newI][newJ];
	board[tempI][tempJ]->setPosition(tempI, tempJ);
	board[newI][newJ] = savedPiece;

	if (board[tempI][tempJ]) {
		board[tempI][tempJ]->setPosition(tempI, tempJ);
	}

	if (board[newI][newJ]) {
		board[newI][newJ]->setPosition(newI, newJ);
	}

	return illegal;
}

void Board::removeIlegalMoves(std::vector<std::pair<int, int>>& allMoves, Piece* piece)
{

	for (int i = 0; i < allMoves.size(); i++) {
		bool illegalMove = isIllegalMove(piece, allMoves[i].first, allMoves[i].second);

		if (illegalMove) {
			allMoves.erase(allMoves.begin() + i);
			i--;
		}
	}
}

void Board::removeIlegalCastle(std::vector<std::pair<int, int>>& allMoves, Piece* piece)
{
	if (castleAvailable(piece) == std::pair<bool, bool>({0, 0})) {
		return;
	}

	int tempI = piece->getPosition().first;
	int tempJ = piece->getPosition().second;

	if (std::find(allMoves.begin(), allMoves.end(), std::pair<int, int>({ tempI, tempJ - 1 })) == allMoves.end()) {
		if (std::find(allMoves.begin(), allMoves.end(), std::pair<int, int>({ tempI, tempJ - 2 })) != allMoves.end()) {
			allMoves.erase(std::remove(allMoves.begin(), allMoves.end(), std::pair<int, int>({ tempI, tempJ - 2 })), allMoves.end());
		}
	}

	if (std::find(allMoves.begin(), allMoves.end(), std::pair<int, int>({ tempI, tempJ + 1 })) == allMoves.end()) {
		if (std::find(allMoves.begin(), allMoves.end(), std::pair<int, int>({ tempI, tempJ + 2 })) != allMoves.end()) {
			allMoves.erase(std::remove(allMoves.begin(), allMoves.end(), std::pair<int, int>({ tempI, tempJ + 2 })), allMoves.end());
		}
	}
}

std::pair<int, int> Board::inCheck()
{
	std::vector<std::pair<int, int>> availableChecks{};
	bool foundCheck{}, done{};

	Piece* king;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (dynamic_cast<King*>(board[i][j]) && board[i][j]->getType() == whitesTurn) {

				king = board[i][j];

				std::vector<std::pair<int, int>> temp = rookMoves(board[i][j]);
				
				if (kingChecked(temp, "Rook")) {
					foundCheck = true;
				}
				

				temp = bishopMoves(board[i][j]);
				if (kingChecked(temp, "Bishop")) {
					foundCheck = true;
				}


				temp = knightMoves(board[i][j]);
				if (kingChecked(temp, "Knight")) {
					foundCheck = true;
				}

				temp = kingMoves(board[i][j]);
				if (kingChecked(temp, "King")) {
					foundCheck = true;
				}

				temp = pawnChecks(board[i][j]);
				if (kingChecked(temp, "Pawn")) {
					foundCheck = true;
				}

				done = true;
				break;
			}
		}
		if (done) {
			break;
		}
	}

	if (!foundCheck) {
		return {0,0};
	}
	else {
		return { 1, whitesTurn };
	}
}

bool Board::kingChecked(std::vector<std::pair<int, int>>& dangerousSquares, const std::string& type)
{
	bool check{};

	for (int i = 0; i < dangerousSquares.size(); i++) {
		if (board[dangerousSquares[i].first][dangerousSquares[i].second] && 
			board[dangerousSquares[i].first][dangerousSquares[i].second]->getType() != whitesTurn &&
			(board[dangerousSquares[i].first][dangerousSquares[i].second]->getName() == type ||
			 (board[dangerousSquares[i].first][dangerousSquares[i].second]->getName() == "Queen" &&
			 type != "Knight"))) {
			check = true;
		}
	}

	return check;
}

bool Board::gameOver() {
	if (insufficientMaterial()) {
		return true;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] && board[i][j]->getType() == whitesTurn && availableMoves(board[i][j]).size())
				return false;
		}
	}
}

bool Board::insufficientMaterial()
{
	int whiteMaterial{}, blackMaterial{};

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] && board[i][j]->getType()) {
				if (dynamic_cast<Knight*>(board[i][j]) || dynamic_cast<Bishop*>(board[i][j]) || dynamic_cast<King*>(board[i][j]))
					whiteMaterial++;
				else {
					whiteMaterial += 2;
				}
			}
			else if (board[i][j] && !board[i][j]->getType()) {
				if (dynamic_cast<Knight*>(board[i][j]) || dynamic_cast<Bishop*>(board[i][j]) || dynamic_cast<King*>(board[i][j]))
					blackMaterial++;
				else {
					blackMaterial += 2;
				}
			}

			if (blackMaterial > 2 || whiteMaterial > 2) {
				return false;
			}
		}
	}

	return true;
}

std::pair<bool, bool> Board::castleAvailable(Piece* piece)
{
	if (!dynamic_cast<King*>(piece)->kingCastleAvailable()) {
		return std::pair<bool, bool>({ 0, 0 });
	}

	bool shortCastle{true}, longCastle{true};

	Piece* tempRook = board[piece->getPosition().first][0];
	if (!dynamic_cast<Rook*>(tempRook)) {
		shortCastle = false;
	}
	else if (!dynamic_cast<Rook*>(tempRook)->rookHasMoved()) {
		shortCastle = true;
	}
	tempRook = board[piece->getPosition().first][7];
	if (!dynamic_cast<Rook*>(tempRook)) {
		longCastle = false;
	}
	else if (dynamic_cast<Rook*>(tempRook)->rookHasMoved()) {
		longCastle = true;
	}

	if (!shortCastle && !longCastle) {
		return std::pair<bool, bool>({ 0, 0 });
	}

	int kingRank = piece->getPosition().first;

	if (board[kingRank][1] || board[kingRank][2] && board[kingRank][3]) {
		shortCastle = false;
	}

	if (board[kingRank][5] || board[kingRank][6]) {
		longCastle = false;
	}

	return std::pair<bool, bool>({ shortCastle, longCastle });
}

void Board::promotePawn(Piece* piece)
{
	int i = piece->getPosition().first;
	int j = piece->getPosition().second;
	bool done{ false };
	std::string input{};
	std::cout << "Promotion!!!\nEnter the piece that you want (Queen, Rook, Bishop, Knight):";
	do {
		std::cin >> input;
		for (auto& c : input) {
			c = toupper(c);
		}
		if ((input.size() == 1 && input[0] == 'Q') || input == "QUEEN") {
			if (whitesTurn) {
				Piece* temp = new Queen(1);
				placePiece(temp, i, j);
			}
			else {
				Piece* temp = new Queen(0);
				placePiece(temp, i, j);
			}
			done = true;
		}
		else if ((input.size() == 1 && input[0] == 'R') || input == "ROOK") {
			if (whitesTurn) {
				Piece* temp = new Rook(1);
				placePiece(temp, i, j);
			}
			else {
				Piece* temp = new Rook(0);
				placePiece(temp, i, j);
			}
			done = true;
		}
		else if ((input.size() == 1 && input[0] == 'B') || input == "BISHOP") {
			if (whitesTurn) {
				Piece* temp = new Bishop(1);
				placePiece(temp, i, j);
			}
			else {
				Piece* temp = new Bishop(0);
				placePiece(temp, i, j);
			}
			done = true;
		}
		else if ((input.size() == 1 && input[0] == 'K') || input == "Knight") {
			if (whitesTurn) {
				Piece* temp = new Knight(1);
				placePiece(temp, i, j);
			}
			else {
				Piece* temp = new Knight(0);
				placePiece(temp, i, j);
			}
			done = true;
		}
		if (!done) {
			std::cout << "Please enter a valid input:";
		}
	} while (!done);

	piece->setPosition(i, j);
}

void Board::placePiece(Piece* piece, int i, int j)
{
	if (piece->getType() == 1) {
		white.insertPiece(piece);
	}
	else {
		black.insertPiece(piece);
	}
	board[i][j] = piece;
	board[i][j]->setPosition(i, j);
}

void Board::print()
{
	std::cout << "   ";
	for (char file = 'A'; file < 'I'; file++) {
		std::cout << file << "\t";
	}
	std::cout << "\n";

	for (int file = 7; file >= 0; file--) {
		std::cout << file+1 << "  ";
		for (int rank = 0; rank < 8; rank++) {
			if (board.at(file).at(rank)) {
				bool whitePiece{ false };
				for (const auto& piece : white.getPieces()) {
					if (piece == board.at(file).at(rank)) {
						whitePiece = true;
					}
				}

				if (whitePiece) {
						std::cout << "w" << board.at(file).at(rank)->getShortName() << "\t";
				}
				else {
					std::cout << "b" << board.at(file).at(rank)->getShortName() << "\t";
				}
			}
			else {
				std::cout << "  \t";
			}
		}
		std::cout << "\n\n\n";
	}
}

std::ostream& operator<<(std::ostream& output, const Board& board)
{
	output << "   ";
	for (char file = 'A'; file < 'I'; file++) {
		output << file << "\t";
	}
	output << "\n";

	for (size_t file = 0; file < 8; file++) {
		output << 8 - file << "  ";
		for (size_t rank = 0; rank < 8; rank++) {
			if (board.board.at(file).at(rank)) {
				output << board.board.at(file).at(rank)->getName() << "\t";
			}
			else {
				output << "  ";
			}
		}
		output << "\n\n\n";
	}

	return output;
}

