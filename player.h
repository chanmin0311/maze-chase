#ifndef PLAYER_H
#define PLAYER_H

// �÷��̾� ����ü
typedef struct {
	int x;			// ���� x��ǥ
	int y;			// ���� y ��ǥ
} Player;

void PrintPlayerPosition(Player* player, int coord_x, int coord_y);
void GameEnd(int x, int y);

#endif 
