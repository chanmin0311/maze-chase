// 메뉴와 관련된 동작 처리
#include "menu.h"
#include "utility.h"
#include "maze.h"
#include "constants.h"

void ShowButton(int number) {
	if (number == 0) {
		SetColor(GREEN);
		BoldBoxMessege("시작", 44, 20);
		SetColor(WHITE);
	}
	else {
		BoxMessege("시작", 44, 20);
	}

	if (number == 1) {
		SetColor(DARK_SKYBLUE);
		BoldBoxMessege("설명", 54, 20);
		SetColor(WHITE);
	}
	else {
		BoxMessege("설명", 54, 20);
	}

	if (number == 2) {
		SetColor(DARK_RED);
		BoldBoxMessege("종료", 64, 20);
		SetColor(WHITE);
	}
	else {
		BoxMessege("종료", 64, 20);
	}
}

void show_menu() {
	int button_number = -1;

	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (button_number == 0 && nkey == ENTER) {
				play_game();

			}
			if (button_number == 1 && nkey == ENTER) {
				show_rule();
			}
			if (button_number == 2 && nkey == ENTER) {
				exit_game();
			}

			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
				case LEFT:
					if (button_number == -1 || button_number == 0) button_number = 2;
					else button_number = (button_number - 1);
					break;
				case RIGHT:
					button_number = (button_number + 1) % 3;
					break;
				}
			}
		}

		ShowButton(button_number);
		printMazeChase(19, 10);
		GotoXY(45, 25); ClrStr(YELLOW, "조작 : ← or →   선택 : ENTER");
		GotoXY(101, 0); ClrStr(YELLOW, "[by michin_chanmin]");
	}
}

void show_rule() {
	system("cls");

	BoxMessege("메뉴바 설명", 45, 2);
	GotoXY(45, 6);
	ClrStr(GREEN, "PLAY"); printf(" : 레벨을 설정하고 게임을 시작합니다.");
	GotoXY(45, 7);
	ClrStr(DARK_SKYBLUE, "RULE"); printf(" : 게임 방법을 확인합니다.");
	GotoXY(45, 8);
	ClrStr(DARK_RED, "EXIT"); printf(" : 게임을 종료합니다.");

	BoxMessege("플레이 방법", 45, 11);
	GotoXY(45, 15);
	printf("1. "); ClrStr(GREEN, "PLAY"); printf(" 버튼을 선택합니다.");
	GotoXY(45, 16);
	printf("2. 레벨을 선택합니다");
	GotoXY(45, 17);
	printf("3. 화면에 미로가 생성됩니다.");
	GotoXY(45, 18);
	printf("4. S는 출발점, E는 종점입니다.");
	GotoXY(45, 19);
	printf("5. 방향키로 말을 움직여 미로를 탈출합니다.");


	GotoXY(45, 22);
	SetColor(YELLOW); printf("확인하셨으면 ENTER를 누르세요. . ."); SetColor(WHITE);
	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (nkey == ENTER) {
				system("cls");
				break;
			}
		}
	}
}

