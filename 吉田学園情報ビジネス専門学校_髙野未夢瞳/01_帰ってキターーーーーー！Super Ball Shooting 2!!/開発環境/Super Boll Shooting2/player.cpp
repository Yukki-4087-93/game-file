//--------------------------------------------------------------------------------------
//
// �v���C���[
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "player.h"
#include "game.h"
#include "application.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "effect.h"
#include "sound.h"
#include "result.h"
#include "ranking.h"
#include "score.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>

//--------------------------------------
//�萔��`
//--------------------------------------
static const float SCREEN_WIDH = 1280.0f;			//��ʂ̓����蔻��Ŏg�p���鉡��
static const float SCREEN_HIGHT = 720.0f;			//��ʂ̓����蔻��Ŏg�p����c��
static const float COLLISION_SIZE = 14.0f;			//��ʂ̓����蔻��Ŏg�p����v���C���[�̃T�C�Y
static const float PLAYER_MOVEMENT = 0.62f;			//�v���C���[�̈ړ���
static const int MAX_COUNT = 80;					//�e���˃J�E���g�̍ő吔

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CPlayer::CPlayer()
{
	m_nCount = 0;
	m_nPi = 0;
	m_nRand = 0;
	m_nPressCount = 0;
	m_nLife = 0;
	m_Damage = 0;
	m_nColorCount = 0;
	m_col = (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_bSetTexture = false;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CPlayer::Init()
{
	CObject2D::Init();										//�I�u�W�F�N�g2D�̏�����
	CObject2D::SetTexture(CTexture::TEXTURE_PLAYER);		//�e�N�X�`���̔z�u
	srand((unsigned int)time(nullptr));						//�����_���̏�����
	m_nLife = 99;

	return S_OK;
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd)
{
	CPlayer *m_pPlayer = new CPlayer;		//�v���C���[�̓��I�m��

	if (m_pPlayer != nullptr)
	{//�v���C���[�̃|�C���^�[�ɒl�������Ă��Ȃ�������
		m_pPlayer->Init();
		m_pPlayer->SetObjectType(OBJTYPE_PLAYER);
		m_pPlayer->Setpos(pos);
		m_pPlayer->SetSize(ObfHi, ObfWd);
	}
	else
	{
		assert(false);
	}

	return m_pPlayer;
}

//--------------------------------------
//�X�V
//--------------------------------------
void CPlayer::Update()
{
	if (m_nLife <= 0)
	{
		Uninit();
		CRanking::Set(CScore::Get());
		CResult::Set(1);
		CApplication::SetMode(CApplication::MODE::MODE_RESULT);
		return;				//�X�V�ɂ���ȏ����Ȃ��悤�ɕԂ�
	}

	CObject2D::Update();

	CObject2D::SetColor(m_col);

	//����̏����̌Ăяo��
	Command();

	//�e����̏����̌Ăяo��
	CommandBullet();

	//�ړ��n���̏����̌Ăяo��
	Move();

	//�����蔻��n���̏����̌Ăяo��
	Collision();

	//��ԊǗ�
	State();

#ifdef _DEBUG
	// ���U���g�Ɉڍs
	
	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_R))
	{//R�L�[�������ꂽ��
		CResult::Set(1);
		CRanking::Set(CScore::Get());
		CApplication::SetMode(CApplication::MODE::MODE_RESULT);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_H))
	{
		HitDamage(19);
	}

#endif // _DEBUG
}

//--------------------------------------
//�`��
//--------------------------------------
void CPlayer::Draw()
{
	CObject2D::Draw();
}

