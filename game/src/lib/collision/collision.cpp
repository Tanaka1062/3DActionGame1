#include "collision.h"


//　点と四角の当たり判定
bool CCollision::ChekHitDotToSquare(VECTOR dotPos, VECTOR squarePos,
	int width, int height)
{
	//四角形の上下左右それぞれの座標を計算する
	float up = squarePos.y - height * 0.5f;
	float down = squarePos.y + height * 0.5f;
	float left = squarePos.x - width * 0.5f;
	float right = squarePos.x + width * 0.5f;

	//4つの端をそれぞれチェックして、すべての条件を満たしたらヒット！
	if (dotPos.x >= left && dotPos.x <= right
		&& dotPos.y >= up && dotPos.y <= down)
	{
		return true;
	}
	else return false;
}

//矩形同士の当たり判定
bool CCollision::CheckHitSquareToSqure(VECTOR squarePos1, int width1, int height1,
	VECTOR squarePos2, int width2, int height2)
{
	//1つ目の四角形の上下左右の座標を計算する
	float up1 = squarePos1.y - height1 * 0.5f;
	float down1 = squarePos1.y + height1 * 0.5f;
	float left1 = squarePos1.x - width1 * 0.5f;
	float right1 = squarePos1.x + width1 * 0.5f;

	//2つ目の四角形の上下左右の座標を計算する
	float up2 = squarePos2.y - height2 * 0.5f;
	float down2 = squarePos2.y + height2 * 0.5f;
	float left2 = squarePos2.x - width2 * 0.5f;
	float right2 = squarePos2.x + width2 * 0.5f;

	//4つの端をそれぞれチェックして、すべての下の条件を満たしたらヒット！
	//矩形１の上端が矩形２の下端よりも上側にある
	//矩形１の下端が矩形２の上端よりも下側にある
	//矩形１の左端が矩形２の右端よりも左側にある
	//矩形１の右端が矩形２の左端よりも右側にある

	if (up1 <= down2 && down1 >= up2
		&& left1 <= right2 && right1 >= left2)
	{
		return true;
	}
	else return false;
}

// 円同士の当たり判定
bool CCollision::CheckHitCircleToCircle(VECTOR circlePos1, int redius1,
	VECTOR circlePos2, int redius2)
{
	//横の長さの２乗を調べる
	float lenX = circlePos1.x - circlePos2.x;
	lenX *= lenX;
	//縦の長さの２乗を調べる
	float lenY = circlePos1.y - circlePos2.y;
	lenY *= lenY;
	//最短距離の２乗
	float len = lenX + lenY;
	//半径２個を足した値の２乗を調べる
	float totleRedius = static_cast<float>(redius1 + redius2);

	totleRedius *= totleRedius;
	if (len < totleRedius)
	{
		return true;
	}
	else return false;

}

//扇と点の当たり判定
bool CCollision::CheckHitDotToFan(VECTOR dotPos,
	VECTOR fanPos, float rangeDegree, float length, float directionDegree)
{
	//点と扇のベクトルを求める
	 float vec_x = dotPos.x - fanPos.x;
	 float vec_y = dotPos.y - fanPos.y;
	
	//ベクトルの長さを求める
	 float vec_length = sqrtf((vec_x * vec_x) + (vec_y * vec_y));

	 //ベクトルと扇の長さの比較
	 if (length < vec_length)return false;	//当たっていない

	 //ラジアンに変換
	 float direction_rad = (directionDegree * DX_PI_F) / 180;

	 //方向ベクトルを求める
	 VECTOR fan_dir{0};
	 fan_dir.x = cosf(direction_rad);
	 fan_dir.y = sinf(direction_rad);

	 //扇と点のベクトルを単位ベクトルにする
	 VECTOR normal_fan_to_point{ 0 };
	 normal_fan_to_point.x = vec_x / vec_length;
	 normal_fan_to_point.y = vec_y / vec_length;

	 //内積計算
	 float dot = normal_fan_to_point.x * fan_dir.x + normal_fan_to_point.y * fan_dir.y;

	 //扇の範囲をcosにする
	 float fan_cos = cosf(((rangeDegree * DX_PI_F) / 180) / 2.0f);

	 //点が扇の範囲内にあるかを比較する
	 if (fan_cos > dot)return false;	//当たってない

	 //ここまで来たら当たっている
	 return true;
}

