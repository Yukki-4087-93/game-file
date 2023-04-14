//--------------------------------------------------------------------------------------
//
// �Q�[���Ǘ�
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "game.h"
#include "ranking.h"
#include "renderer.h"
#include "object.h"
#include "object2d.h"
#include "object3d.h"
#include "objectx.h"
#include "player.h"
#include "input.h"
#include "score.h"
#include "ui.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "meshifild.h"
#include "ranking.h"
#include "result.h"
#include "enemymanager.h"
#include "bildingmanager.h"
#include "skybox.h"
#include "effect.h"
#include "eatdescription.h"
#include <time.h>

//--------------------------------------
//�ÓI�����o�ϐ��̐錾
//--------------------------------------
CCamera *CGame::m_pCamera;
CPlayer *CGame::m_pPlayer;
CEnemyManager *CGame::m_pEnemyManager;
CUi *CGame::m_pUi;
CScore *CGame::m_pScore;
CLight *CGame::m_pLight;
CMeshField *CGame::m_pMeshifild;
CSkybox *CGame::m_pSkybox;
CBildingManager *CGame::m_pBildingManager;
CEatDescription *CGame::m_pEatDescription;

const float TEST_PLAYER = -300.0f;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CGame::CGame()
{
	m_pEnemyManager = nullptr;
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
/*�Q�[�����̃I�u�W�F�N�g����*/

	//�X�J�C�{�b�N�X�̐���
	m_pSkybox = CSkybox::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���b�V���t�B�[���h�̐���
	m_pMeshifild = CMeshField::Create();

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, TEST_PLAYER));

	//�G�l�~�[�}�l�[�W���[�̓��I�m��
	m_pEnemyManager = new CEnemyManager;

	//�G�l�~�[�}�l�[�W���[�̏�����
	m_pEnemyManager->Init();

	m_pEatDescription = CEatDescription::Create(D3DXVECTOR3(0.0f, 200.0f, 369.0f),
		D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2),
		400.0f,
		800.0f,
		CObject::OBJTYPE_DESCRIPTION,
		CTexture::TEXTURE_TUTORIAL);

	m_pEatDescription = CEatDescription::Create(D3DXVECTOR3(600.0f, 100.0f, -3069.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, -D3DX_PI / 2),
		200.0f,
		400.0f,
		CObject::OBJTYPE_DESCRIPTION,
		CTexture::TEXTURE_DISCRIPTION);

	m_pEatDescription = CEatDescription::Create(D3DXVECTOR3(1600.0f, 100.0f, -3069.0f),
		D3DXVECTOR3(0.0f, D3DX_PI, -D3DX_PI / 2),
		200.0f,
		400.0f,
		CObject::OBJTYPE_DESCRIPTION,
		CTexture::TEXTURE_ARROW);

	m_pEatDescription = CEatDescription::Create(D3DXVECTOR3(5400.0f, 100.0f, -3069.0f),
		D3DXVECTOR3(0.0f, D3DX_PI /2, -D3DX_PI / 2),
		200.0f,
		400.0f,
		CObject::OBJTYPE_DESCRIPTION,
		CTexture::TEXTURE_ARROW);

	m_pEatDescription = CEatDescription::Create(D3DXVECTOR3(5400.0f, 100.0f, -500.0f),
		D3DXVECTOR3(0.0f, D3DX_PI / 2, -D3DX_PI / 2),
		200.0f,
		400.0f,
		CObject::OBJTYPE_DESCRIPTION,
		CTexture::TEXTURE_DISCRIPTION2);

	m_pEatDescription = CEatDescription::Create(D3DXVECTOR3(5400.0f, 100.0f, -1000.0f),
		D3DXVECTOR3(0.0f, D3DX_PI / 2, -D3DX_PI / 2),
		200.0f,
		400.0f,
		CObject::OBJTYPE_DESCRIPTION,
		CTexture::TEXTURE_ARROW);

	m_pEatDescription = CEatDescription::Create(D3DXVECTOR3(4385.0f, 250.0f, 4300.0f),
		D3DXVECTOR3(0.0f, 0.0f, -D3DX_PI / 2),
		1200.0f,
		1600.0f,
		CObject::OBJTYPE_EAT_DESCRIPTION,
		CTexture::TEXTURE_EAT_ME);

	//�r���f�B���O�}�l�[�W���[�̓��I�m��
	m_pBildingManager = new CBildingManager;

	//�����̐���
	m_pBildingManager->Init();

	//�X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3(393.0f, 68.0f, 0.0f), 0);

	//���[�U�[�C���^�[�t�F�[�X�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(480.0f, 60.0f, 0.0f), 780.0f, 100.0f, CTexture::TEXTURE::TEXTURE_UI);

	//���[�U�[�C���^�[�t�F�[�X�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(635.0f, 605.0f, 0.0f), 200.0f, 100.0f, CTexture::TEXTURE::TEXTURE_UI_PLAYERDATA);

	//���C�g�̐���
	m_pLight = CLight::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�J�����̐���
	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�T�E���h�̍Đ�
	CApplication::GetSound()->Play(CSound::SOUND_BGM_TUTORIAL);

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CGame::Uninit()
{
	//�T�E���h��S��~����
	CApplication::GetSound()->Stop();
	
	if (m_pBildingManager != nullptr)
	{//�����̃|�C���^�ɉ�������̒l�������Ă�����
		m_pBildingManager->Uninit();				//�I������
		delete m_pBildingManager;					//�����}�l�[�W���[�̃|�C���^�����
		m_pBildingManager = nullptr;				//�k������
	}

	if (m_pUi != nullptr)
	{//���[�U�[�C���^�[�t�F�[�X�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pUi = nullptr;						//�k������
	}

	if (m_pScore != nullptr)
	{//�X�R�A�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pScore = nullptr;						//�k������
	}
	
	if (m_pPlayer != nullptr)
	{//�v���C���[�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pPlayer = nullptr;					//�k������
	}

	if (m_pEnemyManager != nullptr)
	{//�G�l�~�[�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pEnemyManager->Uninit();				//�I������
		delete m_pEnemyManager;					//�G�l�~�[�}�l�[�W���[�̃|�C���^�����
		m_pEnemyManager = nullptr;				//�k������
	}

	if (m_pCamera != nullptr)
	{//�J�����̃|�C���^�ɉ�������̒l�������Ă�����
		m_pCamera = nullptr;					//�k������
	}

	if (m_pMeshifild != nullptr)
	{//���b�V���t�B�[���h�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pMeshifild = nullptr;					//�k������
	}

	if (m_pEatDescription != nullptr)
	{//���b�V���t�B�[���h�̃|�C���^�ɉ�������̒l�������Ă�����
		m_pEatDescription = nullptr;					//�k������
	}
}

