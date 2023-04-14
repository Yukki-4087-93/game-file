//--------------------------------------------------------------------------------------
//
// �G�t�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _EFFECT_H_
#define _EFFECT_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object2d.h"

//----------------------------------------
//�N���X��`
//�G�t�F�N�g
//----------------------------------------
class CEffect : public CObject2D
{
public:
	CEffect();																				//�R���X�g���N�^
	~CEffect();																				//�f�X�g���N�^
	HRESULT Init()override;																	//������
	static CEffect * Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife);		//�N���G�C�g
	void Update()override;																	//�X�V
	void Draw()override;																	//�`��
	void Uninit()override;																	//�I��
	void SetEffect(D3DXCOLOR col, float fRadius, int nLife);

private:
	float m_fRadius;												//���a
	int m_nRun;														//����J�E���g
	D3DXCOLOR m_Col;												//�F
	int m_nLife;													//����
	D3DXVECTOR3 m_nMove;											//�ړ���
};

#endif // !_EFFECT_H_
