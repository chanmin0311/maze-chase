// menu.c의 함수 선언 포함
#ifndef MENU_H
#define MENU_H

void ShowButton(int number);
void show_menu();
void show_rule();
int set_level();
void play_game();
void exit_game();

void BoxMessege(const char* str, int x, int y);
void BoldBoxMessege(const char* str, int x, int y);


#endif
