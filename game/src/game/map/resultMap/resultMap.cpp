#include "resultMap.h"
#include "../../player/playerData.h"
#include "../../ranking/ranking.h"

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };	//大きさ
static const char* MAP_MODEL_PATH = {			//ロードするファイル名
	"data/model/map/resultMap/resultMap.mv1",
};					

static const char* OBJECT_MODEL_PATH = {		//オブジェクトのロードするファイル名
	"data/model/map/resultMap/podium.mv1",
};
constexpr int OBJECT_FRAME_NUM = 4;				//マップのオブジェクトの配置フレーム
constexpr float PODIUM_UP_SPEED = 0.03f;		//表彰台の動く速度

constexpr float PODIUM_MAX_Y[PLAYER_NUM] =		//表彰台の最大の高さ
{
	10.0f,
	8.0f,
	6.0f,
	4.0f,
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
	}
}

//------------------------
//		   初期化
//------------------------
void CResultMap::Init()
{
	m_isPodiumMoveEnd = false;
	CMapBase::Init();
	for (int stage_i = 0; stage_i < m_stage.size(); stage_i++)
	{
		m_stage[stage_i]->Init();
		m_stage[stage_i]->SetPos(ZERO);
	}
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		m_object[object_i]->Init();
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

	//最大まで伸びた表彰台を数える
	int podiumMaxNum = 0;
	for (int object_i = 0; object_i < m_object.size(); object_i++)
	{
		VECTOR scale = m_object[object_i]->GetScale();
		//順位ごとに設定された大きさまで表彰台を伸ばす
		if (PODIUM_MAX_Y[ranking->GetPlayerRank(static_cast<tagPlayerName>(object_i))] > scale.y)
		{
			scale.y += PODIUM_UP_SPEED;
		}
		else
		{
			podiumMaxNum++;
			scale.y = PODIUM_MAX_Y[ranking->GetPlayerRank(static_cast<tagPlayerName>(object_i))];
		}
		m_object[object_i]->SetScale(scale);
	}
	//全ての表彰台が最大まで伸びたらフラグをtrueにする
	if (podiumMaxNum == m_object.size())
	{
		m_isPodiumMoveEnd = true;
	}
}

