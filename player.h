#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
	int x;
	int y;
} Player;

void print_player_position(Player* player, int coord_x, int coord_y);
void game_end(int x, int y);

#endif 
