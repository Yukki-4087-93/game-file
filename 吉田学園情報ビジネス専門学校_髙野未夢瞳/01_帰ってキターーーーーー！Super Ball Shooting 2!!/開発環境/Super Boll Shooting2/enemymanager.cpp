//--------------------------------------------------------------------------------------
//
// �G�l�~�[�}�l�[�W���[
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
  
//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "enemymanager.h"
#include "object.h"
#include "enemy.h"
#include "sound.h"
#include "time.h"

//--------------------------------------
//�O���[�o���ϐ�
//--------------------------------------
CEnemy *CEnemyManager::m_pEnemy;

//--------------------------------------
//�萔��`
//--------------------------------------
const float TUTORIAL_FIRST_SPAWN_WD = 1400.0f;				//�`���[�g���A���G�l�~�[�̏o���ʒu
const float OUTSIDE_SPAWN = (1280.0f + 40.0f);				//�G�l�~�[�̏o���ʒu
const float BOSS_WD = 1250.0f;								//�{�X�N���X�G�l�~�[�̏o���ʒu
const float TUTORAL_ENEMY_HI = 180.0f;						//�`���[�g���A���p�G�l�~�[�̏c�T�C�Y
const float TUTORAL_ENEMY_WD = 200.0f;						//�`���[�g���A���p�G�l�~�[�̉��T�C�Y
const float SIZE_TUTORIAL_ENEMY = 80.0f;					//�G�l�~�[�̃T�C�Y
const float SIZE_ENEMY = 50.0f;								//�G�l�~�[�̃T�C�Y
const float SIZE_MIDENEMY = 120.0f;							//�{�X�N���X�G�l�~�[�̃T�C�Y
const float SPAWN_TUTORIAL_HI = 180.0f;						//�o���̏c�ʒu
const float SPAWN_HI = 250.0f;								//�o���̏c�ʒu
const float SPAWN_MIDHI = 100.0f;							//�{�X�N���X�o���̏c�ʒu
const float SPAWN_TUTORIAL_WD = 440.0f;						//�o���̉��ʒu
const float SPAWN_WD = 390.0f;								//�o���̉��ʒu
const float SPAWN_MIDWD = 500.0f;							//�{�X�N���X�o���̉��ʒu
const float QUARTER_HI = (720.0f / 2);						//�c��ʂ̔���
const float ZERO_F = 0.0f;									//�y���̈ʒu
const int MULTIPLY_FIRST = 0;								//���߂Ɋ|���鐔
const int MULTIPLY_SECOND = 1;								//���Ɋ|���鐔
const int TUTORIAL_LIFE = 1;								//�`���[�g���A���G�l�~�[�̃��C�t
const int NOMAL_LIFE = 1;									//��ʓI�ȃG�l�~�[�̃��C�t
const int STRANGER_LIFE = 2;								//�ꕗ�ς�����G�l�~�[�̃��C�t
const int MIDBOSS_LIFE = 6;									//�{�X�N���X�G�l�~�[�̃��C�t
const int TRYMIDBOSS_LIFE = 6;								//�{�X�N���X�G�l�~�[3�A���̃��C�t
const int BOSS_LIFE = 18;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CEnemyManager::CEnemyManager()
{
	m_pEnemy = nullptr;
	m_nPopCount = 0;
	m_CollPop = 0;
	m_BossCount = 0;
	m_nCount = 0;
	m_UseSound = false;
	m_BossColl = false;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CEnemyManager::~CEnemyManager()
{
}

//--------------------------------------
//������
//--------------------------------------
void CEnemyManager::Init()
{
	m_nCount = 0;
	m_Part = PART_WAVETYPE_ONE;
}

//--------------------------------------
//�I��
//--------------------------------------
void CEnemyManager::Uninit()
{
	if (m_pEnemy != nullptr)
	{
		m_pEnemy = nullptr;
	}
}

//--------------------------------------
//�G�l�~�[�̐���
//--------------------------------------
void CEnemyManager::CreateEnemy()
{
	m_pEnemy = CEnemy::Create(D3DXVECTOR3(TUTORIAL_FIRST_SPAWN_WD,
										  SIZE_TUTORIAL_ENEMY + SPAWN_TUTORIAL_HI * MULTIPLY_FIRST, ZERO_F),
									      TUTORIAL_LIFE,
										  TUTORAL_ENEMY_WD,
										  TUTORAL_ENEMY_HI,
										  CTexture::TEXTERE_TUTORIAL_ZERO,
										  CObject::OBJTYPE_ENEMY,
										  CEnemy::ENEMY_TYPE::TYPE_TUTORIAL,
										  -0.8f,
										  0.0f);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(TUTORIAL_FIRST_SPAWN_WD,
										  SIZE_TUTORIAL_ENEMY + SPAWN_TUTORIAL_HI * MULTIPLY_SECOND, ZERO_F),
										  TUTORIAL_LIFE,
										  TUTORAL_ENEMY_WD,
										  TUTORAL_ENEMY_HI,
										  CTexture::TEXTERE_TUTORIAL_ONE,
										  CObject::OBJTYPE_ENEMY,
										  CEnemy::ENEMY_TYPE::TYPE_TUTORIAL,
										  -0.8f,
										  0.0f);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(TUTORIAL_FIRST_SPAWN_WD,
										  SPAWN_TUTORIAL_WD + SPAWN_TUTORIAL_HI * MULTIPLY_FIRST, ZERO_F),
										  TUTORIAL_LIFE,
										  TUTORAL_ENEMY_WD,
										  TUTORAL_ENEMY_HI,
										  CTexture::TEXTERE_TUTORIAL_TWO,
										  CObject::OBJTYPE_ENEMY,
										  CEnemy::ENEMY_TYPE::TYPE_TUTORIAL,
										  -0.8f,
										  0.0f);

	m_pEnemy = CEnemy::Create(D3DXVECTOR3(TUTORIAL_FIRST_SPAWN_WD,
										  SPAWN_TUTORIAL_WD + SPAWN_TUTORIAL_HI * MULTIPLY_SECOND, ZERO_F),
										  TUTORIAL_LIFE,
										  TUTORAL_ENEMY_WD,
										  TUTORAL_ENEMY_HI,
										  CTexture::TEXTERE_TUTORIAL_ZERO,
										  CObject::OBJTYPE_ENEMY,
										  CEnemy::ENEMY_TYPE::TYPE_TUTORIAL,
										  -0.8f,
										  0.0f);

	CApplication::GetSound()->Play(CSound::SOUND_BGM_TUTORAL);

	m_UseSound = true;
}

