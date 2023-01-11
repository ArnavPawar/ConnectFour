
#define __Board_h_
#include <iostream>
#include <string>
#include <cassert>



class Board{
public:
	
	Board();//empty constructor will print board
    ~Board(); //deconstructer
    Board(const Board& b);//copy construct
	Board(std::string player1, std::string player2, std::string emp);//this will create the initial values//construct

    friend std::ostream& operator<<(std::ostream& out, Board &b);//freind func to print

	int numRows()const{return colSize ;} ;//getters
	int numColumns()const{return rowSize ;};

	int numTokensInRow(int row);//returns num in row and col
	int numTokensInColumn(int col);

	std::string insert(int col, bool play);//insert func to put in token in board
	void clear();//clears the board to stock chart

	bool winLoss(int row,int col);//checks if win/loss game

private:

	std::string p1,p2,empty;
	int rowSize;//number of rows
	int colSize;//number of cols

    std::string **initPoin[1];//m_data stores all content of board

    int *sizeP[1];//stores sizes of all cols


};