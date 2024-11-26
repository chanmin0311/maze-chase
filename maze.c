// �̷� ���� �� �̷� ���� ����
#include "maze.h"
#include "utility.h"
#include "player.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

// �̷� ���� ���
Maze* CreateMaze(int width, int height) {
    Maze* maze = (Maze*)malloc(sizeof(Maze));
	// ���� �޸� �Ҵ� ���� �� ���α׷� ����
    if (!maze) return NULL;

	// �� �ʱ�ȭ
    maze->width = width;
    maze->height = height;
	// �̷� ������ ������ ������ ó��
	// �̷��� ���� x ���� ��ŭ �޸𸮸� �Ҵ� �� 0���� �ʱ�ȭ
	// 1���� �迭�� ������ �ε��� ������ ������ 2���� �迭ó�� ���
    maze->cells = (int*)calloc(width * height, sizeof(int));
    return maze;
}

// �޸� �ݳ�
void FreeMaze(Maze* maze) {
    if (maze) {
		// maze����ü�� ���� �����ϸ� maze����ü�� �ɹ��� ���� �� �� �����Ƿ�
		// ��� ���� ��  ���� �޸� �Ҵ��� ���� cells�� ���� ���� �������μ� �޸� ���� ����
        free(maze->cells);
        free(maze);
    }
}

// �ش� ��ġ�� cell������ get
int GetCell(Maze* maze, int x, int y) {
	// 2���� �迭�� 1 �������� ����
	// �ε����� ������ �����Ͽ� 1���� �迭�� 2���� �迭ó�� ���
	// cell�� ������ŭ�� �޸𸮸� �Ҵ��� �� ����
    return maze->cells[y * maze->width + x];
}

// �ش� ��ġ�� cell������ set
void SetCell(Maze* maze, int x, int y, int value) {
    maze->cells[y * maze->width + x] = value;
}

// �÷��̾��� ���� �̷��� �ٿ���� �ȿ� �ִ��� Ȯ��
bool InBounds(Maze* maze, int x, int y) {
    return x >= 0 && x <= maze->width && y >= 0 && y <= maze->height;
}

// binary tree algorithm�� ����Ͽ� �̷� ���� 
void BinaryTreeAlgorithm(Maze* maze) {
	/*
	* https://weblog.jamisbuck.org/2011/2/1/maze-generation-binary-tree-algorithm �̷� ���� �˰��� ���� ��ũ ����
	*  1. �̷ξ��� ��� cell�鿡 ���Ͽ� ���� �ٸ� �� ������ ��θ��� �����Ѵ�
	*     ��/��, ��/��, ��/��, ��/�� �� �� ������̴��� �밢�� ������ �̷�Բ� �������ָ� �ȴ�
	*     ���⿡���� ���ʰ� ���� ��θ� �����ϵ��� �ߴ�
	*     �����ϱ� ���� ������ �缱 �������� ġ�������ٴ� ������ �ִ�
	*     ���� �̷��� �� ���� �� ���� �ϳ��� ��η� �̾����� �ȴ�
	*     ���� 1�� 2�� ���� �����̱⶧���� ���� ���� �̷θ� �����ϰ� �;��� �� �˰������� �̷θ� �����ϱ�� �����ߴ�
	*/
	for (int y = 0; y < maze->height; y++) {
		for (int x = 0; x < maze->width; x++) {
			int options = 0;

			// ���� ������ ���� Ȯ��
			if (y > 0) options++;								// ���� ���� ���� ����, ���� ���� �����ϸ� ����
			if (x < maze->width - 1) options++;		// ���� ���� ���� ����, ������ ���� �����ϸ� ����

			if (options > 0) {
				int direction = rand() % options;		// 0 ~ option - 1 ������ �� �� �ϳ� ��ȯ

				// ù��° �ɼ��� ������ ��� �������� ����
				// y��ǥ�� 0� �������� �̵��� �� �����Ƿ� ������ �������� ����
				if (y == 0 || (direction == 1 && x < maze->width - 1)) {
					// ���� ����
					SetCell(maze, x, y, GetCell(maze, x, y) | EAST);				// ���� ���� EAST ��Ʈ �߰�
					SetCell(maze, x + 1, y, GetCell(maze, x + 1, y) | WEST);	// ���� ���� WEST ��Ʈ �߰�
				}
				// �� ��° �ɼ� ������ ��� �������� ����
				else {
					// ���� ����
					SetCell(maze, x, y, GetCell(maze, x, y) | NORTH);			// ���� ���� NORTH ��Ʈ �߰�
					SetCell(maze, x, y - 1, GetCell(maze, x, y - 1) | SOUTH); // ���� ���� SOUTH ��Ʈ �߰�
				}
			}
		}
	}

	// �������� ���� ����
	SetCell(maze, maze->width - 1, maze->height - 1, GetCell(maze, maze->width - 1, maze->height - 1) | START);
	SetCell(maze, 0, 0, GetCell(maze, 0, 0) | END);			

	// �������� ��� ����
	int start_x = maze->width - 1;
	int start_y = maze->height - 1;
	SetCell(maze, start_x, start_y, GetCell(maze, start_x, start_y) | WEST);
	SetCell(maze, start_x - 1, start_y, GetCell(maze, start_x - 1, start_y) | EAST);

	// ���� ���������� ��� ����
	// ���� �������� ���� ���� �� ���(0,0 -> 1,0)�� ������
	SetCell(maze, 0, 0, GetCell(maze, 0, 0) | EAST);
	SetCell(maze, 1, 0, GetCell(maze, 1, 0) | WEST);
}

