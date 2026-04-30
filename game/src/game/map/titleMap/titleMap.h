#pragma once
#include<DxLib.h>
#include "../mapBase.h"

class CTitleMap : public CMapBase
{
private:
	enum tagAnimId
	{
		ANIMID_DEFAULT,		//デフォルト
		ANIMID_MOVE,		//移動

		ANIMID_NUM,			//アニメーションの数
	};
public:
	//コンストラクタ
	CTitleMap();

	//初期化
	void Init();

	//モデルロード
	void Load();

	//毎フレームする処理
	void Step();

};

