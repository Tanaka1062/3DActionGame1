#include "gimmickBase.h"

//----------------------------
//		  コンストラクタ
//----------------------------
CGimmickBase::CGimmickBase()
{
	CObject::Init();
}

//----------------------------
//		  デストラクタ
//----------------------------
CGimmickBase::~CGimmickBase()
{
	CObject::Exit();
}

//----------------------------
//		 モデルのロード
//----------------------------
void CGimmickBase::Load(const char* _filePath, const char* _mapFrame, int _mapFrameNum)
{
	CObject::LoadModel(_filePath);

	int mapFrameHndl = MV1LoadModel(_mapFrame);

	m_pos = MV1GetFramePosition(mapFrameHndl, _mapFrameNum);

	///マップのフレームを削除
	if (mapFrameHndl != -1)
	{
		MV1DeleteModel(mapFrameHndl);
	}
}

