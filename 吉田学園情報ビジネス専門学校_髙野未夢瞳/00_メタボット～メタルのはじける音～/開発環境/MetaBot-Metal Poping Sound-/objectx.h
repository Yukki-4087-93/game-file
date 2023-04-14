//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object.h"
#include "texture.h"

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CObjectX : public CObject
{
public:
	// ���_�f�[�^
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;														//���_���W
		D3DXVECTOR3 nor;														//�@���x�N�g��
		D3DCOLOR col;															//���_�J���[
		D3DXVECTOR2 tex;														//�e�N�X�`���̍��W
	};

public:
	CObjectX();																	//�R���X�g���N�^
	~CObjectX();																//�f�X�g���N�^
	HRESULT Init()override;														//������
	static CObjectX * Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd);		//�N���G�C�g
	void Update()override;														//�X�V
	void Draw()override;														//�`��
	void Uninit()override;														//�I��
	const D3DXVECTOR3& Getpos() const;											//�ʒu�̎擾

protected:
	LPD3DXMESH m_Mesh;															//���b�V�����
	LPD3DXBUFFER m_BuffMat;														//�}�e���A�����
	DWORD m_nNumMat;															//�}�e���A�����̐�
	D3DXVECTOR3 m_rotDest;														//���̊p�x
	D3DXMATRIX m_mtxWorld;														//���[���h�}�g���b�N�X
};

#endif // !_OBJECTX_H_
