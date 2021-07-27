#if !defined(BINGROWBOARD_H)
#define BINGROWBOARD_H

#include "BingrowSquare.h"
#include <algorithm>
#include <vector>
//#include "Symbol.h"

using namespace std;

class BingrowBoard
{

private:
	vector<vector<BingrowSquare>> board; //use the STL vector container
	int origsize;
	int size;
	int lowervalue;
	int uppervalue;
	int rightvalue;
	int leftvalue;
	int ULC, URC, LLC, LRC;
public:
	BingrowBoard(int n);  // Constructor for board with side length n
	void GrowBoard(ArrowType direction); // Grow board in the specified direction
	bool UpdateBoard(Symbol symbol); // Cover all occurences of symbol on board 
			 //	    // and possibly grow the board if symbol is arrow
	bool WinningBoard(void); // True if winning condition is satisfied, false otherwise
	int GetSize(void); // Returns the side length of the board

	 //// After being called, the square corresponding to the row'th row and col'th column
	 //// will be set to square.  This is only to be used for testing purposes.
	void SetSquare(int row, int col, BingrowSquare square); 

	//void move(int);
	void GenerateBoard(int size);
	Symbol GenerateSymbol(int col);
	void DisplayGame();
};
#endif