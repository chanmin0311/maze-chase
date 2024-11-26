// �޴��� ���õ� ���� ó��
#include "menu.h"
#include "utility.h"
#include "maze.h"
#include "constants.h"

// Ȩȭ���� ���� ������ ��ư���� �����ִ� ���
void ShowButton(int number) {
	// number �� ��ư�� ��ȣ��

	// ù��° ��ư ���� ��
	if (number == 0) {
		// �� ��ư�� ��Ŀ�� �Ǹ� �ʷϻ� ���� �ڽ� ���
		SetColor(GREEN);
		BoldBoxMessege("����", 44, 20);
		SetColor(WHITE);
	}
	else {
		// �ٸ� ��ư���� ��Ŀ���� �Ű����� ���� �ڽ� ���
		BoxMessege("����", 44, 20);
	}

	if (number == 1) {
		// �� ��ư�� ��Ŀ�� �Ǹ� ��ο� �ϴû� ���� �ڽ� ���
		SetColor(DARK_SKYBLUE);
		BoldBoxMessege("����", 54, 20);
		SetColor(WHITE);
	}
	else {
		// �ٸ� ��ư���� ��Ŀ���� �Ű����� ���� �ڽ� ���
		BoxMessege("����", 54, 20);
	}

	if (number == 2) {
		// �� ��ư�� ��Ŀ�� �Ǹ� ��ο� ������ ���� �ڽ� ���
		SetColor(DARK_RED);
		BoldBoxMessege("����", 64, 20);
		SetColor(WHITE);
	}
	else {
		// �ٸ� ��ư���� ��Ŀ���� �Ű����� ���� �ڽ� ���
		BoxMessege("����", 64, 20);
	}
}

// ���� ���۽� ó�� ���̴� Ȩȭ���� �����ִ� ���
void ShowMenu() {
	// Ư�� ��ư�� ��Ŀ�� �Ǿ����� Ȯ���ϱ� ���� ��ȣ�� 0������ ���������Ƿ�
	// �ʱⰪ�� -1�� ����
	int button_number = -1;

	while (1) {
		// Ű���� �Է� ����
		if (_kbhit()) {
			// Ű���� �Է� �� ����
			int nkey = _getch();
			// 1�� ��ư(����)�� ��Ŀ���� �Ǿ��ְ� ���� Ű���� ���� enter�� ���
			if (button_number == 0 && nkey == ENTER) {
				PlayGame();		// ���� ����
			}
			// 2�� ��ư(����)�� ��Ŀ���� �Ǿ��ְ� ���� Ű���� ���� enter�� ���
			if (button_number == 1 && nkey == ENTER) {
				ShowRule();		// ��Ģ ����
			}
			// 3�� ��ư(����)�� ��Ŀ���� �Ǿ��ְ� ���� Ű���� ���� enter�� ���
			if (button_number == 2 && nkey == ENTER) {
				ExitGame();		// ���� ����
			}

			// ����Ű�� ȭ��ǥ ����Ű���� �켱 ����
			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
					// ���� ����Ű �Է� ��
				case LEFT:
					// ���� �ʱ갪�̰ų� ù��° ��ư�� ��Ŀ���� �Ǿ��ִ� ��Ȳ����
					// ���� ȭ��ǥ�� �ԷµǸ� ��ư�� ��Ŀ���� ���� ������ ��ư���� �ű�
					if (button_number == -1 || button_number == 0) button_number = 2;
					// �װ� �ƴ� ��쿣 �� ĭ�� �������� ��Ŀ���� �ű�
					else button_number = (button_number - 1);
					break;
					// ������ ����Ű �Է� ��
				case RIGHT:
					// ��ư�� ��Ŀ���� ���������� �ű�
					// ������ ��ư�� ��Ŀ���� �Ǿ��ְ� ������ ����Ű �Է��� ��������
					// �� �̻� ���������� �̵� �� ��ư�� �����Ƿ� ù��° ��ư���� ��Ŀ���� �־���
					// ������ ��ư�� ��Ŀ���� �ξ��� ���� button_number �� 2�� ����̰� 
					// �� ���¿��� ������ ����Ű���� ������ 1�� �����ְ� 
					// 3���� ���� ������ ��, 0�� �ٽ� button_number�� ������ �����ϸ� ù��° ��ư���� ��Ŀ���� ���� ��
					button_number = (button_number + 1) % 3;
					break;
				}
			}
		}

		// ��ư ���
		ShowButton(button_number);
		// ���� �ΰ� �Ű������� ��ǥ���� ���
		PrintMazeChase(19, 10);
		// ���� ���
		GotoXY(45, 25); ClrStr(YELLOW, "���� : �� or ��   ���� : ENTER");
		GotoXY(101, 0); ClrStr(YELLOW, "[by michin_chanmin]");
	}
}

