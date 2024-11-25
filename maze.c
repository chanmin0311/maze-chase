// 미로 생성 및 미로 관련 로직
#include "maze.h"
#include "utility.h"
#include "player.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

Maze* create_maze(int width, int height) {
    Maze* maze = (Maze*)malloc(sizeof(Maze));
    if (!maze) return NULL;

    maze->width = width;
    maze->height = height;
    maze->cells = (int*)calloc(width * height, sizeof(int));
    return maze;
}

void free_maze(Maze* maze) {
    if (maze) {
        free(maze->cells);
        free(maze);
    }
}

int get_cell(Maze* maze, int x, int y) {
    return maze->cells[y * maze->width + x];
}

void set_cell(Maze* maze, int x, int y, int value) {
    maze->cells[y * maze->width + x] = value;
}

bool in_bounds(Maze* maze, int x, int y) {
    return x >= 0 && x <= maze->width && y >= 0 && y <= maze->height;
}

void binary_tree_algorithm(Maze* maze) {
	for (int y = 0; y < maze->height; y++) {
		for (int x = 0; x < maze->width; x++) {
			int options = 0;

			// Check possible directions
			if (y > 0) options++;
			if (x < maze->width - 1) options++;

			if (options > 0) {
				int direction = rand() % options;

				if (y == 0 || (direction == 1 && x < maze->width - 1)) {
					// Connect East
					set_cell(maze, x, y, get_cell(maze, x, y) | EAST);
					set_cell(maze, x + 1, y, get_cell(maze, x + 1, y) | WEST);
				}
				else {
					// Connect North
					set_cell(maze, x, y, get_cell(maze, x, y) | NORTH);
					set_cell(maze, x, y - 1, get_cell(maze, x, y - 1) | SOUTH);
				}
			}
		}
	}

	// Set start and end points
	set_cell(maze, 0, 0, get_cell(maze, 0, 0) | END);
	set_cell(maze, maze->width - 1, maze->height - 1, get_cell(maze, maze->width - 1, maze->height - 1) | START);

	// Ensure path from start
	set_cell(maze, 0, 0, get_cell(maze, 0, 0) | EAST);
	set_cell(maze, 1, 0, get_cell(maze, 1, 0) | WEST);

	// Ensure path to end
	int end_x = maze->width - 1;
	int end_y = maze->height - 1;
	set_cell(maze, end_x, end_y, get_cell(maze, end_x, end_y) | WEST);
	set_cell(maze, end_x - 1, end_y, get_cell(maze, end_x - 1, end_y) | EAST);
}

void ellers_algorithm(Maze* maze) {
	int width = maze->width;
	int* sets = (int*)malloc(width * sizeof(int));
	if (!sets) return;

	int next_set = 1;

	// Initialize first row
	for (int x = 0; x < width; x++) {
		sets[x] = next_set++;
	}

	// Process each row
	for (int y = 0; y < maze->height; y++) {
		// Random horizontal connections
		for (int x = 0; x < width - 1; x++) {
			if (sets[x] != sets[x + 1] && (rand() % 2 == 0 || y == maze->height - 1)) {
				int old_set = sets[x + 1];
				for (int i = 0; i < width; i++) {
					if (sets[i] == old_set) sets[i] = sets[x];
				}
				set_cell(maze, x, y, get_cell(maze, x, y) | EAST);
				set_cell(maze, x + 1, y, get_cell(maze, x + 1, y) | WEST);
			}
		}

		if (y < maze->height - 1) {
			// Vertical connections
			bool* connected = (bool*)calloc(next_set, sizeof(bool));
			if (connected) {
				for (int x = 0; x < width; x++) {
					if (rand() % 2 == 0 || !connected[sets[x]]) {
						connected[sets[x]] = true;
						set_cell(maze, x, y, get_cell(maze, x, y) | SOUTH);
						set_cell(maze, x, y + 1, get_cell(maze, x, y + 1) | NORTH);
					}
				}
				free(connected);
			}

			// Prepare next row
			int* next_row = (int*)malloc(width * sizeof(int));
			if (next_row) {
				for (int x = 0; x < width; x++) {
					if (get_cell(maze, x, y) & SOUTH)
						next_row[x] = sets[x];
					else
						next_row[x] = next_set++;
				}
				memcpy(sets, next_row, width * sizeof(int));
				free(next_row);
			}
		}
	}
	free(sets);

	// Set start and end points
	set_cell(maze, 0, 0, get_cell(maze, 0, 0) | END);
	set_cell(maze, maze->width - 1, maze->height - 1, get_cell(maze, maze->width - 1, maze->height - 1) | START);
}