// ellers algorithm�� ����Ͽ� �̷� ����
void EllersAlgorithm(Maze* maze) {
	/* 
	*   https://weblog.jamisbuck.org/2010/12/29/maze-generation-eller-s-algorithm �̷� ���� �˰��� ���� ��ũ ����
	*  1. ù��° ���� cell���� ������ set���� �ʱ�ȭ �Ѵ�.
	*  2. �������� ������ cell���� �����Ѵ�. �̶� ������ cell���� ���� �ٸ� set�� ���ؾ� �Ѵ�.
	*     cell���� ������ ��, �� set�� ��� cell�� ���յǾ����� ��Ÿ���鼭 
	*     �ΰ��� ���� �ٸ� set�� �ϳ��� set���� �����ؾ��Ѵ�.
	*  3. ������ set�� �������� �Ʒ��� ���� ��� ���� ������ �ؾ��Ѵ�.
	*     ������ set�� ��� �ϳ��� ���� ������ �ؾ��Ѵ�.
	*     ���յ� ���� ���� ������ �ݵ�� ������ ���յ� set���� ���յǾ�� �Ѵ�.
	*  4. �ٸ� cell���� �ڽ��� set���� �߰��� ������ ���� ���� ä�� ������.
	*  5. ���� ������ ������ �࿡ �����Ҷ����� �ݺ��Ѵ�.
	*  6. ���������� ���� ������ �����ϰ� set�� ���Ե��� ���� cell���� ���������� ������ ������
	*/

	// �� �྿ �̷θ� ����� ���Ƿ� �̷��� ���� ���� �ʿ�
	int width = maze->width;
	// ������ ���鰣�� ���������� ����
	int* sets = (int*)malloc(width * sizeof(int));
	if (!sets) return;

	// �ʱ� ���յ��� ���� �� ���� ������ ������ �ϳ��� ������ ���е�
	// ù��° ���� ù��° ���� �ش��ϴ� ���� 1�� set���� �ʱ�ȭ �ϱ� ���� ���� ����
	int next_set = 1;

	// ù��° �� �ʱ�ȭ
	for (int x = 0; x < width; x++) {
		// ù��° ���� ���� 1�� set���� width�� set���� �ʱ�ȭ
		// ���������� �������� set�� �����ϴ� �ܰ�
		sets[x] = next_set++;
	}

	// ������ ����� ó��
	for (int y = 0; y < maze->height; y++) {
		// ���� �������� ���� ����
		for (int x = 0; x < width - 1; x++) {
			// ������ �� ���� �������� �����ϱ� ���� ����
			// 1. ������ �� ���� ���� �ٸ� set�� ���ԵǾ� �־�� �ϰ�
			// 2. �������� ���� ���� ���θ� ���� ���⶧���� ������ ������ ¦���� ��쿡 ����
			// 3. ������ ���� ��쿡�� �������� �����ؾ��ϴ� ��Ģ�� ����
			if (sets[x] != sets[x + 1] && (rand() % 2 == 0 || y == maze->height - 1)) {
				// ������ �� set���� ���� set ������ ����
				int old_set = sets[x + 1];
				for (int i = 0; i < width; i++) {
					// ���� ������ ��ȸ�ϸ� �ش��ϴ� ���� ���� set�� �ش��Ѵٸ�
					// ���� set�� ������ set�� ���� set���� ����
					if (sets[i] == old_set) sets[i] = sets[x];
				}

				// ������ �� set�� �����ϴ� ����
				// ������ set�� ���� set�� ���� EAST(0b0100)�� �����ϰ�
				// ������ set�� ������ set�� ���� WEST(0b1000)�� ������
				// ������ set�� ���� �������� ���յ�
				SetCell(maze, x, y, GetCell(maze, x, y) | EAST);
				SetCell(maze, x + 1, y, GetCell(maze, x + 1, y) | WEST);
			}
		}

		if (y < maze->height - 1) {
			// ������������ ����
			// ������ set�� �������� �Ʒ��� ��ġ�� ���� �࿡ ���� �������� ������ �ؾ���
			// ������ set�� ��� �ϳ��� ���� ������ �־�� ��
			// ���� �� �Ʒ��� ���� ���� ���� ���� set���� ���յ�
			
			// next_set�� ����ŭ ���� �޸� �Ҵ��� 0(false)���� �ʱ�ȭ 
			bool* connected = (bool*)calloc(next_set, sizeof(bool));
			// �޸� �Ҵ翡 �����Ͽ��ٸ�
			if (connected) {
				for (int x = 0; x < width; x++) {
					// ������ ������ ¦���̰ų� �ش� set�� ���� ���� �ϳ��� ���� ������ �̷��� ���� ���
					if (rand() % 2 == 0 || !connected[sets[x]]) {
						// �ش� set�� ���� ���� ���θ� true�� ����
						connected[sets[x]] = true;
						// �������� ���� ������ SOUTH(0b0010)������ ����
						SetCell(maze, x, y, GetCell(maze, x, y) | SOUTH);
						// �������� ���� ���� �Ʒ� ���� ���� NORTH(0b0001)������ ����
						SetCell(maze, x, y + 1, GetCell(maze, x, y + 1) | NORTH);
					}
				}
				// �� ���� ��� ��ȸ�� �� �޸� �ݳ�
				free(connected);
			}

			// ���� ������ �Ʒ� ���� �� ó�� �غ�

			// ���� �࿡ ���� ������ ó���� ���� �迭 ����
			int* next_row = (int*)malloc(width * sizeof(int));
			// �迭 �Ҵ翡 ���� �ϸ�
			if (next_row) {
				for (int x = 0; x < width; x++) {
					// ���� ��ΰ� ���� �ִ� �� Ȯ��
					// ���� (x, y) ���� ���ʰ� ���� ��ΰ� ���� �ִٸ�
					// SOUTH | EAST = 0b0010 | 0b0100 = 0b0110
					// ��, get_cell(maze, x, y)�� 0b0110 (����, ���� ����) �̶��
					// 0b0110 &  0b0010 = 0b0010 �̹Ƿ� ���� ��ΰ� �����ִ� �������� Ȯ��
					// ���� ���ʸ� �����ִٸ�
					// 0b0100 & 0b0010 = 0b0000 �̹Ƿ� ���� ��ΰ� �����ִ� �����
					
					// ���� ��ΰ� ���� �ִ� ���
					if (GetCell(maze, x, y) & SOUTH)
						// ���� ���� �Ʒ��� ���� ���� set�� ���ϵ��� ��
						next_row[x] = sets[x];
					// ���� ��ΰ� ���� �ִ� ���
					else
						// �Ʒ��� ���� ���ο� �������� set���� ��
						next_row[x] = next_set++;
				}
				// ���� ������ ��(next_row)�� ������ set�迭�� ����
				memcpy(sets, next_row, width * sizeof(int));
				// �޸� ����
				free(next_row);
			}
		}
	}
	free(sets);

	// ���������� �������� ����

	// (0, 0)������ ���� ���� �������� ����
	SetCell(maze, 0, 0, GetCell(maze, 0, 0) | END);
	// (width - 1, height -1) ������ ���� �������� ����
	SetCell(maze, maze->width - 1, maze->height - 1, GetCell(maze, maze->width - 1, maze->height - 1) | START);
}

