// 미로 관련 함수 선언 포함
#ifndef MAZE_H
#define MAZE_H
#define STDBOOL_H
#include<stdbool.h>

// 미로 구조체
typedef struct {
    int width;          // 미로의 가로 길이
    int height;         // 미로의 세로 길이
    int* cells;          // cell 
} Maze;

Maze* CreateMaze(int width, int height);
void FreeMaze(Maze* maze);
int GetCell(Maze* maze, int x, int y);
void SetCell(Maze* maze, int x, int y, int value);
bool InBounds(Maze* maze, int x, int y);

void BinaryTreeAlgorithm(Maze* maze);
void EllersAlgorithm(Maze* maze);
void WilsonsAlgorithm(Maze* maze);

Maze* GenerateMaze(int level);
void PrintMaze(Maze* maze);

bool CanMove(Maze* maze, int start_x, int start_y, int direction);

void PrintMazeChase(int x, int y);

#endif
