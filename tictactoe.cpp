/*===============================================================
CSUF, CPSC254 - SPRING 2022
Contributor: Trong Pham, Adam Harb, Albert Paez
Edit By: Desirae Prather, Zachary Worcster, Taylor Ramsay
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
File Description: Define all game operators declared in tictactoe.h
================================================================*/

#include "tictactoe.h"
// Draw a line with SIDE cell in each row
void Tictactoe::Draw_A_Line() const {
  cout << "\t\t";
  for (int k = 0; k < SIDE * 5 - 1; k++)
    cout << "-";
  cout << endl;
}
// Draw a separator between 2 cell of a row
void Tictactoe::Draw_Separator(const int j) const {
  if (j < SIDE - 1) // not the last cell of row yet
    cout << " | ";

  else if (j == SIDE - 1) // last cell of row now
    cout << endl;
}
// Display current board status
void Tictactoe::Draw_Board() const {
  for (int i = 0; i < SIDE; i++) {
    cout << "\t\t ";
    for (int j = 0; j < SIDE; j++) {
      auto iter = positions.find(make_pair(i, j));
      if (iter != positions.end()){
        cout << iter->second << " ";
        Draw_Separator(j);
      }else {
        cout << board_(i, j) << " ";
        Draw_Separator(j);
      }
    }
    Draw_A_Line();
  }
}
// Display the game's guide
void Tictactoe::Show_Instruction() const {
  cout << endl << "Pick a cell(1-" << SIDE * SIDE << "): " << endl;
  int cell_number = 0;
  for (int i = 0; i < SIDE; i++) {
    cout << "\t\t ";
    for (int j = 0; j < SIDE; j++) {
      cell_number = i * SIDE + j + 1;
      if (cell_number < 10)
        cout << " " << cell_number;
      else // if (cell_number >=10)
        cout << cell_number;
      Draw_Separator(j);
    }
    Draw_A_Line();
  }
}
// Initialize the board
void Tictactoe::Initialize_Board_Value() {
  board_ = ' '; }
