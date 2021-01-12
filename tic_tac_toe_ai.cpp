#include <iostream>
#include <algorithm>

void print_board(char board[3][3]);
bool valid_move(char board[3][3], unsigned int pos_y, unsigned int pos_x);
bool win_or_tie(char board[3][3]);
int minimax(char board[3][3], int depth, bool maximizing_player);
bool board_filled(char board[3][3]);
void pick_best_move(char board[3][3]);
char computer_letter{'O'};
char human_letter{'X'};
char winner{' '};


int main();

int main(){

	bool play_again{true};
	int user_input;

	std::cout << "Welcome to Tic-Tac-Toe!" << "\n" "=======================" << "\n";

	while(play_again){

		char game_board[3][3]{{' ', ' ', ' '},
							  {' ', ' ', ' '},
							  {' ', ' ', ' '}};

		int first_turn;
		int turn{0};
		int human;
		bool game_over{false};

		std::cout << "Would you like to go first or second? Enter 1 to go first, 2 to go second: ";
		std::cin >> first_turn;

		if(first_turn != 2){
			std::cout << "\n";
			print_board(game_board);
		}

		if(first_turn == 1){
			human = 0;
		}
		else{
			human = 1;
			human_letter = 'O';
			computer_letter = 'X';
		}

		while(game_over == false){

			if(turn == human){
				unsigned int row;
				unsigned int col;

				std::cout << "\n" << "Please enter the row number you would like to place your move: ";
				std::cin >> row;
				std::cout << "Please enter the column number you would like to place your move: ";
				std::cin >> col;
				std::cout << "\n";

				if(valid_move(game_board, row - 1, col - 1)){
					game_board[row - 1][col - 1] = human_letter;
					print_board(game_board);
					if(win_or_tie(game_board) && (winner == 'H')){
						std::cout << "\n" << "You won!";
						game_over = true;
					}
				}
				else{
					std::cout << "You cannot place your move here." << "\n";
					if(first_turn == 1){
						turn = -1;
					}
					else{
						turn -= 1;
					}
				}
			}
			else{
				pick_best_move(game_board);
				std::cout << "\n" << "Computer's turn..." << "\n\n";
				print_board(game_board);
				if(win_or_tie(game_board) && (winner == 'C')){
					std::cout << "\n" << "Computer won!";
					game_over = true;
				}
			}

			if(board_filled(game_board) && (winner == 'T')){
				std::cout << "\n" << "It's a tie!";
				game_over = true;
			}

			turn += 1;
			turn = turn % 2;

		}

		if(first_turn == 2){
			human_letter = 'X';
			computer_letter = 'O';
		}

		std::cout << "\n\n" << "Would you like to play again? Enter 1 to play again, 2 to exit: ";
		std:: cin >> user_input;
		std::cout << std::endl;

		if(user_input == 2){
			std::cout << "===== PROGRAM TERMINATED =====";
			play_again = false;
		}
		else{
			continue;
		}

	}

	return 0;

}

void print_board(char board[3][3]){

	for(unsigned int i{0}; i < 3; ++i){
		for(unsigned int j{0}; j < 3; ++j){
			std::cout << " " << board[i][j];
			if((j == 0) || (j == 1)){
				std::cout << " |";
			}
		}
		std::cout << std::endl;
	}

}

bool valid_move(char board[3][3], unsigned int pos_y, unsigned int pos_x){

	if(board[pos_y][pos_x] == ' '){
		return true;
	}

	return false;

}

bool board_filled(char board[3][3]){

	for(unsigned int i{0}; i < 3; ++i){
		for(unsigned int j{0}; j < 3; ++j){
			if(board[i][j] == ' '){
				return false;
			}
		}
	}

	return true;

}

bool win_or_tie(char board[3][3]){

	for(unsigned int i{0}; i < 3; ++i){
		if((board[i][0] == board[i][1]) && (board[i][0] == board[i][2]) && (board[i][0] != ' ') &&
			(board[i][1] != ' ') && (board[i][2] != ' ')){
			if((board[i][0] == human_letter) && (board[i][1] == human_letter) && (board[i][2] == human_letter)){
				winner = 'H';
			}
			else{
				winner = 'C';
			}
			return true;
		}
	}

	for(unsigned int j{0}; j < 3; ++j){
		if((board[0][j] == board[1][j]) && (board[0][j] == board[2][j]) && (board[0][j] != ' ') &&
			(board[1][j] != ' ') && (board[2][j] != ' ')){
			if((board[0][j] == human_letter) && (board[1][j] == human_letter) && (board[2][j] == human_letter)){
				winner = 'H';
			}
			else{
				winner = 'C';
			}
			return true;
		}
	}

	if((board[0][0] == board[1][1]) && (board[0][0] == board[2][2]) && (board[0][0] != ' ') && (board[1][1] != ' ') &&
		(board[2][2] != ' ')){
		if((board[0][0] == human_letter) && (board[1][1] == human_letter) && (board[2][2] == human_letter)){
			winner = 'H';
		}
		else{
			winner = 'C';
		}
		return true;
	}

	if((board[0][2] == board[1][1]) && (board[0][2] == board[2][0]) && (board[0][2] != ' ') && (board[1][1] != ' ') &&
		(board[2][0] != ' ')){
		if((board[0][2] == human_letter) && (board[1][1] == human_letter) && (board[2][0] == human_letter)){
			winner = 'H';
		}
		else{
			winner = 'C';
		}
		return true;
	}

	if(board_filled(board)){
		winner = 'T';
		return true;
	}

	return false;

}

void pick_best_move(char board[3][3]){

	int max_eval = -10000;
	unsigned int y_pos{0};
	unsigned int x_pos{0};

	for(unsigned int i{0}; i < 3; ++i){
		for(unsigned int j{0}; j < 3; ++j){
			if(valid_move(board, i, j)){
				board[i][j] = computer_letter;
				int eval{minimax(board, 0, false)};
				board[i][j] = ' ';
				if(eval > max_eval){
					max_eval = eval;
					y_pos = i;
					x_pos = j;
				}
			}
		}
	}

	board[y_pos][x_pos] = computer_letter;

}

int minimax(char board[3][3], int depth, bool maximizing_player){

	if(win_or_tie(board)){
		if(winner == 'C'){
			return 10 - depth;
		}
		else if(winner == 'H'){
			return -10 + depth;
		}
		else{
			return 0;
		}
	}

	if(maximizing_player){
		int max_eval = -10000;
		for(unsigned int i{0}; i < 3; ++i){
			for(unsigned int j{0}; j < 3; ++j){
				if(valid_move(board, i, j)){
					board[i][j] = computer_letter;
					max_eval = std::max(max_eval, minimax(board, depth - 1, false));
					board[i][j] = ' ';
				}
			}
		}

		return max_eval;
	}
	else{
		int min_eval = 10000;
		for(unsigned int i{0}; i < 3; ++i){
			for(unsigned int j{0}; j < 3; ++j){
				if(valid_move(board, i, j)){
					board[i][j] = human_letter;
					min_eval = std::min(min_eval, minimax(board, depth - 1, true));
					board[i][j] = ' ';
				}
			}
		}

		return min_eval;
	}

}


