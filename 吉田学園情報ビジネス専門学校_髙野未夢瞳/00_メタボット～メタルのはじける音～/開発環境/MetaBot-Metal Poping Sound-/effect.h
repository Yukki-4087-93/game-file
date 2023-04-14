//--------------------------------------------------------------------------------------
//
//�G�t�F�N�g
//Author;takano
//
//--------------------------------------------------------------------------------------
#ifndef _EFFECT_H_													//���̃}�N����`���Ȃ���Ȃ�������
#define _EFFECT_H_													//��d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include <d3dx9.h>
#include "object3d.h"

//----------------------------------------
//�N���X��`
//�G�t�F�N�g�֘A
//----------------------------------------
class CEffect : public CObject3D
{
public:
	CEffect();										//�R���X�g���N�^
	~CEffect();										//�f�X�g���N�^
	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//�z�u

public:
	static CEffect* Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXCOLOR col,float fHi,float fWd);		//�G�t�F�N�g�̐���
	static void Spawn(D3DXVECTOR3 pos, int nMaxSpawn, float fRandMax, float fRandMin, D3DXCOLOR col, float fHi, float fWd);				//�G�t�F�N�g�̏o�����Ǘ�����֐�

private:
	D3DXVECTOR3 m_move;								//�ړ���
	D3DXCOLOR m_color;
};

#endif // !EFFECT_H_
