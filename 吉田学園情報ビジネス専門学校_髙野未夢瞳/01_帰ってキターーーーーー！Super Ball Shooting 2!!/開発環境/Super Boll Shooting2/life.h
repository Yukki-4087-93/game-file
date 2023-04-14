//-----------------------------------------------------------------------------------------------------------
//
//���C�t
//Author::TAKANO
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _LIFE_H_
#define _LIFE_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"
#include "renderer.h"
#include "texture.h"

//----------------------------------------
//�N���X��`
//�L�[�{�[�h�n���̓��͏���
//----------------------------------------
class CLife : public CObject2D
{
public:
	CLife();
	~CLife();
	HRESULT Init()override;													//������
	static CLife * Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd);		//�N���G�C�g
	void Update()override;													//�X�V
	void Draw()override;													//�`��
	void Uninit()override;													//�I��
	void HitDamage(int nDamage);											//�_���[�W����
	void SetLife();
	void HitLife();

private:
	int m_nCountNumber;

};


#endif // !_LIFE_H_