void wilsons_algorithm(Maze* maze) {
	bool* in_maze = (bool*)calloc(maze->width * maze->height, sizeof(bool));
	int* next_step = (int*)malloc(maze->width * maze->height * sizeof(int));

	if (!in_maze || !next_step) {
		free(in_maze);
		free(next_step);
		return;
	}

	// Add first cell to maze
	in_maze[0] = true;
	int cells_left = maze->width * maze->height - 1;

	while (cells_left > 0) {
		// Find a cell not in maze
		int start_x, start_y;
		do {
			start_x = rand() % maze->width;
			start_y = rand() % maze->height;
		} while (in_maze[start_y * maze->width + start_x]);

		// Perform random walk
		int x = start_x, y = start_y;
		while (!in_maze[y * maze->width + x]) {
			int dir = rand() % 4;
			next_step[y * maze->width + x] = dir;
			switch (dir) {
			case 0: if (y > 0) y--; break;
			case 1: if (y < maze->height - 1) y++; break;
			case 2: if (x < maze->width - 1) x++; break;
			case 3: if (x > 0) x--; break;
			}
		}

		// Carve path
		x = start_x;
		y = start_y;
		while (!in_maze[y * maze->width + x]) {
			in_maze[y * maze->width + x] = true;
			cells_left--;

			int dir = next_step[y * maze->width + x];
			switch (dir) {
			case 0: // North
				set_cell(maze, x, y, get_cell(maze, x, y) | NORTH);
				y--;
				set_cell(maze, x, y, get_cell(maze, x, y) | SOUTH);
				break;
			case 1: // South
				set_cell(maze, x, y, get_cell(maze, x, y) | SOUTH);
				y++;
				set_cell(maze, x, y, get_cell(maze, x, y) | NORTH);
				break;
			case 2: // East
				set_cell(maze, x, y, get_cell(maze, x, y) | EAST);
				x++;
				set_cell(maze, x, y, get_cell(maze, x, y) | WEST);
				break;
			case 3: // West
				set_cell(maze, x, y, get_cell(maze, x, y) | WEST);
				x--;
				set_cell(maze, x, y, get_cell(maze, x, y) | EAST);
				break;
			}
		}
	}

	free(in_maze);
	free(next_step);

	// Set start and end points
	set_cell(maze, 0, 0, get_cell(maze, 0, 0) | END);
	set_cell(maze, maze->width - 1, maze->height - 1, get_cell(maze, maze->width - 1, maze->height - 1) | START);
}

Maze* generate_maze(int level) {
	int size;
	switch (level) {
	case 1: size = 10; break;
	case 2: size = 15; break;
	case 3: size = 20; break;
	case 4: size = 25; break;
	case 5: size = 30; break;
	default: return NULL;
	}

	Maze* maze = create_maze(size, size);
	if (!maze) return NULL;

	// Choose algorithm based on level
	if (level <= 2) {
		binary_tree_algorithm(maze);
	}
	else if (level == 3) {
		ellers_algorithm(maze);
	}
	else {
		wilsons_algorithm(maze);
	}

	return maze;
}

