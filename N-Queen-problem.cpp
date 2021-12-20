// N-Queen problem using C++

#include<bits/stdc++.h>
using namespace std;

void printBoard(int chessBoard[][100],int boardSize){
      for(int i=0;i<boardSize;i++){
        for(int j=0;j<boardSize;j++)
            cout<<chessBoard[i][j]<<" ";     
        cout<<endl;  
      }
    
}

bool isQueenSafe(int chessBoard[][100],int boardSize,int currentRow,int currentCol){
    
    //column check
    int j = currentCol;
    for( int i=currentRow; i>=0; i--){//going upper straightly
        if(chessBoard[i][j]==1)
        return false;
    } 

    //right diagonal...row decrease ...column increase
    int i = currentRow;
     j = currentCol;
    while(i>=0 && j<boardSize){
      if(chessBoard[i][j]==1)
         return false;
      i--;
      j++;
    }

    //left diagonal...column decrease ...row increase
     i = currentRow;
     j = currentCol;
    while(i>=0 && j>=0){
      if(chessBoard[i][j]==1)
        return false;
      i--;
      j--;
    }

  return true;

}

bool solveNQueen(int chessBoard[][100],int boardSize,int currentRow){

   //Base Case...if current row == size of board
   if(currentRow==boardSize){
       printBoard(chessBoard,boardSize);
       return true;
   }

   //details from above tutorials...
   for(int i=0; i<boardSize; i++){
       //if queen is safe in chessBoard[currentRow][i]...then procedure
       if(isQueenSafe(chessBoard,boardSize,currentRow,i)){
           chessBoard[currentRow][i] = 1;
           bool ans = solveNQueen(chessBoard,boardSize,currentRow + 1);
           if(ans)
              return true;//will be execute for right answer
           chessBoard[currentRow][i] = 0;
       }
   }

   return false;
}

int main(){
    
    int boardSize=4;
    //cin>>boardSize;

    int chessBoard[100][100] = {};//initializing each cell of board with 0

    solveNQueen(chessBoard,boardSize,0);

    return 0;
}