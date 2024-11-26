// 미로 생성 및 미로 관련 로직
#include "maze.h"
#include "utility.h"
#include "player.h"
#include "constants.h"
#include <stdlib.h>
#include <time.h>

// 미로 생성 기능
Maze* CreateMaze(int width, int height) {
    Maze* maze = (Maze*)malloc(sizeof(Maze));
	// 동적 메모리 할당 실패 시 프로그램 종료
    if (!maze) return NULL;

	// 값 초기화
    maze->width = width;
    maze->height = height;
	// 미로 생성과 관련한 정보를 처리
	// 미로의 가로 x 세로 만큼 메모리를 할당 후 0으로 초기화
	// 1차원 배열을 적절한 인덱스 값으로 접근해 2차원 배열처럼 사용
    maze->cells = (int*)calloc(width * height, sizeof(int));
    return maze;
}

// 메모리 반납
void FreeMaze(Maze* maze) {
    if (maze) {
		// maze구조체를 먼저 해제하면 maze구조체의 맴버를 접근 할 수 없으므로
		// 멤버 변수 중  동적 메모리 할당을 받은 cells을 먼저 해제 해줌으로서 메모리 누수 방지
        free(maze->cells);
        free(maze);
    }
}

// 해당 위치의 cell정보를 get
int GetCell(Maze* maze, int x, int y) {
	// 2차원 배열을 1 차원으로 구현
	// 인덱스를 적절히 접근하여 1차원 배열을 2차원 배열처럼 사용
	// cell의 갯수만큼만 메모리를 할당할 수 있음
    return maze->cells[y * maze->width + x];
}

// 해당 위치의 cell정보를 set
void SetCell(Maze* maze, int x, int y, int value) {
    maze->cells[y * maze->width + x] = value;
}

// 플레이어의 말이 미로의 바운더리 안에 있는지 확인
bool InBounds(Maze* maze, int x, int y) {
    return x >= 0 && x <= maze->width && y >= 0 && y <= maze->height;
}

// binary tree algorithm을 사용하여 미로 생성 
void BinaryTreeAlgorithm(Maze* maze) {
	/*
	* https://weblog.jamisbuck.org/2011/2/1/maze-generation-binary-tree-algorithm 미로 생성 알고리즘 관련 링크 참조
	*  1. 미로안의 모든 cell들에 대하여 각기 다른 두 방향의 경로만을 선택한다
	*     북/서, 북/동, 남/서, 남/동 쪽 등 어느쪽이던지 대각선 방향을 이루게끔 설정해주면 된다
	*     여기에서는 북쪽과 동쪽 경로를 선택하도록 했다
	*     구현하기 비교적 쉽지만 사선 방향으로 치우쳐진다는 단점이 있다
	*     또한 미로의 네 변중 두 변은 하나의 경로로 이어지게 된다
	*     레벨 1과 2는 낮은 레벨이기때문에 아주 쉬운 미로를 생성하고 싶었고 이 알고리즘으로 미로를 생성하기로 결정했다
	*/
	for (int y = 0; y < maze->height; y++) {
		for (int x = 0; x < maze->width; x++) {
			int options = 0;

			// 선택 가능한 방향 확인
			if (y > 0) options++;								// 북쪽 방향 가능 여부, 위쪽 셀이 존재하면 가능
			if (x < maze->width - 1) options++;		// 동쪽 방향 가능 여부, 오른쪽 셀이 존재하면 가능

			if (options > 0) {
				int direction = rand() % options;		// 0 ~ option - 1 사이의 값 중 하나 반환

				// 첫번째 옵션을 선택할 경우 동쪽으로 연결
				// y좌표가 0어도 북쪽으로 이동할 수 없으므로 무조건 동쪽으로 연결
				if (y == 0 || (direction == 1 && x < maze->width - 1)) {
					// 동쪽 연결
					SetCell(maze, x, y, GetCell(maze, x, y) | EAST);				// 현재 셀에 EAST 비트 추가
					SetCell(maze, x + 1, y, GetCell(maze, x + 1, y) | WEST);	// 현재 셀에 WEST 비트 추가
				}
				// 두 번째 옵션 선택할 경우 북쪽으로 연결
				else {
					// 북쪽 연결
					SetCell(maze, x, y, GetCell(maze, x, y) | NORTH);			// 현재 셀에 NORTH 비트 추가
					SetCell(maze, x, y - 1, GetCell(maze, x, y - 1) | SOUTH); // 현재 셀에 SOUTH 비트 추가
				}
			}
		}
	}

	// 시작점과 끝점 설정
	SetCell(maze, maze->width - 1, maze->height - 1, GetCell(maze, maze->width - 1, maze->height - 1) | START);
	SetCell(maze, 0, 0, GetCell(maze, 0, 0) | END);			

	// 시작점의 경로 보장
	int start_x = maze->width - 1;
	int start_y = maze->height - 1;
	SetCell(maze, start_x, start_y, GetCell(maze, start_x, start_y) | WEST);
	SetCell(maze, start_x - 1, start_y, GetCell(maze, start_x - 1, start_y) | EAST);

	// 종료 지점에서의 경로 보장
	// 종료 지점에서 종료 지점 전 경로(0,0 -> 1,0)을 보장함
	SetCell(maze, 0, 0, GetCell(maze, 0, 0) | EAST);
	SetCell(maze, 1, 0, GetCell(maze, 1, 0) | WEST);
}

