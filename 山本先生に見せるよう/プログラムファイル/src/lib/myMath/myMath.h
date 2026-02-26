#pragma once
#include <DxLib.h>

class CMyMath
{
public:


static float MyMath(float x1, float y1, float x2, float y2);

//ベクトルの計算==============================

//VECTOR型の足し算
static VECTOR VecAdd(VECTOR pos1, VECTOR pos2);

//ベクトルの生成
static VECTOR VecCreate(VECTOR state_vec, VECTOR end_vec);

//ベクトルの長さを取得する
static float GetVecLength(VECTOR vec);

//ベクトルの正規化
static VECTOR VecNormalize(VECTOR vec,float veclen);

//ベクトルのスカラー倍
static VECTOR VecScale(VECTOR vec, float scalar);

//内積
static float VecDot(VECTOR vec1, VECTOR vec2);

//外積
static float VecCross2D(VECTOR vec1, VECTOR vec2);

//============================================


//行列の計算==================================

//単位行列を取得する
static MATRIX GetIdentityMatrix();

//平行移動行列を取得する(float用)
static MATRIX GetTranslateMatrix(float _moveX, float _moveY, float _moveZ);

//平行移動行列を取得する(VECTOR用)
static MATRIX GetTranslateMatrix(VECTOR _move);

//拡縮行列を取得する(float用)
static MATRIX GetScaleMatrix(float _scaleX, float _scaleY, float _scaleZ);

//拡縮行列を取得する(VECTOR用)
static MATRIX GetScaleMatrix(VECTOR _scale);

//X軸回転行列を取得する
static MATRIX GetPitchMatrix(float _rotX);

//Y軸回転行列を取得する
static MATRIX GetYawMatrix(float _rotY);

//Z軸回転行列を取得する
static MATRIX GetRollMatrix(float _rotZ);

//2つの行列の足し算する
static MATRIX MatAdd(MATRIX _mat1, MATRIX _mat2);

//2つの行列の引き算する
static MATRIX MatSub(MATRIX _mat1, MATRIX _mat2);

//行列をスカラー倍する
static MATRIX MatScale(MATRIX _mat, float _scale);

//2つの行列の掛け算をする
static MATRIX MatMult(MATRIX _mat1, MATRIX _mat2);

//行列×ベクトルをする
static VECTOR MatTransform(MATRIX _mat, VECTOR _vec);

//行列転置をする
static MATRIX MatTranspose(MATRIX _mat);

//============================================

};

