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
	return m_controller[_padName].IsRep(_button);
}

//-------------------------------
//	ボタン入力判定（トリガー判定）
//-------------------------------
bool CControllerManager::IsTrg(tagControllerButton _button, tagPadName _padName)
{
	return m_controller[_padName].IsTrg(_button);
}

//-------------------------------
//左レバーの左右の入力情報を取得
//-------------------------------
float CControllerManager::GetLX(tagPadName _padName)
{
	return m_controller[_padName].GetLX();
}

//-------------------------------
//左レバーの上下の入力情報を取得
//-------------------------------							 
float CControllerManager::GetLY(tagPadName _padName)
{
	return m_controller[_padName].GetLY();
}

//-------------------------------
//右レバーの左右の入力情報を取得
//-------------------------------
float CControllerManager::GetRX(tagPadName _padName)
{
	return m_controller[_padName].GetRX();
}

//-------------------------------
//右レバーの上下の入力情報を取得
//-------------------------------
float CControllerManager::GetRY(tagPadName _padName)
{
	return m_controller[_padName].GetRY();
}

//-------------------------------
//	  コントローラーのIDを設定
//-------------------------------
bool CControllerManager::SetId()
{
	//コントローラーのID一覧
	int controllerId[4] =
	{
		DX_INPUT_PAD1,
		DX_INPUT_PAD2,
		DX_INPUT_PAD3,
		DX_INPUT_PAD4,
	};

	//Bを押したコントローラーを調べ、IDに設定する、
	for (int controllerId_i = 0; controllerId_i < 4; controllerId_i++)
	{
		for (int controller_j = 0; controller_j < PAD_NUM; controller_j++)
		{

			//すでにIDが設定されている場合スキップする
			if (m_controller[controllerId_i].GetId() != -1)continue;
	
			if (PAD_INPUT_2 == GetJoypadInputState(controllerId[controllerId_i]))
			{
	
				m_controller[controllerId_i].SetId(controllerId[controllerId_i]);
				return true;
			}
		}
	}

	return false;
}

//-------------------------------
//コントローラーが全部接続されているかどうか
//-------------------------------
bool CControllerManager::IsAllConnection()
{
	//idをセットされているコントローラーの数
	int setIdPadNum = 0;
	for (int controller_i = 0; controller_i < PAD_NUM; controller_i++)
	{
		if (m_controller[controller_i].GetId() != -1)
		{
			setIdPadNum++;
		}

	}

	if (setIdPadNum == PAD_NUM)
	{
		return true;
	}

	return false;
}

//-------------------------------
//コントローラーが接続されているかどうか
//-------------------------------
bool CControllerManager::IsConnection(tagPadName _padName)
{
	//コントローラーのIDが設定されていたらtrueを返す
	if (m_controller[_padName].GetId() != PAD_NONE)
	{
		return true;
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
		return PAD_1;
		break;
	case 1:
		return PAD_2;
		break;
	case 2:
		return PAD_3;
		break;
	case 3:
		return PAD_4;
		break;

	}

	return PAD_NONE;
}

