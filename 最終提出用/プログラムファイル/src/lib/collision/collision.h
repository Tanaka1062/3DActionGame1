#pragma once

#include <DxLib.h>

class CCollision
{
public:

	// 点と四角の当たり判定
	//	dotPos		:	点の座標
	//	squarePos	:	四角形の中心座標
	//	width		:	四角形の横幅
	//	height		:	四角形の縦幅
	//	@return		:	true=当たった　false=当たっていない
	static bool ChekHitDotToSquare(VECTOR dotPos, VECTOR squarePos,
		int width, int height);

	// 矩形同士の当たり判定
	//	squarePos	:	矩形の中心座標
	//	width		:	矩形の横幅
	//	height		:	矩形の縦幅
	//	@return		:	true=当たった　false=当たっていない
	static bool CheckHitSquareToSquare(VECTOR squarePos1, int width1, int height1,
		VECTOR squarePos2, int width2, int height2);

	// 円同士の当たり判定
	//	circlePos	:	円の中心座標
	//	radius		:	円の半径
	//	@return		:	true=当たった　false=当たっていない
	static bool CheckHitCircleToCircle(VECTOR circlePos1, int radius1,
		VECTOR circlePos2, int radius2);

	// 立方体同士の当たり判定
	//	pos			:	箱の中心座標
	//	size		:	箱のサイズ
	//	@return		:	true=当たった　false=当たっていない
	static bool CheckHitBoxToBox(VECTOR pos1, VECTOR size1,
		VECTOR pos2, VECTOR size2);

	// 球同士の当たり判定
	//	spherePos	:	球の中心座標
	//	radius		:	球のサイズ
	//	@return		:	true=当たった　false=当たっていない
	static bool CheckHitSphereToSphere(VECTOR spherePos1, float radius1,
		VECTOR spherePos2, float radius2);

};


