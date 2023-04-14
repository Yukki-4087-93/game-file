//-----------------------------------------------------------------------------------------------------------
//
//�G�l�~�[
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------

//--------------------------
//�C���N���[�h�t�@�C��
//--------------------------
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "enemymanager.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "score.h"
#include <assert.h>
#include <time.h>
#include "helperfunction.h"
#include "sound.h"
#include "effect.h"
#include "bildingmanager.h"
#include "bilding.h"

//-------------------------
//�萔��`
//-------------------------
const D3DXCOLOR BLOOD_COLOR = D3DXCOLOR(1.f, 0.f, 0.f, 1.0f);	//�o��������G�t�F�N�g�̐F
const D3DXCOLOR SCALE_UP_COLOR = D3DXCOLOR(0.f,0.f,1.f,1.0f);	//�o��������G�t�F�N�g�̐F
const float MOVE_SPEED = 4.0f;								//�ړ��p
const float CHASE_SPEED = 4.6f;								//�Ǐ]�̍ۂɎg�p����ړ����x
const float CHASE_SPEEDER = 8.0f;							//���x�}�V�}�V�̒Ǐ]���x
const float RUN_SPEED = 4.0f;								//�����鑬�x
const float RUN_SPEEDER = 8.0f;								//���x�}�V�}�V�������鑬�x
const float DEFAULT_MOTION_FRAME = 60.0f;					//���[�V�����Ŏg�p����t���[���̃f�t�H���g�l
const float PLAYER_COLLISION_AREA = 200.0f;					//�v���C���[�ɔ������锻��͈̔�
const float ENEMY_REACTION_AREA = 200.0f;					//�G�l�~�[���v���C���[�ɔ�������͈�
const float COUNTER_ATTACK_AREA = 100.0f;					//�G�l�~�[���J�E���^�[������͈�
const float MAX_SCALE = 40.0f;								//�X�P�[���̍ő�l
const float EFFECT_SIZE = 30.0f;							//�G�t�F�N�g�T�C�Y�̊�{�l
const float DEFAULT_EFFECT_SIZE = 20.0f;					//�G�t�F�N�g�̊�{�l
const int NUM_EFFECT = 10;									//��x�ɏo��������G�t�F�N�g�̍ő�l
const int DEFAULT_SCORE = 100;								//�v���C���[�ɗ^����X�R�A�̊�{�l
const int DEFAULT_BOSS_SCORE = 1000;						//�v���C���[�ɗ^����{�X�X�R�A�̊�{�l

//-------------------------
//�R���X�g���N�^
//-------------------------
CEnemy::CEnemy()
{
	for (int i = 0; i < 4; i++)
	{
		m_pParts[i] = nullptr;				//�p�[�c���ϐ����N���A�����O����
	}

	m_nNumber = 0;

	m_HitCount = 0;

	m_motionType = TYPE_NONE;				//���[�V�����^�C�v���N���A�����O����
}

//-------------------------
//�f�X�g���N�^
//-------------------------
CEnemy::~CEnemy()
{
}

//-------------------------
//�N���G�C�g
//-------------------------
CEnemy * CEnemy::Create(const char* pfileParent, const char* pfileSon, D3DXVECTOR3 pos, ObjType type, int nLife)
{
	//���I�m��
	CEnemy* pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{//�G�l�~�[�̃|�C���^�ɉ�������̒l�������Ă�����
		pEnemy->Init();										//�G�l�~�[�̏�����
		pEnemy->m_pParts[0]->SetModel(pfileParent);
		pEnemy->m_pParts[1]->SetModel(pfileSon);
		pEnemy->SetPos(pos);								//�ʒu��ݒ�
		pEnemy->SetLife(nLife);								//���C�t�̐ݒ�
		pEnemy->SetObjectType(type);						//�I�u�W�F�N�g�^�C�v�̐ݒ�"Data/Model/enemy_up.x"
	}

	//�l��Ԃ�
	return pEnemy;
}

