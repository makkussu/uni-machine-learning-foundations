#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 7
#define HEIGHT 6
#define BOARD_SIZE WIDTH * HEIGHT
#define N_MOVES 100

typedef struct entity {
	int id;
	int lastMove;
	int *moves;
	int madeMoves;
} Entity;

// Generalized function to allocate memory when needed.
int* initializeArray(int size) {
	int *array;
	array = malloc(size * sizeof array);
	memset(array, 0, size * sizeof array);
	return array;
}

void resetArray(int *array, int size) {
	memset(array, 0, size * sizeof array);
}

// Make a full copy of one Entity;
void copyEntity(Entity *entity1, Entity *entity2) {
	int movesCopy[BOARD_SIZE];

	memcpy(&movesCopy, entity1->moves, sizeof movesCopy);
	entity2->moves = movesCopy;
}

// Printing board using traditional for-loops
void printBoard(int *board) {
	printf("|");
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (i % (WIDTH) == 0 && i != 0)
			printf("|\n|");
		printf("%d", board[i]);
	}
	printf("|\n|-------|\n");
	printf("|0123456|\n");
}

void updateGame(int *board, Entity *entity, int col) {
	for (int i = 0; i < HEIGHT; i++) {
		int pos = i * WIDTH + col;
		if (board[pos] == 0) {
			board[pos] = entity->id;
			entity->lastMove = pos;
			return ;
		}
	}
}

void updateEntityData(Entity *entity) {
	entity->moves[entity->madeMoves] = entity->lastMove;
	entity->madeMoves += 1;
}

void possibleMoves(int *board, int *moves, int *movesSize) {
	for (int i = 0; i < WIDTH; i++) {
		for (int b = 0; b < HEIGHT; b++) {
			if (board[b * WIDTH + i] == 0) {
				moves[*movesSize] = i;
				*movesSize += 1;
				break;
			}
		}
	}
}

// Return 1 if move is legal, otherwise return zero;
int legalMove(int *board, int col) {
	for (int i = 0; i < HEIGHT; i++) {
		if (board[i * WIDTH + col] == 0) {
			return 1;
		}
	}

	return 0;
}

// If game is over, return 1, otherwse return zero;
int gameOver(int *board) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (board[i] == 0)
			return 0;
	}

	return 1;
}

// If somebody has won, return 1. Otherwise return zero.
int hasWon(int *board, Entity *entity) {
	int steps, combinations;
	int row, col, pos;
	int forward, backwards;
	int frontPos, backPos;

	steps = combinations = 0;
	for (int i = 0; i < entity->madeMoves; i++) {
		pos = entity->moves[i];
		col = pos % WIDTH;
		row = (pos - col) / HEIGHT;

		steps = combinations = 0;
		if (board[pos] != entity->id)
			continue;

		// Horizontal check (basically checks in both directions)
		steps = combinations = 0;
		forward = backwards = 1;
		while (steps < 4) {
			steps++;

			if ((pos - backwards >= pos - col) && board[pos - backwards] == entity->id) {
				backwards += 1;
				combinations += 1;
			}

			if (pos + forward < WIDTH && board[pos + forward] == entity->id) {
				forward += 1;
				combinations += 1;
			}
		}

		if (combinations >= 3)  {
			return 1;
		}

		// Vertical check
		steps = combinations = 0;
		forward = backwards = WIDTH;
		while (steps < 4) {
			steps++;

			if (pos - backwards >= 0 && board[pos - backwards] == entity->id) {
				backwards += WIDTH;
				combinations += 1;
			}

			if (pos + forward < BOARD_SIZE && board[pos + forward] == entity->id) {
				forward += WIDTH;
				combinations += 1;
			}
		}

		if (combinations >= 3) {
			return 1;
		}

		// Diagonal check (from left down to right up)
		steps = combinations = 0;
		forward = backwards = 1;
		while (steps < 4) {
			steps++;
			backPos = backwards * WIDTH - backwards;
			frontPos = forward * WIDTH + forward;

			if (pos - backPos >= 0 && backPos >= 0 && board[pos - backPos] == entity->id) {
				backwards += 1;
				combinations += 1;
			}

			if (pos + frontPos < BOARD_SIZE && frontPos < WIDTH && board[pos + frontPos] == entity->id) {
				forward += 1;
				combinations += 1;
			}
		}

		if (combinations >= 3) {
			return 1;
		}

		// Diagonal check (from left up to right down)
		steps = combinations = 0;
		forward = backwards = 1;
		while (steps < 4) {
			steps++;
			backPos = backwards * WIDTH + backwards;
			frontPos = forward * WIDTH - forward;

			if (pos - backPos >= 0 && backPos >= 0 && board[pos - backPos] == entity->id) {
				backwards += 1;
				combinations += 1;
			}

			if (pos + frontPos < BOARD_SIZE && frontPos < WIDTH && board[pos + frontPos] == entity->id) {
				forward += 1;
				combinations += 1;
			}
		}

		if (combinations >= 3) {
			return 1;
		}
	}

	return 0;
}

