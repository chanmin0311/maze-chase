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

// 해당 상수의 2진수 값
#define NORTH 1          // 1
#define SOUTH 2          // 10
#define EAST 4            // 100
#define WEST 8           // 1000
#define VISITED 16      // 10000
#define END 32           // 100000
#define START 64        // 1000000

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