// wilsonsalgorithm�� ����Ͽ� �̷� ����
void WilsonsAlgorithm(Maze* maze) {
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
				SetCell(maze, x, y, GetCell(maze, x, y) | NORTH);
				y--;
				SetCell(maze, x, y, GetCell(maze, x, y) | SOUTH);
				break;
			case 1: // South
				SetCell(maze, x, y, GetCell(maze, x, y) | SOUTH);
				y++;
				SetCell(maze, x, y, GetCell(maze, x, y) | NORTH);
				break;
			case 2: // East
				SetCell(maze, x, y, GetCell(maze, x, y) | EAST);
				x++;
				SetCell(maze, x, y, GetCell(maze, x, y) | WEST);
				break;
			case 3: // West
				SetCell(maze, x, y, GetCell(maze, x, y) | WEST);
				x--;
				SetCell(maze, x, y, GetCell(maze, x, y) | EAST);
				break;
			}
		}
	}

	free(in_maze);
	free(next_step);

	// Set start and end points
	SetCell(maze, 0, 0, GetCell(maze, 0, 0) | END);
	SetCell(maze, maze->width - 1, maze->height - 1, GetCell(maze, maze->width - 1, maze->height - 1) | START);
}

// �̷� ����
Maze* GenerateMaze(int level) {
	int size;				// ������ ���� �̷��� ũ�� ����
	switch (level) {
	case 1: size = 10; break;			// lv.1 10 x 10
	case 2: size = 15; break;			// lv.2 15 x 15
	case 3: size = 20; break;			// lv.3 20 x 20
	case 4: size = 25; break;			// lv.4 25 x 25
	case 5: size = 30; break;			// lv. 5 30 x 30
	default: return NULL;
	}

	// ������ �ش��ϴ� ũ���� �� �̷� ����
	Maze* maze = CreateMaze(size, size);
	if (!maze) return NULL;

	// ������ ���� �̷� ���� �˷θ����� �ٸ��� �Ͽ� �̷� ����
	// ������ �ö󰥼��� ������ �̷θ� �����ϴ� �˰�����
	if (level <= 2) {				// ���� 1�� 2�� binary tree �˰����� ����Ͽ� �̷� ����
		BinaryTreeAlgorithm(maze);
	}
	else if (level == 3) {		// ���� 3�� ellers �˰����� ����Ͽ� �̷� ����
		EllersAlgorithm(maze);
	}
	else {							// ���� 4�� 5�� wilsons �˰����� ����Ͽ� �̷� ����
		WilsonsAlgorithm(maze);
	}

	return maze;
}

