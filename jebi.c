#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>

void jebi_init();
void jebi();

void jebi_init() {
	map_init(14, 25);
	int x, y;
	for (int i = 0; i < n_alive; i++) {
		// 같은 자리가 나오면 다시 생성

		back_buf[6][3 + 2 * i] = '*';
	}

	tick = 0;
}

void  jebi() {
	jebi_init();

	system("cls");
	display();
	while (1) {
		// player 0만 손으로 움직임(4방향)
		key_t key = get_key();
		if (key == K_QUIT) {
			break;
		}
		else if (key != K_UNDEFINED) {
			move_manual(key);
		}

		display();
		Sleep(10);
		tick += 10;
	}
}
