#include "resultMap.h"
#include "../../player/playerData.h"
#include "../../ranking/ranking.h"
#include "../../../lib/input/keyInput.h"
#include "../../system/sound/soundManager.h"

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };	//大きさ
static const char* MAP_MODEL_PATH = {			//ロードするファイル名
	"data/model/map/resultMap/resultMap.mv1",
};					

static const char* OBJECT_MODEL_PATH = {		//オブジェクトのロードするファイル名
	"data/model/map/resultMap/podium.mv1",
};
constexpr int OBJECT_FRAME_NUM = 10;			//マップのオブジェクトの配置フレーム
constexpr float PODIUM_UP_SPEED = 1.7f;			//表彰台の動く速度

constexpr float PODIUM_MAX_Y[PLAYER_NUM] =		//表彰台の最大の高さ
{
	300.0f,
	260.0f,
	230.0f,
	190.0f,
};
//==========================================

//------------------------
//	コンストラクタ
//------------------------
CResultMap::CResultMap()
{
	m_stage.push_back(new CActor);

	for (int player_i = 0; player_i < PLAYER_NUM; player_i++)
	{
		m_object.push_back(new CObject);
		m_isPodiumMoveEnd.push_back(false);
	}
}

//------------------------
//		   初期化
//------------------------
void CResultMap::Init()
{
	m_isPodiumAllMoveEnd = false;
	CMapBase::Init();
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->Init();
		m_stage[stage_i]->SetPos(ZERO);
	}
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		m_object[object_i]->Init();
		m_isPodiumMoveEnd[object_i] = false;
	}
}

//------------------------
//		モデルロード
//------------------------
void CResultMap::Load()
{
	m_stage[0]->LoadModel(MAP_MODEL_PATH);

	int frameNum = OBJECT_FRAME_NUM;
	int object_hndl = MV1LoadModel(OBJECT_MODEL_PATH);
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		m_object[object_i]->DuplicateModel(object_hndl);
		m_object[object_i]->SetPos(MV1GetFramePosition(m_stage[0]->GetHndl(),frameNum));
		frameNum += 2;
	}
	MV1DeleteModel(object_hndl);

}

//------------------------
//	 毎フレームする処理
//------------------------
void CResultMap::Step()
{

	//順位管理クラス取得
	CRanking* ranking = CRanking::GetInstance();

	bool isButton = false;

	if (CKeyInput::IsTrg(KEY_SELECT) == true ||
		CControllerManager::IsTrg(BUTTON_B))
	{
		isButton = true;
	}

	//最大まで伸びた表彰台を数える
	int podiumMaxNum = 0;
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{

		VECTOR pos = m_object[object_i]->GetPos();
		//順位ごとに設定された大きさまで表彰台を移動させる
		if (PODIUM_MAX_Y[ranking->GetPlayerRank(static_cast<tagPlayerName>(object_i))] > pos.y)
		{
			pos.y += PODIUM_UP_SPEED;
		}
		else if(m_isPodiumMoveEnd[object_i] == false)
		{
			CSoundManager::Play(CSoundManager::SE_PODIUM_STOP,DX_PLAYTYPE_BACK);
			m_isPodiumMoveEnd[object_i] = true;
			pos.y = PODIUM_MAX_Y[ranking->GetPlayerRank(static_cast<tagPlayerName>(object_i))];
		}

		if (m_isPodiumMoveEnd[object_i] == true)
		{
			podiumMaxNum++;
		}

		if (isButton == true)
		{
			pos.y = PODIUM_MAX_Y[ranking->GetPlayerRank(static_cast<tagPlayerName>(object_i))];
		}

		m_object[object_i]->SetPos(pos);
	}
	//全ての表彰台が最大まで伸びたらフラグをtrueにする
	if (podiumMaxNum == m_object.size() &&
		m_isPodiumAllMoveEnd == false)
	{
		//拍手SEを再生
		CSoundManager::Play(CSoundManager::SE_APPLAUSE, DX_PLAYTYPE_BACK);
		//ドラムロールを止める
		CSoundManager::Stop(CSoundManager::BGM_DRUMROLL);
		//BGMを再生
		CSoundManager::Play(CSoundManager::BGM_RESULT);
		m_isPodiumAllMoveEnd = true;
	}
}

