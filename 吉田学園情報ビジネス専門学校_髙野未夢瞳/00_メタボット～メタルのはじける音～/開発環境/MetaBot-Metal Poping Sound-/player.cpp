//-----------------------------------------------------------------------------------------------------------
//
//�v���C���[
//Author::takano()
//
//-----------------------------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "enemymanager.h"
#include "bilding.h"
#include "bildingmanager.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "helperfunction.h"
#include "score.h"
#include "result.h"
#include "ranking.h"
#include "effect.h"
#include "ui.h"
#include "eatdescription.h"
#include "sound.h"
#include <assert.h>

//--------------------------------------
//�萔��`
//--------------------------------------
const float DEFAULT_MOTION_FRAME = 60.0f;				//���[�V�����L�[�t���[���̃f�t�H���g�l
const float PLAYER_LIFE = 10;							//�v���C���[�̏����̗�
const float PLAYER_INERTIA = 10.5f;						//�v���C���[�̊�����
const float DEFAULT_SIZE = 1.0f;						//�����T�C�Y
const float MAX_SCALE = 40.f;							//�ő�T�C�Y
const float SIZE_PLUS = 30.0f;							//�����蔻��Ɋ|����T�C�Y

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CPlayer::CPlayer()
{
	for (int i = 0; i < 4; i++)
	{
		m_pParts[i] = nullptr;	//�p�[�c�̃N���A�����O
	}
	m_motionType = TYPE_NONE;	//���[�V�����^�C�v�̃N���A�����O

	m_nComboCounter = 0;		//�R���{�L���J�E���^�̏�����

	m_bDenger = false;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	//���I�m��
	CPlayer* pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{//�|�C���^�ɒl�������Ă�����
		pPlayer->Init();									//�v���C���[�̏�����
		pPlayer->SetPos(pos);								//�ʒu��ݒ�
		pPlayer->SetObjectType(CObject::OBJTYPE_PLAYER);	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	}

	//�l��ԋp
	return pPlayer;
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CPlayer::Init()
{
	//�ϐ��̏�����
	m_fMotionCounter = 0.0f;												//���[�V�����J�E���^�[�̏�����
	m_nNumKey = 0;															//�L�[�ԍ��̏�����
	m_nComboCounter = 0;													//�R���{�J�E���^�[��������
	m_motionType = TYPE_IDLE;												//���[�V�����^�C�v�̏�����
	m_nLife = PLAYER_LIFE;													//�v���C���[�̃��C�t�̏�����
	m_fInertia = PLAYER_INERTIA;											//�����͂̏�����
	m_fAttack = 1.f;														//�Η͂̏�����
	m_Scale = D3DXVECTOR3(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);		//�X�P�[����������

	//���f���̐���
	m_pParts[0] = CModel::Create("Data/Model/PlayerModel/Down_Head.x",D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::TYPE_PLAYER);
	m_pParts[1] = CModel::Create("Data/Model/PlayerModel/Up_Head.x", D3DXVECTOR3(0.0f, 19.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::TYPE_PLAYER);

	for (int nPartsCount = 0; nPartsCount < PARTS_MAX; nPartsCount++)
	{//	�p�[�c�̏�����
		if (nPartsCount == 0)
		{//�p�[�c��0�Ԗڂ������Ƃ�(�e�������Ƃ�)
			continue;		//for��߂�
		}

		//�e�q�t���ɂ���
		m_pParts[nPartsCount]->SetParent(m_pParts[0]);
	}

	for (int nKeyCount = 0; nKeyCount < KEY_MAX; nKeyCount++)
	{// �t���[���̏�����
		m_MotionInfo.aKeyInfo[nKeyCount].fFrame = DEFAULT_MOTION_FRAME;
	}
	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CPlayer::Uninit()
{
	//�I�u�W�F�N�g�̊J��
	CObject::Release();
}

//--------------------------------------
//�X�V
//--------------------------------------
void CPlayer::Update()
{
	m_posOld = m_pos;					//�Â��ʒu�Ɍ��݂̈ʒu��ݒ�

	m_motionType = TYPE_IDLE;			//���[�h�̍X�V

	Command();							//�v���C���[�̑���n��

	PlayMotion();						//���[�V�����𓮂���

	MotionManager(m_motionType);		//���[�V�����̐ݒ�

	CollisionManager();					//�����蔻����Ăяo��

	DethPlayer(m_nLife);				//�v���C���[�̎��S���̏���

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_U))
	{//U�L�[�������ꂽ�Ƃ�
		UpScale(0.1f);	//�X�P�[��UP�I
	}

#ifdef _DEBUG
	
	
	
#endif // _DEBUG

}

//--------------------------------------
//�`��
//--------------------------------------
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans,mtxScale;										//�v�Z�p�}�g���b�N�X

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

	for (int i = 0; i < 2; i++)
	{//�p�[�c���`�悷��
		m_pParts[i]->Draw();
	}
}

