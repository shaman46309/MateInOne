/*
 * chess_board.h
 *
 *  Created on: Mar 3, 2015
 *      Author: pankajm
 */

#ifndef CHESS_BOARD_H_
#define CHESS_BOARD_H_

#include "common.h"

#include <iostream>
#include <vector>
#include <set>

namespace chess {

class FEN;

class ChessPiece;

// Represents a chess board state during game play.
//  [FEN "4k3/R7/1R6/8/8/8/8/4K3 w - - 0 1"]
// 4k3 => empty empty empty empty Black-King empty empty empty
// R7  => White-rook empty * 7
// 1R6 => empty White-rook empty * 6
// 8 => empty * 8
// 8 => same as above
// 8 => same as above
// 8 => same as above
// 4K3 => empty * 4 White-King empty*3
// w => white to move
// - => no castling for white or black
// - => en passant case.
// 0 => unknown; TODO(pankajm): Document this.
// 1 => unknown; TODO(pankajm): Document this.
// I don't expect this to be used as a base class.
class ChessBoard {
public:
	explicit ChessBoard(const chess::FEN& fen);

	bool IsMate();
	void PrintPieces() {
		std::cout << "Listing all pieces on the board..." << std::endl;

		for (auto &p : pieces) {
			if (p.color == WHITE) {
				std::cout << "White ";
			} else {
				std::cout << "Black ";
			}

			switch (p.kind) {
			case KING:
				std::cout << "King "; break;
			case PAWN:
				std::cout << "Pawn "; break;
			case BISHOP:
				std::cout << "Bishop "; break;
			case KNIGHT:
				std::cout << "Knight "; break;
			case ROOK:
				std::cout << "Rook "; break;
			case QUEEN:
				std::cout << "Queen "; break;
			case UNKNOWN:
				std::cout << "PROGRAM ERROR!!!";
			}
			std::cout << "at "
					<< FileToChar(p.file) << p.rank << std::endl;
		}
	}

	// Whether king: black or white is in check?
	bool IsKingInCheck(PieceColor color);


private:

	// Internal method for implementing IsKingInCheck.
	bool IsChecked(ChessPiece* king,
			std::set<ChessPiece>::const_iterator opposition);
	void InitPieces(const chess::FEN& fen);
	/*
	 * Its convenient to keep a vector while constructing pieces from
	 * initial FEN configuration. However for decisions like IsKingInCheck
	 * its not optimal.
	 * TODO(pankajm): Choose a data structure which understands piece color
	 * and piece kind better to allow more efficient lookups.
	 */
	std::vector<ChessPiece> pieces;
	std::set<ChessPiece> black_pieces;
	std::set<ChessPiece> white_pieces;

	// Since we refer to the kings so much, explicitly store reference to them
	// TODO(pankajm): This should be const?
	ChessPiece* black_king;
	ChessPiece* white_king;

	// TODO(pankajm): Move out of chess board?
	inline Rank NextFENRank(Rank current) {
		switch(current) {
		case EIGHT: return SEVEN;
		case SEVEN: return SIX;
		case SIX: return FIVE;
		case FIVE: return FOUR;
		case FOUR: return THREE;
		case THREE: return TWO;
		case TWO: return ONE;
		// This entire Rank enum is hacky. I wrote it in a haste.
		default:return OUT_OF_BOUNDS_LOWER;
		}
	}

	// TODO(pankajm): Move out of chess board?
	inline File IntToFile(int file) {
		switch (file) {
		case 1 : return a;
		case 2 : return b;
		case 3 : return c;
		case 4 : return d;
		case 5 : return e;
		case 6 : return f;
		case 7 : return g;
		case 8 : return h;
		default : return left_edge;
		}
	}

	// TODO(pankajm): Move out of chess board?
	inline char FileToChar(File file) {
		switch (file) {
		case a : return 'a';
		case b : return 'b';
		case c : return 'c';
		case d : return 'd';
		case e : return 'e';
		case f : return 'f';
		case g : return 'g';
		case h : return 'h';
		default : return '!';
		}
	}

	// TODO(pankajm): Move out of chess board?
	inline int CharToInt(char c) {
		switch(c) {
		case '1' : return 1;
		case '2' : return 2;
		case '3' : return 3;
		case '4' : return 4;
		case '5' : return 5;
		case '6' : return 6;
		case '7' : return 7;
		case '8' : return 8;
		default: return -1;
		}
	}

	// TODO(pankajm): Move out of chess board?
	inline PieceKind CharToKind(char c) {
		char lower_c = tolower(c);
		switch(lower_c) {
		case 'k' : return PieceKind::KING;
		case 'b' : return PieceKind::BISHOP;
		case 'n' : return PieceKind::KNIGHT;
		case 'p' : return PieceKind::PAWN;
		case 'q' : return PieceKind::QUEEN;
		case 'r' : return PieceKind::ROOK;
		default: {
			std::cerr << "Could not find kind of piece for char [" << c << "]\n";
			return PieceKind::UNKNOWN;
		}
		}
	}
};


/*
 * Interprets FEN strings like
 * [FEN "4k3/R7/1R6/8/8/8/8/4K3 w - - 0 1"]
 */
class FEN {

public:
	FEN(const std::string& fen) : fen_(fen) {
		trimmed_ = GetTrimmedFen();
	}

	// TODO(pankajm): Move back to private section once we have a method to get all pieces from fen.
	// See the nasty chess_board constructor.
	std::string trimmed_;
private:
	const std::string& fen_;
	const std::string GetTrimmedFen();
};
}

#endif /* CHESS_BOARD_H_ */
