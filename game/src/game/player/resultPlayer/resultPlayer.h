#pragma once
#include "../player.h"
#include"../../../lib/input/controllerManager.h"

//プレイヤークラス
class CResultPlayer:public CPlayer 
{
private:
	int m_rank;				//順位
	enum tagResultState		//リザルトの状態
	{
		WISH,				//願う
		POSE_IN,			//ポーズ前
		POSE,				//ポーズ
	};
	tagResultState m_resultState;
public:
	//コンストラクタ・デストラクタ
	CResultPlayer();

	//初期化
	void Init(tagPlayerName _name, tagPadName _padName,int _rank);

	//モデルロード
	void Load(int _modelHndl);

	//毎フレームする処理
	void Step(bool _podiumMoveEnd);

	//描写処理
	void Draw();

private:

	//願いモーション
	void Wish();

	//リザルト前モーション
	void ResultPoseIn();

	//リザルトモーション
	void ResultPose();


};

