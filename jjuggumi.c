
// 2023-2 ������α׷��� ����: �޲ٹ� ����
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include "jjuggumi.h"

#define	DATA_FILE	"jjuggumi.dat"

int jjuggumi_init(void);
void intro(void);

// low �̻� high ���� ������ �߻���Ű�� �Լ�
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

// �÷��̾� �� �Է�
int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("�÷��̾� ��: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	system("cls");
	return 0;
}

//������
void intro(void) {
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#$$$$$$$$$$$$@@@@@\n");
	printf("@@@@@@@$~,,,:#@@@@@@@@*;@@@@@@@~...........,#@@@@\n");
	printf("@@@@@@!,,~:~,,!@@@@@@$,-#@@@@@@~,:;;;;;;;;~.#@@@@\n");
	printf("@@@@@;.:$@@@$-,!@@@@@;..;@@@@@@~-@@@@@@@@@*.#@@@@\n");
	printf("@@@@=,~#@@@@@@~.$@@@#,~~,$@@@@@~-@@@@@@@@@*,#@@@@\n");
	printf("@@@@;,#@@@@@@@=,;@@@:,$$-~@@@@@~,@@@@@@@@@*,#@@@@\n");
	printf("@@@@-:@@@@@@@@@-~@@=,!@@:.*@@@@~,@@@@@@@@@*,#@@@@\n");
	printf("@@@@,;@@@@@@@@@~~##~,$@@#--@@@@~,@@@@@@@@@*,#@@@@\n");
	printf("@@@@-~@@@@@@@@@-~@*,*@@@@*.!@@@~,@@@@@@@@@*,#@@@@\n");
	printf("@@@@;,#@@@@@@@=.:#,~@@@@@@~.#@@~,@@@@@@@@@*,#@@@@\n");
	printf("@@@@=,~#@@@@@@~.=:,=@@@@@@=.;@@~,@@@@@@@@@*,#@@@@\n");
	printf("@@@@@:.:#@@@$~.;=,~@@@@@@@@-,=@~,@@@@@@@@@!,#@@@@\n");
	printf("@@@@@@;,,:;:,,!@:.@@@@@@@@@@-.~#~.~~~~~~~~~,,#@@@\n");
	printf("@@@@@@@#~..,:@@$-,,,,,,,,,,,,-*:,,,,,,,,,,,,#@@@@\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("\n");

	Sleep(1500);
	system("cls");


	int y = 4;
	int x = 10;
	while (y < 42) {
		gotoxy(0, y); printf("*");
		Sleep(10);

		gotoxy(2, 2); printf("���ڸ��� ���� �������� �������� ȯ���մϴ�");

		gotoxy(4, 2); printf("������ �����ϽǷ��� Enter �� �����ֽʽÿ�.");

		gotoxy(7, 16); printf("Press Enter...");

		gotoxy(x, y); printf("*");
		Sleep(10);
		y++;
	}
	int get = getchar();
	system("cls");
}

//����
void ending(void) {
	//����� ���
	if (ending_choice == 1 || clear_player > 1) {
		system("cls");
		for (int i = 0; i < n_player; i++) {
			if (player[i]) {
				i++;
			}
		}
		printf("����ڸ� ������ ���߽��ϴ�.\n\n");
		printf("��Ƴ��� �÷��̾� : ");

		for (int i = 0; i < n_player; i++) {
			if (player[i]) {
				printf(" %d", i);
			}
		}
	}

	//q�� ����
	else {
		system("cls");

		printf("***** ȯ���մϴ�. *****\n");

		for (int i = 0; i < n_player; i++) {
			if (player[i]) {
				printf(" %d�� ����� ����� �����մϴ�. \n", i);
			}
		}
		printf("\n");

		printf(".");
		Sleep(1000);
		printf(".");
		Sleep(1000);
		printf(".");
		Sleep(1000);
		system("cls");
		printf("***** �׷� ��ſ��� ���ñ��� �帮�ڽ��ϴ�. *****\n\n");
		printf("������ �׸� �Ͻðڽ��ϱ�? �ƴϸ� ����Ͻðڽ��ϱ�?\n");
		printf("\n");
		printf("             Yes = 'Y' or No = 'N'    \n");
		printf("\n");
		printf("                 �������ֽ���!     \n\n");

	}
}


void stop(void) {
	system("cls");
	for (int i = 0; i < n_player; i++) {
		if (player[i]) {
			i++;
		}
	}
	printf("����ڸ� ������ ���߽��ϴ�.\n\n");
	printf("��Ƴ��� �÷��̾� : ");

	for (int i = 0; i < n_player; i++) {
		if (player[i]) {
			printf(" %d", i);
		}
	}
}

int main(void) {
	//intro();
	jjuggumi_init();
	start();
	mugunghwa();
	//nightgame();
	//juldarigi();
	//jebi();
	ending();
	return 0;
}