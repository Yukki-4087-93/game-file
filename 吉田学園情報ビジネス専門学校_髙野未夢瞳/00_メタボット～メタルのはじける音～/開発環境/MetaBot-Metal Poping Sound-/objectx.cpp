//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "objectx.h"
#include "renderer.h"
#include "application.h"
#include "texture.h"
#include "main.h"
#include <assert.h>

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CObjectX::CObjectX()
{
	m_pos = { 0.0f,0.0f,0.0f };
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CObjectX::~CObjectX()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CObjectX::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("Data/Model/H.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMat,
		NULL,
		&m_nNumMat,
		&m_Mesh);

	
	//���f���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̏�����

	return S_OK;
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
CObjectX *CObjectX::Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd)
{
	CObjectX* pObject3D;

	pObject3D = new CObjectX;

	if (pObject3D != nullptr)
	{
		pObject3D->Init();
		pObject3D->SetPos(pos);
	}
	else
	{
		assert(false);
	}

	return pObject3D;
}

//--------------------------------------
//�X�V
//--------------------------------------
void CObjectX::Update()
{
	//VERTEX_3D* pVtx;			//���_���ւ̃|�C���^

	////���_�o�b�t�@���R�b�N���A���_���ւ̃|�C���^���擾
	//m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�
	//pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	//pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	//pVtx[0].pos.z = 150.0f;

	//pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	//pVtx[1].pos.z = 150.0f;

	//pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	//pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	//pVtx[2].pos.z = 150.0f;

	//pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	//pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	//pVtx[3].pos.z = 150.0f;

	////���_�o�b�t�@���A�����b�N����
	//m_Vertex->Unlock();
}

//--------------------------------------
//�`��
//--------------------------------------
void CObjectX::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;							//���݂̃}�g���b�N�X�ۑ��p
	D3DXMATERIAL *pMat;								//�}�e���A���f�[�^�ւ̃|�C���^

													//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A���ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_BuffMat->GetBufferPointer();

	for (int i = 0; i < (int)m_nNumMat; i++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//���f���p�[�c�̕`��
		m_Mesh->DrawSubset(i);
	}

	//�ێ����Ă����}�e���A����ԋp
	pDevice->SetMaterial(&matDef);
}

//--------------------------------------
//�I��
//--------------------------------------
void CObjectX::Uninit()
{
	//���b�V���̔j��
	if (m_Mesh != NULL)
	{
		m_Mesh->Release();
		m_Mesh = NULL;
	}

	//�}�e���A���̔j��
	if (m_BuffMat != NULL)
	{
		m_BuffMat->Release();
		m_BuffMat = NULL;
	}

	CObject::Release();
}

//--------------------------------------
//�ʒu�̃Q�b�^�[
//--------------------------------------
const D3DXVECTOR3 & CObjectX::Getpos() const
{
	return m_pos;
}
