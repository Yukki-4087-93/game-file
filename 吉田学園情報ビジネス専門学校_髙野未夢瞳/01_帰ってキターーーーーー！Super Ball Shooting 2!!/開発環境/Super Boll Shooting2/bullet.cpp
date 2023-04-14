//--------------------------------------------------------------------------------------
//
// �e
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "bullet.h"
#include "application.h"
#include "explosion.h"
#include "effect.h"
#include "enemy.h"
#include "enemymanager.h"
#include "player.h"
#include <assert.h>
#include <time.h>

//----------------------------------------
//�萔��`
//----------------------------------------
const int MAX_BULLET_OBJECT = 1280;
const float HitSizeEnemy = 40.0f;
const float HitSizePlayer = 30.0f;

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------
CBullet::CBullet()
{//�l���N���A(�Y���)����
	m_nBLife = 0;
	m_nMove = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_TypeUser = USER_NOME;
	m_nColorCount = 0;
	m_nPattarnCount = 0;
}

//----------------------------------------
//�f�X�g���N�^
//----------------------------------------
CBullet::~CBullet()
{
}

//----------------------------------------
//������
//----------------------------------------
HRESULT CBullet::Init()
{
	m_fPatternAnim = 0;																			//�A�j���[�V�����p�^�[���̏�����
	CObject2D::Init();																			//������
	m_nBLife = 50;																				//���C�t�̏����ݒ�
	m_nMove = D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.5f) * 20.0f, 0.0f);	//�ړ��ʂ̏�����
	m_TypeUser = USER_NOME;																		//���[�U�[��Ԃ𖢎g�p�ɐݒ�
	return S_OK;
}

//----------------------------------------
//�N���G�C�g
//----------------------------------------
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, CTexture::TEXTURE tex, CBullet::BULLET_USER user)
{
	//���I�m��
	CBullet* pBullet = new CBullet;

	if (pBullet != nullptr)
	{//�e�̃|�C���^�ɒl�������Ă��Ȃ������Ƃ�
		pBullet->Init();														//������
		pBullet->SetObjectType(OBJTYPE_BULLET);									//�I�u�W�F�N�g�^�C�v�̐ݒ�
		pBullet->SetTexture(tex);												//�e�N�X�`���̐ݒ�
		pBullet->Setpos(pos);													//�ʒu�̐ݒ�
		pBullet->SetMove(move);													//�ړ��ʂ̐ݒ�
		pBullet->SetTypeBullet(user);											//�e�̃��[�U�[�ݒ�
	}
	else
	{//����ȊO(�e�̃|�C���^�ɒl�������Ă����Ƃ�)
		assert(false);
	}

	return pBullet;
}

//----------------------------------------
//�X�V
//----------------------------------------
void CBullet::Update()
{
	//���C�t�����炷
	m_nBLife--;

	//�G�t�F�N�g�̈ʒu�̍X�V
	CObject2D::Addmove(m_nMove);

	//�I�u�W�F�N�g���̂̍X�V
	CObject2D::Update();

	m_nPattarnCount++;

	//�e�N�X�`���p�^�[���̍X�V
	CObject2D::PattarnTexture(m_nPattarnCount,8);
	
	//�e���C�t�̌���
	SubstructLife();

	//�����蔻��
	Collisison();
}

//----------------------------------------
//�`��
//----------------------------------------
void CBullet::Draw()
{
	CObject2D::Draw();
}

//----------------------------------------
//�I��
//----------------------------------------
void CBullet::Uninit()
{
	CObject2D::Uninit();
}

//----------------------------------------
//�e�̊J��
//----------------------------------------
void CBullet::Release()
{
	CObject2D::Release();
}

//----------------------------------------
//���[�u���Z�b�g����
//----------------------------------------
void CBullet::SetMove(D3DXVECTOR3 move)
{
	m_nMove = move;
}

//----------------------------------------
//�ړ��ʂ̏��擾
//----------------------------------------
D3DXVECTOR3 CBullet::GetMove()
{
	return m_nMove;
}

//----------------------------------------
//���[�U�[���擾
//----------------------------------------
CBullet::BULLET_USER CBullet::GetUser()
{
	return m_TypeUser;
}

//----------------------------------------
//�e�̃��[�U�[�̐ݒ�
//----------------------------------------
void CBullet::SetTypeBullet(CBullet::BULLET_USER user)
{
	m_TypeUser = user;
}

