#include "resultPlayerManager.h"
#include "../../lib/input/controllerManager.h"
#include "../../data.h"
#include "../../lib/myMath/myMath.h"

using namespace std;

enum tagModelName								//モデル一覧
{
	MODEL_PLAYER1,								//プレイヤー1のモデル

	MODEL_NUM,									//モデルの数
};

constexpr float TARGET_LEN = -200.0f;			//ターゲットと認識するまでの長さ
constexpr float TARGET_MAX_DISTANCE = 40.0f;	//どれくらい法線から離せるか

static const char* MODEL_PATH =					//モデルのパス
{ "data/model/player/player.mv1" };

static const char* MATERIAL_PATH[PLAYER_NUM] =	//マテリアルのパス
{ "data/material/player/playerBody1.png",
 "data/material/player/playerBody2.png",
 "data/material/player/playerBody3.png",
 "data/material/player/playerBody4.png", };

//------------------------
//	  コンストラクタ
//------------------------
CResultPlayerManager::CResultPlayerManager()
{
	Init(nullptr);
}

//------------------------
//	  デストラクタ
//------------------------
CResultPlayerManager::~CResultPlayerManager()
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
void CResultPlayerManager::Init(CWinner* _winner)
{
	if (m_modelHndl.size() < MODEL_NUM)
	{
		for (int modelHndl_i = 0; modelHndl_i < MODEL_NUM; modelHndl_i++)
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
			m_player.push_back(new CResultPlayer);
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

		if (_winner == nullptr)continue;

		if (m_player[player_i]->GetPlayerName() == _winner->GetWinnerPlayerName())
		{
			m_player[player_i]->SetIsWin(true);
		}

		//ゲーム中の取得コイン量を取得
		m_player[player_i]->SetMoney(_winner->GetPlayerGetCoin(m_player[player_i]->GetPlayerName()));
	}
	
	//スポーン座標を全て消す
	m_spawnPos.clear();
}

//------------------------
//	オブジェクトのロード
//------------------------
void CResultPlayerManager::Load(CMapBase* _map)
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

	int frameId[3] = { 4,8,10 };
	int frameIdNum = 0;

	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//プレイヤーのスポーン位置をロード
		VECTOR start = { 0.0f,0.0f,0.0f };

		//スポーン位置をセット
		if (m_player[player_i]->GetIsWin() == true)
		{
			start = MV1GetFramePosition(mapHndl, 2);
		}
		else
		{
			start = MV1GetFramePosition(mapHndl, frameId[frameIdNum]);
			frameIdNum++;
		}

		m_player[player_i]->Load(m_modelHndl[MODEL_PLAYER1]);
		MV1SetTextureGraphHandle(m_player[player_i]->GetHndl(), 0, m_materialHndl[player_i], FALSE);
		m_player[player_i]->SetPos(start);
		m_spawnPos.push_back(start);
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CResultPlayerManager::Step()
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
void CResultPlayerManager::Update()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CResultPlayerManager::Draw()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Draw();
	}

}

//------------------------
//		  終了処理
//------------------------
void CResultPlayerManager::Exit()
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
		if (m_materialHndl[material_i] != -1)
		{
			DeleteGraph(m_materialHndl[material_i]);
			m_materialHndl[material_i] = -1;
		}
	}
	m_materialHndl.clear();
}

