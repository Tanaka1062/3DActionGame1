#pragma once
#include <DxLib.h>

//定義関連----------------------

static const int WINDOW_SIZE_X = 1280;			//ウィンドウサイズ横
static const int WINDOW_SIZE_Y = 720;				//ウィンドウサイズ縦

static const VECTOR ZERO = { 0.0f,0.0f,0.0f };	//VECTORの初期化用

//------------------------------

//アイテムの名前
enum tagItemName
{
	ITEM_NONE = -1,			//何もない			
	ITEM_FIRE_RING,			//ファイアリング
	ITEM_HARB_AMULENT,		//薬草のお守り

	ITEM_NUM,				//アイテムの種類
};
//アイテムのタイプ
enum tagItemType
{
	ITEM_TYPE_NONE = -1,	//何もないタイプ
	ITEM_TYPE_SHOT,			//弾発射タイプ
	ITEM_TYPE_USE,			//使用タイプ
	ITEM_TYPE_SKILL,		//スキルタイプ
};


