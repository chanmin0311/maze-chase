// �������� ���Ǵ� ��ƿ��Ƽ �Լ��� ó��
#include "utility.h"
#include <windows.h>
#include <stdio.h>
#include "constants.h"
#include <stdbool.h>

// ���� ���� �� ��ƿ��Ƽ �ʱ�ȭ 
void InitGameSet() {
    CursorView(0);                  // Ŀ���� �Ⱥ��̰� ��
    SetConsoleView();             // �ܼ�â ����
}

// �ܼ�ȭ���� ������ ��ġ�� �̵�
void GotoXY(int x, int y) {
    COORD Pos = { .X = x, .Y = y };             // �Ű������� ���� (x, y) ��ǩ������ ���� ����
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Ŀ�� ������ ����
void CursorView(char show) {
    CONSOLE_CURSOR_INFO ConsoleCursor = { .bVisible = show, .dwSize = 1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

// �ؽ�Ʈ ���� ����
void SetColor(unsigned short text) {
    // unsigned short back �Ű������� �߰��Ͽ� ���ȭ�� ���� ���� ����
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

// �ؽ�Ʈ ������ �����ϰ� �ٽ� ���� ������ ����
void ClrStr(const char* clr, const char* message) {
    // �ٲ� ���� �̸��� ���� �ٲ� ���ڿ� �Է�
    // ���� ���� ��, �� ������ �� ����
    // ���� �� �ٸ� �������� ���� �ؾ��� ��� �ʿ�� ����
    SetColor(clr); printf("%s", message); SetColor(WHITE);
}

// �ܼ�ȭ�� ����
void SetConsoleView() {
    system("mode con: cols=120 lines=40");
    system("title Maze Chase [By. ChanMin Park]");
    CursorView(false);
}