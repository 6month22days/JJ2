#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h> //      ���� ���񿡼� �� �͵� : 1. ���帶�� �÷��̾� ǥ��, 2. �� ��� ����, 3. ��� ���̱�

#define DIR_LEFT	2
#define DIR_RIGHT	3
#define DIR_SPACE	4

int px[PLAYER_MAX], py[PLAYER_MAX], period[PLAYER_MAX];

void jebi_init();
void jebi();
void print_status_J(void);
void move_manual_J(key_t key);
void move_tail_J(int player, int nx, int ny);
bool placable_J(int row, int col);

void jebi_shuf(void);
void jebi_pick(void);

void jebi_pick(void) {
	char str2[50];
}


void jebi_shuf(void) {
	int a = randint(1, n_alive);
	if (a == 1) {
		dialog(2,"pass");
	}
	else {
		dialog(2,"dead");
	}
}

void jebi_init() {
	map_init(9, 20);
	for (int i = 0; i < n_alive; i++) {
		// ���� �ڸ��� ������ �ٽ� ����

		back_buf[4][4 + 2 * i] = '?';
	}
	px[0] = 4;
	py[0] = 4;
	back_buf[px[0]][py[0]] = '@';
}

void print_status_J() { // round �ø���, �ش� ���� �÷��̾� �̸� ���
	gotoxy(N_ROW, 0);
	int n = 1;
	printf("round %d, turn: player %d", n, n_alive);
}

void move_manual_J(key_t key) {
	// �� �������� ������ �� x, y�� delta
	static int dx[4] = { -1, 1, 0, 0 };
	static int dy[4] = { 0, 0, -1, 1 };

	int dir;  // ������ ����(0~3)
	switch (key) {
	case K_LEFT: dir = DIR_LEFT; break;
	case K_RIGHT: dir = DIR_RIGHT; break;
	case K_SPACE: dir = DIR_SPACE; break;
	default: return;
	}

	// �������� ���� �ڸ�
	int nx, ny;
	nx = px[0];
	ny = py[0] + dy[dir]*2;
	if (!placable_J(nx, ny)) {
		return;
	}

	move_tail_J(0, nx, ny);
}

void move_tail_J(int player, int nx, int ny) {
	int p = player;  // �̸��� ��...
	back_buf[nx][ny] = back_buf[px[p]][py[p]];
	back_buf[px[p]][py[p]] = '?';
	px[p] = nx;
	py[p] = ny;
}

// back_buf[row][col]�� �̵��� �� �ִ� �ڸ����� Ȯ���ϴ� �Լ�
bool placable_J(int row, int col) {
	if (row < 0 || row >= N_ROW ||
		col < 0 || col >= N_COL ||
		back_buf[row][col] != '?') {
		return false;
	}
	return true;
}

void jebi() {
	// while (n_alive == 1) {} // - �Ѹ� ���������� �ݺ���Ű��
	jebi_init();
	system("cls");
	display();

	print_status_J();
	while (1) {
		// player 0�� ������ ������(4����)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key == K_SPACE) {
			jebi_shuf();
		}
		else if (key != K_UNDEFINED) {
			move_manual_J(key);
		}

		display();
		Sleep(10);
		tick += 10;
	}
}
