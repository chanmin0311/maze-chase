// 공통으로 사용되는 유틸리티 함수들 처리
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
    // 바꿀 색상 이름과 색을 바꿀 문자열 입력
    // 색상 변경 후, 휜 색으로 색 변경
    // 변경 후 다른 색상으로 변경 해야할 기능 필요시 수정
    SetColor(clr); printf("%s", message); SetColor(WHITE);
}

void SetConsoleView() {
    system("mode con: cols=120 lines=40");
    system("title Maze Chase [By. ChanMin Park]");
    CursorView(false);
}