//--------------------------------------
//�Đ����[�V����
//--------------------------------------
void CPlayer::PlayMotion()
{
	D3DXVECTOR3 DestPos[PARTS_MAX];			//���[�V�����̈ʒu�̍���������ϐ�
	D3DXVECTOR3 DestRot[PARTS_MAX];			//���[�V�����̊p�x�̍���������ϐ�
	D3DXVECTOR3 AuthorPos[PARTS_MAX];		//���[�V�����̈ʒu�̌v�Z���ʂ�����ϐ�
	D3DXVECTOR3 AuthorRot[PARTS_MAX];		//���[�V�����̊p�x�̌v�Z���ʂ�����ϐ�

	if (m_nNumKey + 1 >= KEY_MAX)
	{//�L�[�̍ő�l����������
		m_nNumKey = 0;						//�L�[�̏�����
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
	{//���[�V�����J�E���^�[���z��̃t���[���l�ȏ�ɂȂ�����
		m_fMotionCounter = 0.0f;					//���[�V�����J�E���^�[������������
		m_nNumKey++;								//�L�[�ԍ���i�߂�
	}

	if (m_nNumKey >= KEY_MAX)
	{//�L�[�ԍ��̒l���ő�l���������Ƃ�

		/*�Ō�̃L�[����Ō�̃L�[�̍��������߂�*/

		//�ʒu�̍��������߂�
		DestPos[KEY_MAX].x = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fPosX - m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosX;
		DestPos[KEY_MAX].y = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fPosY - m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosY;
		DestPos[KEY_MAX].z = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fPosZ - m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosZ;

		//�p�x�̍��������߂�
		DestRot[KEY_MAX].x = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fRotX - m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotX;
		DestRot[KEY_MAX].y = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fRotY - m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotY;
		DestRot[KEY_MAX].z = m_MotionInfo.aKeyInfo[m_nNumKey].aKeyData[KEY_MAX].fRotZ - m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotZ;

		//�L�[�̉��Z���ꂽ�l������������
		m_nNumKey = 0;
	}
}

//--------------------------------------
//���C�t�̉��Z
//--------------------------------------
void CPlayer::AddLife(int nAdd)
{
	if (m_nLife <= 99)
	{//���C�t��99�ȉ��Ȃ�
		m_nLife += nAdd;		//���C�t�����Z����
	}
	
}

//--------------------------------------
//���C�t�̌��Z
//--------------------------------------
void CPlayer::SubLife(int nSub)
{
	if (m_nLife >= 0)
	{//���C�t��0�ȏゾ������
		m_nLife -= nSub;		//���C�t�����Z����
	}
}

//--------------------------------------
//�X�P�[���A�b�v
//--------------------------------------
void CPlayer::UpScale(float fScale)
{
	if (m_Scale.x <= MAX_SCALE &&
		m_Scale.y <= MAX_SCALE &&
		m_Scale.z <= MAX_SCALE)
	{//��L�̃X�P�[���ȉ��Ȃ�e�X�P�[���ɉ��Z
		m_Scale.x += fScale;
		m_Scale.y += fScale;
		m_Scale.z += fScale;
	}
}

//--------------------------------------
//�X�P�[���̐ݒ�
//--------------------------------------
void CPlayer::SetScale(float fScale)
{//�e�l�ɐݒ�
	m_Scale.x = fScale;
	m_Scale.y = fScale;
	m_Scale.z = fScale;
}

//--------------------------------------
//�R���{�����Z�b�g����֐�
//--------------------------------------
void CPlayer::ResetCombo()
{
	if (m_nComboCounter > 0)
	{
		m_nComboCounter = 0;								//�G�l�~�[�̃X�R�A�Ɋ֘A����R���{�J�E���^�[�����Z�b�g
		CGame::GetScore()->AddCombo(m_nComboCounter);	//UI��̃R���{�J�E���^�[�����Z�b�g
	}
}

//--------------------------------------
//�X�P�[���̐ݒ�
//--------------------------------------
void CPlayer::DethPlayer(int nLifeChacker)
{
	if (!m_bDenger &&
		nLifeChacker == 3)
	{
		CApplication::GetSound()->Play(CSound::SOUND_SE_LIFE_WARNING);
		m_bDenger = true;
	}

	if (nLifeChacker <= 0)
	{//���C�t��0���傫��������
		Uninit();													//�I������
		CRanking::Set(CScore::Get());								//�����L���O��ݒ�
		CResult::Set(1);											//���U���g��ʂ̐ݒ�(0���ʏ�A����ȊO�͎��S������Ԃɐݒ肷��B)
		CApplication::SetMode(CApplication::MODE::MODE_RESULT);		//���[�h��ݒ肷��
		return;														//�X�V�ɂ���ȏ����Ȃ��悤�ɕԂ�
	}
}

//--------------------------------------
//�X�V�̊֐�����
//�v���C���[�̑���n��
//--------------------------------------
void CPlayer::Command()
{
	//�J�������擾
	CCamera* pCam = CGame::GetCamera();

	//�J�����̊p�x������
	D3DXVECTOR3 camrot = pCam->GetRot();

/*�ړ��n��*/
		if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_W))
		{//�Y������L�[�������ꂽ�Ƃ�

			m_move.x = sinf(camrot.y - D3DX_PI * 0.0f) * m_fInertia;		//�v���C���[�̈ʒu��X�����ɓ�����
			m_move.z = cosf(camrot.y - D3DX_PI * 0.0f) * m_fInertia;		//�v���C���[�̈ʒu��Z�����ɓ�����

			m_rotDest.y = camrot.y - D3DX_PI * 1.0f;						//�v���C���[�̈ړ����̌�����ݒ�

			m_motionType = TYPE_WARK;										//�g�p���郂�[�V�����̐ݒ�

		}

		if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_S))
		{//�Y������L�[�������ꂽ�Ƃ�

			m_move.x = sinf(camrot.y - D3DX_PI * 1.0f) * m_fInertia;		//�v���C���[�̈ʒu��X�����ɓ�����
			m_move.z = cosf(camrot.y - D3DX_PI * 1.0f) * m_fInertia;		//�v���C���[�̈ʒu��Z�����ɓ�����

			m_rotDest.y = camrot.y + D3DX_PI * 0.0f;						//�v���C���[�̈ړ����̌�����ݒ�

			m_motionType = TYPE_WARK;										//�g�p���郂�[�V�����̐ݒ�
		}

		if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_A))
		{//�Y������L�[�������ꂽ�Ƃ�

			m_move.x = -sinf(camrot.y + D3DX_PI * 0.5f) * m_fInertia;		//�v���C���[�̈ʒu��X�����ɓ�����
			m_move.z = -cosf(camrot.y + D3DX_PI * 0.5f) * m_fInertia;		//�v���C���[�̈ʒu��Z�����ɓ�����

			m_rotDest.y = camrot.y + D3DX_PI * 0.5f;						//�v���C���[�̈ړ����̌�����ݒ�

			m_motionType = TYPE_WARK;										//�g�p���郂�[�V�����̐ݒ�
		}
		
		if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_D))
		{//�Y������L�[�������ꂽ�Ƃ�

			m_move.x = sinf(camrot.y + D3DX_PI * 0.5f) * m_fInertia;		//�v���C���[�̈ʒu��X�����ɓ�����
			m_move.z = cosf(camrot.y + D3DX_PI * 0.5f) * m_fInertia;		//�v���C���[�̈ʒu��Z�����ɓ�����

			m_rotDest.y = camrot.y - D3DX_PI * 0.5f;						//�v���C���[�̈ړ����̌�����ݒ�

			m_motionType = TYPE_WARK;										//�g�p���郂�[�V�����̐ݒ�
		}

