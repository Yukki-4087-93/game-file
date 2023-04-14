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
#include "meshifild.h"
#include "input.h"
#include "player.h"
#include <d3dx9.h>

//--------------------------------------
//�萔��`
//--------------------------------------
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);	//���_�t�H�[�}�b�g

const float CENTER_POINT = 20000.0f;														//���b�V���t�B�[���h�̒��S�_
const float MESH_SIZE = 100.0f;																//1���b�V���̃T�C�Y
const int  MAX_MENX = 200;																	//X�̕ӂ̍ő吔
const int  MAX_MENZ = 200;																	//Z�̕ӂ̍ő吔
const int VEX = ((MAX_MENX + 1) * (MAX_MENZ + 1));											//�ő咸�_��
const int INDEX = ((((MAX_MENX + 1) * 2) * MAX_MENZ) + ((MAX_MENZ - 1) * 2));				//�C���f�b�N�X�̌v�Z
const int POLYGON = ((MAX_MENX * MAX_MENZ * 2) + ((MAX_MENZ - 1) * 4));						//�|���S���̑���

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CMeshField::CMeshField()
{
	m_pIdxBuff = nullptr;				//�C���f�b�N�X�o�b�t�@�̃N���A
	m_pVtxBuff = nullptr;				//���_�o�b�t�@�̃N���A
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CMeshField::~CMeshField()
{
}

//--------------------------------------
//����
//--------------------------------------
CMeshField * CMeshField::Create()
{
	CMeshField *pMeshfild = new CMeshField;

	if (pMeshfild != nullptr)
	{
		pMeshfild->Init();
	}

	return pMeshfild;
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CMeshField::Init()
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
	VERTEX_3D*pVtx;			

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ <= MAX_MENZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX <= MAX_MENX; nCntX++)
		{
			pVtx[0].pos = D3DXVECTOR3(MESH_SIZE * nCntX - CENTER_POINT / 2,
									  0.0f + 2.0f, 
									  -MESH_SIZE * nCntZ + CENTER_POINT / 2);

			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			pVtx[0].col = D3DXCOLOR(0.2f, 0.5f, 0.1f, 1.0f);

			pVtx += 1;
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

	for (int nCtZ = 0; nCtZ < MAX_MENZ; nCtZ++)
	{
		for (int nCtX = 0; nCtX <= MAX_MENX; nCtX++)
		{
			pIdx[0] = (nCtX)+(MAX_MENX + 1) + (nCtZ * (MAX_MENX + 1));		//���_�̏�i�̔ԍ�
			pIdx[1] = (nCtX)+(nCtZ * (MAX_MENX + 1));						//���_�̉��i�̔ԍ�		�@
			pIdx += 2;														//���_�̔ԍ������炷
		}

		if (nCtZ < MAX_MENZ - 1)
		{
			pIdx[0] = pIdx[-1];				//�k�ރ|���S����i
			pIdx[1] = ((MAX_MENX + 1) * 2) + (nCtZ * (MAX_MENX + 1));	//�k�ރ|���S�����i

			//������n�܂�X�^�[�g�n�_�����炷(���̂܂܂��ƒl������for���ŏ㏑������Ă��܂�)
			pIdx += 2;										//���_�̔ԍ������炷
		}
		else
		{

		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CMeshField::Uninit()
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
void CMeshField::Update()
{

}

//--------------------------------------
//�`��
//--------------------------------------
void CMeshField::Draw()
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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���b�V���̕`��
	pDevice->DrawIndexedPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		0,
		VEX,
		0,
		POLYGON);
}

//--------------------------------------------------
// 2D�x�N�g���̊O��
//--------------------------------------------------
float CMeshField::Vec2Cross(D3DXVECTOR3 * v1, D3DXVECTOR3 * v2)
{
	return (v1->x * v2->z) - (v1->z * v2->x);
}

//--------------------------------------------------
// 2D�x�N�g���̊O��
//--------------------------------------------------
float CMeshField::Vec2Dot(D3DXVECTOR3 * v1, D3DXVECTOR3 * v2)
{
	return (v1->x * v2->x) + (v1->z * v2->z);
}

//--------------------------------------
//�����蔻��
//--------------------------------------
void CMeshField::Collision(D3DXVECTOR3 *pos)
{
	VERTEX_3D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD *pIdx;
	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	for (int i = 0; i < POLYGON; i++)
	{
		if (pIdx[i] == pIdx[i + 1] ||
			pIdx[i] == pIdx[i + 2] ||
			pIdx[i + 1] == pIdx[i + 2])
		{
			continue;
		}

		D3DXVECTOR3 Vecpos[3] = {};

		Vecpos[0] = pVtx[pIdx[i]].pos;
		Vecpos[1] = pVtx[pIdx[i] + 1].pos;
		Vecpos[2] = pVtx[pIdx[i] + 2].pos;

		for (int j = 0; j < 3; j++)
		{
			D3DXVec3TransformCoord(&Vecpos[j], &Vecpos[j], &mtxWorld);
		}

		int nLine = 0;

		for (int j = 0; j < 3; j++)
		{
			D3DXVECTOR3 Vec = Vecpos[(j + 1) % 3] - Vecpos[j];			//�|���S���̐���̌v�Z

			D3DXVECTOR3 DiffVec = *pos - Vecpos[j];						//���݂̈ʒu�Ɛ���̌��Z

			float fVecLine = Vec2Cross(&DiffVec, &Vec);

			if ((i % 2 == 0 && fVecLine > 0.0f) ||
				(i % 2 != 0 && fVecLine < 0.0f))
			{
				nLine++;
			}
			else
			{
				break;
			}

		}

		if (nLine == 3)
		{
			//�x�N�g�����v�Z
			D3DXVECTOR3 Vec1 = Vecpos[1] - Vecpos[0];
			D3DXVECTOR3 Vec2 = Vecpos[2] - Vecpos[0];
			D3DXVECTOR3 Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���K���̏�����

																	//�O�ς̌v�Z
			D3DXVec3Cross(&Normal, &Vec1, &Vec2);

			//���K��
			D3DXVec3Normalize(&Normal, &Normal);

			D3DXVECTOR3 VecA = *pos - Vecpos[0];

			//���b�V���t�B�[���h�̃v���C���[�̈ʒu�ݒ�
			pos->y = (Vecpos[0].y - (Normal.x * (pos->x - Vecpos[0].x) + Normal.z * (pos->z - Vecpos[0].z)) / Normal.y);
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
