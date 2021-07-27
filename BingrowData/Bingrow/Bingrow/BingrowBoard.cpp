// Bingrow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "BingrowBoard.h"
#include <iostream>
#include <time.h>
#include <iostream>
#include <vector>
#include "Symbol.h"
using namespace std;

BingrowBoard::BingrowBoard(int n) //creating a constructor for our BingrowBoard Class
{
	//initializing variables to use later in the code
	origsize = n;
	size = n;
	int lowervalue = 0;
	int uppervalue = 0;
	int rightvalue = 0;
	int leftvalue = 0;
	GenerateBoard(origsize);
};

void BingrowBoard::GenerateBoard(int size)
{
	//initialzing a temporary vector for the rows in our board
	vector<BingrowSquare> temporow;

	//initilazing and creating squares on a board
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			// initializing an instance of our Class BingrowSquare
			BingrowSquare temp = BingrowSquare();

			//making our "FREE" spot in our board
			if ((r == (origsize / 2)) && (c == (origsize / 2))) {
				//setting that square to "FREE" using the functions provided in "BingrowSquare.h"
				Symbol Freespace;
				Freespace.setSymbolType(Free);
				temp.setSymbol(Freespace);
				temp.setCovered(true);

			}
			else {
				//generating random numbers for the other spots
				temp.setSymbol(GenerateSymbol(c + 1));
			}
			//filling out our temporary vector
			temporow.push_back(temp);
		}
		//filling out our board with the values we have in "temporow" 
		board.push_back(temporow);
		//clearing our temporary vector to fill out the next column/row 
		temporow.clear();
	}
}

ostream& operator<<(ostream& os, BingrowSquare& sqr) 
//creating an overload operator to be able to print our board
{
	if (sqr.getSymbol().getSymbolType() == Free) {
		if (sqr.getCovered()) {
			os << "X";
		}
		else {
			os << "X";
		}
	}
	else if (sqr.getSymbol().getSymbolType() == Number) {
		os << sqr.getSymbol().getNumber();
	}
	else if (sqr.getSymbol().getSymbolType() == Arrow) {
		if (sqr.getSymbol().getArrowType() == UpperLeft) {
			if (sqr.getCovered()) {
				os << "X";
			}
			else {
				os << "UL";
			}
		}

		else if (sqr.getSymbol().getArrowType() == UpperRight) {
			if (sqr.getCovered()) {
				os << "X";

			}
			else {
				os << "UR";
			}
		}

		else if (sqr.getSymbol().getArrowType() == LowerLeft) {
			if (sqr.getCovered()) {
				os << "X";
			}
			else {
				os << "LL";
			}
		}

		else if (sqr.getSymbol().getArrowType() == LowerRight) {
			if (sqr.getCovered()) {
				os << "X";
			}
			else {
				os << "LR";
			}
		}
	}
	return os;
}

int BingrowBoard::GetSize(void)
{
	//returning the size of the board
	return size;
}

bool BingrowBoard::WinningBoard()
{
	//initialzing the variables that we will use later in this function 
	BingrowSquare temposqr;
	BingrowSquare temposqrSec;
	int sumAcroos = 0;
	int sumDown = 0;
	int sumDiaR = 0;
	int sumDiaL = 0;


	bool boardstrt = false;

	//creating two nested for-loops to iterate through our board/squares
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			//filling our class object with values that are stored in the squares
			temposqr = board[r][c];
			temposqrSec = board[c][r];

			//checking if the square in a given row is alreaady covered
			if (temposqr.getCovered() == true)
			{
				sumAcroos++;
			}
			//checking if the square in a given column is alreaady covered
			if (temposqrSec.getCovered() == true)
			{
				sumDown++;
			}
		}

		//re-initializing our ojects to check the diagonal winning condition 
		temposqr = board[r][r];
		temposqrSec = board[r][(size - 1) - r];

		//checking if the square in a given row is alreaady covered
		if (temposqr.getCovered() == true)
		{
			sumDiaR++;
		}

		//checking if the square in a given column is alreaady covered
		if (temposqrSec.getCovered() == true)
		{
			sumDiaL++;
		}

		//checking if the covered squares met the winning condition 

		if (sumAcroos >= 5 || sumDown >= 5 || sumDiaR >= 5 || sumDiaL >= 5)
		{
			//we set the status of our winning condition as true
			boardstrt = true;
		}

		else
		{
			//we reset our variables counters
			sumDiaR = 0;
			sumDiaL = 0;
			sumAcroos = 0;
			sumDown = 0;
		}
	}
	//we return the status of the board whether the user won or not
	return boardstrt;
}

