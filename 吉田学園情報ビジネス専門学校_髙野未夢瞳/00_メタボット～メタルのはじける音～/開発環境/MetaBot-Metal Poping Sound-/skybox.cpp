//-----------------------------------------------------------------------------------------------------------
//
//���b�V��
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "renderer.h"
#include "skybox.h"
#include "input.h"
#include "player.h"
#include <d3dx9.h>

//--------------------------------------
//�萔��`
//--------------------------------------
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);		//���_�t�H�[�}�b�g

const float CENTER_POINT = 20000.0f;															//���b�V���t�B�[���h�̒��S�_
const float MESH_SIZE = 100.0f;																	//1���b�V���̃T�C�Y
const float WIDTH_MESH = 20000.0f;																//���̕�
const int MESH_DIVISION = 20;																	//���̕�����
const int  MAX_MENX = 200;																		//X�̕ӂ̍ő吔
const int  MAX_MENZ = 200;																		//Y�̕ӂ̍ő吔
const int VEX = ((MESH_DIVISION + 1) * (MESH_DIVISION + 1));									//�ő咸�_��
const int INDEX = ((((MESH_DIVISION + 1) * 2) * MESH_DIVISION) + ((MESH_DIVISION - 1) * 2));	//�C���f�b�N�X�̌v�Z
const int POLYGON = ((MESH_DIVISION * MESH_DIVISION * 2) + ((MESH_DIVISION - 1) * 4));			//�|���S���̑���

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CSkybox::CSkybox()
{
	m_pIdxBuff = nullptr;				//�C���f�b�N�X�o�b�t�@�̃N���A
	m_pVtxBuff = nullptr;				//���_�o�b�t�@�̃N���A
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CSkybox::~CSkybox()
{
}

//--------------------------------------
//����
//--------------------------------------
CSkybox * CSkybox::Create(D3DXVECTOR3 pos)
{
	CSkybox *pMeshfild = new CSkybox;

	if (pMeshfild != nullptr)
	{
		pMeshfild->Init();
		pMeshfild->SetPos(pos);
	}

	return pMeshfild;
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CSkybox::Init()
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�~��T�������̕������Ŋ����Ċp�x�����߂�(Z��)
	float fDivisionNumberZ = (D3DX_PI * 2.0f) / (MESH_DIVISION - 1);

	//�~��T�������̕������Ŋ����Ċp�x�����߂�(X��)
	float fDivisionNumberX = (D3DX_PI) / (MESH_DIVISION - 1);

	for (int nCntZ = 0; nCntZ < MESH_DIVISION; nCntZ++)
	{
		//���݂�Z���̊p�x�����߂�
		float fRotZ = fDivisionNumberZ * nCntZ;

		for (int nCntX = 0; nCntX < MESH_DIVISION; nCntX++)
		{
			//���݂�X���̊p�x�����߂�
			float fRotX = fDivisionNumberX * nCntX;

			//���_���W�̐ݒ�(�ɍ��W���g�p)
			pVtx[0].pos.x = sinf(fRotX) * sinf(fRotZ) * WIDTH_MESH;
			pVtx[0].pos.y = cosf(fRotX) * WIDTH_MESH;
			pVtx[0].pos.z = sinf(fRotX) * cosf(fRotZ) * WIDTH_MESH;

			//�@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(sinf(fRotX), 0.0f, cosf(fRotZ));

			//�F�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`���̐ݒ�
			float fTexZ = 1.0f / MESH_DIVISION * fRotZ;
			float fTexX = 1.0f / MESH_DIVISION * fRotX;
			pVtx[0].tex = D3DXVECTOR2(fTexZ, -(fTexX * 2.f));

			//���_�ԍ������炷
			pVtx++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	int nCount = 0;

	for (int nCtZ = 0; nCtZ < MESH_DIVISION -1; nCtZ++)
	{
		for (int nCtX = 0; nCtX <= MESH_DIVISION; nCtX++)
		{
			pIdx[nCount] = nCtX + nCtZ * MESH_DIVISION + MESH_DIVISION;		//���_�̏�i�̔ԍ�
			pIdx[nCount + 1] = nCtX + nCtZ * MESH_DIVISION;						//���_�̉��i�̔ԍ�		�@
			nCount += 2;														//���_�̔ԍ������炷

			if (nCtX == MESH_DIVISION - 1)
			{
				pIdx[nCount] = nCtX + nCtZ * MESH_DIVISION;				//�k�ރ|���S����i
				pIdx[nCount + 1] = (nCtZ + 2) * MESH_DIVISION;			//�k�ރ|���S�����i

				//������n�܂�X�^�[�g�n�_�����炷(���̂܂܂��ƒl������for���ŏ㏑������Ă��܂�)
				nCount += 2;				//���_�̔ԍ������炷
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CSkybox::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	//�I�u�W�F�N�g�̊J��
	CObject::Release();
}

//--------------------------------------
//�X�V
//--------------------------------------
void CSkybox::Update()
{
	
}

//--------------------------------------
//�`��
//--------------------------------------
void CSkybox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;												//�v�Z�p���C�g���b�N�X

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

	//���C�g�̖�����
	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̎擾
	CTexture *pTexture = CApplication::GetTexture();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(CTexture::TEXTURE_SKY));

	//���b�V���̕`��
	pDevice->DrawIndexedPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		0,
		VEX,
		0,
		POLYGON);

	//�e�N�X�`���̃��Z�b�g
	pDevice->SetTexture(0, NULL);

	//���C�g�̗L����
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