//----------------------------------------
//�e�̃��C�t����
//----------------------------------------
void CBullet::SubstructLife()
{
	if (m_nBLife <= 0)
	{//���C�t��0�ȉ��ɂȂ�����
		CExplosion::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Uninit();		//�e�̉��

		return;
	}
}

//----------------------------------------
//�e�̓����蔻��
//----------------------------------------
void CBullet::Collisison()
{
	for (int i = 0; i < MAX_BULLET_OBJECT; i++)
	{
		CObject *pObj;
		CObject::ObjType objType;
		pObj = CObject::Getobject(i);

		if (pObj == nullptr)
		{//�I�u�W�F�N�g���g�p����Ă��Ȃ������Ƃ�
			continue;
		}
		if (m_TypeUser == USER_NOME)
		{//���[�U�[�^�C�v���g�p����Ă��Ȃ��Ƃ�
			continue;
		}
		objType = pObj->GetObjectType();
		D3DXVECTOR3 ObjPos = pObj->Getpos();

/*�e�g�p���[�U�[���v���C���[�ŃI�u�W�F�N�g�^�C�v���G�l�~�[�������Ƃ�*/

		if (m_TypeUser == USER_PLAYER &&
			objType == OBJTYPE_ENEMY &&
			m_pos.x >= ObjPos.x - HitSizeEnemy &&
			m_pos.x <= ObjPos.x + HitSizeEnemy &&
			m_pos.y <= ObjPos.y + HitSizeEnemy &&
			m_pos.y >= ObjPos.y - HitSizeEnemy)
		{//�ʒu�̒��S�ɒe�̔����̃T�C�Y��+-�����͈͂ɓ��������Ƃ�
			CExplosion::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			CEnemy* pEnemy = (CEnemy*)pObj;						//pObject��CEnemy�^�Ƀ_�E���L���X�g
			pEnemy->SetState(CEnemy::ENEMY_STATE::STARE_DAMAGE);
			pEnemy->SetColor(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
			pEnemy->HitLife(1);

			Release();						//�e���g���J������

			//����ȏ㏈���ɓ���Ȃ��悤�ɂ���
			return;
		}

/*�e�g�p���[�U�[���v���C���[�ŃI�u�W�F�N�g�^�C�v���{�X�������Ƃ�*/

		if (m_TypeUser == USER_PLAYER &&
			objType == OBJTYPE_BOSS &&
			m_pos.x >= ObjPos.x - 200.0f &&
			m_pos.x <= ObjPos.x + 200.0f &&
			m_pos.y <= ObjPos.y + 200.0f &&
			m_pos.y >= ObjPos.y - 200.0f)
		{//�ʒu�̒��S�ɒe�̔����̃T�C�Y��+-�����͈͂ɓ��������Ƃ�
			CExplosion::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			CEnemy* pEnemy = (CEnemy*)pObj;						//pObject��CEnemy�^�Ƀ_�E���L���X�g
			pEnemy->SetState(CEnemy::ENEMY_STATE::STARE_DAMAGE);
			pEnemy->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			pEnemy->HitLife(1);

			Release();						//�e���g���J������

			//����ȏ㏈���ɓ���Ȃ��悤�ɂ���
			return;
		}

/*�e�g�p���[�U�[���G�l�~�[�ŃI�u�W�F�N�g�^�C�v���v���C���[�������Ƃ�*/

		if (m_TypeUser == USER_ENEMY &&
			objType == OBJTYPE_PLAYER &&
			m_pos.x >= ObjPos.x - HitSizePlayer &&
			m_pos.x <= ObjPos.x + HitSizePlayer &&
			m_pos.y <= ObjPos.y + HitSizePlayer &&
			m_pos.y >= ObjPos.y - HitSizePlayer)
		{//�ʒu�̒��S�ɒe�̔����̃T�C�Y��+-�����͈͂ɓ��������Ƃ�
			CExplosion::Create(m_pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			CPlayer* pPlayer = (CPlayer*)pObj;						//pObject��CPlayer�^�Ƀ_�E���L���X�g
			pPlayer->SetState(CPlayer::PLAYER_STATE::STARE_DAMAGE);
			pPlayer->HitDamage(1);
			Release();						//�e���g���J������

			//����ȏ㏈���ɓ���Ȃ��悤�ɂ���
			return;
		}
	}
}