//--------------------------------------
//�G�l�~�[�̐���
//--------------------------------------
void CEnemyManager::PopEnenmy()
{
	//�J�E���^�[��������
	m_nCount++;

	if (m_nCount >= 600)
	{
		m_nPopCount++;

		SwitchPart(m_Part);
	}
}

//--------------------------------------
//�G�l�~�[�̃p�^�[���ω�
//--------------------------------------
void CEnemyManager::SwitchPart(ENEMY_PART part)
{
	m_Part = part;

	switch (m_Part)
	{
	case CEnemyManager::PART_NONE:

		/*�ݒ�Ȃ�*/

		break;

/*�E�F�[�u�P*/
	case CEnemyManager::PART_WAVETYPE_ONE:

		if (m_UseSound)
		{
			CApplication::GetSound()->Stop();
			CApplication::GetSound()->Play(CSound::SOUND_BGM_GAME);
			m_UseSound = false;
		}

		if (m_nPopCount % 960 == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDHI + SPAWN_HI * i,
					ZERO_F),
					STRANGER_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRANGER_DOWN,
					-1.12f, 1.12f);

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDWD + SPAWN_HI * i, ZERO_F),
					STRANGER_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRANGER_UP,
					-1.12f, -1.12f);
			}
		}

		if (m_nPopCount % 840 == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDHI + SPAWN_HI * i,
					ZERO_F),
					NOMAL_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_COLLISION_DOWN,
					-1.12f,
					1.12f);

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDWD + SPAWN_HI * i, ZERO_F),
					NOMAL_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_COLLISION_UP,
					-1.12f,
					-1.12f);

				m_CollPop++;
			}
		}

		if (m_nPopCount % 600 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDHI + SPAWN_HI * i,
					ZERO_F),
					NOMAL_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRAIGHT,
					-2.0f, 0.0f);
				m_CollPop++;
			}
		}

		if (m_nPopCount % 180 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN + 40.0f * i,
					SPAWN_MIDHI,
					ZERO_F),
					NOMAL_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRAIGHT,
					-2.0f,
					0.0f);
				m_CollPop++;
			}
			for (int i = 0; i < 4; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN + 40.0f * i,
					620.0f,
					ZERO_F),
					NOMAL_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRAIGHT,
					-2.0f,
					0.0f);
			}
		}

		if (m_CollPop >= 10)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(BOSS_WD,
				QUARTER_HI,
				ZERO_F),
				MIDBOSS_LIFE,
				SIZE_MIDENEMY,
				SIZE_MIDENEMY,
				CTexture::TEXTERE_ENEMETYPE,
				CObject::OBJTYPE_ENEMY,
				CEnemy::ENEMY_TYPE::TYPE_MIDBOSS,
				0.4f, 0.4f);
			m_CollPop = 0;
			m_BossCount++;
		}

		if (m_BossCount >= 4)
		{
			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_HI + SPAWN_HI * i,
					ZERO_F),
					TRYMIDBOSS_LIFE,
					SIZE_MIDENEMY,
					SIZE_MIDENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_MIDBOSS,
					0.4f, 0.4f);
			}
			m_BossCount = 0;
		}

		if (m_nPopCount >= 1200)
		{
			m_Part = PART_WAVETYPE_TWO;
		}

		break;

