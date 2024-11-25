// 미로 관련 함수 선언 포함
#ifndef MAZE_H
#define MAZE_H
#define STDBOOL_H
#include<stdbool.h>

typedef struct {
    int width;
    int height;
    int* cells;
} Maze;

Maze* create_maze(int width, int height);
void free_maze(Maze* maze);
int get_cell(Maze* maze, int x, int y);
void set_cell(Maze* maze, int x, int y, int value);
bool in_bounds(Maze* maze, int x, int y);

void binary_tree_algorithm(Maze* maze);
void ellers_algorithm(Maze* maze);
void wilsons_algorithm(Maze* maze);

Maze* generate_maze(int level);
void print_maze(Maze* maze);

bool can_move(Maze* maze, int start_x, int start_y, int direction);

void printMazeChase(int x, int y);

#endif
