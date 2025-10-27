#include "controllerManager.h"
#include <DxLib.h>

//-------------------------------
//		  コンストラクタ
//-------------------------------
CControllerManager::CControllerManager()
{

}

//-------------------------------
//	 コントローラー入力初期化
//-------------------------------
void CControllerManager::Init()
{
	for (int i = 0; i < CONTROLLER_ID_NUM; i++)
	{
		m_controller[i].Init();
	}
}

//-------------------------------
//	コントローラー入力情報更新
//-------------------------------
void CControllerManager::Update()
{
	for (int i = 0; i < CONTROLLER_ID_NUM; i++)
	{
		m_controller[i].Update();
	}
}

//-------------------------------
//	 ボタン入力判定（通常判定）
//-------------------------------
bool CControllerManager::IsRep(tagControllerButton _button, tagControllerId _id = CONTROLLER_ID_NONE)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_id == CONTROLLER_ID_NONE)
	{
		return m_controller[CONTROLLER_ID_PLAYER_1].IsRep(_button);
	}

	return m_controller[_id].IsRep(_button);
}

//-------------------------------
//	ボタン入力判定（トリガー判定）
//-------------------------------
bool CControllerManager::IsTrg(tagControllerButton _button, tagControllerId _id = CONTROLLER_ID_NONE)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_id == CONTROLLER_ID_NONE)
	{
		return m_controller[CONTROLLER_ID_PLAYER_1].IsTrg(_button);
	}

	return m_controller[_id].IsTrg(_button);
}

//-------------------------------
//左レバーの左右の入力情報を取得
//-------------------------------
float CControllerManager::GetLX(tagControllerId _id = CONTROLLER_ID_NONE)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_id == CONTROLLER_ID_NONE)
	{
		return m_controller[CONTROLLER_ID_PLAYER_1].GetLX();
	}

	return m_controller[_id].GetLX();
}

//-------------------------------
//左レバーの上下の入力情報を取得
//-------------------------------							 
float CControllerManager::GetLY(tagControllerId _id = CONTROLLER_ID_NONE)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_id == CONTROLLER_ID_NONE)
	{
		return m_controller[CONTROLLER_ID_PLAYER_1].GetLY();
	}

	return m_controller[_id].GetLY();
}

//-------------------------------
//右レバーの左右の入力情報を取得
//-------------------------------
float CControllerManager::GetRX(tagControllerId _id = CONTROLLER_ID_NONE)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_id == CONTROLLER_ID_NONE)
	{
		return m_controller[CONTROLLER_ID_PLAYER_1].GetRX();
	}

	return m_controller[_id].GetRX();
}

//-------------------------------
//右レバーの上下の入力情報を取得
//-------------------------------
float CControllerManager::GetRY(tagControllerId _id = CONTROLLER_ID_NONE)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_id == CONTROLLER_ID_NONE)
	{
		return m_controller[CONTROLLER_ID_PLAYER_1].GetRX();
	}

	return m_controller[_id].GetRY();
}

//-------------------------------
//	  コントローラーのIDを設定
//-------------------------------
bool CControllerManager::SetId(tagControllerId _id)
{
	//コントローラーのID一覧
	int controllerNum[4] =
	{
		PAD_INPUT_1,
		PAD_INPUT_2,
		PAD_INPUT_3,
		PAD_INPUT_4,
	};

	//Bを押したコントローラーを調べ、IDに設定する、
	for (int i = 0; i < 4; i++)
	{
		if (PAD_INPUT_2 == GetJoypadInputState(controllerNum[i]))
		{
			m_controller[_id].SetId(controllerNum[i]);
			return true;
		}
	}

	return false;
}
