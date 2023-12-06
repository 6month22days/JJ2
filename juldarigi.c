#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

#define DIR_UP		0
#define DIR_DOWN	1
#define DIR_LEFT	2
#define DIR_RIGHT	3

void juldarigi(void);
void juldarigi_init(void);

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기

void juldarigi_init(void) {
	map_init(3, 27);
	int x, odd, even;
	odd = 16;
	even = 12;
	for (int i = 0; i < n_player; i++) {
		// 같은 자리가 나오면 다시 생성
		x = 1;

		px[i] = x;
		//back_buf[px[i]][y] = '-';  //13,14,15가 줄
		back_buf[px[i]][13] = '-';
		back_buf[px[i]][14] = '-';
		back_buf[px[i]][15] = '-';
		if (i % 2 == 0 ) {
			py[i] = even;
			even--;
		}
		else{
			py[i] = odd;
			odd++;
		}
		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
}


void juldarigi(void) {
	juldarigi_init();

	juldarigi_play = 1;
	system("cls");
	display();
	gotoxy(0, 14);
	printf(" ");
	gotoxy(2, 14);
	printf(" ");

	while (1) {

		display();
		gotoxy(5, 0);
		printf("str: %4d",0);
		Sleep(10);
			//if (tick % 3000 == 0) {
			//	dialog("초후 게임이 시작됩니다");
			//	break;
			//}
	}
}