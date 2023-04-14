//--------------------------------------------------------------------------------------
//
// �Q�[���}�l�[�W���[
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "game.h"
#include "renderer.h"
#include "object.h"
#include "object2d.h"
#include "player.h"
#include "input.h"
#include "bg.h"
#include "enemymanager.h"
#include "protect_city.h"
#include "score.h"
#include "ui.h"
#include "sound.h"
#include "ranking.h"

//--------------------------------------
//�ÓI�����o�ϐ��̐錾
//--------------------------------------
CPlayer *CGame::m_pPlayer;
CEnemyManager *CGame::m_pEnemyManager;
Cprotect_City *CGame::m_pProtect_City;
CUi *CGame::m_pUi;
CScore *CGame::m_pScore;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CGame::CGame()
{

}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CGame::~CGame()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CGame::Init()
{
	//�G�l�~�[�}�l�[�W���[�̓��I�m��
	m_pEnemyManager = new CEnemyManager;

	//�G�l�~�[�}�l�[�W���[�̏�����
	m_pEnemyManager->Init();

/*�Q�[�����̃I�u�W�F�N�g����*/

	//�w�i�̐���
	CBg* pBg = CApplication::GetBg()->Create(D3DXVECTOR3(1280.0f / 2, 720.0f / 2, 0.0f),
											1280.0f,
											720.0f,
											CTexture::TEXTURE::TEXTERE_BG);

	//�ǂ̐���
	m_pProtect_City = Cprotect_City::Create(D3DXVECTOR3(0.0f, 720.0f / 2, 0.0f), 100.0f, 720.0f);

	//���[�U�[�C���^�[�t�F�[�X�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(480.0f, 60.0f, 0.0f), 780.0f, 100.0f, CTexture::TEXTURE::TEXTURE_UI);
	
	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(423.0f,68.0f,0.0f),0);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(100.0f, 720.0f / 2, 0.0f), 30.0f, 30.0f);

	//�G�l�~�[�}�l�[�W���[���N��
	m_pEnemyManager->CreateEnemy();

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CGame::Uninit()
{
	//�T�E���h�̒�~
	CApplication::GetSound()->Stop();
	
	if (m_pProtect_City != nullptr)
	{//�ǂ̃|�C���^�ɒl�ɉ�������̒l�������Ă�����
		m_pProtect_City = nullptr;		//�k������
	}
	
	if (m_pUi != nullptr)
	{//���[�U�[�C���^�[�t�F�[�X�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pUi->Uninit();				//���[�U�[�C���^�[�t�F�[�X�̏I��
		m_pUi = nullptr;				//�k������
	}
	
	if (m_pScore != nullptr)
	{//�X�R�A�̃|�C���^�ɒl����������̒l�������Ă�����
		m_pScore = nullptr;				//�k������
	}
	
	if (m_pPlayer != nullptr)
	{//�v���C���[�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pPlayer = nullptr;			//�k������
	}

	if (m_pEnemyManager != nullptr)
	{//�����_���[�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pEnemyManager->Uninit();		//�I������
		delete m_pEnemyManager;			//�����_���[�|�C���^�����
		m_pEnemyManager = nullptr;		//�k������
	}
}

//--------------------------------------
//�X�V
//--------------------------------------
void CGame::Update()
{
	if (m_pEnemyManager != nullptr)
	{//�G�l�~�[�}�l�[�W���[�̃|�C���^�ɒl�������Ă����Ƃ�
		m_pEnemyManager->PopEnenmy();				//�G�l�~�[���Ăяo��
	}
}

//--------------------------------------
//�`��
//--------------------------------------
void CGame::Draw()
{
	
}

//---------------------------------------
//�v���C���[�̏��擾
//---------------------------------------
CPlayer * CGame::GetPlayer()
{
	return m_pPlayer;
}

//---------------------------------------
// �X�̏��擾
//---------------------------------------
Cprotect_City * CGame::GetProtect_City()
{
	return m_pProtect_City;
}

//---------------------------------------
// UI�̏��擾
//---------------------------------------
CUi * CGame::GetUi()
{
	return m_pUi;
}

//---------------------------------------
// �X�R�A�̏��擾
//---------------------------------------
CScore * CGame::GetScore()
{
	return m_pScore;
}
