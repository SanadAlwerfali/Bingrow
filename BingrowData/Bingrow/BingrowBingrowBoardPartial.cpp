
#include "BingrowBoardPartial.h"
#include <iostream>
#include <time.h>

#include <iostream>
#include <vector>
using namespace std;

BingrowBoard::BingrowBoard()
{
    vector<vector<unsigned int> > board; //use the STL vector container

    vector <int> possValues;
    int start = 0;
    for (int i = 0; i < 5; i++)
    {
        board.push_back(vector<unsigned int>(5, 0));
        //  possValues.push_back(i);
    }
    // srand(time(NULL));

    for (int c = 0; c < board[0].size(); c++)
    {
        //  srand(time(NULL));

        fillVector(possValues, start);

        for (int r = 0; r < board.size(); r++)
        {

            unsigned int pos = rand() % (possValues.size() - 1);

            board[r][c] = possValues.at(pos);
            possValues.erase(possValues.begin() + pos);
        }
        start += 15;

    }
    for (int i = 0; i < board[0].size(); i++)
    {


        std::cout << "\n";
        for (int j = 0; j < board.size(); j++)
        {


            std::cout << board[i][j];
            std::cout << "\t ";
        }
    }


};

void fillVector(vector <int>& possValues, int& start)
{
    possValues.clear();
    for (int i = start; i < start + 15; i++)
    {
        possValues.push_back(i);
    }

}
