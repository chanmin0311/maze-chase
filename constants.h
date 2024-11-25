#ifndef CONSTANTS_H
#define CONSTANTS_H

// ����Ű �� Ű���� �Է� ���� ���
#define ARROW 224
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32
#define ENTER 13
#define ESC 27

// �̷� ���� ���� ���
#define MAX_SIZE 30
#define NORTH 1  // 00001
#define SOUTH 2  // 00010
#define EAST 4   // 00100
#define WEST 8   // 01000
#define VISITED 16  // 10000
#define END 32      // 100000
#define START 64    // 1000000

// ���� �ڵ�
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
