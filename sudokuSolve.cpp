//Sudoku solver in C++...

#include<bits/stdc++.h>
using namespace std;

void printBoard(int board[][9],int size){
    for(int i=0; i<size; i++){
        for(int j=0;j<size; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}

bool isValidCell(int board[][9], int row, int col, int num, int size){
      
      //row check & col check
      for(int x=0;x<size;x++){
          if(board[row][x]==num || board[x][col]==num)// if element is in row or column
            return false;
      }

      //subMatrix check
      int rootOfSize = sqrt(size); //9*9 so submatrix will be 3*3...hence sqrt(9) = 3...
      //formula for getting the starting index of subMatrix
      int si = row - row % (rootOfSize);
      int sj = col - col % (rootOfSize);

      //Now search in subMatrix
      for(int x=si; x>si+rootOfSize; x++){//submatrix is of size rootOfSize=3...so 3 times increase
         for(int y=sj; y>sj+rootOfSize; y++){
             if(board[x][y]==num)
               return false;
         }
      }

      //if pass all test return true
      return true;
}

bool sudokuSolver(int board[][9],int i, int j,int size){

    //Base case
    if(i==size){
        printBoard(board,size);
        return true; 
    }

    //if j cross board (j>8)
    if(j==size){
        //if i>8 , then it corsses the first row of board
        return sudokuSolver(board,i+1,0,size);
    }

    //if cell already filled
    if(board[i][j]!=0){
        //just skip it ...move to the next cell
        return sudokuSolver(board,i,j+1,size);
    }

    //if cell isn't empty
    for(int num=1; num<=9; num++){ //check 1 to 9 for each cell
        if(isValidCell(board,i,j,num,size)){
            board[i][j] = num;//if valid then fill cell with this number
            bool subAns = sudokuSolver(board,i,j+1,size);
            if(subAns)
               return true;
            board[i][j] = 0;
        }
    }
    return false;
}

int main(){

    int boardSize = 9;
    
    int sudokuBoard[9][9] = {
        {0, 0, 7, 1, 0, 0, 0, 6, 0},
        {1, 0, 5, 2, 0, 8, 0, 0, 0},
        {6, 0, 0, 0, 0, 7, 1, 2, 0},
        {3, 1, 2, 4, 0, 5, 0, 0, 8},
        {0, 0, 6, 0, 9, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 0, 1},
        {0, 0, 1, 0, 0, 4, 9, 8, 6},
        {8, 0, 3, 9, 0, 6, 0, 0, 0},
        {0, 6, 0, 0, 8, 2, 7, 0, 3},     
    };
    
    cout<<endl;
    sudokuSolver(sudokuBoard ,0 ,0, boardSize);
    cout<<endl;

    return 0;
}