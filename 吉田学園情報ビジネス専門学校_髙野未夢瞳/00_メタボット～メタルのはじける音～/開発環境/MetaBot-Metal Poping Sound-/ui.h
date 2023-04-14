//--------------------------------------------------------------------------------------
//
// User Interface
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _UI_H_
#define _UI_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"
#include "renderer.h"
#include "texture.h"

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CUi : public CObject2D
{
public:
	CUi();																//�R���X�g���N�^
	~CUi();																//�f�X�g���N�^
	static CUi * Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd, CTexture::TEXTURE tex);		//�N���G�C�g
	void Uninit()override;												//�I��

private:
};

#endif // !_UI_H_