/*�E�F�[�u�Q*/
	case CEnemyManager::PART_WAVETYPE_TWO:

		if (m_UseSound)
		{
			m_nPopCount = 0;
			CApplication::GetSound()->Stop();
			CApplication::GetSound()->Play(CSound::SOUND_BGM_GAME);
			m_UseSound = false;
		}

		if (m_nPopCount % 600 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDHI + SPAWN_HI * i,
					ZERO_F),
					3,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRANGER_DOWN,
					-2.0f, 0.0f);
				m_CollPop++;
			}

			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDHI + SPAWN_HI * i,
					ZERO_F),
					3,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRANGER_UP,
					-2.0f, 0.0f);
				m_CollPop++;
			}
		}
		
		if (m_nPopCount % 180 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN + 40.0f * i,
					SPAWN_MIDHI,
					ZERO_F),
					2,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_COLLISION_DOWN,
					-2.0f,
					0.0f);
				m_CollPop++;
			}

			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN + 40.0f * i,
					680.0f,
					ZERO_F),
					2,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_COLLISION_UP,
					-2.0f,
					0.0f);
				m_CollPop++;
			}
		}

		if (m_CollPop >= 40)
		{
			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					180.0f + 200 * i,
					ZERO_F),
					TRYMIDBOSS_LIFE,
					SIZE_MIDENEMY,
					SIZE_MIDENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_MIDBOSS,
					0.4f, 0.4f);
			}
			m_CollPop = 0;
		}

		if (m_nPopCount >= 1200)
		{
			m_UseSound = true;
			m_Part = PART_WAVETYPE_TREE;
		}

		break;

