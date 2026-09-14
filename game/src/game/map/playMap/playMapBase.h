#pragma once
#include "../mapBase.h"

class CPlayMapBase : public CMapBase
{
private:
	bool m_isStageFall;		//ステージが落下するかどうか
	bool m_isStageShake;	//ステージが移動しているかどうか

protected:
	//ステージの移動処理
	void StageMove(VECTOR _moveSpeed);

	//ステージの揺れる処理
	void StageShake(VECTOR _pos);

};