//-------------------------
//������
//-------------------------
HRESULT CEnemy::Init()
{
	//������
	m_fMotionCounter = 0.0f;					//���[�V�����J�E���^�[�̏�����
	m_nNumKey = 0;								//�L�[�̃J�E���^�[��������
	m_motionType = TYPE_IDLE;					//�������[�V�����̐ݒ�
	m_fSpeed = MOVE_SPEED;
	m_Scale = D3DXVECTOR3(1.0f,1.0f,1.0f);		//�X�P�[���̏�����

	//���f���̐���
	m_pParts[0] = CModel::Create("Data/Model/EnemyModel/enemy_down.x", D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),CModel::TYPE_ENEMY);
	m_pParts[1] = CModel::Create("Data/Model/EnemyModel/enemy_up.x", D3DXVECTOR3(0.0f, 19.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::TYPE_ENEMY);

	for (int nPartsCount = 0; nPartsCount < PARTS_MAX; nPartsCount++)
	{//	�p�[�c�̏�����
		if (nPartsCount == 0)
		{//�p�[�c��0�Ԗڂ������Ƃ�(�e�������Ƃ�)
			continue;		//for���΂��B(�߂�)
		}

		//�e�q�t�����Ȃ��H
		m_pParts[nPartsCount]->SetParent(m_pParts[0]);
	}

	for (int nKeyCount = 0; nKeyCount < KEY_MAX; nKeyCount++)
	{// �t���[���̏�����
		m_MotionInfo.aKeyInfo[nKeyCount].fFrame = DEFAULT_MOTION_FRAME;
	}

	srand((unsigned int)time(nullptr));						//�����_���̏�����

	m_nRand = rand() % 5;									//�����_���l�̏����l��ݒ�

	m_nRand_Up_Multi = rand() % 2;							//multi�Ŏg�p����ϐ��̏�����

	return S_OK;
}

//------------------------
//�I��
//------------------------
void CEnemy::Uninit()
{
	//�I�u�W�F�N�g�̊J��
	CObject::Release();
}

//---------------------
//�X�V
//---------------------
void CEnemy::Update()
{
	m_posOld = m_pos;					//�ʒu�̐ݒ�

	m_motionType = TYPE_WARK;			//���[�h�̍X�V

	Command();							//�s���K�͂�ݒ�

	PlayMotion();						//���[�V�����𓮂���

	MotionManager(m_motionType);		//���[�V�����^�C�v�̐ݒ�

	Collision();						//�����蔻��
}

//----------------------
//�`��
//----------------------
void CEnemy::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;										//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int k = 0; k < 2; k++)
	{
		m_pParts[k]->Draw();		//�p�[�c�̕`��
	}
}