//--------------------------------------
//�X�V
//--------------------------------------
void CGame::Update()
{
	if (m_pCamera != nullptr)
	{//�J�����̃|�C���^�ɒl�������Ă�����
		m_pCamera->Update();						//�J�����̍X�V
	}

	if (m_pEnemyManager != nullptr)
	{//�J�����̃|�C���^�ɒl�������Ă�����
		m_pEnemyManager->Update();					//�G�l�~�[�}�l�[�W���[�̍X�V
	}

	if (m_pBildingManager != nullptr)
	{
		m_pBildingManager->Update();
	}

#ifdef _DEBUG
	// ���U���g�Ɉڍs

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_RSHIFT))
	{//Enter�L�[�������ꂽ��
		CResult::Set(0);
		CRanking::Set(CScore::Get());
		CApplication::SetMode(CApplication::MODE::MODE_RESULT);
	}

	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_4))
	{
		m_pPlayer->AddLife(1);
		m_pScore->AddLife(1);
	}

	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_3))
	{
		m_pPlayer->SubLife(1);
		m_pScore->HitDamage(1);
		m_pScore->Sub(10);
	}

	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_9))
	{
		m_pCamera->Sequence(10.0f,20.0f);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_M))
	{
		//�G�t�F�N�g�̐ݒ�
		CEffect::Spawn(D3DXVECTOR3(0.0f,100.0f,0.0f),					//�ʒu�̐ݒ�
								   10,									//�G�t�F�N�g�̍ő吔
								   5.f,									//�����_���̍ő吔
								   -5.f,								//�����_���̍ŏ���
								   D3DXCOLOR(1.0f,0.f,0.f,1.0f),			//�F�̐ݒ�
								   30.0f * m_pPlayer->GetScale().y,
								   30.0f * m_pPlayer->GetScale().y);

		m_pPlayer->AddInertia(1.0f);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_B))
	{
		m_pScore->SetStartTimer(true);
	}

#endif // _DEBUG

}

//--------------------------------------
//�`��
//--------------------------------------
void CGame::Draw()
{
}
