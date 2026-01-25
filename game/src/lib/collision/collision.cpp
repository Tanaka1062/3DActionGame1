#include "collision.h"

//---------------------------------
// 点と四角の当たり判定
//---------------------------------
bool CCollision::ChekHitDotToSquare(VECTOR _dotPos, VECTOR _squarePos,
	int _width, int _height)
{
	// 四角形の上下左右それぞれの座標を計算する
	float up = _squarePos.y - _height * 0.5f;
	float down = _squarePos.y + _height * 0.5f;
	float left = _squarePos.x - _width * 0.5f;
	float right = _squarePos.x + _width * 0.5f;

	// 4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (_dotPos.x >= left && _dotPos.x <= right
		&& _dotPos.y >= up && _dotPos.y <= down)
	{
		return true;
	}
	else return false;
}


//---------------------------------
// 矩形同士の当たり判定
//---------------------------------
bool CCollision::CheckHitSquareToSquare(VECTOR _squarePos1, int _width1, int _height1,
	VECTOR _squarePos2, int _width2, int _height2)
{
	// 四角形の上下左右それぞれの座標を計算する
	float up1 = _squarePos1.y - _height1 * 0.5f;
	float down1 = _squarePos1.y + _height1 * 0.5f;
	float left1 = _squarePos1.x - _width1 * 0.5f;
	float right1 = _squarePos1.x + _width1 * 0.5f;

	float up2 = _squarePos2.y - _height2 * 0.5f;
	float down2 = _squarePos2.y + _height2 * 0.5f;
	float left2 = _squarePos2.x - _width2 * 0.5f;
	float right2 = _squarePos2.x + _width2 * 0.5f;

	// 4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (left1 <= right2 && right1 >= left2
		&& up1 <= down2 && down1 >= up2)
	{
		return true;
	}
	else return false;
}


//---------------------------------
// 円同士の当たり判定
//---------------------------------
bool CCollision::CheckHitCircleToCircle(VECTOR _circlePos1, int _radius1,
	VECTOR _circlePos2, int _radius2)
{
	// 円1から円2までの距離を計算
	float lengthX = _circlePos1.x - _circlePos2.x;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
	lengthX *= lengthX;
	float lengthY = _circlePos1.y - _circlePos2.y;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
	lengthY *= lengthY;
	float length = lengthX + lengthY;	// これがaの2乗＋bの2乗

	// 2つの円の半径を加算し、2乗する
	float lengthRadius = (float)(_radius1 + _radius2);
	lengthRadius *= lengthRadius;


	// 以下の条件を満たせばヒットする！
	if (lengthRadius >= length)
	{
		return true;
	}
	else return false;
}

//---------------------------------
// 立方体同士の当たり判定
//---------------------------------
bool CCollision::CheckHitBoxToBox(VECTOR _pos1, VECTOR _size1,
	VECTOR _pos2, VECTOR _size2)
{
	// 四角形の上下左右手前奥それぞれの座標を計算する
	float up1 = _pos1.y - _size1.y * 0.5f;
	float down1 = _pos1.y + _size1.y * 0.5f;
	float left1 = _pos1.x - _size1.x * 0.5f;
	float right1 = _pos1.x + _size1.x * 0.5f;
	float front1 = _pos1.z - _size1.z * 0.5f;
	float back1 = _pos1.z + _size1.z * 0.5f;

	float up2 = _pos2.y - _size2.y * 0.5f;
	float down2 = _pos2.y + _size2.y * 0.5f;
	float left2 = _pos2.x - _size2.x * 0.5f;
	float right2 = _pos2.x + _size2.x * 0.5f;
	float front2 = _pos2.z - _size2.z * 0.5f;
	float back2 = _pos2.z + _size2.z * 0.5f;

	// 4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (left1 <= right2 && right1 >= left2
		&& up1 <= down2 && down1 >= up2
		&& front1 <= back2 && back1 >= front2)
	{
		return true;
	}
	else return false;
}

//---------------------------------
// 球同士の当たり判定
//---------------------------------
bool CCollision::CheckHitSphereToSphere(VECTOR _spherePos1, float _radius1,
	VECTOR _spherePos2, float _radius2)
{
	// 球1から球2までの距離を計算
	float lengthX = _spherePos1.x - _spherePos2.x;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
	lengthX *= lengthX;
	float lengthY = _spherePos1.y - _spherePos2.y;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
	lengthY *= lengthY;
	float lengthZ = _spherePos1.z - _spherePos2.z;	// どうせ2乗するとマイナスが消えるので、順番はどうでもいい
	lengthZ *= lengthZ;
	float length = lengthX + lengthY + lengthZ;		// これがaの2乗＋bの2乗

	// 2つの円の半径を加算し、2乗する
	float lengthRadius = _radius1 + _radius2;
	lengthRadius *= lengthRadius;

	// 以下の条件を満たせばヒットする！
	if (lengthRadius >= length)
	{
		return true;
	}
	else return false;
}

//---------------------------------
//立方体と球の当たり判定
//---------------------------------
bool CCollision::CheckHitBoxToSohere(VECTOR _boxPos, VECTOR _boxSize,
	VECTOR _spherePos, float _sphereRadius)
{
	// 四角形の上下左右手前奥それぞれの座標を計算する
	float boxUp = _boxPos.y - _boxSize.y * 0.5f;
	float boxDown = _boxPos.y + _boxSize.y * 0.5f;
	float boxLeft = _boxPos.x - _boxSize.x * 0.5f;
	float boxRight = _boxPos.x + _boxSize.x * 0.5f;
	float boxFront = _boxPos.z - _boxSize.z * 0.5f;
	float boxBack = _boxPos.z + _boxSize.z * 0.5f;

	//値をmin～maxの間に収める
	auto Clamp = [](float v, float min, float max)
		{
			if (v < min)return min;
			if (v > max)return max;
			return v;
		};

	//球と箱の最近接点を求める
	VECTOR closest;
	closest.x = Clamp(_spherePos.x, boxLeft, boxRight);
	closest.y = Clamp(_spherePos.y, boxDown, boxUp);
	closest.z = Clamp(_spherePos.z, boxBack, boxFront);

	//最近接点から球の中心座標までの距離を求める
	VECTOR diff = VSub(_spherePos, closest);

	//距離の２乗を求める
	float distSq = VDot(diff, diff);

	//求めた距離が球の半径の２乗以下なら当たっている
	if (distSq <= _sphereRadius * _sphereRadius)
	{
		return true;
	}
	return false;
}

