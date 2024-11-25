#include "player.h"
#include "constants.h"

void print_player_position(Player* player, int coord_x, int coord_y) {
	GotoXY(coord_x + player->x * 2 + 1, coord_y + player->y + 1);
	SetColor(DARK_RED);
	printf("¡Ü");
	SetColor(WHITE);
}

void game_end(int x, int y) {
	for (int i = 0; i < 3; i++) {
		GotoXY(x + 1, y + 1);
		printf(" ");
		Sleep(500);
		GotoXY(x + 1, y + 1);
		ClrStr(DARK_RED, "¡Ü");
		Sleep(500);
	}
}