//---------------------------------
//�Đ����[�V����
//---------------------------------
void CEnemy::PlayMotion()
{
	D3DXVECTOR3 DestPos[PARTS_MAX];			//���[�V�����̈ʒu�̍���������ϐ�
	D3DXVECTOR3 DestRot[PARTS_MAX];			//���[�V�����̊p�x�̍���������ϐ�
	D3DXVECTOR3 AuthorPos[PARTS_MAX];		//���[�V�����̈ʒu�̌v�Z���ʂ�����ϐ�
	D3DXVECTOR3 AuthorRot[PARTS_MAX];		//���[�V�����̊p�x�̌v�Z���ʂ�����ϐ�

	if (m_nNumKey + 1 >= KEY_MAX)
	{//�L�[���ő吔�𒴂�����
		m_nNumKey = 0;						//�L�[���ŏ��ɐݒ肷��
	}

	for (int nCountParts = 0; nCountParts < PARTS_MAX; nCountParts++)
	{
		//�ʒu�̍��������߂�
		DestPos[nCountParts].x = m_MotionInfo.aKeyInfo[m_nNumKey + 1].aKeyData[nCountParts].fPosX - m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fPosX;
		DestPos[nCountParts].y = m_MotionInfo.aKeyInfo[m_nNumKey + 1].aKeyData[nCountParts].fPosY - m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fPosY;
		DestPos[nCountParts].z = m_MotionInfo.aKeyInfo[m_nNumKey + 1].aKeyData[nCountParts].fPosZ - m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fPosZ;

		//�p�x�̍��������߂�
		DestRot[nCountParts].x = m_MotionInfo.aKeyInfo[m_nNumKey + 1].aKeyData[nCountParts].fRotX - m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fRotX;
		DestRot[nCountParts].y = m_MotionInfo.aKeyInfo[m_nNumKey + 1].aKeyData[nCountParts].fRotY - m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fRotY;
		DestRot[nCountParts].z = m_MotionInfo.aKeyInfo[m_nNumKey + 1].aKeyData[nCountParts].fRotZ - m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fRotZ;

		//�ۊǂ���ʒu�̒l�����߂�
		AuthorPos[nCountParts].x = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fPosX + DestPos[nCountParts].x * (m_fMotionCounter / m_MotionInfo.aKeyInfo[m_nNumKey].fFrame);
		AuthorPos[nCountParts].y = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fPosY + DestPos[nCountParts].y * (m_fMotionCounter / m_MotionInfo.aKeyInfo[m_nNumKey].fFrame);
		AuthorPos[nCountParts].z = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fPosZ + DestPos[nCountParts].z * (m_fMotionCounter / m_MotionInfo.aKeyInfo[m_nNumKey].fFrame);

		//�ۊǂ���p�x�̒l�����߂�
		AuthorRot[nCountParts].x = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fRotX + DestRot[nCountParts].x * (m_fMotionCounter / m_MotionInfo.aKeyInfo[m_nNumKey].fFrame);
		AuthorRot[nCountParts].y = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fRotY + DestRot[nCountParts].y * (m_fMotionCounter / m_MotionInfo.aKeyInfo[m_nNumKey].fFrame);
		AuthorRot[nCountParts].z = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[nCountParts].fRotZ + DestRot[nCountParts].z * (m_fMotionCounter / m_MotionInfo.aKeyInfo[m_nNumKey].fFrame);

		//���߂��l���g�p���Ĉʒu�𓮂���
		m_pParts[nCountParts]->SetPos(D3DXVECTOR3(AuthorPos[nCountParts].x + m_pParts[nCountParts]->GetStartPoint().x,
			AuthorPos[nCountParts].y + m_pParts[nCountParts]->GetStartPoint().y,
			AuthorPos[nCountParts].z + m_pParts[nCountParts]->GetStartPoint().z));

		//���߂��l���g�p���Ċp�x�𓮂���
		m_pParts[nCountParts]->SetRot(D3DXVECTOR3(AuthorRot[nCountParts].x + m_pParts[nCountParts]->GetStartRotation().x,
			AuthorRot[nCountParts].y + m_pParts[nCountParts]->GetStartRotation().y,
			AuthorRot[nCountParts].z + m_pParts[nCountParts]->GetStartRotation().z));
	}

	//���[�V�����J�E���^�[�̉��Z
	m_fMotionCounter++;

	if (m_fMotionCounter >= m_MotionInfo.aKeyInfo[m_nNumKey].fFrame)
	{
		m_fMotionCounter = 0.0f;
		m_nNumKey++;
	}

	if (m_nNumKey >= KEY_MAX)
	{
		//�ʒu�̍��������߂�
		DestPos[KEY_MAX].x = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fPosX - m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosX;
		DestPos[KEY_MAX].y = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fPosY - m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosY;
		DestPos[KEY_MAX].z = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fPosZ - m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosZ;

		//�p�x�̍��������߂�
		DestRot[KEY_MAX].x = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fRotX - m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotX;
		DestRot[KEY_MAX].y = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fRotY - m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotY;
		DestRot[KEY_MAX].z = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fRotZ - m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotZ;

		m_nNumKey = 0;
	}
}

//---------------------------------
//�G�l�~�[�ɓ��������Ƃ�
//---------------------------------
void CEnemy::HitNormal(int nCombo)
{
	SubLife(1);

	if (m_nLife <= 0)
	{
		CPlayer* pPlayer = CGame::GetPlayer();

		//�X�R�A�����Z
		CGame::GetScore()->Add(DEFAULT_SCORE + ((nCombo -1) * 10));

		CEffect::Spawn(D3DXVECTOR3(m_pos.x,m_pos.y,m_pos.z),		//�ʒu�̐ݒ�
			NUM_EFFECT,												//�G�t�F�N�g�̍ő吔
			DEFAULT_EFFECT_SIZE,			//�����_���̍ő吔
			-DEFAULT_EFFECT_SIZE,			//�����_���̍ŏ���
			BLOOD_COLOR,											//�F�̐ݒ�
			EFFECT_SIZE,							//�G�t�F�N�g�T�C�Y
			EFFECT_SIZE);							//�G�t�F�N�g�T�C�Y

		CApplication::GetSound()->Play(CSound::SOUND_SE_BREAK);

		if (pPlayer->GetScale().y < MAX_SCALE)
		{
			CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
				NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
				DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
				-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
				SCALE_UP_COLOR,									//�F�̐ݒ�
				EFFECT_SIZE* pPlayer->GetScale().y,
				EFFECT_SIZE* pPlayer->GetScale().y);

			CApplication::GetSound()->Play(CSound::SOUND_SE_SIZE_UP);
			pPlayer->UpScale(0.5f);

			pPlayer->AddInertia(0.4f);
		}

		//�I�u�W�F�N�g�̊J��
		Release();
	}
}