// ��Ģ ����
void ShowRule() {
	// ȭ�� �����
	system("cls");

	// ���� ���� ���� ���� ���
	BoxMessege("�޴��� ����", 45, 2);
	GotoXY(45, 6);
	ClrStr(GREEN, "PLAY"); printf(" : ������ �����ϰ� ������ �����մϴ�.");
	GotoXY(45, 7);
	ClrStr(DARK_SKYBLUE, "RULE"); printf(" : ���� ����� Ȯ���մϴ�.");
	GotoXY(45, 8);
	ClrStr(DARK_RED, "EXIT"); printf(" : ������ �����մϴ�.");

	BoxMessege("�÷��� ���", 45, 11);
	GotoXY(45, 15);
	printf("1. "); ClrStr(GREEN, "PLAY"); printf(" ��ư�� �����մϴ�.");
	GotoXY(45, 16);
	printf("2. ������ �����մϴ�");
	GotoXY(45, 17);
	printf("3. ȭ�鿡 �̷ΰ� �����˴ϴ�.");
	GotoXY(45, 18);
	printf("4. S�� �����, E�� �����Դϴ�.");
	GotoXY(45, 19);
	printf("5. ����Ű�� ���� ������ �̷θ� Ż���մϴ�.");


	GotoXY(45, 22);
	SetColor(YELLOW); printf("Ȯ���ϼ����� ENTER�� ��������. . ."); SetColor(WHITE);
	// enterŰ �Է½� ����ȭ�� ���ư���
	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (nkey == ENTER) {
				system("cls");
				break;
			}
		}
	}
}

// ���� ������ �̷� ���
int SetLevel() {
	system("cls");

	GotoXY(52, 3);
	ClrStr(YELLOW, "���� �����ϱ�");

	GotoXY(0, 0);
	ClrStr(YELLOW, "���� : �� OR ��");
	GotoXY(15, 0);
	ClrStr(YELLOW, "���� : Enter");
	GotoXY(0, 1);
	ClrStr(YELLOW, "Ȩ : ESC");

	PrintMazeChase(19, 21);

	int user_lever_choice = 0;

	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			// ���õ� ������ ������
			if (user_lever_choice == 1 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 2 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 3 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 4 && nkey == ENTER) return user_lever_choice;
			if (user_lever_choice == 5 && nkey == ENTER) return user_lever_choice;
			if (nkey == ESC) {
				system("cls");
				ShowMenu();
			}

			// show_menu�Լ����� ��ư�� �����ϴ� ��ɰ� ���� ����
			// ������ �� �� ����Ű�� �ƴ� �� �� ����Ű�� ����
			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
				case UP:
					if (user_lever_choice == 0 || user_lever_choice == 1) user_lever_choice = 5;
					else user_lever_choice -= 1;
					break;
				case DOWN:
					user_lever_choice = (user_lever_choice + 1) % 5;
					if (user_lever_choice == 0) user_lever_choice = 5;
					break;
				}
			}
		}
		int x = 48;
		int y = 5;

		// ��Ŀ���� ������ ���� ���� �ٸ� ����� �׵θ��� �β��� �Ͽ� ����Ͽ�
		// ���� ȿ���� ���̵��� ��
		if (user_lever_choice == 1) {
			// ���� 1�� ��Ŀ�� �Ǿ����� ���� �ٲ��� �ʰ� �׵θ��� �β��� ���̵��� ��
			BoldBoxMessege("Lv. 1 : 10 by 10", x, y);
		}
		else {
			BoxMessege("Lv. 1 : 10 by 10", x, y);
		}

		if (user_lever_choice == 2) {
			SetColor(DARK_YELLOW);
			BoldBoxMessege("Lv. 2 : 15 by 15", x, y + 3);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 2 : 15 by 15", x, y + 3);
		}

		if (user_lever_choice == 3) {
			SetColor(GREEN);
			BoldBoxMessege("Lv. 3 : 20 by 20", x, y + 6);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 3 : 20 by 20", x, y + 6);
		}

		if (user_lever_choice == 4) {
			SetColor(DARK_RED);
			BoldBoxMessege("Lv. 4 : 25 by 25", x, y + 9);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 4 : 25 by 25", x, y + 9);
		}

		if (user_lever_choice == 5) {
			SetColor(VIOLET);
			BoldBoxMessege("Lv. 5 : 30 by 30", x, y + 12);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Lv. 5 : 30 by 30", x, y + 12);
		}
	}
	return user_lever_choice;
}

