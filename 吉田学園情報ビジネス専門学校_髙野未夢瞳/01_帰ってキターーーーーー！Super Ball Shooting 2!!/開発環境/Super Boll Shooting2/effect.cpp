//--------------------------------------------------------------------------------------
//
// �G�t�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "effect.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "application.h"
#include <assert.h>
#include <time.h>

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CEffect::CEffect()
{
	m_nRun = 0;
	m_nLife = 0;
	m_nMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CEffect::~CEffect()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CEffect::Init()
{
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_BULLET_E);
	m_nLife = 50;
	
	return S_OK;
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	CEffect* pEffect;

	pEffect = new CEffect;

	if (pEffect != nullptr)
	{
		pEffect->Init();
		pEffect->SetObjectType(OBJTYPE_EFFECT);
		pEffect->Setpos(pos);
		pEffect->SetEffect(col, fRadius, nLife);
	}
	else
	{
		assert(false);
	}

	return pEffect;
}

//--------------------------------------
//�X�V
//--------------------------------------
void CEffect::Update()
{
	CObject2D::Update();

	CObject2D::PattarnTexture(m_nRun, 8);
	
	m_nLife--;

	//���a�̌��炷��
	m_fRadius -= 0.7891f;

	//�F�̕ύX
	m_Col += D3DXCOLOR(0.005f, 0.005f, 0.005f, 0.0f);

	if (m_nLife <= 0)
	{
		Uninit();		//�G�t�F�N�g�̉��
	}
}

//--------------------------------------
//�`��
//--------------------------------------
void CEffect::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//A�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject2D::Draw();

	//A�u�����f�B���O�����ɖ߂�ze��
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//--------------------------------------
//�I��
//--------------------------------------
void CEffect::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------
//�G�t�F�N�g�̐ݒ�
//--------------------------------------
void CEffect::SetEffect(D3DXCOLOR col, float fRadius, int nLife)
{
	col = m_Col;
	fRadius = m_fRadius;
	nLife = m_nLife;
}