// ellers algorithm을 사용하여 미로 생성
void EllersAlgorithm(Maze* maze) {
	/* 
	*   https://weblog.jamisbuck.org/2010/12/29/maze-generation-eller-s-algorithm 미로 생성 알고리즘 관련 링크 참조
	*  1. 첫번째 행의 cell들을 각각의 set으로 초기화 한다.
	*  2. 무작위로 인접한 cell들을 병합한다. 이때 인접한 cell들은 각각 다른 set에 속해야 한다.
	*     cell들을 병합할 때, 두 set의 모든 cell이 병합되었음을 나타내면서 
	*     두개의 각기 다른 set을 하나의 set으로 병합해야한다.
	*  3. 각각의 set은 무작위로 아래의 다음 행과 수직 결합을 해야한다.
	*     각각의 set은 적어도 하나의 수직 결합을 해야한다.
	*     결합된 다음 행의 셀들은 반드시 위에서 결합된 set으로 병합되어야 한다.
	*  4. 다른 cell들을 자신의 set으로 추가해 나가며 다음 행을 채워 나간다.
	*  5. 위의 과정을 마지박 행에 도달할때까지 반복한다.
	*  6. 마지막행은 수직 결합은 생략하고 set에 포함되지 않은 cell들을 수평적으로 결합해 나간다
	*/

	// 한 행씩 미로를 만들어 가므로 미로의 가로 길이 필요
	int width = maze->width;
	// 인접한 셀들간의 결합정보를 저장
	int* sets = (int*)malloc(width * sizeof(int));
	if (!sets) return;

	// 초기 결합되지 않은 한 행의 각각의 셀들은 하나의 셋으로 구분됨
	// 첫번째 행의 첫번째 열에 해당하는 셀을 1번 set으로 초기화 하기 위한 변수 선언
	int next_set = 1;

	// 첫번째 행 초기화
	for (int x = 0; x < width; x++) {
		// 첫번째 행의 셀을 1번 set부터 width번 set까지 초기화
		// 아직까지는 독립적인 set을 구분하는 단계
		sets[x] = next_set++;
	}

	// 각각의 행들을 처리
	for (int y = 0; y < maze->height; y++) {
		// 수평 방향으로 랜덤 연결
		for (int x = 0; x < width - 1; x++) {
			// 인접한 두 셀을 수평으로 연결하기 위한 조건
			// 1. 인접한 두 셀이 서로 다른 set에 포함되어 있어야 하고
			// 2. 랜덤으로 결합 진행 여부를 결정 짓기때문에 생성된 난수가 짝수일 경우에 결합
			// 3. 마지막 행일 경우에는 수평으로 연결해야하는 규칙이 있음
			if (sets[x] != sets[x + 1] && (rand() % 2 == 0 || y == maze->height - 1)) {
				// 인접한 두 set에서 나중 set 정보를 저장
				int old_set = sets[x + 1];
				for (int i = 0; i < width; i++) {
					// 행의 셀들을 순회하며 해당하는 셀이 나중 set에 해당한다면
					// 나중 set과 인접한 set을 같은 set으로 포함
					if (sets[i] == old_set) sets[i] = sets[x];
				}

				// 인접한 두 set을 병합하는 과정
				// 인접한 set중 왼쪽 set의 값을 EAST(0b0100)로 설정하고
				// 인접한 set중 오른쪽 set의 값을 WEST(0b1000)로 설정함
				// 인접한 set이 수평 방향으로 병합됨
				SetCell(maze, x, y, GetCell(maze, x, y) | EAST);
				SetCell(maze, x + 1, y, GetCell(maze, x + 1, y) | WEST);
			}
		}

		if (y < maze->height - 1) {
			// 수직방향으로 결합
			// 각각의 set은 무작위로 아래의 위치한 다음 행에 수직 방향으로 결합을 해야함
			// 각각의 set은 적어도 하나의 수직 결합이 있어야 함
			// 결합 된 아래의 셀은 위의 셀이 속한 set으로 결합됨
			
			// next_set의 수만큼 동적 메모리 할당후 0(false)으로 초기화 
			bool* connected = (bool*)calloc(next_set, sizeof(bool));
			// 메모리 할당에 성공하였다면
			if (connected) {
				for (int x = 0; x < width; x++) {
					// 생성된 난수가 짝수이거나 해당 set의 셀이 아직 하나의 수직 결합을 이루지 않은 경우
					if (rand() % 2 == 0 || !connected[sets[x]]) {
						// 해당 set의 수직 결합 여부를 true로 설정
						connected[sets[x]] = true;
						// 진행중인 행의 셀에서 SOUTH(0b0010)쪽으로 결합
						SetCell(maze, x, y, GetCell(maze, x, y) | SOUTH);
						// 진행중인 행의 셀의 아래 행의 셀은 NORTH(0b0001)쪽으로 결합
						SetCell(maze, x, y + 1, GetCell(maze, x, y + 1) | NORTH);
					}
				}
				// 한 행을 모두 순회한 후 메모리 반납
				free(connected);
			}

			// 수직 결합후 아래 다음 행 처리 준비

			// 다음 행에 대한 정보를 처리할 동적 배열 선언
			int* next_row = (int*)malloc(width * sizeof(int));
			// 배열 할당에 성공 하면
			if (next_row) {
				for (int x = 0; x < width; x++) {
					// 남쪽 경로가 열려 있는 지 확인
					// 만약 (x, y) 셀이 남쪽과 동쪽 경로가 열려 있다면
					// SOUTH | EAST = 0b0010 | 0b0100 = 0b0110
					// 즉, get_cell(maze, x, y)가 0b0110 (남쪽, 동쪽 열림) 이라면
					// 0b0110 &  0b0010 = 0b0010 이므로 남쪽 경로가 열려있는 상태임을 확인
					// 만약 동쪽만 열려있다면
					// 0b0100 & 0b0010 = 0b0000 이므로 남쪽 경로가 닫혀있는 경우임
					
					// 남쪽 경로가 열려 있는 경우
					if (GetCell(maze, x, y) & SOUTH)
						// 현재 셀과 아래쪽 셀이 같은 set에 속하도록 함
						next_row[x] = sets[x];
					// 남쪽 경로가 닫혀 있는 경우
					else
						// 아래쪽 셀은 새로운 독립적인 set으로 함
						next_row[x] = next_set++;
				}
				// 새로 연산한 행(next_row)을 기존의 set배열로 복사
				memcpy(sets, next_row, width * sizeof(int));
				// 메모리 해제
				free(next_row);
			}
		}
	}
	free(sets);

	// 종료지점과 시작지점 설정

	// (0, 0)지점의 셀을 종료 지점으로 설정
	SetCell(maze, 0, 0, GetCell(maze, 0, 0) | END);
	// (width - 1, height -1) 지점을 시작 지점으로 설정
	SetCell(maze, maze->width - 1, maze->height - 1, GetCell(maze, maze->width - 1, maze->height - 1) | START);
}