//---------------------------------
//�A�^�b�J�[�ɓ��������Ƃ�
//---------------------------------
void CEnemy::HitAttacker(int nCombo)
{
	SubLife(1);

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_nLife <= 0)
	{
		//�X�R�A�����Z
		CGame::GetScore()->Add(DEFAULT_SCORE + 20);

		CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
			NUM_EFFECT,												//�G�t�F�N�g�̍ő吔
			DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
			-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
			BLOOD_COLOR,						//�F�̐ݒ�
			EFFECT_SIZE,
			EFFECT_SIZE);

		CApplication::GetSound()->Play(CSound::SOUND_SE_BREAK);

		if (pPlayer->GetScale().y < MAX_SCALE)
		{
			CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
				NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
				DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
				-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
				SCALE_UP_COLOR,									//�F�̐ݒ�
				EFFECT_SIZE* pPlayer->GetScale().y,
				EFFECT_SIZE* pPlayer->GetScale().y);

			CApplication::GetSound()->Play(CSound::SOUND_SE_SIZE_UP);
			pPlayer->UpScale(0.2f);
		}

		pPlayer->AddInertia(0.1f);

		//�I�u�W�F�N�g�̊J��
		Release();
	}
}

//---------------------------------
//�X�s�[�_�[�ɓ��������Ƃ�
//---------------------------------
void CEnemy::HitSpeeder(int nCombo)
{
	SubLife(1);

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_nLife <= 0)
	{
		//�X�R�A�����Z
		CGame::GetScore()->Add(DEFAULT_SCORE);

		CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
			NUM_EFFECT,												//�G�t�F�N�g�̍ő吔
			DEFAULT_EFFECT_SIZE,						//�����_���̍ő吔
			-DEFAULT_EFFECT_SIZE,						//�����_���̍ŏ���
			BLOOD_COLOR,											//�F�̐ݒ�
			EFFECT_SIZE,
			EFFECT_SIZE);

		CApplication::GetSound()->Play(CSound::SOUND_SE_BREAK);

		if (pPlayer->GetScale().y < MAX_SCALE)
		{
			CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
				NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
				DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
				-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
				SCALE_UP_COLOR,									//�F�̐ݒ�
				EFFECT_SIZE* pPlayer->GetScale().y,
				EFFECT_SIZE* pPlayer->GetScale().y);

			CApplication::GetSound()->Play(CSound::SOUND_SE_SIZE_UP);
			pPlayer->UpScale(0.2f);

		}

		pPlayer->AddInertia(4.0f);

		//�I�u�W�F�N�g�̊J��
		Release();
	}
}

//---------------------------------
//�h�N�^�[�ɓ��������Ƃ�
//---------------------------------
void CEnemy::HitCure(int nCombo)
{
	SubLife(1);

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_nLife <= 0)
	{
		CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
			NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
			DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
			-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
			BLOOD_COLOR,						//�F�̐ݒ�
			EFFECT_SIZE,
			EFFECT_SIZE);

		CApplication::GetSound()->Play(CSound::SOUND_SE_BREAK);

		if (pPlayer->GetScale().y < MAX_SCALE)
		{
			CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
				NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
				DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
				-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
				SCALE_UP_COLOR,									//�F�̐ݒ�
				EFFECT_SIZE* pPlayer->GetScale().y,
				EFFECT_SIZE* pPlayer->GetScale().y);

			CApplication::GetSound()->Play(CSound::SOUND_SE_SIZE_UP);
			pPlayer->UpScale(0.2f);
		}

		pPlayer->AddLife(1);

		//�X�R�A�����Z
		CGame::GetScore()->AddLife(1);

		//�I�u�W�F�N�g�̊J��
		Release();
	}
}

//---------------------------------
//�����ɓ��������Ƃ�
//---------------------------------
void CEnemy::HitMulti(int nCombo)
{
	SubLife(1);

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_nLife <= 0)
	{
		//�X�R�A�����Z
		CGame::GetScore()->Add(DEFAULT_SCORE);

		CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
			NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
			DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
			-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
			BLOOD_COLOR,						//�F�̐ݒ�
			EFFECT_SIZE,
			EFFECT_SIZE);

		CApplication::GetSound()->Play(CSound::SOUND_SE_BREAK);

		if (pPlayer->GetScale().y < MAX_SCALE)
		{
			CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
				NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
				DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
				-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
				SCALE_UP_COLOR,									//�F�̐ݒ�
				EFFECT_SIZE* pPlayer->GetScale().y,
				EFFECT_SIZE* pPlayer->GetScale().y);

			CApplication::GetSound()->Play(CSound::SOUND_SE_SIZE_UP);
			pPlayer->UpScale(0.2f);

		}

		m_nRand_Up_Multi = rand() % 2;								//�\��UP�p�̕ϐ��ɒl��ݒ�

		switch (m_nRand_Up_Multi)
		{
		case 0:

			pPlayer->AddInertia(0.5f);		//���x(����)�̑���

			break;

		case 1:

			pPlayer->AddLife(1);			//�̗͂̑���

			CGame::GetScore()->AddLife(1);	//���C�t�J�E���^�[�����Z

			break;

		default:
			break;
		}

		//�I�u�W�F�N�g�̊J��
		Release();
	}
}