// ���� ����
void PlayGame() {
	system("cls");

	// set_level���� ������ ������ ������ ����
	int level = SetLevel();

	// ������ ��ȿ�� ���� ���� �����̶��
	if (level >= 1 && level <= 5) {
		// �ش� ������ �̷θ� ������
		Maze* maze = GenerateMaze(level);
		// �̷� ������ ���н� ���� �޼��� ��� �� 3�� ��� �� ���α׷� ����
		if (!maze) {
			system("cls");
			BoxMessege("�̷� ���� ����", 49, 10);
			Sleep(3000);
			ShowMenu();
		}
		// �̷� ���� ��
		else {
			system("cls");
			// �̷� ���
			PrintMaze(maze);
			// �޸� �ݳ�
			free(maze);
		}
	}
}

// ���� ����
void ExitGame() {				
	system("cls");
	// ���� ���� �޼��� ���
	GotoXY(52, 12); printf("�����Ͻðڽ��ϱ�?");

	// ��� ��ư�� ��Ŀ���� �ΰ� �� ����
	// ��ư�� ��ȣ�� 0���� ����, button_number�� 0���� �����ϸ� ����Ʈ�� ���� ù(����) ��ư�� ��Ŀ��
	// ��� ��ư���� ��Ŀ���� �ΰ� �ϰ� ���� �ʴٸ� -1�� ����
	int button_number = -1;
	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (button_number == 0 && nkey == ENTER) {				// 0�� ��ư�� ��Ŀ�� �Ǿ��ְ� Enter�� ������
				system("cls");																// ȭ���� �����
				exit(1);																			// ���α׷��� �����Ŵ
			}
			if (button_number == 1 && nkey == ENTER) {					// 1�� ��ư�� ��Ŀ�� �Ǿ� �ְ� Enter�� ������
				system("cls");																// ȭ���� �����												
				break;																			// menuȭ������ ���ư�
			}
			// ����Ű�� ��ư�� ����
			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
				case LEFT:				// �Է��� ���� ����Ű�� ���			
					// button_number�� �ʱ� ���� �̰ų�
					// ���� ��ư �������� ���ʿ� �� �̻� ��ư�� ���� ���
					// ���� ���� ��ư(1�� ��ư)���� �̵���
					if (button_number == -1 || button_number == 0) button_number = 1;
					// button_number�� �ϳ� ���� ��Ŵ
					else button_number -= button_number;
					break;
				case RIGHT:				// �Է��� ������ ����Ű�� ���
					// button_number�� ũ�⸦ �ϳ��� ���� ��Ŵ
					// ��ư�� �ִ� ������ �Ѿ� �� ��츦 �����
					// ���� �� ��ư�� ���� ��ŭ ������ ������ ����
					button_number = (button_number + 1) % 2;
					break;
				}
			}
		}

		// ��Ŀ���� ��ư�� ���� ����� �ڽ��� ���⸦ �ٸ��� �Ͽ� ����ȿ���� ��
		if (button_number == 0) {
			SetColor(RED);
			BoldBoxMessege("Y", 52, 14);
			SetColor(WHITE);
		}
		else {
			BoxMessege("Y", 52, 14);
		}

		if (button_number == 1) {
			SetColor(GREEN);
			BoldBoxMessege("N", 62, 14);
			SetColor(WHITE);
		}
		else {
			BoxMessege("N", 62, 14);
		}
	}
}

