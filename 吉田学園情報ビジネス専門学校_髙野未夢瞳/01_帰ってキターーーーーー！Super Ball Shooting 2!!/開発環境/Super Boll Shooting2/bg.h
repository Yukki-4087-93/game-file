//---------------------------------------------------------
//
//�w�i
//Author::TAKANO
//
//---------------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"

//----------------------------------------
//�N���X��`
//�w�i(�I�u�W�F�N�g����h��)
//----------------------------------------
class CBg : public CObject2D
{
public:
	CBg();																//�R���X�g���N�^
	~CBg() override;													//�f�X�g���N�^

	void Uninit() override;
	void Update() override;												//�X�V
	void Draw() override;												//�`��

public:
	 static CBg * Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd,CTexture::TEXTURE tex);		//�N���G�C�g

private:
	//D3DXVECTOR3 m_move;							//�ړ���
};

#endif // !_BG_H_
