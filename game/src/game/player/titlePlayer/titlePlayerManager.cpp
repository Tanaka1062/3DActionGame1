#include "titlePlayerManager.h"
#include "../../lib/input/controllerManager.h"
#include "../../data.h"
#include "../../lib/myMath/myMath.h"

using namespace std;

enum tagModelName								//モデル一覧
{
	MODEL_PLAYER1,								//プレイヤー1のモデル

	MODEL_NUM,									//モデルの数
};

constexpr const char* MODEL_PATH =					//モデルのパス
{ "data/model/player/player.mv1" };

constexpr const char* MATERIAL_PATH[PLAYER_NUM] =	//マテリアルのパス
{ "data/material/player/playerBody1.png",
 "data/material/player/playerBody2.png",
 "data/material/player/playerBody3.png",
 "data/material/player/playerBody4.png", };

constexpr int MAP_FRAME_NUM = 5;				//マップのフレーム番号
constexpr int MAP_CAMERA_FRAME_NUM = 2;			//マップのカメラのフレーム番号

//------------------------
//	  コンストラクタ
//------------------------
CTitlePlayerManager::CTitlePlayerManager()
{
	Init();
}

//------------------------
//	  デストラクタ
//------------------------
CTitlePlayerManager::~CTitlePlayerManager()
{
	Exit();
}

//------------------------
//		  初期化
//------------------------
void CTitlePlayerManager::Init()
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

		//プレイヤーがいなかったら増やす
		if (m_player.size() < PLAYER_NUM)
		{
			m_player.push_back(make_unique<CTitlePlayer>());
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

		m_player[player_i]->Init(name, PAD_NONE);
	}
	
	//スポーン座標を全て消す
	m_spawnPos.clear();
}

//------------------------
//	オブジェクトのロード
//------------------------
void CTitlePlayerManager::Load(CMapBase* _map)
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

	int frameIdNum = MAP_FRAME_NUM;

	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		//プレイヤーのスポーン位置をロード
		VECTOR start = { 0.0f,0.0f,0.0f };

		//スポーン位置をセット
		start = MV1GetFramePosition(mapHndl, frameIdNum);
		frameIdNum += 2;

		//カメラの方向を向くように調整
		VECTOR cameraPos = MV1GetFramePosition(_map->GetHndl(_map->GetStageId()), MAP_CAMERA_FRAME_NUM);
		VECTOR rot = V_ZERO;
		rot.y = atan2f(start.x - cameraPos.x, start.z - cameraPos.z);

		m_player[player_i]->Load(m_modelHndl[MODEL_PLAYER1]);
		MV1SetTextureGraphHandle(m_player[player_i]->GetHndl(), 0, m_materialHndl[player_i], FALSE);
		m_player[player_i]->SetPos(start);
		m_player[player_i]->SetRot(rot);
		m_spawnPos.push_back(start);
	}
}

//------------------------
//	毎フレームする処理
//------------------------
void CTitlePlayerManager::Step()
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
void CTitlePlayerManager::Update()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CTitlePlayerManager::Draw()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Draw();
	}

}

//------------------------
//		  終了処理
//------------------------
void CTitlePlayerManager::Exit()
{
	for (int player_i = 0; player_i < m_player.size(); player_i++)
	{
		m_player[player_i]->Exit();
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

