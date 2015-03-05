//============================================================================
// Name        : mate_debug.cpp
// Author      : Shaman
// Version     :
// Copyright   : Eat me
// Description : Stand alone main to debug issues. Does not read pgn.
//============================================================================

#include <iostream>
#include <string>
#include <vector>

#include "chess_board.h"

int main(int argc, char** argv) {
	std::cout << "Start of debug main." << std::endl;
	chess::FEN fen("[FEN \"1R6/8/8/k6K/8/8/8/7R w - - 0 1\"]");
	chess::ChessBoard board(fen);
	board.PrintPieces();
	std::cout << "Is mate : " << board.IsMate() << std::endl;
	std::cout << "Is black king in check " << board.IsKingInCheck(chess::BLACK);
	std::cout << "End of main." << std::endl;
	return 0;
}
