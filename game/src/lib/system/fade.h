#pragma once

// フェードの各種状態
enum tagFadeSteate {
	FADE_NON,			//フェードなし
	FADE_IN,			//フェードイン中（徐々に画面が出現）
	FADE_OUT,			//フェードアウト中（徐々に画面が消える）
	FADE_OUT_WAIT,		//フェードアウト後の真っ暗状態
};

class CFade
{
private:
	static tagFadeSteate	m_state;	//現在のフェード状況
	static int				m_count;	//フェードの時間のカウント

public:
	//フェードを初期化する
	static void Init();
	//フェード処理更新
	static void Step();
	//フェード用の画像描画
	static void Draw();

	//フェードイン呼び出し
	static void RequestFadeIn();
	//フェードアウト呼び出し
	static void RequestFadeOut();
	//フェードインが終了しているか
	static bool IsEndFadeIn();
	//フェードアウトが終了しているか
	static bool IsEndFadeOut();


};


