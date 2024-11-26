#include "player.h"
#include "constants.h"

// �̷ο��� �÷��̾��� ���� �����̴� ���
void PrintPlayerPosition(Player* player, int coord_x, int coord_y) {
	// Player����ü�� �̷��� ���� ��ġ ��ǥ�� �ʱ� �Ű����� ������ ����
	GotoXY(coord_x + player->x * 2 + 1, coord_y + player->y + 1);
	// ������ DARK_RED�� ����
	SetColor(DARK_RED);
	printf("��");
	SetColor(WHITE);		// ���� ���� ���� �� �ٽ� ���� �������� ����
}

// ���� ������ �������� �� �������� �༭ ����Ǿ����� �˸��� ���
void GameEnd(int x, int y) {
	// �Ʒ��� ������ 3�� �ݺ��Ͽ� ���� �����̴� ���� ȿ���� ��
	for (int i = 0; i < 3; i++) {
		GotoXY(x + 1, y + 1);				// ���� �������� �̵�
		printf(" ");							// ���� �����
		Sleep(500);							// 0.5�� ��� ��
		GotoXY(x + 1, y + 1);				// �ٽ� ���� �������� �̵�
		ClrStr(DARK_RED, "��");	// ���� ���
		Sleep(500);							// 0.5�� ���
	}
}