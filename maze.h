// �̷� ���� �Լ� ���� ����
#ifndef MAZE_H
#define MAZE_H
#define STDBOOL_H
#include<stdbool.h>

// �̷� ����ü
typedef struct {
    int width;          // �̷��� ���� ����
    int height;         // �̷��� ���� ����
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
