#ifndef CONSTANTS_H
#define CONSTANTS_H

// 방향키 및 키보드 입력 관련 상수
#define ARROW 224
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32
#define ENTER 13
#define ESC 27

// 미로 게임 관련 상수
#define MAX_SIZE 30
#define NORTH 1  // 00001
#define SOUTH 2  // 00010
#define EAST 4   // 00100
#define WEST 8   // 01000
#define VISITED 16  // 10000
#define END 32      // 100000
#define START 64    // 1000000

// 색상 코드
enum COLOR {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VIOLET,
    DARK_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

#endif