void print_maze(Maze* maze) {
	int row_length = maze->width;
	int coord_x, coord_y;
	char level;

	SetColor(YELLOW);
	GotoXY(0, 0); printf("조작 : ← ↑ → ↓");
	GotoXY(0, 1); printf("홈 : ESC");
	SetColor(WHITE);

	switch (row_length) {
	case 10: coord_x = 49; coord_y = 9; level = '1'; break;
	case 15: coord_x = 44; coord_y = 7; level = '2'; break;
	case 20: coord_x = 39; coord_y = 4; level = '3'; break;
	case 25: coord_x = 34; coord_y = 2; level = '4'; break;
	case 30: coord_x = 29; coord_y = 0; level = '5'; break;
	}

	// Print top border
	GotoXY(coord_x, coord_y);
	for (int x = 0; x < maze->width * 2 + 1; x++)
		printf("_");

	// Print maze body
	for (int y = 0; y < maze->height; y++) {
		GotoXY(coord_x, coord_y + y + 1);
		printf("|");
		for (int x = 0; x < maze->width; x++) {
			int cell = get_cell(maze, x, y);
			char cell_char = ' ';

			if (cell & START) cell_char = 'S';
			else if (cell & END) cell_char = 'E';
			else if (!(cell & SOUTH)) cell_char = '_';

			printf("%c", cell_char);
			printf("%c", (cell & EAST) ? ' ' : '|');
		}
		Sleep(100);
		printf("\n");
	}

	// 초기 플레이어 위치 설정 (시작점 'S'에 위치)
	Player player = { maze->width - 1, maze->height - 1 }; // START 위치
	print_player_position(&player, coord_x, coord_y);
	time_t start = clock();

	// 게임 루프
	while (1) {
		if (_kbhit()) {
			int key = _getch();
			int new_x = player.x;
			int new_y = player.y;

			if (key == ARROW) {
				key = _getch();
				bool can_move_direction = false;

				switch (key) {
				case UP:
					if (new_y > 0 && can_move(maze, new_x, new_y, NORTH)) {
						new_y--;
						can_move_direction = true;
					}
					break;
				case DOWN:
					if (new_y < maze->height - 1 && can_move(maze, new_x, new_y, SOUTH)) {
						new_y++;
						can_move_direction = true;
					}
					break;
				case LEFT:
					if (new_x > 0 && can_move(maze, new_x, new_y, WEST)) {
						new_x--;
						can_move_direction = true;
					}
					break;
				case RIGHT:
					if (new_x < maze->width - 1 && can_move(maze, new_x, new_y, EAST)) {
						new_x++;
						can_move_direction = true;
					}
					break;
				}

				if (can_move_direction) {
					// 이전 위치에 원래 셀의 상태를 다시 그리기
					GotoXY(coord_x + player.x * 2 + 1, coord_y + player.y + 1);
					int prev_cell = get_cell(maze, player.x, player.y);
					char prev_cell_char = ' ';

					if (prev_cell & START) prev_cell_char = 'S';
					else if (prev_cell & END) prev_cell_char = 'E';
					else if (!(prev_cell & SOUTH)) prev_cell_char = '_';

					printf("%c", prev_cell_char);

					// 새 위치로 이동
					player.x = new_x;
					player.y = new_y;
					print_player_position(&player, coord_x, coord_y);

					// 도착 지점 체크
					if (get_cell(maze, player.x, player.y) & END) {
						time_t end = clock();

						// 대충 깜박이는 효과
						game_end(coord_x, coord_y);

						system("cls");
						printMazeChase(19, 10);


						SetColor(YELLOW);

						GotoXY(46, 16);
						printf("┌──────────────────────┐");
						GotoXY(46, 17);
						printf("  탈출 성공!       ");
						GotoXY(46, 18);
						printf("  레벨 : %c              ", level);
						GotoXY(46, 19);
						printf("  탈출 시간 : %.1f초     ", (float)(end - start) / CLOCKS_PER_SEC);
						GotoXY(46, 20);
						printf("└──────────────────────┘");
						SetColor(WHITE);

						for (int i = 0; i < 3; i++) {
							GotoXY(46, 22); printf("                       "); Sleep(500);
							GotoXY(46, 22); printf("홈으로 돌아가려면 ENTER"); Sleep(500);
						}

						while (1) {
							if (_kbhit()) {
								int nkey = _getch();
								if (nkey == ENTER) {
									system("cls");
									show_menu();
								}
							}
						}

						system("cls");
						show_menu();
					}
				}
			}
			else if (key == ESC) {
				system("cls");
				show_menu();
			}
		}
	}
}

bool can_move(Maze* maze, int x, int y, int direction) {
	int cell = get_cell(maze, x, y);

	switch (direction) {
	case NORTH:
		return (cell & NORTH) != 0;
	case SOUTH:
		return (cell & SOUTH) != 0;
	case EAST:
		return (cell & EAST) != 0;
	case WEST:
		return (cell & WEST) != 0;
	default:
		return false;
	}
}

void printMazeChase(int x, int y) {
	SetColor(YELLOW);
	GotoXY(x, y);
	printf(" _______  _______  _______  _______   ______  _______  _______  _______  _______ \n");
	GotoXY(x, y + 1);
	printf("|   |   ||   _   ||__     ||    ___| |      ||   |   ||   _   ||     __||    ___|\n");
	GotoXY(x, y + 2);
	printf("|       ||       ||     __||    ___| |   ---||       ||       ||__     ||    ___|\n");
	GotoXY(x, y + 3);
	printf("|__|_|__||___|___||_______||_______| |______||___|___||___|___||_______||_______|\n");
	SetColor(WHITE);
}