/*�ړ��ʒu�̑���ƈړ��ʂ̍X�V*/
		MoveCalculation();				//�ړ��ʂ̌v�Z�p�֐����Ăяo��

/*�p�x�̌v�Z�Ɛ��K��*/
		NormalizRotation();				//�p�x�̐��K���p�֐����Ăяo��
}

//--------------------------------------
//�ړ��ʂ̌v�Z
//--------------------------------------
void CPlayer::MoveCalculation()
{
	//�ړ��ʂ��ʒu�ɑ��
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.6f;
	m_move.z += (0.0f - m_move.z) * 0.6f;
}

//--------------------------------------
//�p�x�̐��K��
//--------------------------------------
void CPlayer::NormalizRotation()
{
	//���̊p�x�̐��K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{//���̉�]�p����ڕW�̉�]�p�Ƃ̍���180�x���傫���Ȃ�����
		m_rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{//���̉�]�p����ڕW�̉�]�p�Ƃ̍���-180�x�����������Ȃ�����
		m_rotDest.y += D3DX_PI * 2.0f;
	}

	//���݂̊p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{//���݂̉�]�p��180�x���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y < -D3DX_PI)
	{//���݂̉�]�p��-180�x�����������Ȃ�����
		m_rot.y += D3DX_PI * 2.0f;
	}

	//�e�ڕW�̊p�x�Ɍ��̊p�x�����Z����
	m_rot.x += (m_rotDest.x - m_rot.x) *  0.1f;
	m_rot.y += (m_rotDest.y - m_rot.y) *  0.1f;
	m_rot.z += (m_rotDest.z - m_rot.z) *  0.1f;
}

