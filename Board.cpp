#include "Board.h"
#include <iostream>
#include <string>
#include <cassert>




Board::~Board(void) {
    //Loop through initPoin,,, if null skip,, if not null delete,,
    for(int j=0; j< rowSize ; j++){
        if(sizeP[0][j]!=0){
            delete [] initPoin[0][j];
        }
    }
    delete [] initPoin[0];

    delete [] sizeP[0];
}

Board::Board(const Board& b){//copy constructer just sets everthing to the objects vals
    std::cout<<b.rowSize;
    rowSize=b.rowSize;
    colSize=b.colSize;
    p1=b.p1;
    p2=b.p2;
    empty=b.empty;
    sizeP[0]= b.sizeP[0];

    initPoin[0]=new std::string*[b.rowSize];

    initPoin[0]= b.initPoin[0];
}

Board::Board(std::string player1, std::string player2, std::string emp){//default const sets all vals
	rowSize=4;//size of the default row and will be printed up to this number horizontally
	colSize=5;//size of the default col and will be printed up to this number vertically
	p1=player1;
	p2=player2;
    empty=emp;

    initPoin[0]=new std::string *[rowSize];//

    sizeP[0]=new int[4];//creates an array of ints in heap adn sets all to 0

    sizeP[0][0]=0;
    sizeP[0][1]=0;
    sizeP[0][2]=0;
    sizeP[0][3]=0;

    for(int EachCol=0; EachCol<rowSize; EachCol++){//sets all to NULL
        initPoin[0][EachCol]=NULL;
    }
}

std::ostream& operator<<(std::ostream& out,Board &b){//will print the board using friend func
    int curRow=b.colSize-1;
    while (curRow!=-1) {
        std::string space=" ";//prints out the ammount of spaces based on where in board
        for (int i = 0; i < b.rowSize; i++) { //runs thru the array of pointers
            if(b.rowSize-1 ==i){
                space="";
            }
            if(b.sizeP[0][i]!=0){ //if the pointer points to something it will print the content of that spot in board

                if (b.sizeP[0][i] >= curRow+1) {
                    out << b.initPoin[0][i][curRow]<< space;
                }
                else {
                    out << b.empty<<space;
                }
            }
            else{
                out<<b.empty<<space;
            }
        }
        out<<std::endl;
        curRow--;
    }
    return out<<"";
}

int Board::numTokensInRow(int row){
    int totTokR=0;
    if (colSize<row+1){
        return -1;
    }

    for(int whatCol=0; whatCol<rowSize;whatCol++){//goes thru the array of pointers and finds how many are in the given row
        if(sizeP[0][whatCol] != 0 and sizeP[0][whatCol] -1 >= row){//if the row exists in that col
                totTokR+=1;
        }
    }
    return totTokR;
}

int Board::numTokensInColumn(int col){//returns the ammount of tokens in the col
	int totTokC=0;
    if (rowSize<col+1){
        return -1;
    }
    if(rowSize-1 >= col){
        totTokC+= sizeP[0][col];
    }
    return totTokC;
}

std::string Board:: insert(int col, bool play){
    if(rowSize-1 >= col){//if col exists then do this

       // if the array points to null then create a new array in heap
        if(sizeP[0][col]==0){
            initPoin[0][col]=new std::string [1];
            sizeP[0][col]+=1;
            if(play){
                initPoin[0][col][0]= p1;
            }
            else{
                initPoin[0][col][0]= p2;
            }
        }
        else{ // if array points to an array then add one and replace the array


            std::string *newArr[1];
            newArr[0]=new std::string[(sizeP[0][col])+1];

             for(int i=0; i< sizeP[0][col] ;i++){//coping the col over to temp array
                 newArr[0][i]=initPoin[0][col][i];
             }
             sizeP[0][col]+=1;

             //add the new element to the col
             if(play){
                 newArr[0][sizeP[0][col]-1] = p1;
             }
             else{
                 newArr[0][sizeP[0][col]-1]=p2;
             }

             // removes the old array and points to the new array
             delete [] initPoin[0][col];
             initPoin[0][col]= newArr[0];

             //resizes the print variables for when to print out its all allgined
             if (sizeP[0][col] > colSize){
                 colSize=sizeP[0][col];
             }
             //add a new element to the vertical array KINDA DONE
        }
    }

    else {//now if they want to add a new col
        std::string **newCol[1];
        newCol[0] = new std::string *[col +1];//makes new array the size of the overall size of the row- what col they want

        int *sizePTem[1];
        sizePTem[0] = new int[col + 1];

        for(int colN=0; colN < col+1 ; colN++){
            sizePTem[0][colN]=0;
        }

        for (int tcol = 0; tcol < rowSize; tcol++) {
            sizePTem[0][tcol] = sizeP[0][tcol];
        }

        sizePTem[0][col] = 1;
        delete[] sizeP[0];
        sizeP[0] = sizePTem[0];

        for (int coll = 0; coll < rowSize; coll++) {

            if(sizeP[0][coll] != 0){

                newCol[0][coll] = new std::string[sizeP[0][coll]];

                for (int valInCol = 0; valInCol < sizeP[0][coll]; valInCol++) {

                    newCol[0][coll][valInCol] = initPoin[0][coll][valInCol];
                }
                //copy all contents to the new array pointer you made
            }
        }

        //after coping content add the new token to the last col
        if (play) {
            newCol[0][col] = new std::string[1];
            newCol[0][col][0] = p1;
        } else {
            newCol[0][col] = new std::string[1];
            newCol[0][col][0] = p2;
        }



        for(int j=0; j< rowSize ; j++){
            if(sizeP[0][j] != 0){
                delete [] initPoin[0][j];
            }
        }
        delete [] initPoin[0];

        rowSize=col+1;



        //now transfer everthing to newCol
        initPoin[0]=newCol[0];
        //add new element to the bottem array and transfer everything over to the new one
    }


    if(winLoss((sizeP[0][col]-1),(col)) == true){//checks if CONNECT FOUR
        return initPoin[0][col][sizeP[0][col]-1];
    }
    else{
        return empty;
    }

}

void Board::clear(){
    rowSize=4;//size of the default row and will be printed up to this number horizontally
    colSize=6;
    for(int j=0; j< rowSize ; j++){
        if(initPoin[0][j] != NULL){
            delete [] initPoin[0][j];
        }
    }
}

bool Board::winLoss(int row, int col){//row is vertically where it is,,,col is where it is in array pointer

    if(sizeP[0][col]>=4){//check Vertically
        int coldown=row;
        int count=0;
        std::string tok=initPoin[0][col][row];
        for(int i=sizeP[0][col]; i>=0; i--){//will just go down and if the count gets to 4 then WINNER

            if(initPoin[0][col][coldown] == tok){
                count ++;
                coldown--;
                if(count==4){
                    return true;
                }
            }
            else{
                break;
            }
        }
    }

    //checking horizontally
    int count=0;
    int topRow=colSize-1;
    std::string whatTok="";

    while(topRow!=-1){//starts from top
        for(int whatCol=0; whatCol<rowSize; whatCol++){//goes through cols
            if(sizeP[0][whatCol]-1  >= topRow){
                if(whatTok ==initPoin[0][whatCol][topRow]) { //if same token then count adds
                    count++;
                }
                else{
                    whatTok=initPoin[0][whatCol][topRow];//if not same token then reset and start at 1
                    count=1;
                }
            }
            else{
                count=0;//if not exist then skip and reset token
                whatTok="";
            }
            if(count==4){//if count gets too 4 then WINNER to the specific token that was placed

                return true;
            }
        }
        topRow--;
    }
    return false;//if no true then false
}