//--------------------------------------
//�I��
//--------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//--------------------------------------
//�v���C���[�̑��쏈��
//--------------------------------------
void CPlayer::Command()
{
/* �v���C���[�̈ړ� */

	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_W))
	{//W�L�[�������ꂽ��
		m_move.x += sinf(D3DX_PI) * PLAYER_MOVEMENT;
		m_move.y += cosf(D3DX_PI) * PLAYER_MOVEMENT;
	}
	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_S))
	{//S�L�[�������ꂽ��
		m_move.x += sinf(D3DX_PI * 0.0f) * PLAYER_MOVEMENT;
		m_move.y += cosf(D3DX_PI * 0.0f) * PLAYER_MOVEMENT;
	}
	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_A))
	{
		//�ړ��ʂ̍X�V
		m_move.x += sinf(-D3DX_PI * 0.5f) * PLAYER_MOVEMENT;
		m_move.y += cosf(-D3DX_PI * 0.5f) * PLAYER_MOVEMENT;
	}
	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_D))
	{
		m_move.x += sinf(D3DX_PI * 0.5f) * PLAYER_MOVEMENT;
		m_move.y += cosf(D3DX_PI * 0.5f) * PLAYER_MOVEMENT;
	}
}

//--------------------------------------
//�v���C���[�̒e����
//--------------------------------------
void CPlayer::CommandBullet()
{
/*�ϐ��Q*/
	m_nCount++;																	//�e���˗p�J�E���g�̉��Z
	bool bSpace = CApplication::GetKyeboard()->GetkeyboardPress(DIK_SPACE);		//�X�y�[�X�L�[�����݂̑�s
	bool bBpush = CApplication::GetKyeboard()->GetkeyboardPress(DIK_B);			//B�L�[�����݂̑�s
	bool bNpush = CApplication::GetKyeboard()->GetkeyboardPress(DIK_N);			//N�L�[�����݂̑�s
	bool bMarisa = CApplication::GetKyeboard()->GetkeyboardPress(DIK_M);		//M�L�[�����݂̑�s(1�x�����g���Ă��Ȃ����A�e�̑���n���̓���̂��ߕϐ���)
	CBullet::BULLET_USER CUser = CBullet::BULLET_USER::USER_PLAYER;				//���[�U�[���̑�s

/* �ʏ�e�̏��� */

	if (bSpace)
	{//�X�y�[�X�L�[�������ꂽ��ʏ�e�𐶐�
		if (m_nCount <= 10)
		{
			if (m_nCount % 3 == 0)
			{
				CApplication::GetSound()->Play(CSound::SOUND_SE_SOOT);
				CBullet::Create(m_pos,
					D3DXVECTOR3(sinf(D3DX_PI * 0.5f),
						cosf(D3DX_PI * 0.5f), 0.0f) * 25.0f,
					CTexture::TEXTURE_BULLET,
					CUser);
			}
		}
		if (m_nCount >= MAX_COUNT)
		{
			m_nCount = 0;
		}
	}

/* �����_�������̃o�[�X�g�e�̏��� */

	if (bSpace == false)
	{//�X�y�[�X�L�[��������Ȃ�������
		if (bBpush)
		{//�����_���o�[�X�g�e�̔��ˏ���
			if (m_nCount <= 12)
			{
				CApplication::GetSound()->Play(CSound::SOUND_SE_SOOT);
				m_nPi = D3DX_PI * 200.0f;									//�p�x�v�Z
				m_nRand = rand() % m_nPi;								//�����_����
				CBullet::Create(m_pos,
					D3DXVECTOR3(sinf(m_nRand * 0.01f),
						cosf(m_nRand * 0.01f), 0.0f) * 5.0f,
					CTexture::TEXTURE_BULLET,
					CUser);
			}
			if (m_nCount >= MAX_COUNT)
			{
				m_nCount = 0;
			}
		}
	}

/* 3�����̒e�̏��� */

	if (bSpace == false &&
		bBpush == false)
	{//�X�y�[�X�L�[��B�L�[��������Ȃ�������
		if (bNpush)
		{//3�����̒e���ˏ���
			if (m_nCount <= 12)
			{
				if (m_nCount % 4 == 0)
				{
					CApplication::GetSound()->Play(CSound::SOUND_SE_SOOT);
					for (int nCnt = 0; nCnt < 3; nCnt++)
					{
						CBullet::Create(m_pos,
							D3DXVECTOR3(sinf(D3DX_PI * 0.5f),
								cosf(D3DX_PI * 0.25f + 0.78f * nCnt),
								0.0f) * 12.0f,
							CTexture::TEXTURE_BULLET,
							CUser);
					}
				}
			}
			
			if (m_nCount >= MAX_COUNT)
			{
				m_nCount = 0;
			}
		}
	}
	
/* �^���}�X�p�̏��� */
	if (bSpace == false &&
		bBpush == false &&
		bNpush == false)
	{//�X�y�[�X�L�[��B�L�[��N�L�[��������Ȃ�������
		if (bMarisa)
		{//�^���}�X�p�[�̔��ˏ���
			if (m_nCount <= 1)
			{
				CApplication::GetSound()->Play(CSound::SOUND_SE_SOOT);
				for (int nCnt = 0; nCnt < 8; nCnt++)
				{
					CBullet::Create(m_pos,
						D3DXVECTOR3(sinf(D3DX_PI * 0.5f),
							cosf(D3DX_PI * 0.25f + 0.25f * nCnt),
							0.0f) * 14.0f,
						CTexture::TEXTURE_BULLET,
						CUser);
				}
			}
			if (m_nCount >= MAX_COUNT)
			{
				m_nCount = 0;
			}
		}
	}
}

