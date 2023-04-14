//-----------------------------------------------------------------------------------------------------------
//
//���b�V��
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _MESHIFILD_H_													//���̃}�N����`���Ȃ���Ȃ�������
#define _MESHIFILD_H_													//��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------
#include"object3d.h"

//-----------------------------------------------------------
//�N���X��`
//���b�V���t�B�[���h�A�I�u�W�F�N�g3D���p��
//-----------------------------------------------------------
class CMeshField : public CObject3D
{
public:
	CMeshField();												//�R���X�g���N�^
	~CMeshField();												//�f�X�g���N�^
	static CMeshField* Create();								//����
	HRESULT Init();												//������
	void Uninit();												//�I��
	void Update();												//�X�V
	void Draw();												//�`��
	float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);			//�|���Z
	float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);			//�p�x
	void Collision(D3DXVECTOR3 *pos);							//�����蔻��

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff ;							//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;										//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X

};

#endif // !MESHIFIL_H_
