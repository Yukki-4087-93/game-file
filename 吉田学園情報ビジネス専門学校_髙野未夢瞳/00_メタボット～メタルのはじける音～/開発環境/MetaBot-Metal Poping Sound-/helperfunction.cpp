//--------------------------------------------------------------------------------------
//
// �w���p�[�֐�
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "helperfunction.h"

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CHelperFunction::CHelperFunction()
{
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CHelperFunction::~CHelperFunction()
{
}

//--------------------------------------
//�~���m�̓����蔻��
//--------------------------------------
bool CHelperFunction::CircleCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//�v�Z���ʂ���
	float fAnser = fRadius1 + fRadius2;			//���a���m�̉��Z���ʂ���	

	//������ۑ�����ϐ�
	float fDifference_X, fDifference_Z;

	//������ۑ�����ϐ�
	float fRange;

	//X�̍���
	fDifference_X = pos1.x - pos2.x;

	//Z�̍���
	fDifference_Z = pos1.z - pos2.z;

	//2�_�̋����̌v�Z
	fRange = sqrtf(fDifference_X * fDifference_X + fDifference_Z * fDifference_Z);

	if (fAnser > fRange)
	{//�������Ă�����
		return true;
	}

	//�������Ă��Ȃ�������
	return false;
}

//--------------------------------------
//�����m�̓����蔻��
//--------------------------------------
bool CHelperFunction::SphereCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//�v�Z���ʂ���
	float fAnser = fRadius1 + fRadius2;			//���a���m�̉��Z���ʂ���

	//�������o��
	D3DXVECTOR3 Vec = pos1 - pos2;

	//������ۑ�����ϐ�
	float fRange;

	//2�_�̋����̌v�Z
	fRange = sqrtf(Vec.x * Vec.x + Vec.y * Vec.y + Vec.z * Vec.z);

	if (fAnser > fRange)
	{//�������Ă�����
		return true;
	}

	//�������Ă��Ȃ�������
	return false;
}

//--------------------------------------
//���^�̓����蔻��(���`)
//--------------------------------------
bool CHelperFunction::BoxCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2, D3DXVECTOR3 posOld)
{
	float fRight = pos2.x + size2.x / 2;
	float fLeft = pos2.x - size2.x / 2;
	float fBack = pos2.z + size2.z / 2;
	float fFlont = pos2.z - size2.z / 2;

	if (pos1.x + size1.x / 2 > fLeft &&
		pos1.x - size1.x / 2 < fRight)
	{
		if (posOld.z + size1.z / 2 <= fFlont &&
			pos1.z + size1.z / 2 > fFlont)
		{//�O������̔���
			return true;
		}

		if (posOld.z - size1.z / 2 >= fBack &&
			pos1.z - size1.z / 2 < fBack)
		{
			return true;
		}
	}

	if (pos1.z + size1.z / 2 > fFlont &&
		pos1.z - size1.z / 2 < fBack)
	{
		if (posOld.x + size1.x / 2 <= fLeft &&
			pos1.x + size1.x / 2 > fLeft)
		{//�O������̔���
			return true;
		}

		if (posOld.x - size1.x / 2 >= fRight &&
			pos1.x - size1.x / 2 < fRight)
		{//�O������̔���
			return true;
		}
	}

	return false;
}

//--------------------------------------
//�����_���֐�
//--------------------------------------
float CHelperFunction::FloatRandom(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}
