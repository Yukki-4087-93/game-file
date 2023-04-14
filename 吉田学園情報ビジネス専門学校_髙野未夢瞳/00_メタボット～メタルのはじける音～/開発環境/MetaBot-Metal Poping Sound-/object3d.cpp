//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "object3d.h"
#include "renderer.h"
#include "application.h"
#include "texture.h"
#include "main.h"
#include <assert.h>

//--------------------------------------
//�萔��`
//--------------------------------------
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CObject3D::CObject3D()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_texture = CTexture::TEXTURE_NONE;
	m_Change_Height = 0.0f;
	m_Change_Width = 0.0f;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CObject3D::~CObject3D()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CObject3D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_Vertex, NULL);

	VERTEX_3D * pVtx;

	m_Change_Height = 30.0f;
	m_Change_Width = 30.0f;
	m_bBillboard = false;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(m_Change_Height * m_Change_Height + m_Change_Width * m_Change_Width) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_Change_Height, m_Change_Width);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = sinf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.y = cosf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//nor�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,1.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�e�N�X�`�����g�p���Ă��Ȃ���Ԃɂ���
	m_texture = CTexture::TEXTURE_NONE;

	//���_�o�b�t�@���A�����b�N����
	m_Vertex->Unlock();

	return S_OK;
}

//--------------------------------------
//�N���G�C�g
//--------------------------------------
CObject3D *CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ObfHi, float ObfWd, CTexture::TEXTURE tex, bool bBillboard)
{
	 CObject3D* pObject3D = new CObject3D;

	if (pObject3D != nullptr)
	{
		pObject3D->Init();
		pObject3D->SetSize(ObfHi, ObfWd);
		pObject3D->SetPos(pos);
		pObject3D->SetRot(rot);
		pObject3D->SetBillboard(bBillboard);
		pObject3D->SetTexture(tex);
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
void CObject3D::Update()
{
	assert(m_objType != OBJTYPE_NONE);
}

//--------------------------------------
//�`��
//--------------------------------------
void CObject3D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	CTexture* pTexture = CApplication::GetTexture();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;					//�v�Z�p�}�g���b�N�X

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_Vertex, 0, sizeof(VERTEX_3D));

	D3DXMatrixIdentity(&m_mtxWorld);

	if (m_bBillboard)
	{
		//�}�g���b�N�X�r���[�̎擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�J�����̋t�s��̐ݒ�
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}
	else
	{
		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�ɐݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);
}

//--------------------------------------
//�I��
//--------------------------------------
void CObject3D::Uninit()
{
	if (m_Vertex != nullptr)
	{
		m_Vertex->Release();
		m_Vertex = nullptr;
	}

	CObject::Release();
}

//--------------------------------------
//�ʒu�̃Q�b�^�[
//--------------------------------------
const D3DXVECTOR3 & CObject3D::Getpos() const
{
	return m_pos;
}

//--------------------------------------
//�������ׂ̊֐�
//--------------------------------------
void CObject3D::Addmove(D3DXVECTOR3 move)
{
	m_pos += move;
}

//--------------------------------------
//�e�N�X�`���̐ݒ�
//--------------------------------------
void CObject3D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//--------------------------------------
//�e�N�X�`���A�j���[�V�����̐ݒ�
//--------------------------------------
void CObject3D::PattarnTexture(int nPattarn, int nSplit)
{
	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	nPattarn = (nPattarn) % nSplit;

	//�e�L�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(nPattarn * 1.0f / nSplit, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPattarn * 1.0f / nSplit + 1.0f / nSplit, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattarn * 1.0f / nSplit, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPattarn * 1.0f / nSplit + 1.0f / nSplit, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_Vertex->Unlock();
}

//--------------------------------------
//�F�̐ݒ�
//--------------------------------------
void CObject3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	//�e�L�X�`���̍��W�ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_Vertex->Unlock();
}

//--------------------------------------
//�T�C�Y�̐ݒ�
//--------------------------------------
void CObject3D::SetSize(float fHi, float fWd)
{
	m_Change_Height = fHi;
	m_Change_Width = fWd;

	VERTEX_3D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(fHi * fHi + fWd * fWd) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(fHi, fWd);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = sinf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.y = cosf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_Vertex->Unlock();
}