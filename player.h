#ifndef PLAYER_H
#define PLAYER_H

// 플레이어 구조체
typedef struct {
	int x;			// 말의 x좌표
	int y;			// 말의 y 좌표
} Player;

void PrintPlayerPosition(Player* player, int coord_x, int coord_y);
void GameEnd(int x, int y);

#endif 
