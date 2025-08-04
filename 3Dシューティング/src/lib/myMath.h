#pragma once
#include <DxLib.h>

float MyMath(float x1, float y1, float x2, float y2);

//ベクトルの計算==============================

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

//============================================


//行列の計算==================================

//単位行列を取得する
MATRIX GetIdentityMatrix();

//平行移動行列を取得する(float用)
MATRIX GetTranslateMatrix(float _moveX, float _moveY, float _moveZ);

//平行移動行列を取得する(VECTOR用)
MATRIX GetTranslateMatrix(VECTOR _move);

//拡縮行列を取得する(float用)
MATRIX GetScaleMatrix(float _scaleX, float _scaleY, float _scaleZ);

//拡縮行列を取得する(VECTOR用)
MATRIX GetScaleMatrix(VECTOR _scale);

//X軸回転行列を取得する
MATRIX GetPitchMatrix(float _rotX);

//Y軸回転行列を取得する
MATRIX GetYawMatrix(float _rotY);

//Z軸回転行列を取得する
MATRIX GetRollMatrix(float _rotZ);

//2つの行列の足し算する
MATRIX MatAdd(MATRIX _mat1, MATRIX _mat2);

//2つの行列の引き算する
MATRIX MatSub(MATRIX _mat1, MATRIX _mat2);

//行列をスカラー倍する
MATRIX MatScale(MATRIX _mat, float _scale);

//2つの行列の掛け算をする
MATRIX MatMult(MATRIX _mat1, MATRIX _mat2);

//行列×ベクトルをする
VECTOR MatTransform(MATRIX _mat, VECTOR _vec);

//行列転置をする
MATRIX MatTranspose(MATRIX _mat);

//============================================