#pragma once
#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		6
#define ITEM_MAX        10
 
////�������������ϸ齺������
typedef struct {
	char name[100];
	int intel_buf, str_buf, stamina_buf;
} ITEM;

 
ITEM item[ITEM_MAX];

typedef struct {
	int id;
	char name[100];

	// �ɷ�ġ:����, ��, ���¹̳�
	int intel, str, stamina;

	// �������
	bool is_alive;  // Ż��������false
	bool hasitem;  // ��������������true
	ITEM item; // ������1����������
} PLAYER;

PLAYER player[PLAYER_MAX];  // ����ü�迭



//bool player[PLAYER_MAX];  // �⺻�� true, Ż���ϸ� false
int n_player, n_alive, n_item;
int tick;  // �ð�
int ending_choice;
int clear_player;
int die_player;


// �̴ϰ���
void start(void);
void mugunghwa(void);
//void nightgame(void);
void juldarigi(void);
void jebi(void);

int randint(int low, int high);

#endif