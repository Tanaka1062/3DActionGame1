#include "selectPlayerManager.h"
#include "../../lib/input/controllerManager.h"
#include "../../data.h"
#include "../../lib/myMath/myMath.h"

using namespace std;

enum tagModelName					//モデル一覧
{
	MODEL_PLAYER1,					//プレイヤー1のモデル
	MODEL_PLAYER2,					//プレイヤー2のモデル
	MODEL_PLAYER3,					//プレイヤー3のモデル
	MODEL_PLAYER4,					//プレイヤー4のモデル

	MODEL_NUM,						//モデルの数
};

constexpr float TARGET_LEN = -200.0f;			//ターゲットと認識するまでの長さ
constexpr float TARGET_MAX_DISTANCE = 40.0f;	//どれくらい法線から離せるか

static const char* MODEL_PATH =					//モデルのパス
{ "data/model/player/playerTest8.mv1" };

static const char* MATERIAL_PATH[PLAYER_NUM] =	//マテリアルのパス
{ "data/material/player/playerBody1.png",
 "data/material/player/playerBody2.png",
 "data/material/player/playerBody3.png",
 "data/material/player/playerBody4.png", };

//------------------------
//	  コンストラクタ
//------------------------
CSelectPlayerManager::CSelectPlayerManager()
{
	Init();
}

//------------------------
//	  デストラクタ
//------------------------
CSelectPlayerManager::~CSelectPlayerManager()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		delete m_player[player_i];

		m_player[player_i]->Exit();

	}
}

//------------------------
//		  初期化
//------------------------
void CSelectPlayerManager::Init()
{
	if (m_modelHndl.size() < MODEL_NUM)
	{
		for (int model_i = 0; model_i < MODEL_NUM; model_i++)
		{
			m_modelHndl.push_back(-1);
		}
	}

	if (m_materialHndl.size() < PLAYER_NUM)
	{
		for (int material_i = 0; material_i < PLAYER_NUM; material_i++)
		{
			m_materialHndl.push_back(-1);
		}
	}

	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		//コントローラーの名前を取得
		tagPadName padName = CControllerManager::GetName(player_i);

		//プレイヤーがいなかったら増やす
		if (m_player.size() < PLAYER_NUM)
		{
			m_player.push_back(new CSelectPlayer);
		}

		tagPlayerName name = PLAYER_NONE;

		VECTOR* pointerPos = nullptr;

		switch (player_i)
		{
		case PLAYER_1:
			name = PLAYER_1;
			break;
		case PLAYER_2:
			name = PLAYER_2;
			break;
		case PLAYER_3:
			name = PLAYER_3;
			break;
		case PLAYER_4:
			name = PLAYER_4;
			break;

		}

		m_player[player_i]->Init(name, padName);

	}
	
	//スポーン座標を全て消す
	m_spawnPos.clear();
}

//------------------------
//	オブジェクトのロード
//------------------------
void CSelectPlayerManager::Load(CMapBase* _map)
{

	//モデルのロード
	for (int model_i = 0; model_i < MODEL_NUM; model_i++)
	{
		if (m_modelHndl[model_i] == -1)
		{
			m_modelHndl[model_i] = MV1LoadModel(MODEL_PATH);
		}
	}

	//マテリアルのロード
	for (int material_i = 0; material_i < m_materialHndl.size(); material_i++)
	{
		if (m_materialHndl[material_i] == -1) 
		{
			m_materialHndl[material_i] = LoadGraph(MATERIAL_PATH[material_i]);
		}
	}

	//マップのフレームのハンドルをロード
	int mapHndl = _map->GetHndl(0);

	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//プレイヤーのスポーン位置をロード
		VECTOR start = { 0.0f,0.0f,0.0f };

		//スポーン位置をセット
		switch (player_i)
		{
		case PLAYER_1:
			start = MV1GetFramePosition(mapHndl, 2);
			break;
		case PLAYER_2:
			start = MV1GetFramePosition(mapHndl, 4);
			break;
		case PLAYER_3:
			start = MV1GetFramePosition(mapHndl, 8);
			break;
		case PLAYER_4:
			start = MV1GetFramePosition(mapHndl, 10);
			break;
		}

		m_player[player_i]->Load(m_modelHndl[player_i]);
		MV1SetTextureGraphHandle(m_player[player_i]->GetHndl(), 0, m_materialHndl[player_i], FALSE);
		m_player[player_i]->SetPos(start);
		m_spawnPos.push_back(start);
	}
		
}

//------------------------
//	毎フレームする処理
//------------------------
void CSelectPlayerManager::Step()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Step();

		if (CControllerManager::IsConnection(m_player[player_i]->GetPadName()) == true)
		{
			m_player[player_i]->SetActive(true);
		}
	}

}

//------------------------
//		 数値の更新
//------------------------
void CSelectPlayerManager::Update()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CSelectPlayerManager::Draw()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		if (m_player[player_i]->GetActive() == false)continue;

		m_player[player_i]->Draw();
	}

}

//------------------------
//		  終了処理
//------------------------
void CSelectPlayerManager::Exit()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Exit();

		delete m_player[player_i];
	}
	m_player.clear();

	for (int model_i = 0; model_i < m_modelHndl.size(); model_i++)
	{
		if (m_modelHndl[model_i] != -1)
		{
			MV1DeleteModel(m_modelHndl[model_i]);
			m_modelHndl[model_i] = -1;
		}
	}
	m_modelHndl.clear();

	for (int material_i = 0; material_i < m_materialHndl.size(); material_i++)
	{
		if (m_materialHndl[material_i])
		{
			DeleteGraph(m_materialHndl[material_i]);
			m_materialHndl[material_i] = -1;
		}
	}
	m_materialHndl.clear();

}

//------------------------
//全員の準備が完了しているか
//------------------------
bool CSelectPlayerManager::GetIsAllReady()
{
	//現在いるプレイヤーの数
	int playerNum = 0;
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//現在いるプレイヤーを確認
		if (m_player[player_i]->GetActive() == true)
		{
			playerNum++;
		}
	}

	//準備できているプレイヤーの数
	int isReadyPlayerNum = 0;
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//現在いるプレイヤーを確認
		if (m_player[player_i]->GetIsReady() == true)
		{
			isReadyPlayerNum++;
		}
	}

	//全員が準備完了ならtrue
	if (playerNum == isReadyPlayerNum)
	{
		return true;
	}

	return false;
}

