//--------------------------------------------------------------
//
//�J����
//Author:takano
//
//--------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include"camera.h"
#include "input.h"
#include "renderer.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include<time.h>

//------------------------
//�R���X�g���N�^
//------------------------
CCamera::CCamera()
{
	srand((unsigned int)time(nullptr));						//�����_���̏�����
}

//------------------------
//�f�X�g���N�^
//------------------------
CCamera::~CCamera()
{
}

//------------------------
//�N���G�C�g
//------------------------
CCamera * CCamera::Create(D3DXVECTOR3 pos)
{
	CCamera* pCamera = new CCamera;

	if (pCamera != nullptr)
	{
		pCamera->Init();
	}

	return pCamera;
}

//------------------------
//�J�����̏�����
//------------------------
void CCamera::Init()
{
	//���_�E�����_�E�������ݒ肷��
	m_InitPosV = D3DXVECTOR3(0.0f, 0.0f, -400.0f);								//���_ ����ʒu
	m_InitPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//���Ă�ʒu
	m_VecU = D3DXVECTOR3(0.0f, 10.0f, 0.0f);								//
	m_rot = D3DXVECTOR3(D3DXToRadian(10.f), 0.0f, 0.0f);					//�p�x
	float fLength1 = (m_InitPosV.x - m_InitPosR.x);							//���_���璍���_�܂ł�X������
	float fLength2 = (m_InitPosV.z - m_InitPosR.z);							//���_���璍���_�܂ł�Y������
	m_fDistance = sqrtf((fLength1 * fLength1) + (fLength2 * fLength2));		//���_���璍���_�̋���
	m_nCameraFlame = -1;
}

//------------------------
//�J�����̏I��
//------------------------
void CCamera::Uninit()
{
}

//------------------------
//�J�����̍X�V
//------------------------
void CCamera::Update()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�v���C���[���̎擾
	CPlayer *pPlayer = CGame::GetPlayer();

	//�v���C���[�̃X�P�[�����擾
	D3DXVECTOR3 Scale = CGame::GetPlayer()->GetScale();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pPlayer->GetPos().x, pPlayer->GetPos().y, pPlayer->GetPos().z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�̒���
	D3DXVECTOR3 VecPosV = m_InitPosV;
	VecPosV.z -= ((Scale.z - 1.0f) * 120.0f);

	//�����_�̒���
	D3DXVECTOR3 VecPosR = m_InitPosR;
	VecPosR.y = (Scale.y - 1.0f) * 40.f + 100.f;

	//���[���h���W�s����g���č��W�����߂�
	D3DXVec3TransformCoord(&m_WorldPosR, &VecPosR, &m_mtxWorld);
	D3DXVec3TransformCoord(&m_WorldPosV, &VecPosV, &m_mtxWorld);

	//���_�̐���
	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_C) ||
		CApplication::GetKyeboard()->GetkeyboardPress(DIK_E) ||
		CApplication::GetKyeboard()->GetkeyboardPress(DIK_RIGHT))
	{//������
		m_rot.y += 0.05f;
	}

	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_Z) ||
		CApplication::GetKyeboard()->GetkeyboardPress(DIK_Q) ||
		CApplication::GetKyeboard()->GetkeyboardPress(DIK_LEFT))
	{//�E����
		m_rot.y -= 0.05f;
	}

	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_UP))
	{
		if (m_rot.x < D3DXToRadian(45.f))
		{
			m_rot.x += 0.02f;
		}

	}

	if (CApplication::GetKyeboard()->GetkeyboardPress(DIK_DOWN))
	{
		if (m_rot.x > D3DXToRadian(10.f))
		{
			m_rot.x -= 0.02f;
		}
	}


	//�p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{//��]�p��180�x���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{//��]�p��-180�x�����������Ȃ�����
		m_rot.y += D3DX_PI * 2;
	}
}

//------------------------
//�J�����̃Z�b�g
//------------------------
void CCamera::Set()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�r���[���C�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�J�����k�x�̐ݒ�
	D3DXVECTOR3 magnitude = D3DXVECTOR3(0, 0, 0);

	if (m_nCameraFlame >= 0)
	{
		m_nCameraFlame--;

		magnitude.x = rand() % (int)m_fCameraMagnitude - m_fCameraMagnitude / 2;					//�����_���l�̏����l��ݒ�

		magnitude.y = rand() % (int)m_fCameraMagnitude - m_fCameraMagnitude / 2;				//�����_���l�̏����l��ݒ�

		magnitude.z = rand() % (int)m_fCameraMagnitude - m_fCameraMagnitude / 2;					//�����_���l�̏����l��ݒ�

	}

	//�r���[�}�g���b�N�X�̐���
	D3DXMatrixLookAtLH(&m_mtxView,
		&(m_WorldPosV + magnitude),
		&(m_WorldPosR + magnitude),
		&m_VecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxprojection);

	//�v���W�F�N�V�����}�g���b�N�X����
	D3DXMatrixPerspectiveFovLH(&m_mtxprojection,
		D3DXToRadian(60.0f),					//�����
		(float)1280.0f / (float)720.0f,			//�A�X�y�N�g��
		100.0f,									//�J�����̋ߎ�����
		40000.0f);								//�J�����̉�������

												//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxprojection);
}

//------------------------
//�J�����̐k�x�ݒ�
//------------------------
void CCamera::Sequence(int nFlame, float fMagnitude)
{
	m_nCameraFlame = nFlame;
	m_fCameraMagnitude = fMagnitude;
}
