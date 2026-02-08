#include "map.h"
#include <math.h>
#include "../gameTime/gameTime.h"

//定義関連==================================
constexpr VECTOR ZERO = { 0.0f,0.0f,0.0f };		//VECTOR用初期化
constexpr VECTOR SCALE = { 1.0f,1.0f,1.0f };		//大きさ
static const char* MAP_MODEL_PATH[MAP_NUM] ={
	"data/model/map/TestMap9.mv1",
	"data/model/map/selectMap/selectMap.mv1",
	"data/model/map/resultMap/resultMap.mv1",
};					//ロードするファイル名
constexpr int MAP_MOVE_TIME = 30;			//ステージが移動するまでの時間

//==========================================


//------------------------
//	コンストラクタ
//------------------------
CMap::CMap()
{
	Init();
}

//------------------------
//	デストラクタ
//------------------------
CMap::~CMap()
{
	Exit();
}

//------------------------
//		初期化
//------------------------
void CMap::Init()
{
	CObject::Init();
	m_pos = ZERO;
	m_scale = SCALE;
	m_rot = ZERO;
	m_hndl = -1;
	m_hitHndl = -1;
	m_mapId = MAP_ID_CENTER1;
	m_mapMoveTimer = 0;
}

//------------------------
//		モデルロード
//------------------------
void CMap::Load(tagMapId _id)
{
	LoadModel(MAP_MODEL_PATH[_id]);

	if (m_hitHndl == -1)
	{
		m_hitHndl = MV1LoadModel(MAP_MODEL_PATH[_id]);

		//マップの当たり判定を取るためにコリジョン情報を構築する
		MV1SetupCollInfo(m_hitHndl);
	}

}

//------------------------
//	毎フレームする処理
//------------------------
void CMap::Step()
{
	CObject::Step();

	CGameTime* gameTime = CGameTime::GetInstance();

	//決められた時間だけ通る
	if (gameTime->GetTime() - m_mapMoveTimer == MAP_MOVE_TIME)
	{
		m_mapMoveTimer += MAP_MOVE_TIME;

		m_mapId += 1;

		if (m_mapId >= MAP_ID_CENTER5)
		{
			m_mapId = MAP_ID_CENTER5;
		}

	}
}

//------------------------
//		モデル描写
//------------------------
void CMap::Draw()
{
	CObject::Draw();

}

//------------------------
//		終了処理
//------------------------
void CMap::Exit()
{
	CObject::Exit();
	
	if (m_hitHndl != -1)
	{
		MV1DeleteModel(m_hitHndl);
		m_hitHndl = -1;
	}
}

