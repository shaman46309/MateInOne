#include "chess_board.h"

#include <iostream>
namespace chess {

bool ChessBoard::IsMate() {
	return false;
}

bool ChessBoard::IsKingInCheck(PieceColor color) {
	std::cout << "Checking if king is in check for color " << color << std::endl;
	std::set<ChessPiece>::const_iterator itr_black = this->black_pieces.cbegin();
	std::set<ChessPiece>::const_iterator itr_white = this->white_pieces.cbegin();

	if (color == BLACK) {
		return IsChecked(black_king, itr_white);
	} else {
		return IsChecked(white_king, itr_black);
	}
	return false;
}

bool ChessBoard::IsChecked(ChessPiece* king, std::set<ChessPiece>::const_iterator opposition) {
	std::cout << "Target king's location " << king->location() << std::endl;

//	do {
//		std::cout << "Now need to check if opposition piece with location "
//				<< opposition->location() << " is  checking the king." << std::endl;
//		opposition++;
//	} while (opposition);
	return false;
}

void ChessBoard::InitPieces(const chess::FEN& fen) {
	// TODO(pankajm): Refactor following logic into InitPieces or somethin'
	const char* raw = fen.trimmed_.c_str();

	Rank current_rank = EIGHT;
	File current_file = File::a;
	for (int i = 0; i < fen.trimmed_.size(); i++) {

		char c = *(raw + i);
		if (c == '/') {
			current_rank = NextFENRank(current_rank);
			current_file = File::a;
			continue;
		}
		if (isnumber(c)) {
			current_file = IntToFile(current_file + CharToInt(c));
			continue;
		}

		PieceKind kind = CharToKind(c);

		// Now add the piece to the board.
		ChessPiece chess_piece;
		chess_piece.file = current_file;
		chess_piece.kind = kind;
		chess_piece.rank = current_rank;

		if (isupper(c)) {
			chess_piece.color = PieceColor::WHITE;
			this->white_pieces.insert(chess_piece);
		} else {
			chess_piece.color = PieceColor::BLACK;
			this->black_pieces.insert(chess_piece);
		}

		if (kind == KING) {
			if (chess_piece.color == BLACK) {
				black_king = &chess_piece;
			} else {
				white_king = &chess_piece;
			}
		}

		this->pieces.push_back(chess_piece);

		// Finally also increment the file
		current_file = IntToFile(current_file + 1);
	}
}

// TODO(pankajm): Refactor InitPieces so that we may be able to initialize
// black_king and white_king using the member initialization list rather
// than assign them in InitPieces. That way we can make those pointers const.
// However, if that does not gain much, delete this TODO instead.
ChessBoard::ChessBoard(const chess::FEN& fen) {
	InitPieces(fen);
}

const std::string FEN::GetTrimmedFen() {
	std::string trimmed_at_start = fen_.substr(6);
	int pos = trimmed_at_start.find(" ", 0);
	std::string trimmed = trimmed_at_start.substr(0, pos);
	return trimmed;

}
}
