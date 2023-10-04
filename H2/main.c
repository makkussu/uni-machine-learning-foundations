#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct vector2d {
	int x;
	int y;
} Vector2;

typedef struct q_data {
	int x;
	int y;
} Queen;


void print_board(int size, long **board) {
	for (int i = 0; i < size; i++) {
		int b = 0;
		while (b < size) {
			printf("%ld", board[i][b]);
			b++;
		}
		printf("\n");
	}
}

void assign_queen_pos(Queen *queens, int size, long **board) {
	int taken[size];
	memset(taken, 0, sizeof taken);

	srand(time(NULL));

	for (int i = 0; i < size; i++) {
		int row;

		do {
			row = rand() % size;
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

int get_random_index(int *indexes, int size) {
	int index = -1;
	while (index == -1)
		index = indexes[rand() % size];

	return index;
}


/*
	Basically calculates every single possible attack
	from the given queen to others on the chess board.
*/
int calculate_attacked_queens(Queen queen, int size, long **board) {
	int attacked = 0;
	int col, row;

	// Checking to the left
	col = queen.x - 1, row = queen.y;
	while (col >= 0) {
		if (board[row][col] == 1) {
			attacked++;
		}
		col--;
	}

	// Checking to the right
	col = queen.x + 1, row = queen.y;
	while (col < size) {
		if (board[row][col] == 1) {
			attacked++;
		}
		col++;
	}

	// Diagonally to the left up
	col = queen.x - 1, row = queen.y - 1;
	while (col >= 0 && row >= 0) {
		if (board[row][col] == 1) {
			attacked++;
		}
		col--;
		row--;
	}

	// Diagonally to the left down
	col = queen.x - 1, row = queen.y + 1;
	while (col >= 0 && row < size) {
		if (board[row][col] == 1) {
			attacked++;
		}
		col--;
		row++;
	}

	// Diagonally to the right up
	col = queen.x + 1, row = queen.y - 1;
	while (col < size && row >= 0) {
		if (board[row][col] == 1) {
			attacked++;
		}
		col++;
		row--;
	}

	// Diagonally to the right down
	col = queen.x + 1, row = queen.y + 1;
	while (col < size && row < size) {
		if (board[row][col] == 1) {
			attacked++;
		}
		col++;
		row++;
	}

	return attacked; 
}

/*
	Calculate the total collisions of all 
	possible combinations.
*/
int calculate_collisions(Queen *queens, int size, long **board) {
	int heurestic = 0;

	for (int i = 0; i < size; i++) {
		heurestic += calculate_attacked_queens(queens[i], size, board);
	}

	return heurestic;
}

int emulate_collisions_calculations(Vector2 best_pos, Queen *queens, int index, int size, long **board) {
	// Copying the data for safety.
	Queen sim_queen_array[size];
	
	long **sim_board;
	sim_board = malloc(size * sizeof(long*));
	for (int i = 0; i < size; i++) {
		sim_board[i] = malloc(size);
		memcpy(sim_board[i], board[i], size);
	}
	
	memcpy(&sim_queen_array, queens, sizeof sim_queen_array);
	// memcpy(&sim_board, board, sizeof sim_board);

	// Alternating the data
	Queen *sim_queen = &sim_queen_array[index];
	sim_board[sim_queen->y][sim_queen->x] = 0;
	sim_queen->y = best_pos.y;
	sim_board[sim_queen->y][sim_queen->x] = 1;

	int collisions = calculate_collisions(sim_queen_array, size, sim_board);
	
	free(sim_board);
	return collisions;
}

void calculate_best_move(Queen *queen, Queen *queens, 
		int size, long **board, Vector2 *vector, int current_heurestic) {

	int smallest_attack = 999999;

	// Copying queen to alter the data.
	Queen queen_copy;
	Queen queen_array_copy[size];

	// Overcomplicated board copying process
	long **board_copy;
	board_copy = malloc(size * sizeof board_copy);
	for (int i = 0; i < size; i++) {
		board_copy[i] = malloc(size * sizeof board_copy[i]);
		memcpy(board_copy[i], board[i], size * sizeof board_copy);
	}

	memcpy(&queen_copy, queen, sizeof queen_copy);
	memcpy(&queen_array_copy, queens, sizeof queen_array_copy);

	// Main logic
	for (int i = 0; i < size; i++) {
		int attacked;

		// Changing the 2d array
		board_copy[queen_copy.y][queen_copy.x] = 0;
		queen_copy.y = i;
		queen_array_copy[queen_copy.x].y = queen_copy.y;
		board_copy[queen_copy.y][queen_copy.x] = 1; 

		attacked = calculate_attacked_queens(queen_copy, size, board_copy);
		int temp_heurestic = calculate_collisions(queen_array_copy, size, board_copy);
		if (attacked <= smallest_attack && temp_heurestic < current_heurestic) {
			current_heurestic = temp_heurestic;
			smallest_attack = attacked;
			vector->y = i;
		}
	}

	free(board_copy);
}

void hill_climbing(Queen *queens, int size, long **board) {
	int current_heurestic, prev_heurestic, iterations;
	
	int mighty_warriors[size], attacks_array[size];
	memset(mighty_warriors, -1, sizeof mighty_warriors);
	memset(attacks_array, 0, sizeof attacks_array);

	int mighty_warrior, max_attacks, total_iterations;

	bool rage_restart;

	srand(time(0));

	current_heurestic = calculate_collisions(queens, size, board);
	iterations = total_iterations = 0;
	while (true) {
		if (total_iterations >= 100 || current_heurestic <= 1)
			break;

		if (iterations >= 5) {
			rage_restart = true;
			iterations = 0;
		}

		Vector2 best_pos;

		if (!rage_restart) {
			// Getting the max from all possible attacks and saving them.
			max_attacks = 0;
			for (int i = 0; i < size; i++) {
				int attacks = calculate_attacked_queens(queens[i], size, board);
				attacks_array[i] = attacks;
				if (attacks >= max_attacks)
					max_attacks = attacks;
			}

			int usedIndex = 0;
			for (int i = 0; i < size; i++) {
				if (attacks_array[i] == max_attacks) {
					mighty_warriors[usedIndex] = i;
					usedIndex++;
				}
			}

			mighty_warrior = get_random_index(mighty_warriors, usedIndex);
		} else {
			mighty_warrior = rand() % size;
			rage_restart = false;
		}

		best_pos.x = queens[mighty_warrior].x;
		best_pos.y = queens[mighty_warrior].y;
		calculate_best_move(&queens[mighty_warrior], queens, size, board, &best_pos, current_heurestic);

		// Peeking into the future :)
		int temp_heurestic = emulate_collisions_calculations(best_pos, queens, mighty_warrior, size, board);

		if (temp_heurestic >= current_heurestic) {
			iterations++;
			total_iterations++;
			continue;
		}

		// Update the main 2D array
		Queen *to_move = &queens[mighty_warrior];
			
		board[to_move->y][to_move->x] = 0;
		to_move->y = best_pos.y;
		board[to_move->y][to_move->x] = 1;

		// Calculate the new array
		prev_heurestic = current_heurestic;
		current_heurestic = temp_heurestic;
	}
}

int main(int argc, char const *argv[]) {
	// Getting input;
	int size, to_print_board;
	printf("Enter the size of a chessboard:\n");
	scanf("%d", &size);
	printf("\n");
	printf("Do you want to print the chessboard? (1 = YES | 0 = NO):\n");
	scanf("%d", &to_print_board);

	// Allocating memory;
	Queen queens[size];
	memset(queens, 0, sizeof queens);

	long **board;
	board = malloc(sizeof(long) * size);
	for (int i = 0; i < size; i++) {
		board[i] = malloc(sizeof(long) * size);
	}

	assign_queen_pos(queens, size, board);

	if (to_print_board == 1)
		print_board(size, board);

	printf("Collisions amount: %d\n", calculate_collisions(queens, size, board) / 2);
	printf("-----\n");

	hill_climbing(queens, size, board);

	if (to_print_board == 1)
		print_board(size, board);

	printf("Final collisions amount: %d\n", calculate_collisions(queens, size, board) / 2);

	free(board);
	return 0;
}