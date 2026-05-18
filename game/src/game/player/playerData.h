#pragma once 
#include<DxLib.h>

enum tagPlayerName
{
	PLAYER_NONE = -1,	//何もなし(初期化用)
	PLAYER_1,			//プレイヤー1
	PLAYER_2,			//プレイヤー2
	PLAYER_3,			//プレイヤー3
	PLAYER_4,			//プレイヤー4

	PLAYER_NUM,			//プレイヤーの数
};

static const int PLAYER_COLOR[PLAYER_NUM] =
{
	GetColor(255,0,0),
	GetColor(0,0,255),
	GetColor(255,50,255),
	GetColor(255,255,50),
};

