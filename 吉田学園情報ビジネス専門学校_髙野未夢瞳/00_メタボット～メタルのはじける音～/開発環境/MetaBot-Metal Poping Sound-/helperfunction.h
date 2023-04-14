//--------------------------------------------------------------------------------------
//
// �w���p�[�֐�
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _HELPERFUNCTION_H_
#define _HELPERFUNCTION_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include <d3dx9.h>

//----------------------------------------
//�N���X��`
//�w���p�[�֐�
//----------------------------------------
class CHelperFunction
{
public:
	CHelperFunction();									//�R���X�g���N�^
	~CHelperFunction();									//�f�X�g���N�^
	static bool CircleCollision(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2);
	static bool SphereCollision(D3DXVECTOR3 pos1,float fRadius1, D3DXVECTOR3 pos2, float fRadius2);
	static bool BoxCollision(D3DXVECTOR3 pos1, D3DXVECTOR3 size1, D3DXVECTOR3 pos2, D3DXVECTOR3 size2, D3DXVECTOR3 posOld);
	static float FloatRandom(float fMax, float fMin);

protected:

};

#endif // !_HELPERFUNCTION_H_
