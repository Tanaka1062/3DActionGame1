#pragma once

#include <DxLib.h>

class CCollision
{
public:

	// 点と四角の当たり判定
	//	_dotPos		:	点の座標
	//	_squarePos	:	四角形の中心座標
	//	_width		:	四角形の横幅
	//	_height		:	四角形の縦幅
	//	return		:	true=当たった　false=当たっていない
	static bool ChekHitDotToSquare(VECTOR _dotPos, VECTOR _squarePos,
		int _width, int _height);

	// 矩形同士の当たり判定
	//	_squarePos	:	矩形の中心座標
	//	_width		:	矩形の横幅
	//	_height		:	矩形の縦幅
	//	return		:	true=当たった　false=当たっていない
	static bool CheckHitSquareToSquare(VECTOR _squarePos1, int _width1, int height1,
		VECTOR _squarePos2, int _width2, int _height2);

	// 円同士の当たり判定
	//	_circlePos	:	円の中心座標
	//	_radius		:	円の半径
	//	return		:	true=当たった　false=当たっていない
	static bool CheckHitCircleToCircle(VECTOR _circlePos1, int _radius1,
		VECTOR _circlePos2, int _radius2);

	// 立方体同士の当たり判定
	//	_pos		:	箱の中心座標
	//	_size		:	箱のサイズ
	//	return		:	true=当たった　false=当たっていない
	static bool CheckHitBoxToBox(VECTOR _pos1, VECTOR _size1,
		VECTOR _pos2, VECTOR _size2);

	// 球同士の当たり判定
	//	_spherePos	:	球の中心座標
	//	_radius		:	球のサイズ
	//	return		:	true=当たった　false=当たっていない
	static bool CheckHitSphereToSphere(VECTOR _spherePos1, float _radius1,
		VECTOR _spherePos2, float _radius2);

	//立方体と球の当たり判定
	// _boxPos		:	箱の中心座標
	// _boxSize		:	箱のサイズ
	// _spherePos	:	球の中心座標
	// _sphereRadius:	球の半径
	// rerurn		:	true=当たった　false=当たっていない
	static bool CheckHitBoxToSohere(VECTOR _boxPos, VECTOR _boxSize,
		VECTOR _spherePos, float _sphereRadius);

};


