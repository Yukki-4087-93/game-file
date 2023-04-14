//--------------------------------------------------------------------------------------
//
// �v���C���[
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "protect_city.h"
#include "application.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "result.h"
#include "ranking.h"
#include "score.h"
#include <assert.h>
#include <stdlib.h>

int Cprotect_City::m_nLife;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
Cprotect_City::Cprotect_City()
{
	m_nLife = 0;
	m_Damage = 0;
	m_nState = STARE_NOMAL;
	m_nColorCount = 0;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
Cprotect_City::~Cprotect_City()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT Cprotect_City::Init()
{
	CObject2D::Init();											//�I�u�W�F�N�g2D�̏�����
	CObject2D::SetTexture(CTexture::TEXTURE_PROTECT);			//�e�N�X�`���̔z�u
	m_nLife = 20;

	return S_OK;
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
Cprotect_City *Cprotect_City::Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd)
{
	Cprotect_City *m_pCity = new Cprotect_City;		//�v���C���[�̓��I�m��

	if (m_pCity != nullptr)
	{//�v���C���[�̃|�C���^�[�ɒl�������Ă��Ȃ�������
		m_pCity->Init();								//������
		m_pCity->SetObjectType(OBJTYPE_PROTECT);		//�I�u�W�F�N�g�̐ݒ�
		m_pCity->Setpos(pos);						//�ʒu�ݒ�
		m_pCity->SetSize(ObfHi, ObfWd);				//�T�C�Y�̐ݒ�
	}
	else
	{
		assert(false);
	}

	return m_pCity;
}

//--------------------------------------
//�X�V
//--------------------------------------
void Cprotect_City::Update()
{
	if (m_nLife <= 0)
	{
		CExplosion::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Uninit();
		CResult::Set(1);
		CRanking::Set(CScore::Get());
		CApplication::SetMode(CApplication::MODE::MODE_RESULT);
		return;				//����ȏ�X�V�ɓ���Ȃ��悤�ɕԂ�
	}


	CObject2D::Update();
	State();
}

//--------------------------------------
//�`��
//--------------------------------------
void Cprotect_City::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------
//�I��
//--------------------------------------
void Cprotect_City::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------
//�_���[�W
//--------------------------------------
void Cprotect_City::Damage(int nDamage)
{
	m_nLife -= nDamage;

	CScore::HitDamage(nDamage);

	if (m_nLife < 20 && m_nLife >= 15)
	{
		SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		CObject2D::SetTexture(CTexture::TEXTURE_PROTECT_ALERT);			//�e�N�X�`���̔z�u
	}

	if (m_nLife < 15 && m_nLife >= 5)
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		CObject2D::SetTexture(CTexture::TEXTURE_PROTECT_DEEPALERT);			//�e�N�X�`���̔z�u
	}

	if (m_nLife < 5 && m_nLife >= 0)
	{
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		CObject2D::SetTexture(CTexture::TEXTURE_PROTECT_DEATHALERT);			//�e�N�X�`���̔z�u
	}
}

//--------------------------------------
//�ǂ̏�ԊǗ�
//--------------------------------------
void Cprotect_City::State()
{
	if (m_nState == STARE_DAMAGE)
	{
		m_nColorCount++;
		if (m_nColorCount >= 10)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_nColorCount = 0;
			//�G�̏�Ԃ�߂�
			m_nState = STARE_NOMAL;
		}
	}
}

//--------------------------------------
//�ǂ̏�Ԑݒ�
//--------------------------------------
void Cprotect_City::SetState(Cprotect_City::CITY_STATE state)
{
	m_nState = state;
}

//--------------------------------------
//�ǂ̎����擾
//--------------------------------------
int Cprotect_City::GetLife()
{
	return m_nLife;
}