// Who is the winner?
void Tictactoe::Define_Winner(const int whose_turn) const {
  if (whose_turn == AI)
    cout << "AI won" << endl;
  else if (whose_turn == PLAYER1)
    cout << "PLAYER 1 won"<< endl;
  else if (whose_turn == PLAYER2)
    cout << "PLAYER 2 won"<< endl;
  else
    cout << "PLAYER won\n" << endl;
}
// Is a player has a row crossed
bool Tictactoe::Is_Cross_Row() const {
  return board_.Exist_Equalized_Row();
}
// Is a player has a column crossed
bool Tictactoe::Is_Cross_Column() const {
  return board_.Exist_Equalized_Column();
}
// Is a player has a diagonal crossed
bool Tictactoe::Is_Cross_Diagonal() const {
  return board_.Exist_Equalized_Diagonal();
}
// Is the game over yet?
bool Tictactoe::Is_Game_Over() const {
  return Is_Cross_Row() || Is_Cross_Column() || Is_Cross_Diagonal();
}
// Support re-assignor functions for comparing 2 numbers
void Tictactoe::Re_Assign_If_Bigger(int &bigger, const int comparee) const {
  bigger = (comparee > bigger) ? comparee : bigger;
}
void Tictactoe::Re_Assign_If_Smaller(int &smaller, const int comparee) const {
  smaller = (comparee < smaller) ? comparee : smaller;
}
// For a specific movement, what is the score for that movement?
int Tictactoe::Mini_Max(const int depth, const bool is_ai, const int max_depth) {
  // Score of the current movement and the best_score for any movement
  int score = 0;
  int best_score = 0;
  //Now let's go through the game loop and begin the fun
  if (Is_Game_Over()) {
    return is_ai ? (-1) : (1);
  }
  // game is NOT over yet!
  else {
    // Come on, let AI do some evaluations here and there...
    if (depth < SIDE * SIDE && depth < max_depth) {
      // This is AI turn
      if (is_ai) {
        //First, assign the best_score for the AIplayer as NEGATIVE INFINITY
        best_score = NEGATIVE_INFINITY;
        //Now try to visit valid movement and try to find the better value for best_score
        for (int i = 0; i < SIDE; i++) {
          for (int j = 0; j < SIDE; j++) {
            // Still valid spot?
            if (board_(i, j) == ' ') {
              board_(i, j) = AI_MOVE; // mark as an AI movement
              score = Mini_Max(depth + 1, false); // then go to evaluate next depth
              board_(i, j) = ' '; // re-assign the value at current spot
              Re_Assign_If_Bigger(best_score, score);
            }
          }
        }
        return best_score;
      }
      else { //oh so here is the player movement
        best_score = POSITIVE_INFINITY;
        for (int i = 0; i < SIDE; i++) {
          for (int j = 0; j < SIDE; j++) {
            if (board_(i, j) == ' ') {
              board_(i, j) = PLAYER_MOVE; // this is player movement
              score = Mini_Max(depth + 1, true); // just redo things like AI
              board_(i, j) = ' ';
              Re_Assign_If_Smaller(best_score, score);
            }
          }
        }
        return best_score;
      }
    }
    else {
      return 0; // neutral value
    }
  }
}
// What is the best movement, based on a specific movement index?
int Tictactoe::Best_Move(const int total_filled_cells, const int max_depth) {
  //First, let's assign the row and column indexes
  //and use it to compute the corresponding array index later
  int row_index = -1;
  int col_index = -1;
  //Let's also assign the score and best_score for AI player
  int score = 0;
  int best_score = NEGATIVE_INFINITY;
  //Now, let's go through the board and check if it is a valid movement for AI
  for (int i = 0; i < SIDE; i++) {
    for (int j = 0; j < SIDE; j++) {
      //cout << "best_move:AI at (" << i << "," << j << ")" << endl;
      if (board_(i, j) == ' ') {
        board_(i, j) = AI_MOVE;
        score = Mini_Max(total_filled_cells + 1, false, max_depth);
        board_(i, j) = ' ';
        if (score > best_score) { // if this movement (i,j) actual a better move then....
          best_score = score; // re-assign best_score...
          col_index = j;      // and mark the point immediately for row
          row_index = i;      // and column
        }
      }
    }
  }
  positions.erase(make_pair(row_index, col_index));
  return row_index * SIDE + col_index;
  // then return the point to the cell position format for use later
}
// Driver to play the game
void Tictactoe::Play(int whose_turn, int amount_players, const DifficultyType difficulty) {
  int total_filled_cells = 0; // total filed cell
  int row_index = 0;          // row position
  int col_index = 0;          // column position
  int max_depth = static_cast<int>(difficulty);		      // difficulty type

  Initialize_Board_Value();
  Show_Instruction();
  if(amount_players == SINGLE_PLAYER ) {
    // Keep playing till the game is over or it is a draw
    while (!Is_Game_Over() && total_filled_cells != SIDE * SIDE) {
      int input_position;
      if (whose_turn == AI) { //hey my turn, i am an AI
        Notify_Movement(Best_Move(total_filled_cells, max_depth), true, SINGLE_PLAYER); //Show the movement
        Next_Turn(whose_turn, total_filled_cells); //And move to next turn
      }
      // else if whose_turn = PLAYER
      else {
        //List out valid movement and ask for player input
        List_Valid_Position();
        cout << endl << "Enter the position = ";
        cin >> input_position;
        input_position--; //convert it to the real array index
        if (Is_Valid_Movement(input_position)) { //what if it is a valid movement?
          positions.erase(positionsKey.find(input_position + 1)->second);
          Notify_Movement(input_position, false, SINGLE_PLAYER); //Show the movement to screen
          Next_Turn(whose_turn, total_filled_cells); //And move to next turn now
        } else
          Is_Filled_Or_Out_Of_Board(input_position); //Make sure to check end game!
      }
    }
    // No one win but running out of spot ?--> A draw...
    Is_A_Draw_Or_Winnable(total_filled_cells, whose_turn);
  }
  else {
  // Keep playing till the game is over or it is a draw
    while (!Is_Game_Over() && total_filled_cells != SIDE * SIDE) {
      int input_position;
      if (whose_turn == PLAYER1) { //player 1 turn
        cout << "PLAYER 1 TURN"<< endl;
        //List out valid movement and ask for player input
        List_Valid_Position();
        cout << endl << "Enter the position = ";
        cin >> input_position;
        input_position--; //convert it to the real array index
        if (Is_Valid_Movement(input_position)) { //what if it is a valid movement?
          positions.erase(positionsKey.find(input_position + 1)->second);
          Notify_Movement(input_position, true, MULTI_PLAYER); //Show the movement to screen
          Next_Turn(whose_turn, total_filled_cells); //And move to next turn now
        } else
          Is_Filled_Or_Out_Of_Board(input_position); //Make sure to check end game!

      }
      // else if whose_turn = PLAYER 2
      else {
        cout << "PLAYER 2 TURN"<< endl;
        //List out valid movement and ask for player input
        List_Valid_Position();
        cout << endl << "Enter the position = ";
        cin >> input_position;
        input_position--; //convert it to the real array index
        if (Is_Valid_Movement(input_position)) { //what if it is a valid movement?
          positions.erase(positionsKey.find(input_position + 1)->second);
          Notify_Movement(input_position, false, MULTI_PLAYER); //Show the movement to screen
          Next_Turn(whose_turn, total_filled_cells); //And move to next turn now
        } else
          Is_Filled_Or_Out_Of_Board(input_position); //Make sure to check end game!
      }
    }
    // No one win but running out of spot ?--> A draw...
    Is_A_Draw_Or_Winnable(total_filled_cells, whose_turn);
  }
}