// �ڽ� ���� �޼��� ���
void BoxMessege(const char* str, int x, int y) {		// �޼����� �ڽ� �޼����� ����� ��ġ�� x, y ��ǥ���� �Ű������� ����
	int boxWidth = strlen(str) + 6; // �޼����� ���̿� �¿� ���� ����  2ĭ, �޼��� �׵θ� �¿� ���� 1ĭ �� 6ĭ �߰��� Ȯ������
	int maxRow = 3;			// �ڽ��� ���ڿ� 1�ٰ� �ڽ� �� �Ʒ��� �����Ͽ� �� 3�ٸ� ���


	// �ڽ� ���� ���
	GotoXY(x, y);													// �Ű������� ���޹��� ��ġ�� �̵�
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("��");									// ���� ���� ���� �𼭸� ���							
		else if (i == boxWidth - 1) printf("��");		// ���� ���� ������ �𼭸� ���
		else printf("��");											// �𼭸��� �̾��ִ� �� ���
	}

	// �ڽ� ���� ���ڿ��� �׵θ� ���
	GotoXY(x, y + 1);												// �ʱ� ��ġ���� ��ĭ ������
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("��");									// �ڽ��� ���� ��
		else if (i == boxWidth - 1) printf("��");		// �ڽ��� ������ ��
		else if (i == 1)printf("  %s  ", str);					// �޼��� ���
	}

	// �ڽ� �غ� ���
	GotoXY(x, y + 2);												// �ʱ� ��ġ���� ��ĭ ������
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("��");									// ���� �Ʒ��� ���� �𼭸� ���
		else if (i == boxWidth - 1) printf("��");		// ���� �Ʒ��� ������ �𼭸� ���
		else printf("��");											// �𼭸��� �̾��ִ� �� ���
	}
}

// ���� �ڽ� �޼��� ���
void BoldBoxMessege(const char* str, int x, int y) {			// BoxMessege�� ������ �Ű�����
	int boxWidth = strlen(str) + 6; // �޼����� ���̿� �¿� ���� ����  2ĭ, �޼��� �׵θ� �¿� ���� 1ĭ �� 6ĭ �߰��� Ȯ������
	int maxRow = 3;			// �ڽ��� ���ڿ� 1�ٰ� �ڽ� �� �Ʒ��� �����Ͽ� �� 3�ٸ� ���

	// �ڽ� ���� ���
	GotoXY(x, y);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("��");									// ���� ���� ���� �𼭸� ���							
		else if (i == boxWidth - 1) printf("��");		// ���� ���� ������ �𼭸� ���
		else printf("��");											// �𼭸��� �̾��ִ� �� ���
	}

	// �ڽ� ���� ���ڿ��� �׵θ� ���
	GotoXY(x, y + 1);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("��");									// �ڽ��� ���� ��
		else if (i == boxWidth - 1) printf("��");		// �ڽ��� ������ ��
		else if (i == 1)printf("  %s  ", str);
	}

	// �ڽ� �غ� ���
	GotoXY(x, y + 2);
	for (int i = 0; i < boxWidth; i++) {
		if (i == 0) printf("��");									// ���� �Ʒ��� ���� �𼭸� ���
		else if (i == boxWidth - 1) printf("��");		// ���� �Ʒ��� ������ �𼭸� ���
		else printf("��");											// �𼭸��� �̾��ִ� �� ���
	}
}