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

constexpr float TARGET_LEN = -200.0f;				//ターゲットと認識するまでの長さ
constexpr float TARGET_MAX_DISTANCE = 40.0f;	//どれくらい法線から離せるか

static const char* MODEL_PATH[PLAYER_NUM] =
{ "data/model/player/playerTest7-1.mv1" ,
  "data/model/player/playerTest7-2.mv1" ,
  "data/model/player/playerTest7-3.mv1" ,
  "data/model/player/playerTest7-4.mv1" ,};			//ロードするファイル名

static const char FRAME_PATH[] =
"data/model/map/selectMap/selectMapFrame.mv1";			//ロードするファイル名


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
		for (int modelHndl_i = 0; modelHndl_i < MODEL_NUM; modelHndl_i++)
		{
			m_modelHndl.push_back(-1);
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
void CSelectPlayerManager::Load()
{

	//モデルのロード
	for (int i = 0; i < MODEL_NUM; i++)
	{
		if (m_modelHndl[i] == -1)
		{
			m_modelHndl[i] = MV1LoadModel(MODEL_PATH[i]);
		}
	}

	//マップのフレームのハンドルをロード
	int frameHndl = MV1LoadModel(FRAME_PATH);

	for (int i = 0; i < m_player.size(); i++)
	{
		//プレイヤーのスポーン位置をロード
		VECTOR start = { 0.0f,0.0f,0.0f };

		//スポーン位置をセット
		switch (i)
		{
		case PLAYER_1:
			start = MV1GetFramePosition(frameHndl, 1);
			break;
		case PLAYER_2:
			start = MV1GetFramePosition(frameHndl, 3);
			break;
		case PLAYER_3:
			start = MV1GetFramePosition(frameHndl, 7);
			break;
		case PLAYER_4:
			start = MV1GetFramePosition(frameHndl, 9);
			break;
		}

		m_player[i]->Load(m_modelHndl[i]);
		m_player[i]->SetPos(start);
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
	for (int i = 0; i < m_player.size(); i++)
	{
		m_player[i]->Update();
	}
}

//------------------------
//	オブジェクトの描写
//------------------------
void CSelectPlayerManager::Draw()
{
	for (int i = 0; i < m_player.size(); i++)
	{
		m_player[i]->Draw();
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

	for (int i = 0; i < m_modelHndl.size(); i++)
	{
		m_modelHndl[i] = -1;
	}

	m_modelHndl.clear();
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
