#pragma once

#include<DxLib.h>
#include<math.h>

class CCollision
{
public:

//点と四角の当たり判定
//	dotPos		:	点の座標
//	squarePos	:	四角形の中心座標
//	width		:	四角形の横幅
//	height		:	四角形の縦幅
//	return		:	true=当たった false=当たってない
//点と四角形の当たり判定
	static bool ChekHitDotToSquare(VECTOR dotPos, VECTOR squarePos, int width, int height);

//矩形同士の当たり判定
// squarePos1	:	一つ目の矩形の中心座標
// width1		:	一つ目の矩形の横幅
// height1		:	一つ目の矩形の縦幅
// squarePos2	:	二つ目の矩形の中心座標
// width2		:	二つ目の矩形の横幅
// height2		:	二つ目の矩形の縦幅
//矩形同士の当たり判定
	static bool CheckHitSquareToSqure(VECTOR squarePos1, int width1, int height1,
										VECTOR squarePos2, int width2, int height2);
//円同士の当たり判定
// circlePos1	:	一つ目の円の中心座標
// redius1		:	一つ目の円の半径
// circlePos2	:	二つ目の円の中心座標
// redius2		:	二つ目の円の半径
//円同士の当たり判定
	static bool CheckHitCircleToCircle(VECTOR circlePos1, int redius1,
										VECTOR circlePos2, int redius2);
//扇と点の当たり判定
// dotPos			:	点の座標
// fanPos			:	扇の中心座標
// rangeDegree		:	扇の範囲（角度）
// length			:	扇の長さ
// directionDegree	:	扇の方向(角度)
//扇と点の当たり判定
	static bool CheckHitDotToFan(VECTOR dotPos, VECTOR fanPos, float rangeDegree, float length, float directionDegree);

};

