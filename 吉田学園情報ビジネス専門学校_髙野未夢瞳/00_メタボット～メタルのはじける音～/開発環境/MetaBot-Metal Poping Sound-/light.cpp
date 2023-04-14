//-----------------------------------------------------------------
//
//���C�g
//Author:takano
//
//----------------------------------------------------------------

//----------------------------
//�C���N���[�h�t�@�C��
//----------------------------
#include <stdio.h>
#include"light.h"
#include "application.h"
#include "renderer.h"

//----------------------------
//�R���X�g���N�^
//----------------------------
CLight::CLight()
{
}

//----------------------------
//�f�X�g���N�^
//----------------------------
CLight::~CLight()
{
}

//----------------------------
//���C�g�̐���
//----------------------------
CLight * CLight::Create(D3DXVECTOR3 pos)
{
	CLight* pLight = new CLight;

	if (pLight != nullptr)
	{
		pLight->Init();
	}

	return pLight;
}

//----------------------------
//���C�g������
//----------------------------
void CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();						//�f�o�C�X�̃|�C���^
	D3DXVECTOR3 vecDir;												//���C�g�̕����x�N�g��

	//���C�g���N���A����
	ZeroMemory(&m_Light, sizeof(D3DLIGHT9));

	//���C�g�̎��
	m_Light[0].Type = D3DLIGHT_DIRECTIONAL;
	//���C�g�̎��
	m_Light[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	m_Light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	//���C�g�̊g�U���̐ݒ�
	m_Light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 0.65f);

	//���C�g�̕�����ݒ�
	m_vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	//���C�g�̕�����ݒ�
	m_vecDir[1] = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

	//���K������i�傫�����h�P�h�x�N�g���ɂ���j
	D3DXVec3Normalize(&m_vecDir[0],&m_vecDir[0]);
	m_Light[0].Direction = m_vecDir[0];

	//���K������i�傫�����h�P�h�x�N�g���ɂ���j
	D3DXVec3Normalize(&m_vecDir[1], &m_vecDir[1]);
	m_Light[1].Direction = m_vecDir[1];

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &m_Light[0]);			//�ŏ��̐���0�̓��C�g�̔ԍ��������Ă���

	//���C�g��ݒ肷��
	pDevice->SetLight(1, &m_Light[1]);			//�ŏ��̐���1�̓��C�g�̔ԍ��������Ă��邺

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);

	pDevice->SetRenderState(D3DRS_AMBIENT, 0xff403333);
}

//----------------------------
//���C�g�I��
//----------------------------
void CLight::Uninit()
{

}

//----------------------------
//���C�g�X�V
//----------------------------
void CLight::Update()
{

}