//--------------------------------------
//���[�V�����^�C�v�̐ݒ�
//--------------------------------------
void CPlayer::MotionManager(MOTION_TYPE type)
{
	m_motionType = type;		//���[�V�����̃^�C�v����

	switch (m_motionType)
	{
	case CPlayer::TYPE_IDLE:

		//0�Ԗڂ̃��[�V�����ݒ�
		m_MotionInfo.aKeyInfo[0].aKeyData[0].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[0].aKeyData[1].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[0].fFrame = DEFAULT_MOTION_FRAME;

		//1�Ԗڂ̃��[�V�����ݒ�
		m_MotionInfo.aKeyInfo[1].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[1].aKeyData[0].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[1].aKeyData[1].fRotX = D3DXToRadian(10);
		m_MotionInfo.aKeyInfo[1].fFrame = DEFAULT_MOTION_FRAME;

		//2�Ԗڂ̃��[�V�����ݒ�
		m_MotionInfo.aKeyInfo[2].aKeyData[0].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[2].aKeyData[2].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[2].fFrame = DEFAULT_MOTION_FRAME;
		
		break;

	case CPlayer::TYPE_WARK:

		//0�Ԗڂ̃��[�V�����ݒ�
		m_MotionInfo.aKeyInfo[0].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[0].aKeyData[1].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[0].fFrame = 30.0f;

		//1�Ԗڂ̃��[�V�����ݒ�
		m_MotionInfo.aKeyInfo[1].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[1].aKeyData[0].fRotX = -0.70f;
		m_MotionInfo.aKeyInfo[1].aKeyData[1].fRotX = D3DXToRadian(92);
		m_MotionInfo.aKeyInfo[1].fFrame = 10.0f;

		//2�Ԗڂ̃��[�V�����ݒ�
		m_MotionInfo.aKeyInfo[2].aKeyData[0].fPosX = 0.0f;
		m_MotionInfo.aKeyInfo[2].aKeyData[2].fRotX = 0.0f;
		m_MotionInfo.aKeyInfo[2].fFrame = 20.0f;

		break;

	default:		//����ȊO
		assert(false);					//�v���O�������~�߂܂���
		break;
	}
}

