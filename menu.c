// 메뉴와 관련된 동작 처리
#include "menu.h"
#include "utility.h"
#include "maze.h"
#include "constants.h"

// 홈화면의 선택 가능한 버튼들을 보여주는 기능
void ShowButton(int number) {
	// number 는 버튼의 번호임

	// 첫번째 버튼 선택 시
	if (number == 0) {
		// 이 버튼이 포커스 되면 초록색 굵은 박스 출력
		SetColor(GREEN);
		BoldBoxMessege("시작", 44, 20);
		SetColor(WHITE);
	}
	else {
		// 다른 버튼으로 포커스가 옮겨지면 보통 박스 출력
		BoxMessege("시작", 44, 20);
	}

	if (number == 1) {
		// 이 버튼이 포커스 되면 어두운 하늘색 굵은 박스 출력
		SetColor(DARK_SKYBLUE);
		BoldBoxMessege("설명", 54, 20);
		SetColor(WHITE);
	}
	else {
		// 다른 버튼으로 포커스가 옮겨지면 보통 박스 출력
		BoxMessege("설명", 54, 20);
	}

	if (number == 2) {
		// 이 버튼이 포커스 되면 어두운 붉은색 굵은 박스 출력
		SetColor(DARK_RED);
		BoldBoxMessege("종료", 64, 20);
		SetColor(WHITE);
	}
	else {
		// 다른 버튼으로 포커스가 옮겨지면 보통 박스 출력
		BoxMessege("종료", 64, 20);
	}
}

// 게임 시작시 처음 보이는 홈화면을 보여주는 기능
void ShowMenu() {
	// 특정 버튼이 포커스 되었는지 확인하기 위한 번호를 0번부터 지정했으므로
	// 초기값을 -1로 설정
	int button_number = -1;

	while (1) {
		// 키보드 입력 감지
		if (_kbhit()) {
			// 키보드 입력 값 저장
			int nkey = _getch();
			// 1번 버튼(시작)에 포커스가 되어있고 눌린 키보드 값이 enter일 경우
			if (button_number == 0 && nkey == ENTER) {
				PlayGame();		// 게임 시작
			}
			// 2번 버튼(설명)에 포커스가 되어있고 눌린 키보드 값이 enter일 경우
			if (button_number == 1 && nkey == ENTER) {
				ShowRule();		// 규칙 설명
			}
			// 3번 버튼(종료)에 포커스가 되어있고 눌린 키보드 값이 enter일 경우
			if (button_number == 2 && nkey == ENTER) {
				ExitGame();		// 게임 종료
			}

			// 방향키가 화살표 방향키인지 우선 구별
			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
					// 왼쪽 방향키 입력 시
				case LEFT:
					// 값이 초깃값이거나 첫번째 버튼에 포커스가 되어있는 상황에서
					// 왼쪽 화살표가 입력되면 버튼의 포커스를 가장 마지막 버튼으로 옮김
					if (button_number == -1 || button_number == 0) button_number = 2;
					// 그게 아닌 경우엔 한 칸씩 왼쪽으로 포커스를 옮김
					else button_number = (button_number - 1);
					break;
					// 오른쪽 방향키 입력 시
				case RIGHT:
					// 버튼의 포커스를 오른쪽으로 옮김
					// 마지막 버튼에 포커스가 되어있고 오른쪽 방향키 입력이 들어왔을때
					// 더 이상 오른쪽으로 이동 할 버튼이 없으므로 첫번째 버튼으로 포커스를 둬야함
					// 마지막 버튼에 포커스가 두어진 경우는 button_number 가 2인 경우이고 
					// 이 상태에서 오른쪽 방향키값이 들어오면 1을 더해주고 
					// 3으로 나눈 나머지 즉, 0을 다시 button_number의 값으로 변경하면 첫번째 버튼으로 포커스가 가게 됨
					button_number = (button_number + 1) % 3;
					break;
				}
			}
		}

		// 버튼 출력
		ShowButton(button_number);
		// 게임 로고를 매개변수의 좌표값에 출력
		PrintMazeChase(19, 10);
		// 도움말 출력
		GotoXY(45, 25); ClrStr(YELLOW, "조작 : ← or →   선택 : ENTER");
		GotoXY(101, 0); ClrStr(YELLOW, "[by michin_chanmin]");
	}
}

