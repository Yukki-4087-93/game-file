//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"
#include "renderer.h"

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CExplosion : public CObject2D
{
public:
	CExplosion();														//�R���X�g���N�^
	~CExplosion();														//�f�X�g���N�^
	HRESULT Init()override;												//������
	static CExplosion * Create(D3DXVECTOR3 pos, D3DXCOLOR col);			//�N���G�C�g
	void Update()override;												//�X�V
	void Draw()override;												//�`��
	void Uninit()override;												//�I��

private:
};

#endif // !_EXPLOSION_H_
