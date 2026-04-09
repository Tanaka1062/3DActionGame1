#pragma once
#include "cameraBase.h"
#include "../player/playerManager.h"
#include "../map/mapBase.h"

//複数のカメラタイプを管理するクラス
class CCameraManager
{
public:

	//カメラタイプID
	enum tagCAMERA_ID
	{
		CAMERA_ID_MAP,						//マップのカメラ
		CAMERA_ID_DEBUG,					//デバッグ時のカメラ
		CAMERA_ID_TITLE,					//タイトル画面のカメラ
		CAMERA_ID_SELECT,					//セレクト画面のカメラ
		CAMERA_ID_RESULT,					//リザルト画面のカメラ

		CAMERA_ID_NUM,						//カメラのタイプの数
	};

private:
	static CCameraBase* m_camera[CAMERA_ID_NUM];	//カメラ
	static tagCAMERA_ID m_id;						//カメラのタイプ
	static VECTOR m_rot;							//カメラの回転値
	
public:

	//コンストラクタ・デストラクタ
	CCameraManager();
	~CCameraManager();

	//初期化
	static void Init(CMapBase* _map = nullptr);

	//毎フレームする処理
	static void Step(CMapManager* _mapManager = nullptr,CPlayerManager* _playerManager = nullptr);

	//表示
	static void Draw();

	//カメラの更新
	// @_tagetPos	:カメラの注視点の座標
	static void Update(VECTOR _tagetPos);

	//終了処理
	static void Exit();

	//カメラのタイプ切り替え
	static void ChangeCamera(tagCAMERA_ID _id) { m_id = _id; };
	//カメラタイプの取得
 	static tagCAMERA_ID GetID() { return m_id; }

	//カメラの回転値の取得
	static VECTOR  GetRot() { return m_rot; }

	//カメラの注視点を取得
	static VECTOR GetFocusPos() { return m_camera[m_id]->GetFocusPos(); }

};

