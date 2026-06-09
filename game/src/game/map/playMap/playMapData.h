#pragma once
namespace playMap
{
	enum tagMapSelect
	{
		MAP_1,		//マップ1つ目
		MAP_2,		//マップ2つ目

		MAP_NUM,	//マップの数
	};

}


class CPlayMapData
{
private:
	static CPlayMapData* m_instance;		//インスタンス
public:

	static CPlayMapData* GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new CPlayMapData;
		}

		return m_instance;
	}

	static void DeleteInstance()
	{
		if (m_instance != nullptr)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

private:
	//コンストラクタ
	CPlayMapData();

	playMap::tagMapSelect m_selectMap;	//選択されたマップ
public:

	//初期化
	void Init();

	//選択されたマップを取得
	playMap::tagMapSelect GetSelectMap() { return m_selectMap; }

	//選択されたマップを設定
	void SetSelectMap(playMap::tagMapSelect _selectMap) { m_selectMap = _selectMap; }
};

