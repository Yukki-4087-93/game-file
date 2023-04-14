//--------------------------------------------------------------------------------------
//
//�G�t�F�N�g
//Author;takano
//
//--------------------------------------------------------------------------------------

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "application.h"
#include "renderer.h"
#include "helperfunction.h"
#include "effect.h"

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------
CEffect::CEffect()
{
}

//----------------------------------------
//�f�X�g���N�^
//----------------------------------------
CEffect::~CEffect()
{
}

//----------------------------------------
//������
//----------------------------------------
HRESULT CEffect::Init()
{
	CObject3D::Init();

	//�e�����o�ϐ��̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_color = (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	CObject3D::SetTexture(CTexture::TRXTURE_EFFECT);

	m_bBillboard = true;

	return S_OK;
}

//----------------------------------------
//�I��
//----------------------------------------
void CEffect::Uninit()
{
	CObject3D::Uninit();
}

//----------------------------------------
//�X�V
//----------------------------------------
void CEffect::Update()
{
	CObject3D::Update();

	m_pos += m_move;

	m_color.a -= 0.05f;

	SetColor(m_color);

	if (m_color.a <= 0.0f)
	{
		Uninit();
	}
}

//----------------------------------------
//�`��
//----------------------------------------
void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���C�g�𖳌�������
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//A�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObject3D::Draw();

	//A�u�����f�B���O�����ɖ߂�ze��
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//���C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//----------------------------------------
//�G�t�F�N�g�̔z�u
//----------------------------------------
void CEffect::Set(D3DXVECTOR3 pos,D3DXVECTOR3 move)
{
	//�ʒu�̂𔽉f
	m_pos = pos;

	//�ʒu�̐ݒ�/*�������ŏ��������ꂽ�I�u�W�F�N�g3D(�|���S��)���`�悳��邱�Ƃ�h������*/
	CObject3D::SetPos(m_pos);
	
	//�ړ��ʂ̔��f
	m_move = move;
}

//----------------------------------------
//�G�t�F�N�g�̐���
//----------------------------------------
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fHi, float fWd)
{
	CEffect* pEffect = new CEffect;

	if (pEffect != nullptr)
	{
		pEffect->Init();				//������
		pEffect->Set(pos, move);
		pEffect->m_color = col;
		pEffect->SetColor(col);
		pEffect->SetSize(fHi, fWd);
		pEffect->SetObjectType(CObject::OBJTYPE_EFFECT);
		pEffect->SetTexture(CTexture::TRXTURE_EFFECT);
	}

	return pEffect;
}

//----------------------------------------
//�G�t�F�N�g�̏o��
//----------------------------------------
void CEffect::Spawn(D3DXVECTOR3 pos,int nMaxSpawn,float fRandMax, float fRandMin, D3DXCOLOR col,float fHi,float fWd)
{
	D3DXVECTOR3 randomPos,move;

	for (int i = 0; i < nMaxSpawn; i++)
	{
		move.x = (CHelperFunction::FloatRandom(fRandMax, fRandMin));
		move.y = (CHelperFunction::FloatRandom(fRandMax, fRandMin));
		move.z = (CHelperFunction::FloatRandom(fRandMax, fRandMin));

		//�G�t�F�N�g�̐���
		Create(pos,move,col, fHi, fWd);
	}
}
