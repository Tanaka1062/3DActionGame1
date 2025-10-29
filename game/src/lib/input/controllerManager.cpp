#include "controllerManager.h"
#include <DxLib.h>

CControllerInput CControllerManager::m_controller[PAD_NUM];		//コントローラークラス


//-------------------------------
//		  コンストラクタ
//-------------------------------
CControllerManager::CControllerManager()
{
	Init();
}

//-------------------------------
//	 コントローラー入力初期化
//-------------------------------
void CControllerManager::Init()
{
	for (int i = 0; i < PAD_NUM; i++)
	{
		m_controller[i].Init();
	}
}

//-------------------------------
//	コントローラー入力情報更新
//-------------------------------
void CControllerManager::Update()
{
	for (int i = 0; i < PAD_NUM; i++)
	{
		m_controller[i].Update();
	}
}

//-------------------------------
//	 ボタン入力判定（通常判定）
//-------------------------------
bool CControllerManager::IsRep(tagControllerButton _button, tagPadName _padName)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_padName == PAD_NONE)
	{
		return m_controller[PAD_PLAYER_1].IsRep(_button);
	}

	return m_controller[_padName].IsRep(_button);
}

//-------------------------------
//	ボタン入力判定（トリガー判定）
//-------------------------------
bool CControllerManager::IsTrg(tagControllerButton _button, tagPadName _padName)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_padName == PAD_NONE)
	{
		return m_controller[PAD_PLAYER_1].IsTrg(_button);
	}

	return m_controller[_padName].IsTrg(_button);
}

//-------------------------------
//左レバーの左右の入力情報を取得
//-------------------------------
float CControllerManager::GetLX(tagPadName _padName)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_padName == PAD_NONE)
	{
		return m_controller[PAD_PLAYER_1].GetLX();
	}

	return m_controller[_padName].GetLX();
}

//-------------------------------
//左レバーの上下の入力情報を取得
//-------------------------------							 
float CControllerManager::GetLY(tagPadName _padName)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_padName == PAD_NONE)
	{
		return m_controller[PAD_PLAYER_1].GetLY();
	}

	return m_controller[_padName].GetLY();
}

//-------------------------------
//右レバーの左右の入力情報を取得
//-------------------------------
float CControllerManager::GetRX(tagPadName _padName)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_padName == PAD_NONE)
	{
		return m_controller[PAD_PLAYER_1].GetRX();
	}

	return m_controller[_padName].GetRX();
}

//-------------------------------
//右レバーの上下の入力情報を取得
//-------------------------------
float CControllerManager::GetRY(tagPadName _padName)
{
	//コントローラーなしの場合プレイヤー１の情報を取得する
	if (_padName == PAD_NONE)
	{
		return m_controller[PAD_PLAYER_1].GetRX();
	}

	return m_controller[_padName].GetRY();
}

//-------------------------------
//	  コントローラーのIDを設定
//-------------------------------
bool CControllerManager::SetId(tagPadName _padName)
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
		//すでにIDが設定されている場合スキップする
		if (m_controller[i].GetId() != -1)continue;
		//同じIDが設定されている場合スキップする
		if (m_controller[0].GetId() == m_controller[1].GetId())continue;

		if (PAD_INPUT_2 == GetJoypadInputState(controllerNum[i]))
		{
			
			m_controller[_padName].SetId(controllerNum[i]);
			return true;
		}
	}

	return false;
}

//-------------------------------
//	コントローラーの名前を取得
//-------------------------------
tagPadName CControllerManager::GetName(int _num)
{
	switch (_num)
	{
	case 0:
		return PAD_PLAYER_1;
		break;
	case 1:
		return PAD_PLAYER_2;
		break;
	}

	return PAD_NONE;
}
