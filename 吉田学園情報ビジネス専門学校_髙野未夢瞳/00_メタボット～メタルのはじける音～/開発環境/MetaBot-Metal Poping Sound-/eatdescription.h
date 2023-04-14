//--------------------------------------------------------------------------------------
//
//���i����
//Author;takano
//
//--------------------------------------------------------------------------------------
#ifndef _EATDESCRIPTION_H_													//���̃}�N����`���Ȃ���Ȃ�������
#define _EATDESCRIPTION_H_													//��d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include <d3dx9.h>
#include "object3d.h"

//----------------------------------------
//�N���X��`
//���i�����֘A
//----------------------------------------
class CEatDescription : public CObject3D
{
public:
	CEatDescription();								//�R���X�g���N�^
	~CEatDescription();								//�f�X�g���N�^
	HRESULT Init();									//������
	void Uninit();									//�I��
	void Update();									//�X�V
	void Draw();									//�`��
	void HitDescription();							//�����蔻��
	void HitEatDescription();						//�����蔻��


public:
	static CEatDescription* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHi, float fWd, ObjType type, CTexture::TEXTURE tex);		//���i�����̐���
	void ChangeSE();

private:
	int m_nCHangeSound;				//�ǂ�SE���g�p���邩���߂邽�߂̕ϐ�
	int m_HitCount;					//���������Ƃ��̓����蔻������Z���邽�߂̕ϐ�
};

#endif // !EATDESCRIPTION_H_