// 규칙 설명
void ShowRule() {
	// 화면 지우기
	system("cls");

	// 게임 설명에 대한 내용 출력
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
	// enter키 입력시 메인화면 돌아가기
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

// 레벨 설정후 미로 출력
int SetLevel() {
	system("cls");

	GotoXY(52, 3);
	ClrStr(YELLOW, "레벨 선택하기");

	GotoXY(0, 0);
	ClrStr(YELLOW, "조작 : ↑ OR ↓");
	GotoXY(15, 0);
	ClrStr(YELLOW, "선택 : Enter");
	GotoXY(0, 1);
	ClrStr(YELLOW, "홈 : ESC");

	PrintMazeChase(19, 21);

	int user_lever_choice = 0;

	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			// 선택된 레벨을 리턴함
			if (user_lever_choice == 1 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 2 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 3 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 4 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 5 && nkey == ENTER) return user_lever_choice;
			if (nkey == ESC) {
				system("cls");
				ShowMenu();
			}

			// show_menu함수에서 버튼을 선택하는 기능과 같은 원리
			// 하지만 좌 우 방향키가 아닌 상 하 방향키로 조작
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

		// 포커스된 레벨에 따라서 각각 다른 색상과 테두리를 두껍게 하여 출력하여
		// 강조 효과가 보이도록 함
		if (user_lever_choice == 1) {
			// 레벨 1이 포커스 되었을때 색은 바꾸지 않고 테두리만 두껍게 보이도록 함
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

// 게임 시작
void PlayGame() {
	system("cls");

	// set_level에서 유저가 선택한 레벨을 저장
	int level = SetLevel();

	// 레벨이 유효한 범위 안의 값이이라면
	if (level >= 1 && level <= 5) {
		// 해당 레벨의 미로를 생성함
		Maze* maze = GenerateMaze(level);
		// 미로 생성에 실패시 예외 메세지 출력 후 3초 대기 후 프로그램 종료
		if (!maze) {
			system("cls");
			BoxMessege("미로 생성 실패", 49, 10);
			Sleep(3000);
			ShowMenu();
		}
		// 미로 생성 시
		else {
			system("cls");
			// 미로 출력
			PrintMaze(maze);
			// 메모리 반납
			free(maze);
		}
	}
}

// 게임 종료
void ExitGame() {				
	system("cls");
	// 게임 종료 메세지 출력
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

		// 포커스된 버튼에 따라 색상과 박스의 굵기를 다르게 하여 강조효과를 줌
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

// 박스 형태 메세지 출력
void BoxMessege(const char* str, int x, int y) {		// 메세지와 박스 메세지를 출력할 위치의 x, y 좌표값을 매개변수로 받음
	int boxWidth = strlen(str) + 6; // 메세지의 길이와 좌우 공백 각각  2칸, 메세지 테두리 좌우 각각 1칸 총 6칸 추가로 확보해줌
	int maxRow = 3;			// 박스는 문자열 1줄과 박스 위 아래를 포함하여 총 3줄만 출력


	// 박스 윗변 출력
	GotoXY(x, y);													// 매개변수로 전달받은 위치로 이동
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("┌");									// 가장 윗쪽 왼쪽 모서리 출력							
		else if (i == boxWidth - 1) printf("┐");		// 가장 윗쪽 오른쪽 모서리 출력
		else printf("─");											// 모서리를 이어주는 변 출력
	}

	// 박스 안의 문자열과 테두리 출력
	GotoXY(x, y + 1);												// 초기 위치에서 한칸 내려옴
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("│");									// 박스의 왼쪽 변
		else if (i == boxWidth - 1) printf("│");		// 박스의 오른쪽 변
		else if (i == 1)printf("  %s  ", str);					// 메세지 출력
	}

	// 박스 밑변 출력
	GotoXY(x, y + 2);												// 초기 위치에서 두칸 내려옴
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("└");									// 가장 아래쪽 왼쪽 모서리 출력
		else if (i == boxWidth - 1) printf("┘");		// 가장 아래쪽 오른쪽 모서리 출력
		else printf("─");											// 모서리를 이어주는 변 출력
	}
}

// 굵은 박스 메세지 출력
void BoldBoxMessege(const char* str, int x, int y) {			// BoxMessege와 동일한 매개변수
	int boxWidth = strlen(str) + 6; // 메세지의 길이와 좌우 공백 각각  2칸, 메세지 테두리 좌우 각각 1칸 총 6칸 추가로 확보해줌
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