//--------------------------------------
//�v���C���[�̈ړ��n������
//--------------------------------------
void CPlayer::Move()
{
	//�v���C���[�̈ʒu�X�V
	//�ʒu���X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.08f;
	m_move.y += (0.0f - m_move.y) * 0.08f;
}

//--------------------------------------
//�v���C���[�̓����蔻��n������
//--------------------------------------
void CPlayer::Collision()
{
	if (m_pos.y >= SCREEN_HIGHT - COLLISION_SIZE)
	{//����(��ʉ�����ʒ[)
		m_pos.y = SCREEN_HIGHT - COLLISION_SIZE;
	}
	else if (m_pos.y <= 0 + COLLISION_SIZE)
	{//�㋴(��ʏ㌓��ʒ[)
		m_pos.y = 0 + COLLISION_SIZE;
	}
	if (m_pos.x >= SCREEN_WIDH - COLLISION_SIZE)
	{//�~�M�[��(��ʉE����ʒ[)
		m_pos.x = SCREEN_WIDH - COLLISION_SIZE;
	}
	else if (m_pos.x <= 0 + COLLISION_SIZE)
	{//����(��ʍ�����ʒ[)
		m_pos.x = 0 + COLLISION_SIZE;
	}
}

//--------------------------------------
//�v���C���[�̏�ԊǗ�����
//--------------------------------------
void CPlayer::State()
{
	if (m_State == STARE_DAMAGE)
	{
		m_nColorCount++;
		if (m_nColorCount >= 240)
		{
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_nColorCount = 0;
			//�G�̏�Ԃ�߂�
			m_State = STARE_NOMAL;
		}
	}
}

//--------------------------------------
//�v���C���[�̃_���[�W����
//--------------------------------------
void CPlayer::HitDamage(int nDamage)
{
	m_nLife -= nDamage;

	SetState(STARE_DAMAGE);

	if (m_nLife <= 99 && m_nLife >= 80)
	{
		SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	if (m_nLife < 80 && m_nLife >= 60)
	{
		if (m_bSetTexture != true)
		{
			CObject2D::SetTexture(CTexture::TEXTURE_PLAYER_VER2);		//�e�N�X�`���̔z�u
			m_bSetTexture = true;
		}
		SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	if (m_nLife < 60 && m_nLife >= 40)
	{
		if (m_bSetTexture != false)
		{
			CObject2D::SetTexture(CTexture::TEXTURE_PLAYER_VER3);		//�e�N�X�`���̔z�u
			m_bSetTexture = false;
		}
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	if (m_nLife < 40 && m_nLife >= 0)
	{
		if (m_bSetTexture != true)
		{
			CObject2D::SetTexture(CTexture::TEXTURE_PLAYER_VER4);		//�e�N�X�`���̔z�u
			m_bSetTexture = true;
		}
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

//--------------------------------------
//�v���C���[�̏�Ԑݒ�
//--------------------------------------
void CPlayer::SetState(CPlayer::PLAYER_STATE state)
{
	m_State = state;
}