/*�E�F�[�u�R*/
	case CEnemyManager::PART_WAVETYPE_TREE:

		if (m_UseSound)
		{
			m_nPopCount = 0;
			m_UseSound = false;
		}

		if (m_nPopCount % 840 == 0)
		{
			for (int i = 0; i < 2; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDHI + SPAWN_HI * i,
					ZERO_F),
					NOMAL_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRANGER_DOWN,
					-1.12f,
					1.12f);

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDWD + SPAWN_HI * i, ZERO_F),
					NOMAL_LIFE,
					SIZE_ENEMY,
					SIZE_ENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRANGER_UP,
					-1.12f,
					-1.12f);

				m_CollPop++;
			}
		}

		if (m_nPopCount % 600 == 0)
		{
			for (int i = 0; i < 3; i++)
			{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN + 60.0f * i,
					360.0f,
					ZERO_F),
					8,
					40.0f,
					40.0f,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_STRANGER_DOWN,
					-2.0f, 0.0f);
				m_CollPop++;
			}
		}

		if (m_nPopCount % 280 == 0)
		{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					SPAWN_MIDHI,
					ZERO_F),
					TRYMIDBOSS_LIFE,
					40.0f,
					40.0f,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_COLLISION_DOWN,
					-2.0f,
					0.0f);

				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					680.0f,
					ZERO_F),
					TRYMIDBOSS_LIFE,
					40.0f,
					40.0f,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_COLLISION_UP,
					-2.0f,
					0.0f);
		}

		if (m_CollPop >= 20)
		{
				m_pEnemy = CEnemy::Create(D3DXVECTOR3(OUTSIDE_SPAWN,
					360.0f,
					ZERO_F),
					8,
					SIZE_MIDENEMY,
					SIZE_MIDENEMY,
					CTexture::TEXTERE_ENEMETYPE,
					CObject::OBJTYPE_ENEMY,
					CEnemy::ENEMY_TYPE::TYPE_MIDBOSS,
					0.4f, 0.4f);

			m_CollPop = 0;
		}

		if (m_nPopCount >= 1200)
		{
			m_UseSound = true;
			m_BossColl = true;
			m_Part = PART_BOSS_THIRD;
		}

		break;

/*�{�X�E�F�[�u�P*/
	case CEnemyManager::PART_BOSS:

		if (m_BossColl)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(BOSS_WD,
				QUARTER_HI,
				ZERO_F),
				BOSS_LIFE,
				340.0f,
				400.0f,
				CTexture::TEXTURE_AGE,
				CObject::OBJTYPE_BOSS,
				CEnemy::ENEMY_TYPE::TYPE_BOSS,
				0.4f, 0.4f);

			m_BossColl = false;
		}

		if (m_nPopCount >= 2400)
		{
			m_UseSound = true;
			m_Part = PART_WAVETYPE_TWO;
		}

		break;

/*�{�X�E�F�[�u�Q*/
	case CEnemyManager::PART_BOSS_SECOND:

		if (m_BossColl)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(BOSS_WD,
				QUARTER_HI,
				ZERO_F),
				BOSS_LIFE,
				340.0f,
				400.0f,
				CTexture::TEXTURE_AGE,
				CObject::OBJTYPE_BOSS,
				CEnemy::ENEMY_TYPE::TYPE_BOSS_TWO,
				0.4f, 0.4f);

			m_BossColl = false;
		}

		if (m_nPopCount >= 2400)
		{
			m_UseSound = true;
			m_Part = PART_WAVETYPE_TREE;
		}

		break;

/*�{�X�E�F�[�u�R*/
	case CEnemyManager::PART_BOSS_THIRD:

		if (m_UseSound)
		{
			CApplication::GetSound()->Stop();
			CApplication::GetSound()->Play(CSound::SOUND_BGM_GAME_BOSS);
			m_UseSound = false;
		}

		if (m_BossColl)
		{
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(BOSS_WD,
				QUARTER_HI,
				ZERO_F),
				36,
				340.0f,
				400.0f,
				CTexture::TEXTURE_AGE,
				CObject::OBJTYPE_BOSS,
				CEnemy::ENEMY_TYPE::TYPE_BOSS_TREE,
				0.4f, 0.4f);

			m_BossColl = false;
		}

		if (m_nPopCount >= 2400)
		{
			m_UseSound = true;
			m_Part = PART_WAVETYPE_TWO;
		}

		break;

	default:
		break;
	}
}

//--------------------------------------
//�G�l�~�[�̍폜
//--------------------------------------
void CEnemyManager::DestroyEnemy()
{
	m_pEnemy->Uninit();
}

//--------------------------------------
//�G�l�~�[�̏��擾
//--------------------------------------
CEnemy * CEnemyManager::GetEnemy()
{
	return m_pEnemy;
}
