#pragma once
#include<DxLib.h>

class C2DUi
{
protected:

	VECTOR m_pos;				//座標
	float m_rot;				//回転角度
	int m_hndl;					//モデルハンドル
	bool m_isActive;			//生存フラグ

public:
	//コンストラクタ・デストラクタ
	C2DUi();
	virtual ~C2DUi();

	//初期化
	virtual void Init(VECTOR _pos = {0.0f,0.0f,0.0f}, float _rot = 0.0f);
	//ロード
	virtual void Load(const char* _hndlPath);
	//毎フレームする処理
	virtual void Step();
	//描写
	virtual void Draw(float _size = 1.0f);
	//破棄
	virtual void Exit();

	//当たり判定後の処理
	virtual void HitCalc();

	//画像をロードする関数
	//_hndl		:画像ハンドル
	//_hndlPath	:画像のパス
	//_allNum	:分割したときの画像の数(分割していなかったら入力しなくていい)
	//_numX		:分割した画像の数横
	//_numY		:分割した画像の数縦
	//_sizeX	:分割した画像の大きさ横
	//_sizeY	:分割した画像の大きさ縦
	void LoadGraphic(const char* _hndlPath, int _allNum = 1,
		int _numX = 1, int _numY = 1, int _sizeX = 1, int _sizeY = 1);

public:

	//座標出力
	VECTOR GetPos() { return m_pos; }
	//角度出力
	float GetRot() { return m_rot; }

	//座標設定
	void SetPos(VECTOR _pos) { m_pos = _pos; }
	//角度設定
	void SetRot(float _rot) { m_rot = _rot; }

	//生存フラグを取得
	bool GetActive() { return m_isActive; }

	//画像ハンドルの設定
	void SetHndl(int _hndl) { m_hndl = _hndl; }
};