// If computer has won, return 1. Otherwise zero (obviously lol)
int simulation(int *board, Entity *player, Entity *computer, int move) {
	int col, c_won, p_won;

	// Cloning the board;
	int fakeBoard[BOARD_SIZE];
	memcpy(&fakeBoard, board, sizeof fakeBoard);

	// Cloning the computer
	Entity fakeComputer;
	fakeComputer = *computer;
	copyEntity(computer, &fakeComputer);

	// Cloning the player
	Entity fakePlayer;
	fakePlayer = *player;
	copyEntity(player, &fakePlayer);

	// Faking the first step in the game.
	updateGame(fakeBoard, &fakeComputer, move);
	updateEntityData(&fakeComputer);

	while (1) {
		if (gameOver(fakeBoard))
			return 0;

		// Computer move
		// Weird way to check legality of a move.
		int legal = 0;
		do {
			col = rand() % (WIDTH - 1 + 1 - 0) + 0;
			legal = legalMove(fakeBoard, col);
		} while (legal != 1);

		updateGame(fakeBoard, &fakeComputer, col);
		updateEntityData(&fakeComputer);
		c_won = hasWon(fakeBoard, &fakeComputer);
		if (c_won) {
			return 1;
		}

		// Fake player move.
		legal = 0;
		do {
			col = rand() % (WIDTH - 1 + 1 - 0) + 0;
			legal = legalMove(fakeBoard, col);
		} while (legal != 1);

		updateGame(fakeBoard, &fakePlayer, col);
		updateEntityData(&fakePlayer);
		p_won = hasWon(fakeBoard, &fakePlayer);
		if (p_won)
			return 0;
	}
}

int computerMovementCalculations(int *board, Entity *player, Entity *computer, int *recommendedMoves, int *movesArraySize) {
	int bestMove, won, lost, prevWon, prevLost;
	prevWon = 0;
	prevLost = 999;

	possibleMoves(board, recommendedMoves, movesArraySize);

	for (int i = 0; i < *movesArraySize; i++) {
		won = lost = 0;
		
		for (int b = 0; b < N_MOVES; b++) {
			int simResult = simulation(board, player, computer, recommendedMoves[i]);
			if (simResult)
				won++;
			else
				lost++;
		}

		printf("Data: %d | %d | %d\n", i, won, lost);

		if (won >= prevWon) {
			if (lost < prevLost) {
				bestMove = i;
				prevLost = lost;
			}
			prevWon = won;
		}
	}

	printf("best move: %d\n", bestMove);

	return bestMove;
}

void game(int *board) {
	// Initializing game-related variables
	Entity player;
	player.id = 1;
	player.moves = initializeArray(BOARD_SIZE);
	player.madeMoves = 0;

	Entity computer;
	computer.id = 2;
	computer.moves = initializeArray(BOARD_SIZE);
	computer.madeMoves = 0;

	int chosenCol, won;

	// Computer-related logic
	int *computerRecommendedMoves = initializeArray(WIDTH);
	int possibleMovesArraySize = 0;

	// Setting the randomness timer
	srand(time(0));

	printf("Player = 1, Computer = 2\n");

	for (;;) {

		// Player makes a move;
		printBoard(board);

		printf("Choose the column:");
		scanf("%d", &chosenCol);

		updateGame(board, &player, chosenCol);
		updateEntityData(&player);
		won = hasWon(board, &player);
		printf("Has player won? %d\n", won);

		// Computer makes a move;
		resetArray(computerRecommendedMoves, WIDTH);
		possibleMovesArraySize = 0;

		int bestMove = computerMovementCalculations(board, &player, &computer, computerRecommendedMoves, &possibleMovesArraySize);
		updateGame(board, &computer, bestMove);
		updateEntityData(&computer);
		won = hasWon(board, &computer);
		printf("Has computer won? %d\n", won);
	}

	free(player.moves);
	free(computer.moves);
	free(computerRecommendedMoves);
}

int main(int argc, char const *argv[]) {
	// Reserving memory for the array;
	int *board;
	board = initializeArray(BOARD_SIZE);

	game(board);
	
	free(board);
	return 0;
}