//---------------------------------
//�{�X�ɓ��������Ƃ�
//---------------------------------
void CEnemy::HitBoss(int nCombo)
{
	SubLife(1);

	CPlayer* pPlayer = CGame::GetPlayer();

	if (m_nLife < 0)
	{
		//�X�R�A�����Z
		CGame::GetScore()->Add(DEFAULT_BOSS_SCORE * (int)m_Scale.y);

		CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
			NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
			DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
			-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
			BLOOD_COLOR,						//�F�̐ݒ�
			EFFECT_SIZE * pPlayer->GetScale().y,
			EFFECT_SIZE * pPlayer->GetScale().y);

		CApplication::GetSound()->Play(CSound::SOUND_SE_BREAK);

		if (pPlayer->GetScale().y < MAX_SCALE)
		{
			CEffect::Spawn(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),		//�ʒu�̐ݒ�
				NUM_EFFECT,														//�G�t�F�N�g�̍ő吔
				DEFAULT_EFFECT_SIZE,							//�����_���̍ő吔
				-DEFAULT_EFFECT_SIZE,							//�����_���̍ŏ���
				SCALE_UP_COLOR,									//�F�̐ݒ�
				EFFECT_SIZE* pPlayer->GetScale().y,
				EFFECT_SIZE* pPlayer->GetScale().y);

			CApplication::GetSound()->Play(CSound::SOUND_SE_SIZE_UP);
			pPlayer->UpScale(2.0f);

		}

		//�I�u�W�F�N�g�̊J��
		Release();
	}
}

//---------------------------------
//�G�l�~�[�̃��C�t���Z����
//---------------------------------
void CEnemy::SubLife(int nSub)
{ 
	m_nLife -= nSub; 
}

//---------------------------------
//�X�P�[���̐ݒ�
//---------------------------------
void CEnemy::SetScale(float fScale)
{
	m_Scale.x = fScale;
	m_Scale.y = fScale;
	m_Scale.z = fScale;
}

