//============================================================================
// Name        : MateInOne.cpp
// Author      : Shaman
// Version     :
// Copyright   : Eat me
// Description : To find all mate in one solutions for the pgn in inputs dir.
//============================================================================

#include <iostream>
#include <ios>
#include <fstream>
#include <string>
#include <vector>

#include "chess_board.h"

int main(int argc, char** argv) {
	std::cout << "Start of main." << std::endl;
	std::ifstream puzzles(
		"/Users/pankajm/cpp/eclipse/MateInOne/inputs/mate_in_one.pgn");

	if (!puzzles) {
		std::cerr << "Couldn't open the puzzles file. exiting" << std::endl;
		return 1;
	}

	char line[100];
	chess::SinglePuzzle single_puzzle;
	std::vector<chess::SinglePuzzle> puzzles_vector;

	while(puzzles) {
		puzzles.getline(line, 80);
		std::string s(line);

		if (s.find("Event", 0) == 1) {
			// copy event
			single_puzzle.event = s;
		}

		if (s.find("FEN", 0) == 1) {
			// copy fen
			single_puzzle.fen = s;

			// Also add to vector.
			puzzles_vector.push_back(single_puzzle);
		}
	}

	puzzles.close();

	for (auto& v : puzzles_vector) {
		chess::FEN fen(v.fen);
		//std::cout << "Creating board for fen : " << v.fen << std::endl;
		chess::ChessBoard board(fen);
		board.PrintPieces();
	}
	std::cout << "End of main." << std::endl;
	return 0;
}