// wilsonsalgorithm을 사용하여 미로 생성
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

// 미로 생성
Maze* GenerateMaze(int level) {
	int size;				// 레벨에 따라서 미로의 크기 결정
	switch (level) {
	case 1: size = 10; break;			// lv.1 10 x 10
	case 2: size = 15; break;			// lv.2 15 x 15
	case 3: size = 20; break;			// lv.3 20 x 20
	case 4: size = 25; break;			// lv.4 25 x 25
	case 5: size = 30; break;			// lv. 5 30 x 30
	default: return NULL;
	}

	// 레벨에 해당하는 크기의 빈 미로 생성
	Maze* maze = CreateMaze(size, size);
	if (!maze) return NULL;

	// 레벨에 따라 미로 생성 알로리즘을 다르게 하여 미로 생성
	// 레벨이 올라갈수록 복잡한 미로를 생성하는 알고리즘임
	if (level <= 2) {				// 레벨 1과 2는 binary tree 알고리즘을 사용하여 미로 생성
		BinaryTreeAlgorithm(maze);
	}
	else if (level == 3) {		// 레벨 3는 ellers 알고리즘을 사용하여 미로 생성
		EllersAlgorithm(maze);
	}
	else {							// 레벨 4와 5는 wilsons 알고리즘을 사용하여 미로 생성
		WilsonsAlgorithm(maze);
	}

	return maze;
}