//---------------------------------
//�X�V�̊֐�����
//---------------------------------
void CEnemy::Command()
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PLpos = CGame::GetPlayer()->GetPos();
	float fScale = CGame::GetPlayer()->GetScale().y;

	if (m_objType == CObject::OBJTYPE_ENEMY_DOCTOR &&
		CHelperFunction::CircleCollision(PLpos, PLAYER_COLLISION_AREA + ((fScale - 1.0f) * 50.0f ), m_pos, ENEMY_REACTION_AREA))
	{// �~�̓����蔻��œ����蔻�肪����������
		Run();		//�v���C���[���瓦����֐����Ăяo��
		return;		//�����ŕԂ�
	}

	else if (m_objType == CObject::OBJTYPE_ENEMY_ATTACKER &&
		CHelperFunction::CircleCollision(PLpos, PLAYER_COLLISION_AREA + ((fScale - 1.0f) * 50.0f), m_pos, ENEMY_REACTION_AREA))
	{// �~�̓����蔻��œ����蔻�肪����������
		Chase();		//�v���C���[��ǌ�����֐����Ăяo��
		return;			//�����Ŕ�����|��
	}

	else
	{
		if (CHelperFunction::CircleCollision(PLpos, PLAYER_COLLISION_AREA + ((fScale - 1.0f) * 50.0f), m_pos, ENEMY_REACTION_AREA))
		{// �~�̓����蔻��œ����蔻�肪����������
			SelectAction();			//�s����I������֐����Ăяo���B
			return;					//�����ŕԂ�
		}
	}

	//�����_�����ϐ������Z
	m_nRandCount++;

	if (m_nRandCount % 120 == 0)
	{//�����_���ϐ��Ƀ����_���̒l������
		m_nRand = rand() % 5;
	}
	
	switch (m_nRand)
	{
	case 0:

		m_motionType = TYPE_IDLE;									//�g�p���郂�[�V�����̐ݒ�

		NormalizationRotation();									//�p�x�̐��K��

		MoveCalculation();											//�ړ��ʂ̌v�Z

		break;

	case 1:

		m_move.x = sinf(D3DX_PI * 0.0f) * m_fSpeed;				//�G�l�~�[�̈ʒu��X�����ɓ�����
		m_move.z = cosf(D3DX_PI * 0.0f) * m_fSpeed;				//�G�l�~�[�̈ʒu��Z�����ɓ�����

		m_rotDest.y = m_move.y - D3DX_PI * 1.0f;					//�G�l�~�[�̈ړ����̌�����ݒ�

		m_motionType = TYPE_WARK;									//�g�p���郂�[�V�����̐ݒ�

		NormalizationRotation();									//�p�x�̐��K��

		MoveCalculation();											//�ړ��ʂ̌v�Z

		break;

	case 2:

		m_move.x = sinf(D3DX_PI * 1.0f) * m_fSpeed;				//�G�l�~�[�̈ʒu��X�����ɓ�����
		m_move.z = cosf(D3DX_PI * 1.0f) * m_fSpeed;				//�G�l�~�[�̈ʒu��Z�����ɓ�����

		m_rotDest.y = m_move.y + D3DX_PI * 0.0f;					//�G�l�~�[�̈ړ����̌�����ݒ�

		m_motionType = TYPE_WARK;									//�g�p���郂�[�V�����̐ݒ�

		NormalizationRotation();									//�p�x�̐��K��

		MoveCalculation();											//�ړ��ʂ̌v�Z

		break;

	case 3:

		m_move.x = -sinf(D3DX_PI * 0.5f) * m_fSpeed;				//�G�l�~�[�̈ʒu��X�����ɓ�����
		m_move.z = -cosf(D3DX_PI * 0.5f) * m_fSpeed;				//�G�l�~�[�̈ʒu��Z�����ɓ�����

		m_rotDest.y = m_move.y + D3DX_PI * 0.5f;					//�G�l�~�[�̈ړ����̌�����ݒ�

		m_motionType = TYPE_WARK;									//�g�p���郂�[�V�����̐ݒ�

		NormalizationRotation();									//�p�x�̐��K��

		MoveCalculation();											//�ړ��ʂ̌v�Z

		break;

	case 4:

		m_move.x = sinf(D3DX_PI * 0.5f) * m_fSpeed;				//�G�l�~�[�̈ʒu��X�����ɓ�����
		m_move.z = cosf(D3DX_PI * 0.5f) * m_fSpeed;				//�G�l�~�[�̈ʒu��Z�����ɓ�����

		m_rotDest.y = m_move.y - D3DX_PI * 0.5f;					//�G�l�~�[�̈ړ����̌�����ݒ�

		m_motionType = TYPE_WARK;									//�g�p���郂�[�V�����̐ݒ�

		NormalizationRotation();									//�p�x�̐��K��

		MoveCalculation();											//�ړ��ʂ̌v�Z

		break;

	default:		//��L�ȊO�������ꍇ
		assert(false);			//�v���O�������~�߂܂��B�f�o�b�N�̎�����
		break;
	}
}

//---------------------------------
//�p�x�̐��K��
//---------------------------------
void CEnemy::NormalizationRotation()
{
	//�p�x�̐��K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{//���̉�]�p����ڕW�̉�]�p�Ƃ̍���180�x���傫���Ȃ�����
		m_rotDest.y -= D3DX_PI * 2;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{//���̉�]�p����ڕW�̉�]�p�Ƃ̍���-180�x�����������Ȃ�����
		m_rotDest.y += D3DX_PI * 2;
	}

	//�e�ڕW�̊p�x�Ɍ��̊p�x�����Z����
	m_rot.x += (m_rotDest.x - m_rot.x) *  0.08f;
	m_rot.y += (m_rotDest.y - m_rot.y) *  0.08f;
	m_rot.z += (m_rotDest.z - m_rot.z) *  0.08f;
}

//---------------------------------
//�ړ��ʂ̌v�Z
//---------------------------------
void CEnemy::MoveCalculation()
{
	//�ړ��ʂ��ʒu�ɑ��
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.08f;
	m_move.z += (0.0f - m_move.z) * 0.08f;
}

