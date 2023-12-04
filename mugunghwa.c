#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "canvas.h"
#include "jjuggumi.h"
#include "keyin.h"

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];

void mugunghwa(void);
void tick_mugunghwa(void);
void move_manual_M(key_t key);
void move_tail_M(int player, int nx, int ny);
void move_random_M(int player, int dir);
void mugunghwa_clear(int player);

int clear_M[PLAYER_MAX];
int dead_player[PLAYER_MAX] = { 0 };

// ����ȭ 
void tick_mugunghwa(void) {
	// ����ȭ ���� ���
	if (tick == 100) {
		gotoxy(13, 1);
		printf("��");
	}
	else if (tick == 300) {
		gotoxy(13, 4);
		printf("��");
	}
	else if (tick == 700) {
		gotoxy(13, 7);
		printf("ȭ");
	}
	else if (tick == 1100) {
		gotoxy(13, 10);
		printf("��");
	}
	else if (tick == 1500) {
		gotoxy(13, 13);
		printf("��");
	}
	else if (tick == 1800) {
		gotoxy(13, 16);
		printf("��");
	}
	else if (tick == 2000) {
		gotoxy(13, 19);
		printf("��");
	}
	else if (tick == 2100) {
		gotoxy(13, 22);
		printf("��");
	}
	else if (tick == 2300) {
		gotoxy(13, 25);
		printf("��");
	}
	else if (tick == 2500) {
		gotoxy(13, 28);
		printf("��");
		//ī�޶� ��ȯ(�� ���ƺ���)
		back_buf[4][1] = '@';
		back_buf[5][1] = '@';
		back_buf[6][1] = '@';
		back_buf[7][1] = '@';

	}
	else if (tick == 5500) {
		for (int i = 13; i <= 13; i++) {
			for (int j = 0; j <= 30; j++) {
				gotoxy(i, j);
				printf(" ");
			}
		}
		//ī�޶� ��ȯ(�ǵ�����)
		back_buf[4][1] = '#';
		back_buf[5][1] = '#';
		back_buf[6][1] = '#';
		back_buf[7][1] = '#';

		// Ż�� ��Ű��
		for (int i = 0; i < n_player; i++) {
			if (dead_player[i] == 1) {
				back_buf[px[i]][py[i]] = ' ';
				//Ż�� �÷��̾� dialog��  ��Ÿ��
				char dead[] = "   player d dead!     ";
				dead[10] = i + '0';
				dialog(dead);
				dead_player[i] = 0;
			}
		}

		tick = 0;
	}		// player 1 ���ʹ� �������� ������(3����)
	for (int i = 1; i < n_player; i++) {
		if (player[i] == false) {
			continue;
		}
		if (tick % period[i] == 0) {
			if (2500 <= tick && tick <= 5500) {
				//10%Ȯ���� ������
				int out = rand() % 100;
				if (out >= 90) {
					int a = 0;
					//�տ� ' ','@'�̿ܿ� �ٸ����� ��������� �������� ����
					for (int j = 1; j < py[i]; j++) {
						if (back_buf[px[i]][j] != ' ' && back_buf[px[i]][j] != '@') {
							a = 1;
							break;
						}
					}
					move_random_M(i, -1);
					if (a == 1) {
						continue;
					}
					player[i] = false;
					n_alive--;
					dead_player[i] = 1;
				}
			}
			else {
				move_random_M(i, -1);
			}
		}
	}


}

//�� ����
void mugunghwa_init(void) {
	map_init(12, 45);
	int x, y;
	for (int i = 0; i < n_player; i++) {
		// ���� �ڸ��� ������ �ٽ� ����
		x = 1 + i;
		y = 43;

		px[i] = x;
		py[i] = y;
		period[i] = randint(100, 500);

		back_buf[px[i]][py[i]] = '0' + i;  // (0 .. n_player-1)
	}
	//ī�޶� ����
	back_buf[4][1] = '#';
	back_buf[5][1] = '#';
	back_buf[6][1] = '#';
	back_buf[7][1] = '#';


	clear_player = 0;
	tick = 0;
}

//�÷��̾� �̵� 4����
void move_manual_M(key_t key) {
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_UP: dir = 0; break;
	case K_DOWN: dir = 1; break;
	case K_LEFT: dir = 2; break;
	case K_RIGHT: dir = 3; break;
		//case 'q': stop();
	default: return;
	}
	int nx, ny;
	nx = px[0] + dx[dir];
	ny = py[0] + dy[dir];
	if (!placable(nx, ny)) {
		return;
	}

	if (player[0] == false) {
		return;
	}

	move_tail_M(0, nx, ny);
	// 0 player ��  ' ','@'�̿ܿ� �ٸ����� ��������� �������� ����
	if (2500 <= tick && tick <= 5500) {
		for (int j = 1; j < py[0]; j++) {
			if (back_buf[px[0]][j] != ' ' && back_buf[px[0]][j] != '@') {
				return;
			}
		}
		player[0] = false;
		n_alive--;
		dead_player[0] = 1;
	}
}
void move_tail_M(int player, int nx, int ny) {
	int p = player;  // �̸��� ��...
	//back_buf�� ����
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = ' ';
	px[p] = nx;
	py[p] = ny;
	mugunghwa_clear(player);
}
void move_random_M(int player, int dir) {
	int p = player;  // �̸��� ��...
	int nx, ny;  // �������� ������ ���� �ڸ�
	int percent = rand() % 100;
	// 70 % Ȯ���� �����̵�
	if (percent < 70) {
		nx = px[p] + (0);
		ny = py[p] + (-1);
	}
	// 10 % Ȯ���� �����̵�
	else if (percent < 80) {
		nx = px[p] + (-1);
		ny = py[p] + (0);
	}
	// 10 % Ȯ���� �Ʒ����̵�
	else if (percent < 90) {
		nx = px[p] + (1);
		ny = py[p] + (0);
	}
	// 10 % Ȯ���� ���ڸ�
	else {
		nx = px[p] + (0);
		ny = py[p] + (0);
		return;
	}
	if (!placable(nx, ny)) {
		return;
	}
	move_tail_M(p, nx, ny);
}

void mugunghwa_clear(int player) {
	int p = player;
	int dx[6] = { 3, 4, 5, 6, 7, 8 };
	int dy[6] = { 1, 2, 2, 2, 2, 1 };

	// Ŭ������ ������ ���ϱ�
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 6; y++) {
			if (px[p] == dx[x] && py[p] == dy[y]) {
				clear_M[p] = true;
				clear_player++;
				back_buf[px[p]][py[p]] = ' ';
			}
		}
	}
}

void mugunghwa(void) {

	system("cls");
	//�� ����
	mugunghwa_init();
	display();
	while (1) {

		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			ending_choice = 1;
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual_M(key);
		}

		display();
		Sleep(10);
		tick += 10;
		tick_mugunghwa();

		if (n_alive <= 1) {
			break;
		}

	}
}