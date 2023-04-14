//--------------------------------------------------------------------------------------
//
// ����
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "explosion.h"
#include "application.h"
#include <assert.h>

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CExplosion::CExplosion()
{
	m_nCounterAnim = 0;
	m_fPatternAnim = 0.0f;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CExplosion::~CExplosion()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CExplosion::Init()
{
	CObject2D::Init();
	CObject2D::SetTexture(CTexture::TEXTURE_EXPLOSION);
	CObject2D::PattarnTexture(m_fPatternAnim,8);

	return S_OK;
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	CExplosion *m_pExplosion = new CExplosion;

	if (m_pExplosion != nullptr)
	{
		m_pExplosion->Init();
		m_pExplosion->SetObjectType(OBJTYPE_EXPLOSION);
		m_pExplosion->Setpos(pos);
		m_pExplosion->SetColor(col);
	}
	else
	{
		assert(false);
	}

	return m_pExplosion;
}

//--------------------------------------
//�X�V
//--------------------------------------
void CExplosion::Update()
{
	CObject2D::Update();

	m_nCounterAnim++;

	if (CTexture::TEXTURE_EXPLOSION)
	{
		if (m_nCounterAnim % 8 == 0)
		{
			m_fPatternAnim++;
			CObject2D::PattarnTexture(m_fPatternAnim,8);
		}
	}

	if (m_fPatternAnim >= 8)
	{
		Uninit();
		return;
	}
	
}

//--------------------------------------
//�`��
//--------------------------------------
void CExplosion::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------
//�I��
//--------------------------------------
void CExplosion::Uninit()
{
	CObject2D::Release();
}
