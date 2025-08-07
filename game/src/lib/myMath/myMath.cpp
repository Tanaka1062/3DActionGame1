#include "myMath.h"
#include <math.h>

float CMyMath::MyMath(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;

	return sqrtf(x * x + y * y);

}

//ベクトルの計算==============================

//VECTOR型の足し算
VECTOR CMyMath::VecAdd(VECTOR pos1, VECTOR pos2)
{
	VECTOR pos = VGet(pos1.x + pos2.x, pos1.y + pos2.y, pos1.z + pos2.z);

	return pos;
};

//ベクトルの生成
VECTOR CMyMath::VecCreate(VECTOR state_vec, VECTOR end_vec)
{
	VECTOR str = VGet(end_vec.x - state_vec.x, end_vec.y - state_vec.y, end_vec.z - state_vec.z);

	return str;

}

//ベクトルの長さを取得する
float CMyMath::GetVecLength(VECTOR vec)
{
	float len = 0.0f;

	len = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);


	return len;
}

//ベクトルの正規化
VECTOR CMyMath::VecNormalize(VECTOR vec, float veclen)
{
	VECTOR vecize;

	vecize.x = vec.x / veclen;
	vecize.y = vec.y / veclen;
	vecize.z = vec.z / veclen;

	return vecize;
}

VECTOR CMyMath::VecScale(VECTOR vec, float scale)
{
	vec.x *= scale;
	vec.y *= scale;
	vec.z *= scale;

	return vec;
}

//内積
float CMyMath::VecDot(VECTOR vec1, VECTOR vec2)
{
	float ret;

	ret = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	return ret;
}

//外積
float CMyMath::VecCross2D(VECTOR vec1, VECTOR vec2)
{
	float ret = vec1.x * vec2.y - vec1.y * vec2.x;

	return ret;
}

//============================================


//行列の計算==================================

//単位行列を取得する
MATRIX CMyMath::GetIdentityMatrix()
{
	MATRIX mat;
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0;j<4;j++)
		{
			if (i == j)
			{
				mat.m[i][j] = 1;
			}
			else
			{
				mat.m[i][j] = 0;
			}
		}
	}

	return mat;
}

//平行移動行列を取得する(float用)
MATRIX CMyMath::GetTranslateMatrix(float _moveX, float _moveY, float _moveZ)
{
	MATRIX mat = GetIdentityMatrix();
	mat.m[0][3] = _moveX;
	mat.m[1][3] = _moveY;
	mat.m[2][3] = _moveZ;

	return mat;
}

//平行移動行列を取得する(VECTOR用)
MATRIX CMyMath::GetTranslateMatrix(VECTOR _move)
{
	MATRIX mat = GetIdentityMatrix();
	mat.m[0][3] = _move.x;
	mat.m[1][3] = _move.y;
	mat.m[2][3] = _move.z;

	return mat;

}

//拡縮行列を取得する(float用)
MATRIX CMyMath::GetScaleMatrix(float _scaleX, float _scaleY, float _scaleZ)
{
	MATRIX mat = GetIdentityMatrix();
	mat.m[0][0] = _scaleX;
	mat.m[1][1] = _scaleY;
	mat.m[2][2] = _scaleZ;

	return mat;
}

//拡縮行列を取得する(VECTOR用)
MATRIX CMyMath::GetScaleMatrix(VECTOR _scale)
{
	MATRIX mat = GetIdentityMatrix();
	mat.m[0][0] = _scale.x;
	mat.m[1][1] = _scale.y;
	mat.m[2][2] = _scale.z;

	return mat;

}

//X軸回転行列を取得する
MATRIX CMyMath::GetPitchMatrix(float _rotX)
{
	MATRIX mat = GetIdentityMatrix();
	mat.m[1][1] = cosf(_rotX);
	mat.m[1][2] = -sinf(_rotX);
	mat.m[2][1] = sin(_rotX);
	mat.m[2][2] = cos(_rotX);

	return mat;
}

//Y軸回転行列を取得する
MATRIX CMyMath::GetYawMatrix(float _rotY)
{
	MATRIX mat = GetIdentityMatrix();
	mat.m[0][0] = cosf(_rotY);
	mat.m[0][2] = sinf(_rotY);
	mat.m[2][0] = -sinf(_rotY);
	mat.m[2][2] = cosf(_rotY);

	return mat;
}

//Z軸回転行列を取得する
MATRIX CMyMath::GetRollMatrix(float _rotZ)
{
	MATRIX mat = GetIdentityMatrix();
	mat.m[0][0] = cosf(_rotZ);
	mat.m[0][1] = -sinf(_rotZ);
	mat.m[1][0] = sinf(_rotZ);
	mat.m[1][1] = cosf(_rotZ);

	return mat;
}

//2つの行列の足し算する
MATRIX CMyMath::MatAdd(MATRIX _mat1, MATRIX _mat2)
{
	MATRIX mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = _mat1.m[i][j] + _mat2.m[i][j];
		}
	}

	return mat;
}

//2つの行列の引き算する
MATRIX CMyMath::MatSub(MATRIX _mat1, MATRIX _mat2)
{
	MATRIX mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = _mat1.m[i][j] - _mat2.m[i][j];
		}
	}

	return mat;

}

//行列をスカラー倍する
MATRIX CMyMath::MatScale(MATRIX _mat, float _scale)
{
	MATRIX mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = _mat.m[i][j] * _scale;
		}
	}

	return mat;

}

//2つの行列の掛け算をする
MATRIX CMyMath::MatMult(MATRIX _mat1, MATRIX _mat2)
{
	MATRIX mat;
	MATRIX ans;
	for (int i1 = 0; i1 < 4; i1++)
	{
		for (int i2 = 0; i2 < 4; i2++) 
		{
			mat.m[i1][i2] = 0;
			for (int i3 = 0; i3 < 4; i3++)
			{
				mat.m[i1][i2] += _mat1.m[i1][i3] * _mat2.m[i3][i2];
				ans = mat;
			}
		}
	}

	return mat;
}

//行列×ベクトルをする
VECTOR CMyMath::MatTransform(MATRIX _mat, VECTOR _vec)
{
	float num1[4];
	num1[0] = _vec.x;
	num1[1] = _vec.y;
	num1[2] = _vec.z;
	num1[3] = 1;

	float num2[4] = {0,0,0,0};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			num2[i] = _mat.m[i][j] * num1[j] + num2[i];
		}
	}

	VECTOR vec;
	vec.x = num2[0];
	vec.y = num2[1];
	vec.z = num2[2];

	return vec;
}

//行列転置をする
MATRIX CMyMath::MatTranspose(MATRIX _mat)
{
	MATRIX mat;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[j][i] = _mat.m[i][j];
		}
	}

	return mat;
}

//============================================