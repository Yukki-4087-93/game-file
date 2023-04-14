//--------------------------------------------------------------------------------------
//
// ���f��
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "renderer.h"
#include "model.h"
#include "object.h"

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CModel::CModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̃N���A
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̃N���A
	m_bChangeColor = false;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CModel::~CModel()
{
}

//--------------------------------------
//����
//--------------------------------------
CModel * CModel::Create(const char* pfile, const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot, MODEL_TYPE type)
{
	CModel * pModel = new CModel;

	if (pModel != nullptr)
	{
		pModel->SetModel(pfile);
		pModel->Init();
		pModel->m_pos = pos;
		pModel->m_rot = rot;
		pModel->m_StartPoint = pos;
		pModel->m_StartRotation = rot;
		pModel->SetModelType(type);
	}

	return pModel;
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CModel::Init()
{
	//���f���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̏�����

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CModel::Uninit()
{
}

//--------------------------------------
//�X�V
//--------------------------------------
void CModel::Update()
{
}

//--------------------------------------
//�`��
//--------------------------------------
void CModel::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParent;					//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;									//���݂̃}�g���b�N�X�ۑ��p
	D3DXMATERIAL *pMat;										//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{//�e���f���̃|�C���^�ɒl�������Ă����Ƃ�
		mtxParent = m_pParent->GetMtxWorld();				//�e���f���̃��[���h���W���擾
	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);		//�ŐV�̃}�g���b�N�X���擾
	}

	//�e�̃}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A���ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)(m_BuffMat->GetBufferPointer());

	for (int i = 0; i < (int)m_nNumMat; i++)
	{
		D3DXCOLOR col = pMat[i].MatD3D.Diffuse;
		if (m_bChangeColor)
		{
			//�}�e���A���̐F�ύX
			col.a = 0.3f;

		}

		else
		{
			//�}�e���A���̐F�ύX
			col.a = 1.f;
		}

		//�ݒ肵���J���[����
		pMat[i].MatD3D.Diffuse = col;

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[i].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, nullptr);

		//���f���p�[�c�̕`��
		m_Mesh->DrawSubset(i);

	}

	//�ێ����Ă����}�e���A����ԋp
	pDevice->SetMaterial(&matDef);

	/*���[���h�}�g���b�N�X�̏������A�����E�ʒu�̔��f
	�@�e�̃}�g���b�N�X�Ɗ|�����킹��
	 ���[���h�}�g���b�N�X�̐ݒ�
	 �@X�t�@�C���̕`��*/
}

//--------------------------------------
//���f���̐ݒ�
//--------------------------------------
void CModel::SetModel(const char* pfile)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pfile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_BuffMat,
		NULL,
		&m_nNumMat,
		&m_Mesh);

	//���f���̃T�C�Y�̒l������������
	m_VtxMax = D3DXVECTOR3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	m_VtxMin = D3DXVECTOR3(FLT_MAX, FLT_MAX, FLT_MAX);

	//���_���̕ۑ�����ϐ���錾
	int nNumVertex = 0;

	//���_����������
	nNumVertex = m_Mesh->GetNumVertices();

	//���_�t�H�[�}�b�g��ۑ�����ϐ���錾
	DWORD SizeFVF;

	//���_�t�H�[�}�b�g�̎擾
	SizeFVF = D3DXGetFVFVertexSize(m_Mesh->GetFVF());

	//���_�o�b�t�@�ւ̃|�C���^
	BYTE* pVtxBuffer;

	//���_�����b�N����
	m_Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuffer);

	//�S�Ă̒��_�̈ʒu���擾����
	for (int nCounter = 0; nCounter < nNumVertex; nCounter++)
	{
		//���_���W����
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuffer;

		if (m_VtxMax.x < Vtx.x)
		{//X
			m_VtxMax.x = Vtx.x;
		}
		if (m_VtxMin.x > Vtx.x)
		{
			m_VtxMin.x = Vtx.x;
		}

		if (m_VtxMax.y < Vtx.y)
		{//Y
			m_VtxMax.y = Vtx.y;
		}
		if (m_VtxMin.y > Vtx.y)
		{
			m_VtxMin.y = Vtx.y;
		}

		if (m_VtxMax.z < Vtx.z)
		{//Z
			m_VtxMax.z = Vtx.z;
		}
		if (m_VtxMin.z > Vtx.z)
		{
			m_VtxMin.z = Vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y�̕��|�C���^��i�߂�
		pVtxBuffer += SizeFVF;
	}

	//���_���A�����b�N����
	m_Mesh->UnlockVertexBuffer();
}
