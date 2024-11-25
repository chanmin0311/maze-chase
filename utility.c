// �������� ���Ǵ� ��ƿ��Ƽ �Լ��� ó��
#include "utility.h"
#include <windows.h>
#include <stdio.h>
#include "constants.h"
#include <stdbool.h>

void InitGameSet() {
    CursorView(0);
    SetConsoleView();
}

void GotoXY(int x, int y) {
    COORD Pos = { .X = x, .Y = y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(char show) {
    CONSOLE_CURSOR_INFO ConsoleCursor = { .bVisible = show, .dwSize = 1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void SetColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void ClrStr(const char* clr, const char* message) {
    // �ٲ� ���� �̸��� ���� �ٲ� ���ڿ� �Է�
    // ���� ���� ��, �� ������ �� ����
    // ���� �� �ٸ� �������� ���� �ؾ��� ��� �ʿ�� ����
    SetColor(clr); printf("%s", message); SetColor(WHITE);
}

void SetConsoleView() {
    system("mode con: cols=120 lines=40");
    system("title Maze Chase [By. ChanMin Park]");
    CursorView(false);
}
