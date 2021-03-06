/*===============================================================
CSUF, CPSC254 - SPRING 2022
Contributor: Trong Pham, Adam Harb, Albert Paez
Edit By: Desirae Prather, Zachary Worcester, Taylor Ramsay
Project Title: Tictactoe Game
Project Description: Standalone game allows user to beat AI.
  The winner is defined that has a cross
  of row, column, or diagonal. This game
  is designed with a smart AI to challenge
  players like you!
  This project includes main files of matrix
  operators, tictactoe game driver, and main
  file to call driver and load the game.
License: Included but not limited of MIT, Harvard, CSUF, Github
File Name: tictactoe.h
File Description: Declare all game operators
================================================================*/
#pragma once
#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

#include "const.h"
#include "matrix.h"
#include <map>
using namespace std;

enum DifficultyType {
	DUNCE = 1,
	EASY = 3,
	NORMAL = 5,
	HARD  = 7,
	IMPOSSIBLE = POSITIVE_INFINITY
};

class Tictactoe
{
  private:
    Matrix<char> board_;
		
		map<pair<int, int>, char> positions = { {make_pair(0, 0), '1'}, {make_pair(0, 1), '2'}, {make_pair(0, 2), '3'},
	   																				{make_pair(1, 0), '4'}, {make_pair(1, 1), '5'}, {make_pair(1, 2), '6'},
	   																				{make_pair(2, 0), '7'}, {make_pair(2, 1), '8'}, {make_pair(2, 2), '9'} };
		map<int, pair<int, int>> positionsKey = { {1, make_pair(0, 0)}, {2, make_pair(0, 1)}, {3, make_pair(0, 2)},
		 																					{4, make_pair(1, 0)}, {5, make_pair(1, 1)}, {6, make_pair(1, 2)},
																							{7, make_pair(2, 0)}, {8, make_pair(2, 1)}, {9, make_pair(2, 2)} };

  public:
    // Display current board status
    void Draw_Board() const;
    // Display the game's guide
    void Show_Instruction() const;
    // Initialize the board
    void Initialize_Board_Value();
    // Who is the winner?
    void Define_Winner(const int whose_turn) const;
    // Is a player has a row crossed
    bool Is_Cross_Row() const;
    // Is a player has a column crossed
    bool Is_Cross_Column() const;
    // Is a player has a diagonal crossed
    bool Is_Cross_Diagonal() const;
    // Is the game over yet?
    bool Is_Game_Over() const;
    // Support re-assignor functions for comparing 2 numbers
    void Re_Assign_If_Bigger(int &bigger, const int comparee) const;
    void Re_Assign_If_Smaller(int &smaller, const int comparee) const;
    // For a specific movement, what is the score for that movement?
    int Mini_Max(const int depth, const bool is_ai, const int max_depth = POSITIVE_INFINITY);
    // What is the best movement
    int Best_Move(const int total_filled_cells, const int max_depth = POSITIVE_INFINITY);
    // Driver to play the game: human vs AI or human vs human
    void Play(int whose_turn, int amount_players, const DifficultyType difficulty = DifficultyType::NORMAL);
    // Draw a line with SIDE cell in each row
    void Draw_A_Line() const;
    // Draw a separator between 2 cell of a row
    void Draw_Separator(const int j) const;
    // Is game a DRAW or who actually won?
    void Is_A_Draw_Or_Winnable(const int total_filled_cells,
    int &whose_turn);
    // List out all current valid position
    void List_Valid_Position() const;
    // If the selected position is a valid movement
    bool Is_Valid_Movement(const int input_position);
    // Test if the selected position is filled or out out board
    void Is_Filled_Or_Out_Of_Board(const int input_position) const;
    // Move to next turn: redraw the board also
    void Next_Turn(int &whose_turn, int &total_filled_cells);
    // Notify the movenent to the screen
    void Notify_Movement(const int input_position, bool is_ai_or_p1, int amount_players);
    // Fot testing purpose of getting an element value
    char Get_Element(const int row, const int column) const;
    char Get_Element(const int index) const;
		// For resetting the positions map for new games
		void Reset_Position_Map();
  };

  #endif
