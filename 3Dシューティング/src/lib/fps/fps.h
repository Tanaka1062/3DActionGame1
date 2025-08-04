#pragma once


class CFps
{
private:
	static float m_frameRate; //今のフレームレートを保存
	static int m_nowTime;		//現在時間
	static int m_prevTime;		//ひとつ前の時間
	static int m_prevDrawTime;	//1つ前の描画したPC時間
	static int m_count;		//カウント用

public:
	//コンストラクタ
	CFps();

	// 初期化関数
	static void Init();
	// FPS更新処理
	static void Update();
	// 次のフレームに進めていいか
	static bool IsNextFrame();
	//　FPS表示関数
	static void Print();


};


