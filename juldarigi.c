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
void juldarigi_tick(void);
void juldarigi_move(void);

int down1 = 0;
int down2 = 0;
int power = 0;
int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기
float juldarigi_pow;

void juldarigi_move(void) {
	int p = player;  // 이름이 길어서...
	if (juldarigi_pow <= 0) { // 오른쪽힘이 더 강함
		//back_buf에 저장
		for (int i = 0; i < n_player; i++) {
			back_buf[px[1]][py[i]] = back_buf[px[1]][py[i]-1];//이동할 위치
			back_buf[px[1]][py[i]] = back_buf[px[1]][py[i]];//이동전 위치
		}
	}
	else{                   // 왼쪽힘이 더 강함
		//back_buf에 저장
		for (int i = 0; i < n_player; i++) {
			back_buf[px[1]][py[i]] = back_buf[px[1]][py[i]+1];//이동할 위치
			back_buf[px[1]][py[i]] = back_buf[px[1]][py[i]];//이동전 위치
		}
	}
}

void juldarigi_tick(void) {
	key_t key = get_key();
	if (tick % 1000 == 0) {   //1초마다 당겨짐
		juldarigi_move();
	}
	else if (2000 <= tick && tick <= 3000) {
		if (key == K_EVEN) {
			juldarigi_pow -= 1;
		}
		if (key == K_ODD) {
			juldarigi_pow += 1;
		}
	}
	if (tick % 3000 == 0) {
		tick = 0;
		juldarigi_pow = power;
	}
}

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
	tick = 0;
}
void players_pow(void);
float odd_pow = 0;
float even_pow = 0;

void players_pow(void) {
	for (int i = 0; i < n_player; i++) {
		if (i % 2 == 0) {
			if (player[i].hasitem == true) {
				even_pow += player[i].item.str_buf;
			}
			even_pow += player[i].str;
		}
		else{
			if (player[i].hasitem == true) {
				odd_pow += player[i].item.str_buf;
			}
			odd_pow += player[i].str;
		}
	}
	juldarigi_pow = even_pow - odd_pow;
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
	players_pow();
	power = juldarigi_pow;

	while (1) {

		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (down1 == 0) {
			if (key == K_L_DOWN) {
				even_pow *= 2;
				gotoxy(3, 0);
				printf("왼쪽팀 눕기중");
				players_pow();
				down1 = 1;
			}
		}
		else if (down2 == 0) {
			if (key == K_R_DOWN) {
				odd_pow *= 2;
				gotoxy(4, 0);
				printf("오른쪽팀 눕기중");
				players_pow();
				down2 = 1;
			}
		}

		display();
		gotoxy(5, 0);
		printf("str: %5.1f    ", juldarigi_pow);

		juldarigi_tick();
		tick += 10;
		Sleep(10);
	}
}