#pragma once
#include "controllerInput.h"

//コントローラーのID一覧
enum tagControllerId
{
	CONTROLLER_ID_NONE = -1,	//コントローラーなし		
	CONTROLLER_ID_PLAYER_1,		//プレイヤー１			
	CONTROLLER_ID_PLAYER_2,		//プレイヤー２

	CONTROLLER_ID_NUM,			//コントローラーのIDの数
};

//コントローラーのマネージャー
class CControllerManager
{
private:
	static CControllerInput m_controller[CONTROLLER_ID_NUM];		//コントローラークラス
	
public:
	//コンストラクタ
	CControllerManager();

	//コントローラー入力初期化
	static void Init();
	//コントローラー入力情報更新
	static void Update();
	//ボタン入力判定（通常判定）
	static bool IsRep(tagControllerButton _button,tagControllerId _id = CONTROLLER_ID_NONE);
	//ボタン入力判定（トリガー判定）
	static bool IsTrg(tagControllerButton _button, tagControllerId _id = CONTROLLER_ID_NONE);

	//レバーの値は1～0～(-1)の間で出力する
	//左レバーの左右の入力情報を取得
	static float GetLX(tagControllerId _id = CONTROLLER_ID_NONE);
	//左レバーの上下の入力情報を取得							 
	static float GetLY(tagControllerId _id = CONTROLLER_ID_NONE);
	//右レバーの左右の入力情報を取得							 
	static float GetRX(tagControllerId _id = CONTROLLER_ID_NONE);
	//右レバーの上下の入力情報を取得							 
	static float GetRY(tagControllerId _id = CONTROLLER_ID_NONE);

	//コントローラーのIDを設定
	//成功したらIDを設定しtrueを返す
	//失敗したらIDを設定せずにfalseを返す
	static bool SetId(tagControllerId _id);
};