Symbol BingrowBoard::GenerateSymbol(int col)
{
	//a method provided by the proffesor to generate numbers and symbols to fill our board
	Symbol tempSymbol;
	int randNum = (int)(((float)rand() / RAND_MAX * (3 * origsize * size + 4)));
	if (randNum >= 3 * origsize * size)
	{
		tempSymbol.setSymbolType(Arrow);
		if (randNum == 3 * origsize * size)
		{
			tempSymbol.setArrowType(UpperLeft);
		}
		else if (randNum == 3 * origsize * size + 1)
		{
			tempSymbol.setArrowType(UpperRight);
		}
		else if (randNum == 3 * origsize * size + 2)
		{
			tempSymbol.setArrowType(LowerLeft);
		}
		else
		{
			tempSymbol.setArrowType(LowerRight);
		}
	}
	else
	{
		randNum = (int)(((float)rand() / RAND_MAX * (3 * origsize)));
		tempSymbol.setSymbolType(Number);
		tempSymbol.setNumber(randNum + 1 + (col - 1) * 3 * origsize);
	}
	return tempSymbol;
}

void BingrowBoard::DisplayGame()
// DisplayGame is method used to print the game to the user in a terminal
{
	//iterating through our board and printing its values
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			cout << board[r][c] << "\t";
		}
		cout << "\n";
	}
	cout << "\n";
}

void BingrowBoard::GrowBoard(ArrowType direction)
{
	//initializing a temporary vector which will help us in this method
	vector<BingrowSquare> rowsqr;
	//initializing counter for each direction since we can only extend the board 2 times
	ULC, URC, LLC, LRC = 0;

	if (direction == LowerLeft && LLC < 2)
	{
		++size;
		++LLC;

		//extending an extra column and filling it using the GenerateSymbol function
		for (int c = leftvalue; c < size; c++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol(c));
			rowsqr.push_back(sqr);
		}

		//extending an extra row and filling it using the GenerateSymbol function
		for (int r = 0; r < board.size(); r++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol((leftvalue)));
			board.at(r).insert(board.at(r).begin(), sqr);
		}

		//moving the extra row and column to our board
		board.insert(board.end(), rowsqr);
		--leftvalue;
	}

	if (direction == UpperLeft && ULC < 2)
	{
		//similary we do the same procces for the UpperRight Arrow
		++size;
		++ULC;

		for (int c = leftvalue; c < size; c++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol((c)));
			rowsqr.push_back(sqr);
		}
		
		for (int r = 0; r < board.size(); r++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol((leftvalue)));
			board.at(r).insert(board.at(r).begin(), sqr);
		}

		board.insert(board.begin(), rowsqr);
		--leftvalue;
	}

	if (direction == LowerRight && LRC < 2)
	{
		//similary we do the same procces for the LowerRight Arrow
		++size;
		++LRC;

		for (int c = 0; c < size; c++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol((c+1)));
			rowsqr.push_back(sqr);
		}

		for (int r = 0; r < board.size(); r++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol(board.at(r).size() + 1));
			board.at(r).push_back(sqr);
		}

		board.insert(board.end(), rowsqr);
	}

	if (direction == UpperRight && URC < 2)
	{
		//similary we do the same procces for the UpperRight Arrow
		++size;
		++rightvalue;
		++URC;

		for (int c = 0; c < size; c++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol((c + 1)));
			rowsqr.push_back(sqr);
		}
		for (int r = 0; r < board.size(); r++)
		{
			BingrowSquare sqr = BingrowSquare();
			sqr.setSymbol(GenerateSymbol(board.at(r).size() + 1));
			board.at(r).push_back(sqr);
		}

		board.insert(board.begin(), rowsqr);
	}
	rowsqr.clear();
}

bool BingrowBoard::UpdateBoard(Symbol symbol)
{
	//looping through the board's rows and columns
	for (int r = 0; r < size; r++)
	{
		for (int c = 0; c < size; c++)
		{
			BingrowSquare& temposquare = board[r][c]; 

			//checking if the symbol that is passed in our function matches the symbol that is in our temposquare
			if (temposquare.getSymbol().getSymbolType() == symbol.getSymbolType())
			{
				//checking if the symbol that is passed in our function matches the arrow that is in our temposquare
				if (temposquare.getSymbol().getArrowType() == symbol.getArrowType())
				{
					//we cover that symbol using the .setCovered method
					temposquare.setCovered(true);
					this->GenerateBoard(temposquare.getSymbol().getArrowType());
				}
				
				//if the symbol that is passed in our function match the number that is in our temposquare
				else
				{
					if (temposquare.getSymbol().getNumber() == symbol.getNumber())
					{
						//we cover that number/symbol with an X 
						temposquare.setCovered(true);
					}
				}
			}
		}
	}
	this->DisplayGame();
	return true;
}

void BingrowBoard::SetSquare(int row, int col, BingrowSquare square)
{
	//for Gradescope purposes
}