int set_level() {
	system("cls");

	GotoXY(52, 3);
	ClrStr(YELLOW, "레벨 선택하기");

	GotoXY(0, 0);
	ClrStr(YELLOW, "조작 : ↑ OR ↓");
	GotoXY(15, 0);
	ClrStr(YELLOW, "선택 : Enter");
	GotoXY(0, 1);
	ClrStr(YELLOW, "홈 : ESC");

	printMazeChase(19, 21);

	int user_lever_choice = 0;

	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (user_lever_choice == 1 && nkey == ENTER) {
				Maze* maze = generate_maze(user_lever_choice);
				if (!maze) {
					system("cls");
					BoxMessege("미로 생성 실패", 49, 10);
					Sleep(3000);
					show_menu();
				}
				else {
					system("cls");
					print_maze(maze);
					free(maze);
					break;
				}
			}
			if (user_lever_choice == 2 && nkey == ENTER) {
				Maze* maze = generate_maze(user_lever_choice);
				if (!maze) {
					system("cls");
					BoxMessege("미로 생성 실패", 49, 10);
					Sleep(3000);
					show_menu();
				}
				else {
					system("cls");
					print_maze(maze);
					free(maze);
					break;
				}
			}
			if (user_lever_choice == 3 && nkey == ENTER) {
				Maze* maze = generate_maze(user_lever_choice);
				if (!maze) {
					system("cls");
					BoxMessege("미로 생성 실패", 49, 10);
					Sleep(3000);
					show_menu();
				}
				else {
					system("cls");
					print_maze(maze);
					free(maze);
					break;
				}
			}
			if (user_lever_choice == 4 && nkey == ENTER) {
				Maze* maze = generate_maze(user_lever_choice);
				if (!maze) {
					system("cls");
					BoxMessege("미로 생성 실패", 49, 10);
					Sleep(3000);
					show_menu();
				}
				else {
					system("cls");
					print_maze(maze);
					free(maze);
					break;
				}
			}
			if (user_lever_choice == 5 && nkey == ENTER) {
				Maze* maze = generate_maze(user_lever_choice);
				if (!maze) {
					system("cls");
					BoxMessege("미로 생성 실패", 49, 10);
					Sleep(3000);
					show_menu();
				}
				else {
					system("cls");
					print_maze(maze);
					free(maze);
					break;
				}
			}
			if (nkey == ESC) {
				system("cls");
				show_menu();
			}

			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
				case UP:
					if (user_lever_choice == 0 || user_lever_choice == 1) user_lever_choice = 5;
					else user_lever_choice -= 1;
					break;
				case DOWN:
					user_lever_choice = (user_lever_choice + 1) % 5;
					if (user_lever_choice == 0) user_lever_choice = 5;
					break;
				}
			}
		}
		int x = 48;
		int y = 5;

		if (user_lever_choice == 1) {
			BoldBoxMessege("Lv. 1 : 10 by 10", x, y);
		}
		else {
			BoxMessege("Lv. 1 : 10 by 10", x, y);
		}

		if (user_lever_choice == 2) {
			SetColor(DARK_YELLOW);
			BoldBoxMessege("Lv. 2 : 15 by 15", x, y + 3);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 2 : 15 by 15", x, y + 3);
		}

		if (user_lever_choice == 3) {
			SetColor(GREEN);
			BoldBoxMessege("Lv. 3 : 20 by 20", x, y + 6);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 3 : 20 by 20", x, y + 6);
		}

		if (user_lever_choice == 4) {
			SetColor(DARK_RED);
			BoldBoxMessege("Lv. 4 : 25 by 25", x, y + 9);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 4 : 25 by 25", x, y + 9);
		}

		if (user_lever_choice == 5) {
			SetColor(VIOLET);
			BoldBoxMessege("Lv. 5 : 30 by 30", x, y + 12);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 5 : 30 by 30", x, y + 12);
		}
	}
	return user_lever_choice;
}

void play_game() {
	system("cls");
	int level = set_level();

	if (level >= 1 && level <= 5) {
		Maze* maze = generate_maze(level);
		if (!maze) {
			system("cls");
			BoxMessege("미로 생성 실패", 49, 10);
			Sleep(3000);
			show_menu();
		}
		else {
			system("cls");
			print_maze(maze);
			free(maze);
		}
	}
}

