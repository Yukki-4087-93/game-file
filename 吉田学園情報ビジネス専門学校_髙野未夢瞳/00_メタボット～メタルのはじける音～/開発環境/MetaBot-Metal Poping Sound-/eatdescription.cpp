//--------------------------------------------------------------------------------------
//
//�H�ׂ��邨�i����
//Author;takano
//
//--------------------------------------------------------------------------------------

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "application.h"
#include "eatdescription.h"
#include "game.h"
#include "effect.h"
#include "player.h"
#include "sound.h"
#include <time.h>

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------
CEatDescription::CEatDescription()
{
	m_HitCount = 0;
}

//----------------------------------------
//�f�X�g���N�^
//----------------------------------------
CEatDescription::~CEatDescription()
{
}

//----------------------------------------
//������
//----------------------------------------
HRESULT CEatDescription::Init()
{
	CObject3D::Init();

	m_HitCount = 0;									//�J�E���^�[��������

	srand((unsigned int)time(nullptr));				//�����_���̏�����

	return S_OK;
}

//----------------------------------------
//�I��
//----------------------------------------
void CEatDescription::Uninit()
{
	CObject3D::Uninit();
}

//----------------------------------------
//�X�V
//----------------------------------------
void CEatDescription::Update()
{
	CObject3D::Update();
}

//----------------------------------------
//�`��
//----------------------------------------
void CEatDescription::Draw()
{
	CObject3D::Draw();
}

//----------------------------------------
//���i�������H�ׂ�ꂽ��
//----------------------------------------
void CEatDescription::HitDescription()
{
	m_HitCount++;	//�q�b�g�J�E���^�����Z

	CPlayer* pPlayer = CGame::GetPlayer();	//�v���C���[���̎擾

											//�o������G�t�F�N�g�̐ݒ�
	CEffect::Spawn(D3DXVECTOR3(pPlayer->GetPos().x,
		pPlayer->GetPos().y,
		pPlayer->GetPos().z),		//�ʒu�̐ݒ�
		10,														//�G�t�F�N�g�̍ő吔
		20.f,													//�����_���̍ő吔
		-20.f,													//�����_���̍ŏ���
		D3DXCOLOR(1.0f, 1.f, 0.f, 1.0f),						//�F�̐ݒ�
		30.0f * pPlayer->GetScale().y,							//�G�t�F�N�g�T�C�Y�̐ݒ�
		30.0f * pPlayer->GetScale().y);							//�G�t�F�N�g�T�C�Y�̐ݒ�

	if (m_HitCount == 20)
	{//�J�E���^�[��60�t���[���𒴂����Ƃ�
		CApplication::GetSound()->Play(CSound::SOUND_SE_EAT);		//�H�����Ƃ���SE���Đ�
	}

	if (m_HitCount > 60)
	{//�J�E���^�[��60�t���[���𒴂����Ƃ�
		ChangeSE();					//CV��ς���
		m_HitCount = 0;				//�J�E���^�[������������
	}
}

//----------------------------------------
//���i�������H�ׂ�ꂽ��
//----------------------------------------
void CEatDescription::HitEatDescription()
{
	CPlayer* pPlayer = CGame::GetPlayer();

	CEffect::Spawn(D3DXVECTOR3(pPlayer->GetPos().x,
		pPlayer->GetPos().y,
		pPlayer->GetPos().z),		//�ʒu�̐ݒ�
		10,														//�G�t�F�N�g�̍ő吔
		20.f,													//�����_���̍ő吔
		-20.f,													//�����_���̍ŏ���
		D3DXCOLOR(1.0f, 1.f, 0.f, 1.0f),						//�F�̐ݒ�
		30.0f * pPlayer->GetScale().y,
		30.0f * pPlayer->GetScale().y);

	CApplication::GetSound()->Play(CSound::SOUND_SE_EAT);		//�H����SE���Đ�

	ChangeSE();					//CV��ς���

	//�I�u�W�F�N�g�̊J��
	Release();
}

//----------------------------------------
//�H�ׂ��邨�i�����̐���
//----------------------------------------
CEatDescription * CEatDescription::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fHi, float fWd,ObjType type,CTexture::TEXTURE tex)
{
	CEatDescription* pEatDescription = new CEatDescription;

	if (pEatDescription != nullptr)
	{
		pEatDescription->Init();					//������
		pEatDescription->SetSize(fHi, fWd);			//�T�C�Y�̐ݒ�
		pEatDescription->SetPos(pos);				//�ʒu�̐ݒ�
		pEatDescription->SetRot(rot);				//�p�x�̐ݒ�
		pEatDescription->SetTexture(tex);			//�e�N�X�`���̐ݒ�
		pEatDescription->SetObjectType(type);		//�I�u�W�F�N�g�^�C�v��ݒ�
	}

	//�l��Ԋ�
	return pEatDescription;
}

//----------------------------------------
//�H�ׂ��邨�i������SE�ݒ�
//----------------------------------------
void CEatDescription::ChangeSE()
{
	m_nCHangeSound = rand() % 3;

	switch (m_nCHangeSound)
	{
	case 0:

		CApplication::GetSound()->Play(CSound::SOUND_SE_EAT_D_ONE);

		break;

	case 1:

		CApplication::GetSound()->Play(CSound::SOUND_SE_EAT_D_TWO);

		break;

	case 2:

		CApplication::GetSound()->Play(CSound::SOUND_SE_EAT_D_THREE);

		break;

	default:
		break;
	}
}
