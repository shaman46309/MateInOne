/*
 * common.h
 *
 *  Created on: Mar 3, 2015
 *      Author: pankajm
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <string>

namespace chess {

/*
SinglePuzzle structure to map to a text input like the following snippet:
<snippet>
[Event "move a rook"]
[Site "?"]
[Date "????.??.??"]
[Round "?"]
[White "White to Move and Mate in One"]
[Black "?"]
[Result "1-0"]
[SetUp "1"]
[FEN "4k3/R7/1R6/8/8/8/8/4K3 w - - 0 1"]
[PlyCount "1"]
[EventDate "2005.12.20"]
</snippet>
We only retain event, fen for now.
 */
struct SinglePuzzle {
	std::string event;
	std::string fen;
};

enum PieceKind {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING, UNKNOWN};
enum PieceColor {BLACK, WHITE};

// TODO(pankajm): Can we remove the bounds?
enum Rank {OUT_OF_BOUNDS_LOWER, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, OUT_OF_BOUNDS_UPPER};

// TODO(pankajm): Can we remove the edges?
enum File {left_edge = 0, a, b, c, d, e, f, g, h, right_edge};

// Denotes a piece on the board.
// This was originally a struct but while inserting into a set
// I ran into
// invalid operands to binary expression ('const chess::ChessPiece' and 'const chess::ChessPiece')
//        {return __x < __y;}

class ChessPiece {
	// Horribly breaks encapsulation for now
	// TODO(pankajm): Fix this. Make kind, color const.
public:
	PieceKind kind;
	PieceColor color;
	Rank rank;
	File file;



	// The operator should take into account color, kind and position.
	bool operator< (const ChessPiece& c) const {
	    return (this->hash() < c.hash());
	}

	// We want to efficiently refer to the location of pieces
	// Traditional locations are like "a1", "d5". Since these strings are costly
	// We compute location = (10 * rank) + file
	// Hence a1 corresponds to 10 * 1 + 0 = 10
	// d5 => 10 * 5 + 3 = 53
	// g7 = 10 * 7 + ('g' - 'a') = 76 and so on.
	// This encoding may not be optimal but will do for now.
	// TODO(pankajm): Run load tests after mate_in_one is complete and play with
	// the encoding here.
	int location() {
		return 10 * rank + file;
	}

private:
	// Color = binary. Lets assign multiplier = +1 or -1 for white or black
	// kind = 0 to 6
	// rank = 1 to 8
	// file = 0 to 7
	// lets compute hash = (kind * 100 + rank * 10 + file ) * multiplier
	inline int hash() const {
		int multiplier = (color == WHITE ? 1 : -1);
		return multiplier * (100 * kind + rank * 10 + file);
	}

};

}

#endif /* COMMON_H_ */
