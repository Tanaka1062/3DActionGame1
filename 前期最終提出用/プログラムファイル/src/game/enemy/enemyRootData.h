#pragma once

static const int ENEMY_NUM = 7;							//敵の数

static const int ENEMY_ROOT_MAX = 4;					//敵のルートの最大数

static const int ENEMY_ROOT[ENEMY_NUM][ENEMY_ROOT_MAX]	//敵のルートデータ
	= {
		{1,2,3,4},
		{6,-1,-1,-1},
		{8,-1,-1,-1},
		{10,-1,-1,-1},
		{12,-1,-1,-1},
		{14,-1,-1,-1},
		{16,-1,-1,-1},
	};

