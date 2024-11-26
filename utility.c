// 공통으로 사용되는 유틸리티 함수들 처리
#include "utility.h"
#include <windows.h>
#include <stdio.h>
#include "constants.h"
#include <stdbool.h>

// 게임 시작 전 유틸리티 초기화 
void InitGameSet() {
    CursorView(0);                  // 커서를 안보이게 함
    SetConsoleView();             // 콘솔창 설정
}

// 콘솔화면의 지정한 위치로 이동
void GotoXY(int x, int y) {
    COORD Pos = { .X = x, .Y = y };             // 매개변수로 받은 (x, y) 좌푯값으로 값을 설정
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 커서 보임을 결정
void CursorView(char show) {
    CONSOLE_CURSOR_INFO ConsoleCursor = { .bVisible = show, .dwSize = 1 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

// 텍스트 색상 설정
void SetColor(unsigned short text) {
    // unsigned short back 매개변수를 추가하여 배경화면 색상도 변경 가능
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

// 텍스트 색상을 변경하고 다시 원래 색으로 변경
void ClrStr(const char* clr, const char* message) {
    // 바꿀 색상 이름과 색을 바꿀 문자열 입력
    // 색상 변경 후, 휜 색으로 색 변경
    // 변경 후 다른 색상으로 변경 해야할 기능 필요시 수정
    SetColor(clr); printf("%s", message); SetColor(WHITE);
}

// 콘솔화면 설정
void SetConsoleView() {
    system("mode con: cols=120 lines=40");
    system("title Maze Chase [By. ChanMin Park]");
    CursorView(false);
}