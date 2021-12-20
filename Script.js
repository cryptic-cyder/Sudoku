
var arr = [[], [], [], [], [], [], [], [], []];

//getting div elements in the arr[][]...
for (var i = 0; i < 9; i++) {
	for (var j = 0; j < 9; j++) {
		arr[i][j] = document.getElementById(i * 9 + j); 
        //getting the div element from 0 to 80 (81 cells) in arr[][] for filling further
		//it will execute only for first time and the will reuse every time when FillBoard() will call
	}
}


var board = [[], [], [], [], [], [], [], [], []];

//filling the board with values get from the link...
function FillBoard(board) {
	for (var i = 0; i < 9; i++) {
		for (var j = 0; j < 9; j++) {
			if (board[i][j] != 0) {
				//arr[i][j] currently holds the div element from 0 to 80 (81 cells)
				//Now if the correspond board[i][j] holds Non-Zero which means board[i][j] get from
				//the link is Non-Zero then we fill arr[i][j] with the Non-Zero value..otherwise we 
				//will fill arr[i][j] with nothing (" ") with innerText
				arr[i][j].innerText = board[i][j];
			}

			else
				arr[i][j].innerText = " ";
		}
	}
}

let GetPuzzle = document.getElementById('GetPuzzle');
let SolvePuzzle = document.getElementById('SolvePuzzle');

GetPuzzle.onclick = function () {
	var xhrRequest = new XMLHttpRequest();
	xhrRequest.onload = function () {
		//getting the response(array values) from the below link...
		var response = JSON.parse(xhrRequest.response)
		//printing in console...(Not necessary)
		//console.log(response)
        
		//Send response(array values) to the board to create puzzle
		board = response.board
		FillBoard(board)
	}
	xhrRequest.open('get', 'https://sugoku.herokuapp.com/board?difficulty=easy');
	//we can change the difficulty of the puzzle the allowed values of difficulty are easy, medium, hard and random
	xhrRequest.send();
}


//for solving the puzzle 
SolvePuzzle.onclick = () => {
	sudokuSolver(board, 0, 0, 9);
};

function isValidCell(board, row, col, num, size){
      
	//row check & col check
	for(let x=0;x<size;x++){
		if(board[row][x]==num || board[x][col]==num)// if element is in row or column
		  return false;
	}

	//subMatrix check
	let rootOfSize = Math.sqrt(size); //9*9 so submatrix will be 3*3...hence sqrt(9) = 3...
	//formula for getting the starting index of subMatrix
	let si = row - row % (rootOfSize);
	let sj = col - col % (rootOfSize);

	//Now search in subMatrix
	for(let x=si; x>si+rootOfSize; x++){//submatrix is of size rootOfSize=3...so 3 times increase
	   for(let  y=sj; y>sj+rootOfSize; y++){
		   if(board[x][y]==num)
			 return false;
	   }
	}

	//if pass all test return true
	return true;
}

function sudokuSolver( board, i, j, size){

	//Base case
	if(i==size){
	    FillBoard(board);//fill with solved values...
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
	for(let num=1; num<=9; num++){ //check 1 to 9 for each cell
		if(isValidCell(board,i,j,num,size)){
			board[i][j] = num;//if valid then fill cell with this number
			let subAns = sudokuSolver(board,i,j+1,size);
			if(subAns)
			   return true;
			board[i][j] = 0;
		}
	}
	return false;
}