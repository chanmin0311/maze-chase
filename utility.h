// utility.c�� �Լ� ���� ����
#ifndef UTILITY_H
#define UTILITY_H

void InitGameSet();
void GotoXY(int x, int y);
void CursorView(char show);
void SetColor(unsigned short text);
void ClrStr(const char* clr, const char* msg);
void SetConsoleView();

#endif