// 미로 출력 함수
void PrintMaze(Maze* maze) {
	// 미로의 각 셀이 특정 비트 값으로 표현되어 있음
	// 그 값을 해석하여 셀의 상태를 출력해 나가며 미로 출력
	// 시작과 종료는 각각 S, E 가로벽과 세로벽은 각각  _, |로 구분

	int maze_width = maze->width;
	int coord_x, coord_y;
	char level;

	SetColor(YELLOW);
	GotoXY(0, 0); printf("조작 : ← ↑ → ↓");
	GotoXY(0, 1); printf("홈 : ESC");
	SetColor(WHITE);

	switch (maze_width) {
	case 10: coord_x = 49; coord_y = 9; level = '1'; break;
	case 15: coord_x = 44; coord_y = 7; level = '2'; break;
	case 20: coord_x = 39; coord_y = 4; level = '3'; break;
	case 25: coord_x = 34; coord_y = 2; level = '4'; break;
	case 30: coord_x = 29; coord_y = 0; level = '5'; break;
	}

	// 미로의 가장 윗 라인 출력
	GotoXY(coord_x, coord_y);
	for (int x = 0; x < maze->width * 2 + 1; x++)
		printf("_");

	// 미로 몸체 출력
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

	// 초기 플레이어 위치 설정 (시작점 'S'에 위치)
	Player player = { maze->width - 1, maze->height - 1 }; // START 위치
	PrintPlayerPosition(&player, coord_x, coord_y);
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
					// 이전 위치에 원래 셀의 상태를 다시 그리기
					GotoXY(coord_x + player.x * 2 + 1, coord_y + player.y + 1);
					int prev_cell = GetCell(maze, player.x, player.y);
					char prev_cell_char = ' ';

					if (prev_cell & START) prev_cell_char = 'S';
					else if (prev_cell & END) prev_cell_char = 'E';
					else if (!(prev_cell & SOUTH)) prev_cell_char = '_';

					printf("%c", prev_cell_char);

					// 새 위치로 이동
					player.x = new_x;
					player.y = new_y;
					PrintPlayerPosition(&player, coord_x, coord_y);

					// 도착 지점 체크
					if (GetCell(maze, player.x, player.y) & END) {
						time_t end = clock();

						// 도착지점에 도착 후 깜박이는 효과
						GameEnd(coord_x, coord_y);

						system("cls");
						PrintMazeChase(19, 10);


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