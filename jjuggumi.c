
// 2023-2 고급프로그래밍 과제: 쭈꾸미 게임
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

// low 이상 high 이하 난수를 발생시키는 함수
int randint(int low, int high) {
	int rnum = rand() % (high - low + 1) + low;
	return rnum;
}

// 플레이어 수 입력
int jjuggumi_init(void) {
	srand((unsigned int)time(NULL));

	printf("플레이어 수: ");
	scanf_s("%d", &n_player);

	n_alive = n_player;
	for (int i = 0; i < n_player; i++) {
		player[i] = true;
	}
	system("cls");
	return 0;
}

//오프닝
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

		gotoxy(2, 2); printf("이자리에 오신 여러분을 진심으로 환영합니다");

		gotoxy(4, 2); printf("게임을 진행하실려면 Enter 를 눌러주십시오.");

		gotoxy(7, 16); printf("Press Enter...");

		gotoxy(x, y); printf("*");
		Sleep(10);
		y++;
	}
	int get = getchar();
	system("cls");
}

//엔딩
void ending(void) {
	//우승자 출력
	if (ending_choice == 1 || clear_player > 1) {
		system("cls");
		for (int i = 0; i < n_player; i++) {
			if (player[i]) {
				i++;
			}
		}
		printf("우승자를 가리지 못했습니다.\n\n");
		printf("살아남은 플레이어 : ");

		for (int i = 0; i < n_player; i++) {
			if (player[i]) {
				printf(" %d", i);
			}
		}
	}

	//q로 종료
	else {
		system("cls");

		printf("***** 환영합니다. *****\n");

		for (int i = 0; i < n_player; i++) {
			if (player[i]) {
				printf(" %d번 당신의 우승을 축하합니다. \n", i);
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
		printf("***** 그런 당신에게 선택권을 드리겠습니다. *****\n\n");
		printf("게임을 그만 하시겠습니까? 아니면 계속하시겠습니까?\n");
		printf("\n");
		printf("             Yes = 'Y' or No = 'N'    \n");
		printf("\n");
		printf("                 선택해주시죠!     \n\n");

	}
}


void stop(void) {
	system("cls");
	for (int i = 0; i < n_player; i++) {
		if (player[i]) {
			i++;
		}
	}
	printf("우승자를 가리지 못했습니다.\n\n");
	printf("살아남은 플레이어 : ");

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