/*
 * chessgamefromtheweb.h
 *
 *  Created on: Mar 5, 2015
 *      Author: pankajm
 */

#ifndef CHESSGAMEFROMTHEWEB_H_
#define CHESSGAMEFROMTHEWEB_H_

#include  <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <sstream>
namespace learndalang {
//
//class chessgamefromtheweb {
//public:
//	chessgamefromtheweb();
//	virtual ~chessgamefromtheweb();
//};

/*
 * This is a small and simple chessgame to be played by two human players.
 * Copyright 2011 Emil Kampp <ekampp@gmail.com>
 *
 * TODO: Check for check- and mate situations.
 *
 */


using namespace std;
using std::vector;

// Contains the current board
int board[8][8];

// Contains a list of the pieces that has been taken out
string taken_pieces = "";

// Reference ids for the pieces
const int pawn    = 1;
const int rock    = 2;
const int knight  = 3;
const int bishop  = 4;
const int queen   = 5;
const int king    = 6;

// Current state of the game
int status = 0;

// Current state of the application
int exit_game = 0;

// Current turn
int current_player = 1;

// Number of played rounds in this game
int turn_counter = 1;

/*
 * Resets the board
 *
 * This takes no arguments and resets all the positions of the pieces to a
 * prestine version of the game.
 *
 */
void reset(){
  // Normal board setup
  board[0][0]=rock;
  board[0][1]=knight;
  board[0][2]=bishop;
  board[0][3]=queen;
  board[0][4]=king;
  board[0][5]=bishop;
  board[0][6]=knight;
  board[0][7]=rock;
  board[1][0]=pawn;
  board[1][1]=pawn;
  board[1][2]=pawn;
  board[1][3]=pawn;
  board[1][4]=pawn;
  board[1][5]=pawn;
  board[1][6]=pawn;
  board[1][7]=pawn;
  board[2][0]=0;
  board[2][1]=0;
  board[2][2]=0;
  board[2][3]=0;
  board[2][4]=0;
  board[2][5]=0;
  board[2][6]=0;
  board[2][7]=0;
  board[3][0]=0;
  board[3][1]=0;
  board[3][2]=0;
  board[3][3]=0;
  board[3][4]=0;
  board[3][5]=0;
  board[3][6]=0;
  board[3][7]=0;
  board[4][0]=0;
  board[4][1]=0;
  board[4][2]=0;
  board[4][3]=0;
  board[4][4]=0;
  board[4][5]=0;
  board[4][6]=0;
  board[4][7]=0;
  board[5][0]=0;
  board[5][1]=0;
  board[5][2]=0;
  board[5][3]=0;
  board[5][4]=0;
  board[5][5]=0;
  board[5][6]=0;
  board[5][7]=0;
  board[6][0]=-pawn;
  board[6][1]=-pawn;
  board[6][2]=-pawn;
  board[6][3]=-pawn;
  board[6][4]=-pawn;
  board[6][5]=-pawn;
  board[6][6]=-pawn;
  board[6][7]=-pawn;
  board[7][0]=-rock;
  board[7][1]=-knight;
  board[7][2]=-bishop;
  board[7][3]=-queen;
  board[7][4]=-king;
  board[7][5]=-bishop;
  board[7][6]=-knight;
  board[7][7]=-rock;
  current_player = 1;
  turn_counter = 1;
  status = 0;
  taken_pieces = "";
}

/*
 * Returns the +current_player+ integer for the opposite player
 *
 */
int oppositePlayer(){
  if(current_player == 1) return 2;
  return 1;
}

/*
 * Returns the +current_player+ integer for the current player
 *
 */
string currentPlayerColor(){
  if(current_player == 1) return "White";
  return "Black";
}

/*
 * Returns the color of the +current_player+
 *
 */
string oppositePlayerColor(){
  if(current_player == 1) return "Black";
  return "White";
}

/*
 * Constructs a text-representation of the given +piece+.
 *
 * All whitespaces can be supressed with the +supress_blank+ option.
 *
 */
string displayPiece(int piece=0, int supress_blank=0){
  string str = "";
  if(piece > 0){ // White piece
    if(supress_blank==1){
      switch(piece){
        case rock:    str = "r"; break;
        case knight:  str = "k"; break;
        case bishop:  str = "b"; break;
        case queen:   str = "Q"; break;
        case king:    str = "K"; break;
        case pawn:    str = "p"; break;
      }
    } else {
      switch(piece){
        case rock:    str = " r "; break;
        case knight:  str = " k "; break;
        case bishop:  str = " b "; break;
        case queen:   str = " Q "; break;
        case king:    str = " K "; break;
        case pawn:    str = " p "; break;
      }
    }
  } else {
    if(piece < 0) {
      switch(-piece){
        case rock:    str = "(r)"; break;
        case knight:  str = "(k)"; break;
        case bishop:  str = "(b)"; break;
        case queen:   str = "(Q)"; break;
        case king:    str = "(K)"; break;
        case pawn:    str = "(p)"; break;
      }
    } else {
      if(supress_blank == 1) return "";
      str = "   ";
    }
  }
  return str;
}

/*
 * Generates a human readable list of all the pieces that has been taken
 * during the game.
 *
 */
string takenPiecesList(){
  string list = taken_pieces;
  if(list.length()==0) list = "N/A";
  return list;
}

/*
 * Ouputs a graphical represntation of the +board+ array to the CLI
 *
 */
void displayBoard(){
  cout << "\n\n";
  cout << "    a   b   c   d   e   f   g   h\n";
  cout << "  +-------------------------------+\n";
  for(size_t i = 0; i < 8; ++i){
    switch(i){
      case 0: cout << "1 "; break;
      case 1: cout << "2 "; break;
      case 2: cout << "3 "; break;
      case 3: cout << "4 "; break;
      case 4: cout << "5 "; break;
      case 5: cout << "6 "; break;
      case 6: cout << "7 "; break;
      case 7: cout << "8 "; break;
    }
    cout << "|";
    for(size_t j = 0; j < 8; ++j){
      cout << displayPiece(board[i][j]);
      cout << "|";
      if(j == 7) cout << "\n";
    }
    cout << "  +-------------------------------+\n";
  }
  cout << "Taken pieces: " << takenPiecesList() << "\n";
}

/*
 * Checks if the given move is valid.
 *
 * The check is based on the originating coordinates and the targeted
 * coordinates.
 *
 */
int validMove(int ox, int oy, int dx, int dy){
  int source = board[oy][ox];
  int target = board[dy][dx];
  // cout << "Validating move for " << displayPiece(source) << "@" << ox << "," << oy
  //      << " to " << target << "@" << dx << "," << dy << "\n";
  switch(abs(source)){
    //Pawn
    case 1: case -1:
    if(dx==ox && abs(dy-oy)==1 && target==0) return 1;
    if(abs(dx-ox)==1 && abs(dy-oy)==1 && target!= 0) return 1;
    if(current_player == 1 && oy==1 && abs(oy-dy)==2 && target == 0) return 1;
    if(current_player == 2 && oy==6 && abs(oy-dy)==2 && target == 0) return 1;
    // TODO: Check for en-passant
    break;

    // Rock
    case 2:
    if(dx==ox){ // Moving vertically
      if(dy>oy){ // Downards
        for(size_t row = (unsigned)(oy+1); row < (unsigned)dy; ++row){
          if(board[row][dx] != 0) return 0;
        }
      } else { // Upwards
        for(size_t row = (unsigned)dy; row < (unsigned)(oy-1); ++row){
          if(board[row][dx] != 0) return 0;
        }
      }
      return 1;
    }
    if(dy==oy){ // Moving horizontally
      if(dx>ox){ // Rightwards
        for(size_t column = (unsigned)(ox+1); column < (unsigned)dy; ++column){
          if(board[dy][column] != 0) return 0;
        }
      }
      if(dx<ox){ // Leftwards
        for(size_t column = (unsigned)dx; column < (unsigned)(ox-1); ++column){
          if(board[dy][column] != 0) return 0;
        }
      }
      return 1;
    }
    return 0;
    break;

    // Knight
    case 3:
    if((abs(dy-oy)==2 && abs(dx-ox)==1) || (abs(dx-ox)==2 && abs(dy-oy)==1)){
      return 1;
    }
    return 0;
    break;

    // Bishop
    case 4:
    if(abs(dy-oy) == abs(dx-ox)){ // Moving diagonally
      if(dy>oy){ // South
        int column = min(dx, ox)+1;
        for(size_t row = oy+1; row < (unsigned)dy; ++row){
          if(board[row][column] != 0) return 0;
          column ++;
        }
        return 1;
      }
      if(dy<oy && dx>ox){ // North
        int column = min(dx, ox)+1;
        for(size_t row = oy+1; row < (unsigned)dy; ++row){
          if(board[row][column] != 0) return 0;
          column ++;
        }
        return 1;
      }
    }
    return 0;
    break;

    // Queen
    case 5:
    if(abs(dy-oy) == abs(dx-ox)){ // Moving diagonally
      if(dy>oy){ // South
        int column = min(dx, ox)+1;
        for(size_t row = oy+1; row < (unsigned)dy; ++row){
          if(board[row][column] != 0) return 0;
          column ++;
        }
        return 1;
      }
      if(dy<oy && dx>ox){ // North
        int column = min(dx, ox)+1;
        for(size_t row = oy+1; row < (unsigned)dy; ++row){
          if(board[row][column] != 0) return 0;
          column ++;
        }
        return 1;
      }
    }
    if(dy==oy || dx==ox){ // Moving straight
      if(dx==ox){ // Moving vertically
        if(dy>oy){ // Downards
          for(size_t row = (unsigned)(oy+1); row < (unsigned)dy; ++row){
            if(board[row][dx] != 0) return 0;
          }
        } else { // Upwards
          for(size_t row = (unsigned)dy; row < (unsigned)(oy-1); ++row){
            if(board[row][dx] != 0) return 0;
          }
        }
        return 1;
      }
      if(dy==oy){ // Moving horizontally
        if(dx>ox){ // Rightwards
          for(size_t column = (unsigned)(ox+1); column < (unsigned)dy; ++column){
            if(board[dy][column] != 0) return 0;
          }
        }
        if(dx<ox){ // Leftwards
          for(size_t column = (unsigned)dx; column < (unsigned)(ox-1); ++column){
            if(board[dy][column] != 0) return 0;
          }
        }
        return 1;
      }
    }
    return 0;
    break;

    // King
    case 6:
    if(abs(dy-oy)<=1 && abs(dx-ox)<=1) return 1;
    // TODO: Check for castling
    return 0;
    break;
  }
  return 0;
}

/*
 * Logs the given +piece+ into the +taken_pieces+ list.
 *
 */
void logTakenPiece(int piece){
  string piece_str = displayPiece(piece, 1);
  if(piece_str.length()>0){
    if(taken_pieces.length()>0) taken_pieces=taken_pieces+",";
    taken_pieces=taken_pieces+displayPiece(piece);
  }
}

/*
 * Displays the help message
 *
 * TODO: Move the help message into the help.txt file.
 *
 */
void displayHelp(){
  cout << "\n\n";
  cout << "When asked for a move, please enter a move in the following fasion: from>to. This means, that if you want to move from a1 to a2 then you should write a1>a2.\n";
  cout << "If you get the warning: Illegal move it means that you entered a move that's either impossible with the selected piece or you't trying to take one of your own pieces or you'r trying to move out of the board.\n";
  cout << "Typing reset will reset the game back to starting position. Typing display will redraw the board. Typing exit or quit will exit the game.\n";
}

/*
 * Gets a letter (a..h) from a number (1..8)
 *
 */
string getLetter(int column){
  switch(column){
    case 0: return "a"; break;
    case 1: return "b"; break;
    case 2: return "c"; break;
    case 3: return "d"; break;
    case 4: return "e"; break;
    case 5: return "f"; break;
    case 6: return "g"; break;
  }
  return "n/a";
}

/*
 * Converts a given letter (a..h) into a corresponding number (1..8)
 *
 */
int getNumber(string letter){
  if(letter == "a") return 0;
  if(letter == "b") return 1;
  if(letter == "c") return 2;
  if(letter == "d") return 3;
  if(letter == "e") return 4;
  if(letter == "f") return 5;
  if(letter == "g") return 6;
  if(letter == "h") return 7;
  return 0;
}

/*
 * Catches the users inputted move
 *
 * This also does some validation of the move..
 * DISCUSS: Should all validation be moved somewhere else?
 *
 */
int getMove(){
  cout << "Turn " << turn_counter << ". " << currentPlayerColor() <<", select a move:";
  string move = "";
  cin >> move;

  // Checks if the move is a command
  if(move == "help"){ // Display help
    displayHelp();
    displayBoard();
    return 0;
  }
  if(move == "reset"){ // Reset the game
    reset(); displayBoard(); return 0;
  }
  if(move == "display"){ // Displays the board
    displayBoard(); return 0;
  }
  if(move == "exit" || move == "quit") exit(1);

  // Splits the move into orgination and destrination and those
  // into x and y parts
  // TODO: Add validation of the y-coordinate of both the
  //       destination and the origination.
  int ox = 0; int oy = 0; int dx = 0; int dy = 0;
  string ox_part = move.substr(0, move.find(">")).substr(0, 1);
  string oy_part = move.substr(0, move.find(">")).substr(1, 1);
  string dx_part = move.substr(move.find(">")+1, move.length()).substr(0, 1);
  string dy_part = move.substr(move.find(">")+1, move.length()).substr(1, 1);
  ox = getNumber(ox_part);
  oy = atoi(oy_part.c_str())-1;
  dx = getNumber(dx_part);
  dy = atoi(dy_part.c_str())-1;

  // Gets the piece in question and moves it
  int source = board[oy][ox];
  int target = board[dy][dx];
  if((current_player == 1 && (source <= 0 || target > 0)) || (current_player == 2 && (source >= 0 || target < 0)) || !validMove(ox, oy, dx, dy)){
    cout << "Illegal move\n"; return 0;
  }

  // Moves the piece
  board[oy][ox] = 0;
  board[dy][dx] = source;
  logTakenPiece(target);

  // Checks for win condition
  // Changes the +status+ for the game to the +current_player+
  if(abs(target) == king){
    status = current_player;
    return 0;
  }

  // Increments the +turn_counter+
  turn_counter ++;

  // Changes the turn
  current_player = oppositePlayer();

  // Redraws the board
  displayBoard();

  return 0;
}

/*
 * Displays the about.txt file content
 *
 * TODO: Add the about.txt file
 *
 */
void displayGameInformation(){
  cout << "This is a game os chess to be played between to humans. To get help with movements and such, type 'help'.\n";
}

/*
 * Initializes the program and contains the main loop that keeps the game
 * alive.
 *
 */
int main(){
  displayGameInformation();
  reset();
  displayBoard();

  while(exit_game == 0){
    while(status == 0){
      getMove();
    }

    // Displays win condition
    cout << currentPlayerColor() << " wins! Start a new game? [y/n]:";
    string new_game = "y";
    cin >> new_game;
    if(new_game == "y"){
      reset();
      displayBoard();
    } else {
      exit_game = 1;
    }
  }

  cout << "Thank you for playing.\n";
  return 0;
}

} /* namespace learndalang */

#endif /* CHESSGAMEFROMTHEWEB_H_ */
