#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "jjuggumi.h"
#include "canvas.h"

#define DIALOG_DURATION_SEC		4

void draw(void);
void print_status(void);

// (zero-base) row��, col���� Ŀ�� �̵�
void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// row��, col���� ch ���
void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

// map ����� �ڵ� / (13,6)
void map_init(int n_row, int n_col) {
	// �� ���۸��� ������ ����
	for (int i = 0; i < ROW_MAX; i++) {
		for (int j = 0; j < COL_MAX; j++) {
			back_buf[i][j] = front_buf[i][j] = ' ';
		}
	}

	N_ROW = n_row;
	N_COL = n_col;
	for (int i = 0; i < N_ROW; i++) {
		// ���Թ� �̷��� �� �� �ִµ� �Ϻη� �� ����������
		back_buf[i][0] = back_buf[i][N_COL - 1] = '#';

		for (int j = 1; j < N_COL - 1; j++) {
			back_buf[i][j] = (i == 0 || i == N_ROW - 1) ? '#' : ' ';
		}
	}
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != ' ') {
		return false;
	}
	return true;
}

// ��ܿ� ����, �ϴܿ��� ���� ���¸� ���
void display(void) {
	draw();
	gotoxy(N_ROW + 4, 0);  // �߰��� ǥ���� ������ ������ �ʰ� ����â ������ �� ������ ���
	print_status();
}

void draw(void) {
	for (int row = 0; row < N_ROW; row++) {
		for (int col = 0; col < N_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void print_status(void) {
	printf("no. of players left: %d\n", n_alive);
	if (juldarigi_play == 0) {
		printf("%24s %9s %7s\n", "intl", "str", "stm");
		for (int p = 0; p < n_player; p++) {
			printf("player %2d: %5s %5d(%s%d) %5d(%s%d) %5d%%\n", p, player[p].is_alive ? "alive" : "DEAD",
				player[p].intel, (player[p].item.intel_buf >= 0) ? "+" : "", player[p].item.intel_buf,
				player[p].str, (player[p].item.str_buf >= 0) ? "+" : "", player[p].item.str_buf, player[p].stamina);
		}
	}
	else if (juldarigi_play == 1) {
		for (int p = 0; p < n_player; p++) {
			printf("player %2d: %5s\n", p, player[p].is_alive ? "alive" : "alive*");
		}
	}
}

void dialog(char message[]) {
	char f_buf[ROW_MAX][COL_MAX] = { 0 };

	for (int row = 0; row < ROW_MAX; row++) {
		for (int col = 0; col < COL_MAX; col++) {
			f_buf[row][col] = back_buf[row][col];
		}
	}

	for (int i = DIALOG_DURATION_SEC; i >= 1; i--) {
		gotoxy(5, 12);
		printf("*************************");
		gotoxy(6, 12);
		printf("*%d%s*", i, message);
		gotoxy(7, 12);
		printf("*************************");
		Sleep(1000);
	}

	for (int row = 0; row < ROW_MAX; row++) {
		for (int col = 0; col < COL_MAX; col++) {
			front_buf[row][col] = ' ';
		}
	}
	system("cls");


	for (int row = 0; row < ROW_MAX; row++) {
		for (int col = 0; col < COL_MAX; col++) {
			back_buf[row][col] = f_buf[row][col];
		}
	}
	display();
}