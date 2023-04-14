//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "object2d.h"
#include "renderer.h"
#include "application.h"
#include "game.h"
#include "texture.h"
#include "main.h"
#include <assert.h>

//--------------------------------------
//�萔��`
//--------------------------------------
// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CObject2D::CObject2D()
{
	m_pos = { 0.0f,0.0f,0.0f };
	m_texture = CTexture::TEXTURE_NONE;
	m_Change_Height = 0.0f;
	m_Change_Width = 0.0f;
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CObject2D::~CObject2D()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_Vertex, NULL);

	VERTEX_2D * pVtx;

	m_Change_Height = 30.0f;
	m_Change_Width = 30.0f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(m_Change_Height * m_Change_Height + m_Change_Width * m_Change_Width) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(m_Change_Height, m_Change_Width);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.z = 0.0f;
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
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
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, float ObfHi, float ObfWd)
{
	CObject2D* pObject2D;

	pObject2D = new CObject2D;

	if (pObject2D != nullptr)
	{
		pObject2D->Init();
		pObject2D->Setpos(pos);
		pObject2D->SetSize(ObfHi, ObfWd);
	}
	else
	{
		assert(false);
	}

	return pObject2D;
}

//--------------------------------------
//�X�V
//--------------------------------------
void CObject2D::Update()
{
	assert(m_objType != OBJTYPE_NONE);

	VERTEX_2D* pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N���A���_���ւ̃|�C���^���擾
	m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_Vertex->Unlock();
}

//--------------------------------------
//�`��
//--------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	CTexture* pTexture = CApplication::GetTexture();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_Vertex, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//--------------------------------------
//�I��
//--------------------------------------
void CObject2D::Uninit()
{
	if (m_Vertex != nullptr)
	{
		m_Vertex->Release();
		m_Vertex = nullptr;
	}

	CObject::Release();
}

//--------------------------------------
//�|�X�̃Z�b�g
//--------------------------------------
void CObject2D::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VERTEX_2D * pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_Vertex->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	pVtx[0].pos.x = pos.x + sinf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.y = pos.y + cosf(m_rot.z + (-D3DX_PI + m_fAngle)) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + sinf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.y = pos.y + cosf(m_rot.z + (D3DX_PI - m_fAngle)) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + sinf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.y = pos.y + cosf(m_rot.z + (m_fAngle * -1.0f)) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + sinf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.y = pos.y + cosf(m_rot.z + (m_fAngle * 1.0f)) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_Vertex->Unlock();
}

//--------------------------------------
//�ʒu�̃Q�b�^�[
//--------------------------------------
const D3DXVECTOR3 & CObject2D::Getpos() const
{
	return m_pos;
}

//--------------------------------------
//�������ׂ̊֐�
//--------------------------------------
void CObject2D::Addmove(D3DXVECTOR3 move)
{
	m_pos += move;
}

//--------------------------------------
//�e�N�X�`���̐ݒ�
//--------------------------------------
void CObject2D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//--------------------------------------
//�e�N�X�`���A�j���[�V�����̐ݒ�
//--------------------------------------
void CObject2D::PattarnTexture(int nPattarn, int nSplit)
{
	VERTEX_2D * pVtx;

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
void CObject2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D * pVtx;

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
void CObject2D::SetSize(float fHi, float fWd)
{
	m_Change_Height = fHi;
	m_Change_Width = fWd;

	//�Ίp���̒������Z�o����
	m_fLength = sqrtf(fHi * fHi + fWd * fWd) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f(fHi, fWd);
}