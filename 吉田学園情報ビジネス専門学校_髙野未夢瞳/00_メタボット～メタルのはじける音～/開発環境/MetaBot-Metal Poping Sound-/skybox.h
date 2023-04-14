//-----------------------------------------------------------------------------------------------------------
//
//���b�V��
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _SKYBOX_H_													//���̃}�N����`���Ȃ���Ȃ�������
#define _SKYBOX_H_													//��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------
#include"object3d.h"

//-----------------------------------------------------------
//�N���X��`
//-----------------------------------------------------------
class CSkybox : public CObject3D
{
public:
	CSkybox();													//�R���X�g���N�^
	~CSkybox();													//�f�X�g���N�^
	static CSkybox* Create(D3DXVECTOR3 pos);					//����
	HRESULT Init() override;									//������
	void Uninit() override;										//�I��
	void Update() override;										//�X�V
	void Draw() override;										//�`��
	void SetPos(D3DXVECTOR3 pos) override { m_pos = pos; }		//�ʒu�̐ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;							//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;										//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X

};

#endif // !MESHIFIL_H_
