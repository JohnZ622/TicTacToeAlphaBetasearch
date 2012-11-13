/*
 * TicTacToeControl.h
 *
 *  Created on: May 17, 2012
 *      Author: shuheng
 */

#ifndef TICTACTOECONTROL_H_
#define TICTACTOECONTROL_H_
#define BOARD_SIZE 4  // board size
#define TOTAL_SIZE BOARD_SIZE*BOARD_SIZE

#include <gtkmm.h>
#include <map>
#include <array>


class TicTacToeControl : public Gtk::Table
{
  public:
		TicTacToeControl();
		virtual ~TicTacToeControl();
		void reset();
		sigc::signal<void, int> signal_game_ended(); // returns in the private signal m_signal_game_ended
		int getGameEnded(); // retrieves the state



  private:
		typedef std::array<int, TOTAL_SIZE> keyType;


		sigc::signal<void, int> m_signal_game_ended; // Signal for ending of the game
		std::string printKey(keyType);


		Gtk::Button buttons[BOARD_SIZE][BOARD_SIZE]; // All the GTK buttons

		// Game board state representation
		// The coordinates of the cells/buttons are represented as (x,y) where x and y are integers between 0 and Board_Size-1
		// The index is a one-dimensional index that starts at 0 and ends with BoardSize^2-1
		int gameEnded;	// 1 meant player 'X' won, -1 meant player 'O' won, '0' mean a tie, and -2 meant has not ended
		keyType currentState; // Represents the current state of the board, 0 means a cell is empty, 1 means it is occupied by player 'X' while -1 means it is occupied by player 'O'
		int valueAt(int, int, const keyType); // Returns the value of current state at a particular coordinate
		bool markCoord(int, int, keyType& state, int); // Mark a coordinate
		std::array<int, 2> IndexToCoord(int);
		int CoordToIndex(int, int);

		// Game AI data and functions
		int checkGameEnding(keyType); // Check to see if the current game ended
			// 1 meant player 'X' won, -1 meant player 'O' won, '0' mean a tie, and -2 meant no ending
		keyType flipState(keyType&);
		std::pair<int, int> calculateValue(keyType& state); // Retrieves, and if necessary calculates the value of a certain state

		struct classcomp{
							bool operator() (const keyType&, const keyType&) const;
						}; // classcomp used for boardStatesValues
		std::map<keyType, std::pair<int, int>, classcomp> boardStatesValues; // Stores the state-value function, the value is the best possible outcome starting with that state assuming next player marks "1" and also the best possible move

		// Signal handlers
		void onUpdate();
		void onClick(int, int); // on click, i, j are the row and columns of the button
};


#endif /* TICTACTOECONTROL_H_ */
