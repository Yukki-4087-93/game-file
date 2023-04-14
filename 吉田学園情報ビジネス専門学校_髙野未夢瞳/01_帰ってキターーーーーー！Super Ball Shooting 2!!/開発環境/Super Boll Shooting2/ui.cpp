//--------------------------------------------------------------------------------------
//
// User Interface
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "ui.h"
#include "application.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "ranking.h"
#include "score.h"
#include <assert.h>
#include <stdlib.h>


//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CUi::CUi()
{
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CUi::~CUi()
{
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
CUi *CUi::Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd, CTexture::TEXTURE tex)
{
	CUi *m_pUi = new CUi;		//�v���C���[�̓��I�m��

	if (m_pUi != nullptr)
	{//�v���C���[�̃|�C���^�[�ɒl�������Ă��Ȃ�������
		m_pUi->Init();								//������
		m_pUi->SetObjectType(OBJTYPE_UI);			//�I�u�W�F�N�g�̐ݒ�
		m_pUi->Setpos(pos);							//�ʒu�ݒ�
		m_pUi->SetSize(ObfHi, ObfWd);				//�T�C�Y�̐ݒ�
		m_pUi->SetTexture(tex);
	}
	else
	{
		assert(false);
	}

	return m_pUi;
}

void CUi::Uninit()
{
	CObject2D::Uninit();
}
