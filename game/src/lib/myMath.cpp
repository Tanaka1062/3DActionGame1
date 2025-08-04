#include "myMath.h"
#include <math.h>

float MyMath(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	return sqrtf(x * x + y * y);

}

//VECTOR型の足し算
VECTOR VecAdd(VECTOR pos1, VECTOR pos2)
{
	VECTOR pos = VGet(pos1.x + pos2.x, pos1.y + pos2.y, pos1.z + pos2.z);

	return pos;
};

//ベクトルの生成
VECTOR VecCreate(VECTOR state_vec, VECTOR end_vec)
{
	VECTOR str = VGet(end_vec.x - state_vec.x, end_vec.y - state_vec.y, end_vec.z - state_vec.z);

	return str;

}

//ベクトルの長さを取得する
float GetVecLength(VECTOR vec)
{
	float len = 0.0f;

	len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);


	return len;
}

//ベクトルの正規化
VECTOR VecNormalize(VECTOR vec, float veclen)
{
	VECTOR vecize;

	vecize.x = vec.x / veclen;
	vecize.y = vec.y / veclen;
	vecize.z = vec.z / veclen;

	return vecize;
}

VECTOR VecScale(VECTOR vec, float scale)
{
	vec.x *= scale;
	vec.y *= scale;
	vec.z *= scale;

	return vec;
}

//内積
float VecDot(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	return ret;
}

//外積
float VecCross2D(VECTOR vec1, VECTOR vec2)
{
	float ret = vec1.x * vec2.y - vec1.y * vec2.x;

	return ret;
}
//VECTOR VecCross(VECTOR vec1, VECTOR vec2)
//{
//	//VECTOR 
//
//}