// Is game a DRAW or who actually won?
void Tictactoe::Is_A_Draw_Or_Winnable(const int total_filled_cells,
    int &whose_turn) {
  if (!Is_Game_Over() && total_filled_cells == SIDE * SIDE) {
    cout << "It's a draw" << endl;
    // Resets position map
    Reset_Position_Map();
  } else { // If there is one winner, who is that?
    // If there is one winner, who is that?
    // Resets position map
    Reset_Position_Map();
    if (whose_turn == AI)
      whose_turn = PLAYER;
    else if (whose_turn == PLAYER)// if whose_turn == PLAYER
      whose_turn = AI;
    else if (whose_turn == PLAYER1)
      whose_turn = PLAYER2;
    else
      whose_turn = PLAYER1;
    //check the winner condition now
    Define_Winner(whose_turn);
  }
}
// List out all current valid position
void Tictactoe::List_Valid_Position() const {
  cout << "Current VALID positions : ";
  for (int i = 0; i < SIDE; i++)
    for (int j = 0; j < SIDE; j++)
      if (board_(i, j) == ' ')
        cout << (i * SIDE + j) + 1 << "; ";
}
// Test if the selected position is filled or not
void Tictactoe::Is_Filled_Or_Out_Of_Board(const int input_position) const {
  if (board_(input_position) != ' ' && input_position < SIDE * SIDE &&
      input_position >= 0)
    cout << endl
         << "It is filled, please choose one from valid positions" << endl;

  if (input_position < 0 || input_position > SIDE * SIDE - 1)
    cout << "Invalid position" << endl;
}
// Move to next player
void Tictactoe::Next_Turn(int &whose_turn, int &total_filled_cells) {
  Draw_Board();
  total_filled_cells++; // total filled cells
  if (whose_turn == AI)
    whose_turn = PLAYER;
  else if (whose_turn == PLAYER)
    whose_turn = AI;
  else if (whose_turn == PLAYER1)
    whose_turn = PLAYER2;
  else
    whose_turn = PLAYER1;
  //whose_turn = (whose_turn == AI ? PLAYER : AI);
}
// Is game a DRAW or who actually won?
bool Tictactoe::Is_Valid_Movement(const int input_position) {
  return board_(input_position) == ' ' && input_position < SIDE * SIDE &&
         input_position >= 0;
}
// Notify the movenent to the screen
void Tictactoe::Notify_Movement(const int input_position, bool is_ai_or_p1, int amount_players) {
  if (amount_players == SINGLE_PLAYER){
    if (!is_ai_or_p1) { //hey this is an player movement
      board_(input_position) = PLAYER_MOVE; // let's set that board element for player sign
      cout << endl << "PLAYER filled spot number " << input_position + 1 << endl;
    } else { //now, this is the AI movement
      board_(input_position) = AI_MOVE; // let's set that board element for AI sign
      cout << endl << "AI filled spot number " << input_position + 1 << endl;
    }
  } else{
    if (!is_ai_or_p1) { //hey this is an player movement
      board_(input_position) = PLAYER2_MOVE; // let's set that board element for player sign
      cout << endl << "PLAYER 2 filled spot number " << input_position + 1 << endl;
    } else { //now, this is the AI movement
      board_(input_position) = PLAYER1_MOVE; // let's set that board element for AI sign
      cout << endl << "PLAYER 1 filled spot number " << input_position + 1 << endl;
    }
  }
}

// For resetting the positions map for new games
void Tictactoe::Reset_Position_Map() {
  positions = { {make_pair(0, 0), '1'}, {make_pair(0, 1), '2'}, {make_pair(0, 2), '3'},
   {make_pair(1, 0), '4'}, {make_pair(1, 1), '5'}, {make_pair(1, 2), '6'},
   {make_pair(2, 0), '7'}, {make_pair(2, 1), '8'}, {make_pair(2, 2), '9'} };
}
// For testing purpose of getting an element value
char Tictactoe::Get_Element(const int row, const int column) const {
  return board_(row, column);
}
char Tictactoe::Get_Element(const int index) const {
  return board_(index);
}