//---------------------------------
//�����蔻��܂Ƃ�
//---------------------------------
void CEnemy::Collision()
{
	for (int i = 0; i < MAX_OBJ; i++)
	{
		CObject *pObj = CObject::Getobject(i);		//�I�u�W�F�N�g�̎擾
		CObject::ObjType objType;					//�I�u�W�F�N�g�^�C�v��錾

		if (pObj == nullptr)
		{//�I�u�W�F�N�g���g�p����Ă��Ȃ������Ƃ�
			continue;						//for���ŏ��ɕԂ�
		}

		//�I�u�W�F�N�g�^�C�v�ϐ��ɃI�u�W�F�N�g�^�C�v������
		objType = pObj->GetObjectType();

		if (objType == OBJTYPE_ENEMY_NORMAL ||
			objType == OBJTYPE_ENEMY_ATTACKER ||
			objType == OBJTYPE_ENEMY_SPEEDER ||
			objType == OBJTYPE_ENEMY_DOCTOR ||
			objType == OBJTYPE_ENEMY_MULTI ||
			objType == OBJTYPE_ENEMY_BOSS)
		{
			CEnemy* pEnemy = CGame::GetEnemyManager()->GetEnemy();

			if (m_nNumber == pEnemy->m_nNumber)
			{
				continue;
			}

			if (CHelperFunction::CircleCollision(m_pos, GetScale().y, pEnemy->m_pos, GetScale().y * 20.0f))
			{//�����蔻��̕Ԃ�l���^�Ȃ�
				m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
			}
		}

		if (objType == OBJTYPE_PLAYER)
		{
			CPlayer* pPlayer = CGame::GetPlayer();

			if (CHelperFunction::CircleCollision(m_pos, m_Scale.y, pPlayer->GetPos(), pPlayer->GetScale().y * 20.0f))
			{//�����蔻��̕Ԃ�l���^�Ȃ�

				m_pos = m_posOld;				//�ʒu���ߋ��̈ʒu�ɐݒ�

				m_HitCount++;					//�J�E���^�[�����Z

				if (m_HitCount % 20 == 0)
				{//�q�b�g�J�E���^�[������؂ꂽ�Ƃ�
					CApplication::GetSound()->Play(CSound::SOUND_SE_HIT);	//HitSE���Đ�
					pPlayer->SubLife(1);									//�v���C���[�̃��C�t�����炷
					pPlayer->ResetCombo();									//�R���{�����Z�b�g����
					CGame::GetCamera()->Sequence(10.0f, 20.0f);				//�J������h�炷
					CScore::HitDamage(1);									//����҂��猩���郉�C�t�J�E���^�[�����Z
				}
			}
		}


		if ((objType == OBJTYPE_BILDING_HELLOWARK ||
			objType == OBJTYPE_BILDING_LANDMARKTOWER ||
			objType == OBJTYPE_BILDING_THUMBSUP ||
			objType == OBJTYPE_BILDING_DTHUMBSUP ||
			objType == OBJTYPE_BILDING_TEMPLE ||
			objType == OBJTYPE_BILDING_APOSTLE) &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(60.0f, 0.0f, 60.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_WALL_OUTSIDE_WIDE &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(10060.0f, 0.0f, 50.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_WALL_OUTSIDE_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(52.0f, 0.0f, 10060.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_WALL_WIDE &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(800.0f, 0.0f, 60.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_WALL_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(60.0f, 0.0f, 800.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_WALL_LONGLONG_WILD &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(2600.0f, 0.0f, 60.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_WALL_LONGLONG_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(60.0f, 0.0f, 2600.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_FENCE_WIDE &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(460.0f, 0.0f, 30.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_FENCE_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(30.0f, 0.0f, 460.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_EAT_DESCRIPTION &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * 30.0f, 0.0f, m_Scale.z * 30.0f), pObj->Getpos(), D3DXVECTOR3(2460.0f, 0.0f, 30.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}
	}
}

//---------------------------------
//���[�V�����^�C�v�̐ݒ�
//---------------------------------
void CEnemy::MotionManager(MOTION_TYPE type)
{
	m_motionType = type;

	switch (m_motionType)
	{
	case CEnemy::TYPE_IDLE:

		m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[0].aKeyData[1].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[0].fFrame = DEFAULT_MOTION_FRAME;

		m_MotionInfo.aKeyInfo[1].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[1].aKeyData[0].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[1].aKeyData[1].fRotX = D3DXToRadian(10.f);
		m_MotionInfo.aKeyInfo[1].fFrame = DEFAULT_MOTION_FRAME;

		m_MotionInfo.aKeyInfo[2].aKeyData[0].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[2].aKeyData[2].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[2].fFrame = DEFAULT_MOTION_FRAME;

		break;

	case CEnemy::TYPE_WARK:

		m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[0].aKeyData[1].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[0].fFrame = 30.0f;

		m_MotionInfo.aKeyInfo[1].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[1].aKeyData[0].fRotX = -0.70f;
		m_MotionInfo.aKeyInfo[1].aKeyData[1].fRotX = D3DXToRadian(92.f);
		m_MotionInfo.aKeyInfo[1].fFrame = 10.0f;

		m_MotionInfo.aKeyInfo[2].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[2].aKeyData[2].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[2].fFrame = 20.0f;

		break;

	default:
		assert(false);
		break;
	}
}

//---------------------------------
//�G�l�~�[�̒Ǐ]�ݒ�
//---------------------------------
void CEnemy::Chase()
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PLpos = CGame::GetPlayer()->GetPos();

	//�x�N�g���������ϐ���錾
	D3DXVECTOR3 Vec;

	//�����������ϐ��̐錾
	float fangle;

	//�v���C���[�̈ʒu����G�l�~�[�̈ʒu������
	Vec = PLpos - m_pos;

	//�x�N�g���̑傫�����o��
	D3DXVec3Length(&Vec);

	//�x�N�g�����P�ɂ��� �������Ɍ��ʂ�ۑ�������́A�������ɕϊ��������x�N�g��������
	D3DXVec3Normalize(&Vec, &Vec);

	//�p�x�̌v�Z
	fangle = atan2f(Vec.x, Vec.z);

	if (m_objType == OBJTYPE_ENEMY_NORMAL ||
		m_objType == OBJTYPE_ENEMY_ATTACKER ||
		m_objType == OBJTYPE_ENEMY_MULTI ||
		m_objType == OBJTYPE_ENEMY_BOSS)
	{
		//�G�l�~�[�̈ʒu�Ƀx�N�g�������Z
		m_move = Vec * CHASE_SPEED;
	}

	else
	{
		//�G�l�~�[�̈ʒu�Ƀx�N�g�������Z
		m_move = Vec * CHASE_SPEEDER;
	}

	//�ړ��ʂ��v�Z
	MoveCalculation();

	//�p�x��Ώۂ̕����ɐݒ�
	m_rot.y = fangle + D3DX_PI;
}

//---------------------------------
//�G�l�~�[�̓��S�ݒ�
//---------------------------------
void CEnemy::Run()
{
	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 PLpos = CGame::GetPlayer()->GetPos();

	//�x�N�g���������ϐ���錾
	D3DXVECTOR3 Vec;

	//�����������ϐ��̐錾
	float fangle;

	//�v���C���[�̈ʒu����G�l�~�[�̈ʒu������
	Vec = PLpos - m_pos;

	//�x�N�g���̑傫�����o��
	D3DXVec3Length(&Vec);

	//�x�N�g�����P�ɂ��� �������Ɍ��ʂ�ۑ�������́A�������ɕϊ��������x�N�g��������
	D3DXVec3Normalize(&Vec, &Vec);

	//�p�x�̌v�Z
	fangle = atan2f(Vec.x, Vec.z);

	if (m_objType == OBJTYPE_ENEMY_NORMAL ||
		m_objType == OBJTYPE_ENEMY_ATTACKER ||
		m_objType == OBJTYPE_ENEMY_DOCTOR ||
		m_objType == OBJTYPE_ENEMY_MULTI ||
		m_objType == OBJTYPE_ENEMY_BOSS)
	{
		//�G�l�~�[�̈ʒu�Ƀx�N�g�������Z
		m_move = -Vec * RUN_SPEED;
	}

	else
	{
		//�G�l�~�[�̈ʒu�Ƀx�N�g�������Z
		m_move = -Vec * RUN_SPEEDER;
	}

	//�ړ��ʂ��v�Z
	MoveCalculation();

	//�p�x��Ώۂ̕����ɐݒ�
	m_rot.y = fangle + D3DX_PI;
}
//---------------------------------
//�G�l�~�[�̒ǌ�or�����̐ݒ�
//---------------------------------
void CEnemy::SelectAction()
{
	D3DXVECTOR3 pScale = CGame::GetPlayer()->GetScale();

	if (m_objType == OBJTYPE_ENEMY_BOSS)
	{
		if (m_Scale.y >= pScale.y)
		{
			m_motionType = TYPE_IDLE;									//�g�p���郂�[�V�����̐ݒ�
			
			NormalizationRotation();									//�p�x�̐��K��

			MoveCalculation();											//�ړ��ʂ̌v�Z
		}

		else
		{
			Chase();		//�ǌ��ݒ�
		}
	}

	else
	{
		if (m_Scale.y >= pScale.y ||
			m_Scale.y == pScale.y ||
			pScale.y - m_Scale.y < 1.0f)
		{//�G�l�~�[�̃X�P�[�����v���C���[�̃X�P�[�����傫�������x�����Ƃ�
			Chase();		//�ǌ��ݒ�
		}

		else
		{//�ȏ�̏����ȊO
			Run();			//Run away.
		}
	}
}
