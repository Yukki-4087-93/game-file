//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "object.h"
#include "object2d.h"
#include "renderer.h"
#include "main.h"

//--------------------------------------
//�ÓI�����o�ϐ��̐錾
//--------------------------------------
CObject *CObject::m_apObject[MAX_OBJ] = {};

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CObject::CObject()
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{
			m_apObject[nCnt] = this;
			m_nID = nCnt;
			break;
		}
	}
}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CObject::~CObject()
{
}

//--------------------------------------
//�|�X
//--------------------------------------
D3DXVECTOR3 CObject::Getpos()
{
	return m_pos;
}

//--------------------------------------
//�I�u�W�F�N�g�̉��
//--------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJ; i++)
	{
		if (m_apObject[i] != nullptr)
		{
			m_apObject[i]->Release();
		}
	}
}

//--------------------------------------
//�I�u�W�F�N�g�̍X�V
//--------------------------------------
void CObject::UpdateAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->Update();
		}
	}
}

//--------------------------------------
//�I�u�W�F�N�g�̕`��
//--------------------------------------
void CObject::DrawAll()
{
	for (int nCnt = 0; nCnt < MAX_OBJ; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_apObject[nCnt]->Draw();
		}
	}
}

//--------------------------------------
//�I�u�W�F�N�g�̕������
//--------------------------------------
void CObject::Release()
{
	if (m_apObject[m_nID] != nullptr)
	{
		const int nId = m_nID;
		delete m_apObject[nId];
		m_apObject[nId] = nullptr;
	}
}

//--------------------------------------
//�I�u�W�F�N�g�̏��擾
//--------------------------------------
CObject * CObject::Getobject(int nID)
{
	return m_apObject[nID];
}

//--------------------------------------
//�I�u�W�F�N�g�^�C�v�̐ݒ�
//--------------------------------------
void CObject::SetObjectType(ObjType objtype)
{
	m_objType = objtype;
}

//--------------------------------------
//�I�u�W�F�N�g�^�C�v�̏��擾
//--------------------------------------
CObject::ObjType CObject::GetObjectType()
{
	return m_objType;
}
