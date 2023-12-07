#pragma once
#ifndef _JJUGGUMI_H_
#define _JJUGGUMI_H_

#include <Windows.h>
#include <stdbool.h>

#define PLAYER_MAX		6
#define ITEM_MAX        10
 
////아이템을장착하면스탯증가
typedef struct {
	char name[100];
	int intel_buf, str_buf, stamina_buf;
} ITEM;

 
ITEM item[ITEM_MAX];

typedef struct {
	int id;
	char name[100];

	// 능력치:지능, 힘, 스태미나
	int intel, str, stamina;

	// 현재상태
	bool is_alive;  // 탈락했으면false
	bool hasitem;  // 아이템이있으면true
	ITEM item; // 아이템1개장착가능
} PLAYER;

PLAYER player[PLAYER_MAX];  // 구조체배열



//bool player[PLAYER_MAX];  // 기본값 true, 탈락하면 false
int n_player, n_alive, n_item;
int tick;  // 시계
int ending_choice;
int clear_player;
int die_player;


// 미니게임
void start(void);
void mugunghwa(void);
//void nightgame(void);
void juldarigi(void);
void jebi(void);

int randint(int low, int high);

#endif