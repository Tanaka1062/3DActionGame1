#pragma once
#include <DxLib.h>

class C3DUi
{
private:
	int		m_hndl;			//画像のハンドル
	VECTOR	m_pos;			//座標
	bool	m_isActive;		//生存フラグ

public:
	C3DUi();
	~C3DUi();

	//初期化
	void Init();

	//モデルロード
	void Load(const char* _filePath);

	//描写処理
	void Draw();

	//終了処理
	void Exit();

	//ハンドルを取得
	int GetHndl() { return m_hndl; }

	//座標を取得
	VECTOR GetPos() { return m_pos; }
	//座標を設定
	void SetPos(VECTOR _pos) { m_pos = _pos; }

	//生存フラグを取得
	bool GetIsActive() { return m_isActive; }
	//生存フラグを設定
	void SetIsActive(bool _isActive) { m_isActive = _isActive; }
};

