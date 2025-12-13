#include <iostream>

const char xPlayer = 'x';
const char oPlayer = 'o';
const char empty = ' ';

void printBoard(char board[3][3]){
	std::cout << ' ' << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
	for(int i = 1; i < 3; ++i){
	std::cout << "---+---+---" << "\n";
	std::cout << ' ' << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";	
	}
}

bool legalMove(int r, int c, char board[3][3]){
	return r >= 0 && r <= 2 && c >= 0 && c <= 2 && board[r][c] == empty; 
}

bool didWin(char player, char board[3][3]){
	for(int i = 0; i < 3; ++i){
		if(board[i][0] == player && board[i][1] == player && board[i][2] == player) {
			return true;
		}  
		if(board[0][i] == player && board[1][i] == player && board[2][i] == player) {
			return true;
		}
	}	

	if(board[0][0] == player && board[1][1] == player && board[2][2] == player) {
		return true;
	}  
	if(board[0][2] == player && board[1][1] == player && board[2][0] == player) {
		return true;
	}

	return false;
}

bool didEnd(char board[3][3]){
	int count = 0;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			if(board[i][j] == empty){
				return false;
			}
		}
	}
	return true;	
}

int main(){
	char board[3][3] = {
		{empty, empty, empty},
		{empty, empty, empty},
		{empty, empty, empty}
	};
	char player = xPlayer; 
	while(true){
		int row, col;

		std::cout << player << ": Please enter the row: ";
		std::cin >> row; 

		std::cout << player <<  ": Please enter the column: ";
		std::cin >> col; 

		if(legalMove(row, col, board) == false){
			std::cout << "Enterd cell is busy or doesn't exist!\n";
			break;
		}

		board[row][col] = player;

		if(didWin(player, board)){
			printBoard(board);
			std::cout << "Player " << player << " won!!!\n";
			break;
		}

		if(didEnd(board)){
			printBoard(board);
			std::cout << "Nothing!\n";
			break;
		}

		if(player == xPlayer){
				player = oPlayer;
		}else{
				player = xPlayer; 
		}

		printBoard(board);
	}
}