// �̷� ��� �Լ�
void PrintMaze(Maze* maze) {
	// �̷��� �� ���� Ư�� ��Ʈ ������ ǥ���Ǿ� ����
	// �� ���� �ؼ��Ͽ� ���� ���¸� ����� ������ �̷� ���
	// ���۰� ����� ���� S, E ���κ��� ���κ��� ����  _, |�� ����

	int maze_width = maze->width;
	int coord_x, coord_y;
	char level;

	SetColor(YELLOW);
	GotoXY(0, 0); printf("���� : �� �� �� ��");
	GotoXY(0, 1); printf("Ȩ : ESC");
	SetColor(WHITE);

	switch (maze_width) {
	case 10: coord_x = 49; coord_y = 9; level = '1'; break;
	case 15: coord_x = 44; coord_y = 7; level = '2'; break;
	case 20: coord_x = 39; coord_y = 4; level = '3'; break;
	case 25: coord_x = 34; coord_y = 2; level = '4'; break;
	case 30: coord_x = 29; coord_y = 0; level = '5'; break;
	}

	// �̷��� ���� �� ���� ���
	GotoXY(coord_x, coord_y);
	for (int x = 0; x < maze->width * 2 + 1; x++)
		printf("_");

	// �̷� ��ü ���
	for (int y = 0; y < maze->height; y++) {
		GotoXY(coord_x, coord_y + y + 1);
		printf("|");
		for (int x = 0; x < maze->width; x++) {
			int cell = GetCell(maze, x, y);
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

	// �ʱ� �÷��̾� ��ġ ���� (������ 'S'�� ��ġ)
	Player player = { maze->width - 1, maze->height - 1 }; // START ��ġ
	PrintPlayerPosition(&player, coord_x, coord_y);
	time_t start = clock();

	// ���� ����
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
					if (new_y > 0 && CanMove(maze, new_x, new_y, NORTH)) {
						new_y--;
						can_move_direction = true;
					}
					break;
				case DOWN:
					if (new_y < maze->height - 1 && CanMove(maze, new_x, new_y, SOUTH)) {
						new_y++;
						can_move_direction = true;
					}
					break;
				case LEFT:
					if (new_x > 0 && CanMove(maze, new_x, new_y, WEST)) {
						new_x--;
						can_move_direction = true;
					}
					break;
				case RIGHT:
					if (new_x < maze->width - 1 && CanMove(maze, new_x, new_y, EAST)) {
						new_x++;
						can_move_direction = true;
					}
					break;
				}

				if (can_move_direction) {
					// ���� ��ġ�� ���� ���� ���¸� �ٽ� �׸���
					GotoXY(coord_x + player.x * 2 + 1, coord_y + player.y + 1);
					int prev_cell = GetCell(maze, player.x, player.y);
					char prev_cell_char = ' ';

					if (prev_cell & START) prev_cell_char = 'S';
					else if (prev_cell & END) prev_cell_char = 'E';
					else if (!(prev_cell & SOUTH)) prev_cell_char = '_';

					printf("%c", prev_cell_char);

					// �� ��ġ�� �̵�
					player.x = new_x;
					player.y = new_y;
					PrintPlayerPosition(&player, coord_x, coord_y);

					// ���� ���� üũ
					if (GetCell(maze, player.x, player.y) & END) {
						time_t end = clock();

						// ���������� ���� �� �����̴� ȿ��
						GameEnd(coord_x, coord_y);

						system("cls");
						PrintMazeChase(19, 10);


						SetColor(YELLOW);

						GotoXY(46, 16);
						printf("������������������������������������������������");
						GotoXY(46, 17);
						printf("  Ż�� ����!       ");
						GotoXY(46, 18);
						printf("  ���� : %c              ", level);
						GotoXY(46, 19);
						printf("  Ż�� �ð� : %.1f��     ", (float)(end - start) / CLOCKS_PER_SEC);
						GotoXY(46, 20);
						printf("������������������������������������������������");
						SetColor(WHITE);

						for (int i = 0; i < 3; i++) {
							GotoXY(46, 22); printf("                       "); Sleep(500);
							GotoXY(46, 22); printf("Ȩ���� ���ư����� ENTER"); Sleep(500);
						}

						while (1) {
							if (_kbhit()) {
								int nkey = _getch();
								if (nkey == ENTER) {
									system("cls");
									ShowMenu();
								}
							}
						}

						system("cls");
						ShowMenu();
					}
				}
			}
			else if (key == ESC) {
				system("cls");
				ShowMenu();
			}
		}
	}
}

bool CanMove(Maze* maze, int x, int y, int direction) {
	int cell = GetCell(maze, x, y);

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

void PrintMazeChase(int x, int y) {
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