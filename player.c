#include "player.h"
#include "constants.h"

// 미로에서 플레이어의 말을 움직이는 기능
void PrintPlayerPosition(Player* player, int coord_x, int coord_y) {
	// Player구조체와 미로의 시작 위치 좌표를 초기 매개변수 값으로 받음
	GotoXY(coord_x + player->x * 2 + 1, coord_y + player->y + 1);
	// 색상을 DARK_RED로 지정
	SetColor(DARK_RED);
	printf("●");
	SetColor(WHITE);		// 말의 색상만 변경 후 다시 원래 색상으로 변경
}

// 말이 종점에 도달했을 시 깜빡임을 줘서 종료되었음을 알리는 기능
void GameEnd(int x, int y) {
	// 아래의 과정을 3번 반복하여 말이 깜빡이는 듯한 효과를 줌
	for (int i = 0; i < 3; i++) {
		GotoXY(x + 1, y + 1);				// 종료 지점으로 이동
		printf(" ");							// 말을 지우고
		Sleep(500);							// 0.5초 대기 후
		GotoXY(x + 1, y + 1);				// 다시 종료 지점으로 이동
		ClrStr(DARK_RED, "●");	// 말을 출력
		Sleep(500);							// 0.5초 대기
	}
}