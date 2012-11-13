/*
 * TicTacToeControl.cpp
 *
 *  Created on: May 17, 2012
 *      Author: shuheng
 */
#include "TicTacToeControl.h"
#include <iostream>
#include <string>

sigc::signal<void, int> TicTacToeControl::signal_game_ended() {
	return m_signal_game_ended;
}

int TicTacToeControl::getGameEnded(){
	return gameEnded;
}
bool TicTacToeControl::classcomp::operator() (const keyType& lhs, const keyType& rhs) const
{
	for (int i=0; i<TOTAL_SIZE; i++)
	{
		if (lhs[i] < rhs[i])
			return true;
		else if (lhs[i] > rhs[i])
			return false;
	}
	return false; // The case where every digit is equal
}

bool TicTacToeControl::markCoord(int i, int j, keyType& state, int target){
	int Index = CoordToIndex(i,j);
	if (state[Index] != 0)
		return false;
	else
	{
		state[Index] = target;
		return true;
	}
}

inline int TicTacToeControl::valueAt(int i, int j, const keyType state){
	return state[CoordToIndex(i,j)];
}


// Returns 1 for 'X' player winning, -1 for 'O' player winning, 0 for tie, -2 for no conclusion
int TicTacToeControl::checkGameEnding(keyType state){
	int countX;
	int countO;
	bool anyempty=false;
	int index;

	// check horizontal winnings (all marks in the same row)
	for (int i=0; i < BOARD_SIZE; i++)
	{
		countX=0;
		countO=0;
		for (int j=0; j < BOARD_SIZE; j++)
		{
			index = CoordToIndex(i,j);
			switch (state[index])
			{
				case 1 :
					countX++;
					break;
				case -1 :
					countO++;
					break;
				case 0 :
					anyempty=true;
			}
		}
		if (countX==BOARD_SIZE)
			return 1;
		else if (countO == BOARD_SIZE)
			return -1;
	}

	// check for vertical wins
	for (int j=0; j < BOARD_SIZE; j++)
	{
		countX=0;
		countO=0;
		for (int i=0; i < BOARD_SIZE; i++)
		{
			index = CoordToIndex(i,j);
			switch (state[index])
			{
				case 1 :
					countX++;
					break;
				case -1 :
					countO++;
					break;
				case 0 :
					anyempty=true;
			}
		}
		if (countX==BOARD_SIZE)
			return 1;
		else if (countO == BOARD_SIZE)
			return -1;
	}

	// check for diagonal win
	countX=0;
	countO=0;
	int countX2 =0;
	int countO2 = 0;
	for (int i=0; i<BOARD_SIZE; i++)
	{
		index = CoordToIndex(i,i);
		switch (state[index])
		{
			case 1 :
				countX++;
				break;
			case -1 :
				countO++;
				break;
			case 0 :
				anyempty=true;
		}
		index = CoordToIndex(i,BOARD_SIZE-i-1);
		switch (state[index])
		{
			case 1 :
				countX2++;
				break;
			case -1 :
				countO2++;
				break;
			case 0 :
				anyempty=true;
		}
	}

	if (countX==BOARD_SIZE || countX2==BOARD_SIZE)
		return 1;
	else if (countO == BOARD_SIZE || countO2==BOARD_SIZE)
		return -1;

	if (anyempty==false)
		return 0;  // for a tie game
	else
		return -2;

}

TicTacToeControl::keyType TicTacToeControl::flipState(keyType& state){
	keyType result;
	for (int i=0; i < TOTAL_SIZE; i++)
	{
		result[i] = state[i]*(-1);
	}
	return result;
}

