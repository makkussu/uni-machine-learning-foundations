#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define N 4

typedef struct q_data {
	int x;
	int y;
} Queen;


void print_board(int board[][N]) {
	for (int i = 0; i < N; i++) {
		int b = 0;
		while (b < N) {
			printf("%d", board[i][b]);
			b++;
		}
		printf("\n");
	}
}

void assign_queen_pos(Queen *queens, int board[][N]) {
	int taken[N] = { 0 };
	srand(time(NULL));

	for (int i = 0; i < N; i++) {
		int row;

		do {
			row = rand() % N;
			if (taken[row] == 0) {
				taken[row] = 1;
				break;
			}
		} while (taken[row] != 0);

		queens[i].x = i;
		queens[i].y = row;
		board[row][i] = 1;
	}
}

/*
	Basically calculates every single possible attack
	from the given queen to others on the chess board.
*/
int calculate_attacked_queens(Queen queen, int board[][N]) {
	int attacked = 0;
	int col = queen.x;
	int row = queen.y;

	// Checking to the left
	while (col > 0) {
		col--;
		if (board[row][col] == 1) {
			attacked += 1;
		}
	}

	// Checking to the right
	col = queen.x, row = queen.y;
	while (col < N - 1) {
		col++;
		if (board[row][col] == 1) {
			attacked++;
		}
	}

	// Diagonally to the left up
	col = queen.x, row = queen.y;
	while (col > 0 && row >= 0) {
		col--;
		row--;
		if (board[row][col] == 1) {
			attacked++;
		}
	}

	// Diagonally to the left down
	col = queen.x, row = queen.y;
	while (col > 0 && row < N - 1) {
		col--;
		row++;
		if (board[row][col] == 1) {
			attacked++;
		}
	}

	// Diagonally to the right up
	col = queen.x, row = queen.y;
	while (col < N - 1 && row > 0) {
		col++;
		row--;
		if (board[row][col] == 1) {
			attacked++;
		}
	}

	// Diagonally to the right down
	col = queen.x, row = queen.y;
	while (col < N - 1 && row < N - 1) {
		col++;
		row++;
		if (board[row][col] == 1) {
			attacked++;
		}
	}

	return attacked;
}

int calculate_heurestic(Queen *queens, int board[][N]) {
	int heurestic = 0;

	for (int i = 0; i < N; i++) {
		heurestic += calculate_attacked_queens(queens[i], board);
	}

	return heurestic;
}

void calculate_best_move(Queen *queens, int board[][N]) {
	int current_heurestic = calculate_heurestic(queens, board);
	int x, y;

	// Copy queens to another array for safety reasons.
	Queen copy_to[N];
	int copy_board[N][N];
	memcpy(&copy_to, queens, sizeof copy_to);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			// Very overcomplicated copying process...
			memcpy(&copy_board, board, sizeof copy_board);
			copy_board[copy_to[i].y][copy_to[i].x] = 0;
			copy_to[i].y = j;
			copy_board[copy_to[i].y][copy_to[i].x] = 1;

			int temp_heurestic = calculate_heurestic(queens, copy_board);

			printf("Queen num: %d\n", i);
			printf("Coordinates: %d/%d\n", copy_to[i].x, copy_to[i].y);
			printf("Heurestic: %d\n", temp_heurestic);

			if (temp_heurestic <= current_heurestic) {
				current_heurestic = temp_heurestic;
				x = copy_to[i].x;
				y = copy_to[i].y;
			}
		}

		printf("\n");
	}

	printf("Best X/Y: %d/%d\n", x, y);
}

int main(int argc, char const *argv[]) {
	Queen queens[N];
	int board[N][N] = { 0 };

	assign_queen_pos(queens, board);
	print_board(board);

	// printf("Heurestic: %d\n", calculate_heurestic(queens, board));
	calculate_best_move(queens, board);
	print_board(board);
	return 0;
}