#pragma once
#include <DxLib.h>

float MyMath(float x1, float y1, float x2, float y2);

//VECTOR型の足し算
VECTOR VecAdd(VECTOR pos1, VECTOR pos2);

//ベクトルの生成
VECTOR VecCreate(VECTOR state_vec, VECTOR end_vec);

//ベクトルの長さを取得する
float GetVecLength(VECTOR vec);

//ベクトルの正規化
VECTOR VecNormalize(VECTOR vec,float veclen);

//ベクトルのスカラー倍
VECTOR VecScale(VECTOR vec, float scalar);

//内積
float VecDot(VECTOR vec1, VECTOR vec2);

//外積
float VecCross2D(VECTOR vec1, VECTOR vec2);
//VECTOR VecCross(VECTOR vec1, VECTOR vec2);