//--------------------------------------
//�e�������蔻��
//--------------------------------------
void CPlayer::CollisionManager()
{
	for (int i = 0; i < MAX_OBJ; i++)
	{//�I�u�W�F�N�g�̑��ʕ��J�E���g����
		CObject *pObj = CObject::Getobject(i);		//�I�u�W�F�N�g�̎擾
		CObject::ObjType objType;					//�I�u�W�F�N�g�^�C�v��錾

		if (pObj == nullptr)
		{//�I�u�W�F�N�g���g�p����Ă��Ȃ������Ƃ�
			continue;						//for���ŏ��ɕԂ�
		}

		//�I�u�W�F�N�g�^�C�v�ϐ��ɃI�u�W�F�N�g�^�C�v������
		objType = pObj->GetObjectType();

		/*�I�u�W�F�N�g�^�C�v���G�l�~�[�œ����蔻��̕Ԃ�l���^��������*/
		if (objType == OBJTYPE_ENEMY_NORMAL)
		{
			CEnemy* pEnemy = (CEnemy*)pObj;			//pObject��CEnemy�^�Ƀ_�E���L���X�g

			if (CHelperFunction::CircleCollision(m_pos, m_Scale.y * 20.0f, pEnemy->GetPos(), 20.0f) &&
				m_Scale.y >= pEnemy->GetScale().y)
			{//�����蔻��̕Ԃ�l���^���v���C���[�̃X�P�[�����G�l�~�[�̃X�P�[���ȏ�Ȃ�
				m_pos = m_posOld;								//�ʒu���ߋ��̈ʒu�ɐݒ�
				m_nComboCounter++;								//�G�l�~�[�̃X�R�A�Ɋ֘A����R���{�J�E���^�[�����Z
				pEnemy->HitNormal(m_nComboCounter);					//�G�l�~�[�̓����蔻�菈������������
				CGame::GetScore()->AddCombo(m_nComboCounter);	//UI��̃R���{�J�E���^�[�����Z
			}
		}

		if (objType == OBJTYPE_ENEMY_ATTACKER)
		{
			CEnemy* pEnemy = (CEnemy*)pObj;			//pObject��CEnemy�^�Ƀ_�E���L���X�g

			if (CHelperFunction::CircleCollision(m_pos, m_Scale.y * 20.0f, pEnemy->GetPos(), 20.0f))
			{//�����蔻��̕Ԃ�l���^
				m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
				m_nComboCounter++;						//�G�l�~�[�̃X�R�A�Ɋ֘A����R���{�J�E���^�[�����Z
				pEnemy->HitAttacker(m_nComboCounter);					//�A�^�b�J�[�̓����蔻�菈������������
				CGame::GetScore()->AddCombo(m_nComboCounter);	//UI��̃R���{�J�E���^�[�����Z
			}
		}

		if (objType == OBJTYPE_ENEMY_SPEEDER)
		{
			CEnemy* pEnemy = (CEnemy*)pObj;			//pObject��CEnemy�^�Ƀ_�E���L���X�g

			if (CHelperFunction::CircleCollision(m_pos, m_Scale.y * 20.0f, pEnemy->GetPos(), 20.0f) &&
				m_Scale.y >= pEnemy->GetScale().y)
			{//�����蔻��̕Ԃ�l���^���v���C���[�̃X�P�[�����G�l�~�[�̃X�P�[���ȏ�Ȃ�
				m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
				m_nComboCounter++;						//�G�l�~�[�̃X�R�A�Ɋ֘A����R���{�J�E���^�[�����Z
				pEnemy->HitSpeeder(m_nComboCounter);					//�X�s�[�_�[�̓����蔻�菈������������
				CGame::GetScore()->AddCombo(m_nComboCounter);	//UI��̃R���{�J�E���^�[�����Z
			}
		}

		if (objType == OBJTYPE_ENEMY_DOCTOR)
		{
			CEnemy* pEnemy = (CEnemy*)pObj;			//pObject��CEnemy�^�Ƀ_�E���L���X�g

			if (CHelperFunction::CircleCollision(m_pos, m_Scale.y * 20.0f, pEnemy->GetPos(), 20.0f) &&
				m_Scale.y >= pEnemy->GetScale().y)
			{//�����蔻��̕Ԃ�l���^���v���C���[�̃X�P�[�����G�l�~�[�̃X�P�[���ȏ�Ȃ�
				m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
				m_nComboCounter++;								//�G�l�~�[�̃X�R�A�Ɋ֘A����R���{�J�E���^�[�����Z
				pEnemy->HitCure(m_nComboCounter);					//�h�N�^�[�̓����蔻�菈������������
				CGame::GetScore()->AddCombo(m_nComboCounter);	//UI��̃R���{�J�E���^�[�����Z
			}
		}

		if (objType == OBJTYPE_ENEMY_MULTI)
		{
			CEnemy* pEnemy = (CEnemy*)pObj;			//pObject��CEnemy�^�Ƀ_�E���L���X�g

			if (CHelperFunction::CircleCollision(m_pos, m_Scale.y * 20.0f, pEnemy->GetPos(), 20.0f) &&
				m_Scale.y >= pEnemy->GetScale().y)
			{//�����蔻��̕Ԃ�l���^���v���C���[�̃X�P�[�����G�l�~�[�̃X�P�[���ȏ�Ȃ�
				m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
				m_nComboCounter++;								//�G�l�~�[�̃X�R�A�Ɋ֘A����R���{�J�E���^�[�����Z
				pEnemy->HitMulti(m_nComboCounter);						//�����^�̓����蔻�菈������������
				CGame::GetScore()->AddCombo(m_nComboCounter);	//UI��̃R���{�J�E���^�[�����Z
			}
		}

		if (objType == OBJTYPE_ENEMY_BOSS)
		{
			CEnemy* pEnemy = (CEnemy*)pObj;			//pObject��CEnemy�^�Ƀ_�E���L���X�g

			if (CHelperFunction::CircleCollision(m_pos, m_Scale.y * 20.0f, pEnemy->GetPos(), 20.0f) &&
				m_Scale.y >= pEnemy->GetScale().y)
			{//�����蔻��̕Ԃ�l���^���v���C���[�̃X�P�[�����G�l�~�[�̃X�P�[���ȏ�Ȃ�
				m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
				m_nComboCounter++;								//�G�l�~�[�̃X�R�A�Ɋ֘A����R���{�J�E���^�[�����Z
				pEnemy->HitBoss(m_nComboCounter);				//�{�X�̓����蔻�菈������������
				CGame::GetScore()->AddCombo(m_nComboCounter);	//UI��̃R���{�J�E���^�[�����Z
			}
		}

		/*�I�u�W�F�N�g�^�C�v�������œ����蔻��̕Ԃ�l���^��������*/
		if ((objType == OBJTYPE_BILDING_HELLOWARK ||							
			objType == OBJTYPE_BILDING_LANDMARKTOWER ||						
			objType == OBJTYPE_BILDING_THUMBSUP ||							
			objType == OBJTYPE_BILDING_DTHUMBSUP ||							
			objType == OBJTYPE_BILDING_TEMPLE ||								
			objType == OBJTYPE_BILDING_APOSTLE) &&								
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(SIZE_PLUS, 0.0f, SIZE_PLUS), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		//if (objType == OBJTYPE_SPOWN_BILDING &&
		//	CHelperFunction::CircleCollision(m_pos, m_Scale.y * SIZE_PLUS, pObj->Getpos(), SIZE_PLUS))
		//{//�I�u�W�F�N�g�^�C�v���o�����錚���������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}

		if (objType == OBJTYPE_WALL_OUTSIDE_WIDE &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(10060.0f, 0.0f, 50.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_WALL_OUTSIDE_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(52.0f, 0.0f, 10060.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_WALL_WIDE &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(800.0f, 0.0f, 60.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_WALL_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(60.0f, 0.0f, 800.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_WALL_LONGLONG_WILD &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(2600.0f, 0.0f, 60.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		}

		if (objType == OBJTYPE_WALL_LONGLONG_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(60.0f, 0.0f, 2600.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_FENCE_WIDE &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(460.0f, 0.0f, 30.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_FENCE_HIGHT &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(30.0f, 0.0f, 460.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		}

		if (objType == OBJTYPE_EAT_DESCRIPTION &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(2000.0f, 0.0f, 30.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			//�����̃T�E���h���~
			CApplication::GetSound()->Stop();
			
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
			CGame::GetEatDescription()->HitEatDescription();
			CGame::GetScore()->SetStartTimer(true);
			
			//�T�E���h�̍Đ�
			CApplication::GetSound()->Play(CSound::SOUND_BGM_GAME);
		}

		if (objType == OBJTYPE_DESCRIPTION &&
			CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(460.0f, 0.0f, 30.0f), m_posOld))
		{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
			m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
			CGame::GetEatDescription()->HitDescription();
		}

	}
}