std::pair<int, int> TicTacToeControl::calculateValue(keyType& state)
{
		g_message("boardStatesValues size: %d \n", boardStatesValues.size());
		if (boardStatesValues.count(state)==0) // If the state's value has not be calculated yet
		{
			int gameEnded = checkGameEnding(state);
			if (gameEnded != -2) // Means the game has ended
			{
				std::pair<int,int> result(gameEnded, -1);
				boardStatesValues[state] = result;
				return result;
			}

			// Otherwise, actually calculate the value
			// Look at all possible states that the opponent can take and take the best one (one that maximizes value)

			// Search for all possible moves for the opponent
			int bestValue = 2;  // The value of the best possible next move, so far, set it to a large number by default
			int bestCoord = -1; // Best possible move so far, no move available by default
			int tempValue = 2 ;
			keyType tempState = flipState(state);
			for (int i=0; i < TOTAL_SIZE; i++)
			{
					if (state[i] == 0) // cell empty, possible to make a move
					{
						tempState[i] = -1;  // Make the cell by the opponent in a temp state
						tempValue = calculateValue(tempState).first; // Retrieve value
						tempState[i] = 0; // Reset State
						if (tempValue < bestValue) // We are minimizing because we are facing an opponent
						{
							bestValue = tempValue;
							bestCoord = i;
							if (tempValue == -1) // This is the global minimum, no need to continue the search
								break;
						}
					}
			}
			std::pair<int,int> result((-1)*bestValue, bestCoord); // flip the sign because we flipped the states
			boardStatesValues[state] = result;
			return result;
		}
		else // The state's value has been calculated before, just return it.
			return boardStatesValues[state]; // returns the value
}

void TicTacToeControl::onClick(int i, int j){
	if (valueAt(i,j, currentState) == 0 && gameEnded == -2) // We need the cell to be empty and game to have not finished
	{
		buttons[i][j].set_label("X");
		markCoord(i,j, currentState, 1);
		g_message("%d, %d marked, current state %d", i, j, currentState);

		// Let the AI decide the next move
		keyType flippedState = flipState(currentState);
		std::pair<int,int> result = calculateValue(flippedState);
		int nextMove = result.second;
		if (nextMove != -1) // If game is not over yet, recommend move
		{
			std::array<int,2> nextMoveCoord = IndexToCoord(nextMove);
			buttons[nextMoveCoord[0]][nextMoveCoord[1]].set_label("O");
			markCoord(nextMoveCoord[0],nextMoveCoord[1], currentState, -1);
			if (calculateValue(currentState).second == -1) // If the game has ended
			{
				gameEnded = calculateValue(currentState).first;
				signal_game_ended().emit(gameEnded);  // Emit game ended signal
				g_message("game Ended");
			}
		}
		else // Game has ended, signal ending
		{
			signal_game_ended().emit(result.first); // Emit the game ending signal
			g_message("game Ended");
		}

	}
	else
		g_message("%d, %d NOT marked", i, j);

}

std::array<int, 2> TicTacToeControl::IndexToCoord(int index){
	std::array<int, 2> result;
	result[0] = index/BOARD_SIZE;
	result[1] = index % BOARD_SIZE;
	return result;
}

inline int TicTacToeControl::CoordToIndex(int i, int j){
	return BOARD_SIZE*i + j;

}

void TicTacToeControl::reset(){
	keyType emptyKey;
	for (int i=0; i<TOTAL_SIZE; i++)
		emptyKey[i]=0; // initialize all to 0
	currentState = emptyKey;
	for (int i=0; i<BOARD_SIZE; i++)
		for (int j=0; j<BOARD_SIZE; j++)
			buttons[i][j].set_label("");
	gameEnded = -2;
	signal_game_ended().emit(gameEnded); // Update the game status box
}

TicTacToeControl::TicTacToeControl()
: Table(BOARD_SIZE, BOARD_SIZE, true)
 {
	// Reset the board and game states
	reset();

	// Attach all the buttons and add the signal handler
	for (int i=0; i<BOARD_SIZE; i++)
		for (int j=0; j<BOARD_SIZE; j++)
		{
			attach(buttons[i][j], j, j+1, i, i+1);
			buttons[i][j].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &TicTacToeControl::onClick), i, j));
		}
}


TicTacToeControl::~TicTacToeControl(){

}

std::string TicTacToeControl::printKey(keyType input){
	std::string result;
	std::array<int, TOTAL_SIZE>::iterator it;
	for (it = input.begin(); it!= input.end(); it++)
	{
		switch (*it)
		{
			case 0:
				result += "0";
				break;
			case 1:
				result += "1";
				break;
			case -1:
				result += "-1";
		}


	}
	return result;

}
