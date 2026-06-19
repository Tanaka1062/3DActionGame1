#pragma once
#include "controllerInput.h"

//コントローラーの名前一覧
enum tagPadName
{
	PAD_NONE = -1,		//コントローラー無し(初期化用) 
	PAD_1,				//コントローラー１			
	PAD_2,				//コントローラー２
	PAD_3,				//コントローラー３
	PAD_4,				//コントローラー４

	PAD_NUM,			//コントローラーの数
};

struct ControllerIdData								//コントローラーのIDデータ
{
	int	 Id;											//ID
	bool isConnection;								//接続フラグ
};

//コントローラーのマネージャー
class CControllerManager
{
private:
	static CControllerInput m_controller[PAD_NUM];		//コントローラークラス
	static ControllerIdData m_controlerIdData[PAD_NUM];	//コントローラーのIDデータ
	
public:
	//コンストラクタ
	CControllerManager();

	//コントローラー入力初期化
	static void Init();
	//コントローラー入力情報更新
	static void Update();
	//ボタン入力判定（通常判定）
	static bool IsRep(tagControllerButton _button, tagPadName _padName = PAD_1);
	//ボタン入力判定（トリガー判定）
	static bool IsTrg(tagControllerButton _button, tagPadName _padName = PAD_1);

	//レバーの値は1～0～(-1)の間で出力する
	//左レバーの左右の入力情報を取得
	static float GetLX(tagPadName _padName = PAD_1);
	//左レバーの上下の入力情報を取得							 
	static float GetLY(tagPadName _padName = PAD_1);
	//右レバーの左右の入力情報を取得							 
	static float GetRX(tagPadName _padName = PAD_1);
	//右レバーの上下の入力情報を取得							 
	static float GetRY(tagPadName _padName = PAD_1);

	//コントローラーのIDを設定
	//成功したらIDを設定しtrueを返す
	//失敗したらIDを設定せずにfalseを返す
	static bool SetId();

	//コントローラーが全部接続されているかどうか
	static bool IsAllConnection();

	//コントローラーが接続されているかどうか
	static bool IsConnection(tagPadName _padName);

	//コントローラーの名前を取得
	static tagPadName GetName(int _num);

};