void exit_game() {				// 종료 메세지를 보여주는 함수
	system("cls");
	GotoXY(52, 12); printf("종료하시겠습니까?");

	// 어느 버튼에 포커스를 두게 할 결정
	// 버튼의 번호는 0부터 시작, button_number를 0으로 설정하면 디폴트가 가장 첫(왼쪽) 버튼에 포커스
	// 어느 버튼에도 포커스를 두게 하고 싶지 않다면 -1로 설정
	int button_number = -1;
	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (button_number == 0 && nkey == ENTER) {				// 0번 버튼이 포커스 되어있고 Enter를 누르면
				system("cls");																// 화면을 지우고
				exit(1);																			// 프로그램을 종료시킴
			}
			if (button_number == 1 && nkey == ENTER) {					// 1번 버튼이 포커스 되어 있고 Enter를 누르면
				system("cls");																// 화면을 지우고												
				break;																			// menu화면으로 돌아감
			}
			// 방향키로 버튼을 선택
			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
				case LEFT:				// 입력이 왼쪽 방향키인 경우			
					// button_number가 초기 상태 이거나
					// 현재 버튼 기준으로 왼쪽에 더 이상 버튼이 없을 경우
					// 가장 끝의 버튼(1번 버튼)으로 이동함
					if (button_number == -1 || button_number == 0) button_number = 1;
					// button_number를 하나 감소 시킴
					else button_number -= button_number;
					break;
				case RIGHT:				// 입력이 오른쪽 방향키인 경우
					// button_number의 크기를 하나씩 증가 시킴
					// 버튼의 최대 개수가 넘어 갈 경우를 대비해
					// 연산 후 버튼의 개수 만큼 나머지 연산을 해줌
					button_number = (button_number + 1) % 2;
					break;
				}
			}
		}
		if (button_number == 0) {
			SetColor(RED);
			BoldBoxMessege("Y", 52, 14);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Y", 52, 14);
		}

		if (button_number == 1) {
			SetColor(GREEN);
			BoldBoxMessege("N", 62, 14);
			SetColor(WHITE);
		}
		else {
			BoxMessege("N", 62, 14);
		}
	}
}

void BoxMessege(const char* str, int x, int y) {
	// 사용자로부터 메세지를 입력받아 메세지를
	// 박스 형식으로 출력해주는 함수

	int boxWidth = strlen(str) + 6; // 메세지의 길이와 좌우 마진 1칸 씩 포함아여 2 더해줌
	int maxRow = 3;			// 박스는 문자열 1줄과 박스 위 아래를 포함하여 총 3줄만 출력


	// 박스 윗변 출력
	GotoXY(x, y);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("┌");									// 가장 윗쪽 왼쪽 모서리 출력							
		else if (i == boxWidth - 1) printf("┐");		// 가장 윗쪽 오른쪽 모서리 출력
		else printf("─");											// 모서리를 이어주는 변 출력
	}

	// 박스 안의 문자열과 테두리 출력
	GotoXY(x, y + 1);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("│");									// 박스의 왼쪽 변
		else if (i == boxWidth - 1) printf("│");		// 박스의 오른쪽 변
		else if (i == 1)printf("  %s  ", str);
	}

	// 박스 밑변 출력
	GotoXY(x, y + 2);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("└");									// 가장 아래쪽 왼쪽 모서리 출력
		else if (i == boxWidth - 1) printf("┘");		// 가장 아래쪽 오른쪽 모서리 출력
		else printf("─");											// 모서리를 이어주는 변 출력
	}
}

void BoldBoxMessege(const char* str, int x, int y) {
	// 사용자로부터 메세지를 입력받아 메세지를
	// 두꺼운 박스 형식으로 출력해주는 함수
	// BoxMessage 참조

	int boxWidth = strlen(str) + 6; // 메세지의 길이와 좌우 마진 3칸 씩 포함아여 6을 더해줌
	int maxRow = 3;			// 박스는 문자열 1줄과 박스 위 아래를 포함하여 총 3줄만 출력


	// 박스 윗변 출력
	GotoXY(x, y);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("┏");									// 가장 윗쪽 왼쪽 모서리 출력							
		else if (i == boxWidth - 1) printf("┓");		// 가장 윗쪽 오른쪽 모서리 출력
		else printf("━");											// 모서리를 이어주는 변 출력
	}

	// 박스 안의 문자열과 테두리 출력
	GotoXY(x, y + 1);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("┃");									// 박스의 왼쪽 변
		else if (i == boxWidth - 1) printf("┃");		// 박스의 오른쪽 변
		else if (i == 1)printf("  %s  ", str);
	}

	// 박스 밑변 출력
	GotoXY(x, y + 2);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("┗");									// 가장 아래쪽 왼쪽 모서리 출력
		else if (i == boxWidth - 1) printf("┛");		// 가장 아래쪽 오른쪽 모서리 출력
		else printf("━");											// 모서리를 이어주는 변 출력
	}
}