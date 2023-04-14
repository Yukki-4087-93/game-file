//--------------------------------------------------------------------------------------
//
// �}�l�[�W���[�A�v���P�[�V����
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "renderer.h"
#include "title.h"
#include "texture.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "input.h"
#include "sound.h"
#include "object.h"
#include "bg.h"
#include <assert.h>

//--------------------------------------
//�O���[�o���ϐ�
//--------------------------------------
CRenderer *CApplication::m_aRenderer;
CTitle *CApplication::m_pTitle;
CTexture *CApplication::m_pTexture;
CGame *CApplication::m_pGame;
CResult *CApplication::m_pResult;
CRanking *CApplication::m_pRanking;
CInput *CApplication::m_pInputKyeboard;
CApplication::MODE CApplication::m_mode;
CSound *CApplication::m_pSound;
CBg *CApplication::m_pBg;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CApplication::CApplication()
{
	m_mode = CApplication::MODE_TITLE;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CApplication::~CApplication()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CApplication::Init(HINSTANCE hInctance, HWND hWnd, bool bWindow)
{
	//�|�C���^�S�~�������Ă��Ȃ����`�F�b�N
	CApplication::ReleseDustCheck();
	
	//���I�m��
	m_aRenderer = new CRenderer;
	m_pInputKyeboard = new CInput;
	m_pSound = new CSound;
	m_pTitle = new CTitle;
	m_pTexture = new CTexture;
	m_pGame = new CGame;
	m_pResult = new CResult;
	m_pRanking = new CRanking;

	//�T�E���h�̏�����
	m_pSound->Init();

	//������
	m_aRenderer->Init(hWnd, bWindow);

	//�L�[�{�[�h�̏�����
	m_pInputKyeboard->Initkeyboard(hInctance, hWnd);
	
	SetMode(m_mode);

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CApplication::Uninit()
{
	//�S�~�������Ă��Ȃ����m�F
	CApplication::ReleseDustCheck();
}

//--------------------------------------
//�X�V
//--------------------------------------
void CApplication::Update()
{
	if (m_pInputKyeboard != nullptr)
	{//�L�[�{�[�h�̃|�C���^�ɒl�������Ă����Ƃ�
		m_pInputKyeboard->Updatekeyboard();			//�L�[�{�[�h�̍X�V
	}

	if (m_aRenderer != nullptr)
	{//�����_���[�̃|�C���^�ɒl�������Ă����Ƃ�
		m_aRenderer->Update();						//�����_���[�̍X�V
	}

	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		//�^�C�g���̍X�V
		m_pTitle->Update();

		break;

	case CApplication::MODE_GAME:
		//�Q�[���̍X�V
		m_pGame->Update();

		break;

	case CApplication::MODE_RESULT:
		//���U���g�̍X�V
		m_pResult->Update();

		break;

	case CApplication::MODE_RANKING:
		//�����L���O�̍X�V
		m_pRanking->Update();

		break;

	default:	//����ȊO
		assert(false);
		break;
	}
}

//--------------------------------------
//�`��
//--------------------------------------
void CApplication::Draw()
{
	if (m_aRenderer != nullptr)
	{
		//�����_���[�̕`��
		m_aRenderer->Draw();
	}
}

//--------------------------------------
//�I�������ƃ_�X�g�`�F�b�N�p�֐�
//--------------------------------------
void CApplication::ReleseDustCheck()
{
	if (m_aRenderer != nullptr)
	{//�����_���[�̃|�C���^�ɉ�������̒l�������Ă�����
		m_aRenderer->Uninit();					//�I������
		delete m_aRenderer;						//�����_���[�|�C���^�����
		m_aRenderer = nullptr;					//�k������
	}

	if (m_pTexture != nullptr)
	{//�e�N�X�`���̃|�C���^�ɉ�������̒l�������Ă�����
		m_pTexture->ReleaseAll();				//�e�N�X�`���S�̂̏I������
		delete m_pTexture;						//�e�N�X�`���̃|�C���^�����
		m_pTexture = nullptr;					//�k������
	}

	if (m_pGame != nullptr)
	{//�Q�[���̃|�C���^�ɉ�������̒l�������Ă�����
		m_pGame->Uninit();						//�Q�[���S�̂̏I������
		delete m_pGame;							//�Q�[���̃|�C���^�����
		m_pGame = nullptr;						//�k������
	}

	if (m_pInputKyeboard != nullptr)
	{//�L�[�{�[�h�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pInputKyeboard->Uninitkeyboard();		//�I������
		delete m_pInputKyeboard;				//�L�[�{�[�h�̃|�C���^�����
		m_pInputKyeboard = nullptr;				//�k������
	}

	if (m_pSound != nullptr)
	{//�T�E���h�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pSound->Uninit();						//�I������
		delete m_pSound;						//�T�E���h�̃|�C���^���J��
		m_pSound = nullptr;						//�k������
	}

	if (m_pBg != nullptr)
	{//�w�i�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pBg->Uninit();						//�I������
	}
}

//---------------------------------------
//���[�h�̐ݒ�
//---------------------------------------
void CApplication::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		//�^�C�g���̏I��
		m_pTitle->Uninit();

		break;

	case CApplication::MODE_GAME:
		//�Q�[���̏I��
		m_pGame->Uninit();

		break;

	case CApplication::MODE_RESULT:
		//���U���g�̏I��
		m_pResult->Uninit();

		break;

	case CApplication::MODE_RANKING:
		//�����L���O�̏I��
		m_pRanking->Uninit();

		break;

	default:	//����ȊO
		assert(false);
		break;
	}

	//���������I�u�W�F�N�g�̑S�j��(�I�u�W�F�N�g���c���Ă����獢��̂�)
	CObject::ReleaseAll();

	//���[�h��ݒ肷��
	m_mode = mode;

	switch (m_mode)
	{
	case CApplication::MODE_TITLE:
		//�^�C�g���̏�����
		m_pTitle->Init();

		break;

	case CApplication::MODE_GAME:
		//�Q�[���̏�����
		m_pGame->Init();

		break;

	case CApplication::MODE_RESULT:
		//���U���g�̏�����
		m_pResult->Init();
		
		break;

	case CApplication::MODE_RANKING:
		//�����L���O�̏�����
		m_pRanking->Init();
		
		break;
	
	default:	//����ȊO
		assert(false);
		break;
	}

}
