// menu.c의 함수 선언 포함
#ifndef MENU_H
#define MENU_H

void ShowButton(int number);
void ShowMenu();
void ShowRule();
int SetLevel();
void PlayGame();
void ExitGame();

void BoxMessege(const char* str, int x, int y);
void BoldBoxMessege(const char* str, int x, int y);

#endif
