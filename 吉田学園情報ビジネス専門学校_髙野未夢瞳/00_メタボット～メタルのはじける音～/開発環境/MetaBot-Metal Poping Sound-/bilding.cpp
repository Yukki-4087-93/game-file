//--------------------------------------------------------------------------------------
//
// ����
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "bilding.h"
#include "model.h"
#include "helperfunction.h"
#include "player.h"
#include "enemy.h"

//----------------------------------------
//�R���X�g���N�^
//----------------------------------------
CBilding::CBilding()
{
}

//----------------------------------------
//�f�X�g���N�^
//----------------------------------------
CBilding::~CBilding()
{
}

//----------------------------------------
//����
//----------------------------------------
CBilding * CBilding::Create(const char* pfile, D3DXVECTOR3 pos, D3DXVECTOR3 rot, ObjType type)
{
	//���I�m��
	CBilding *pBilding = new CBilding;

	if (pBilding != nullptr)
	{//�r���f�B���O�|�C���^�ɒl�������Ă�����
		pBilding->Init();										//������
		pBilding->SetModel(pfile);								//���f���̐ݒ�
		pBilding->SetPos(pos);									//�ʒu�̐ݒ�
		pBilding->SetRot(rot);									//�p�x�̐ݒ�
		pBilding->SetObjectType(type);							//�I�u�W�F�N�g�^�C�v�̐ݒ�
	}

	//�l��Ԃ�
	return pBilding;
}

//----------------------------------------
//������
//----------------------------------------
HRESULT CBilding::Init()
{
	m_pos = D3DXVECTOR3(0.f, 0.f, 0.f);

	return S_OK;
}

//----------------------------------------
//�I��
//----------------------------------------
void CBilding::Uninit()
{
	//�I�u�W�F�N�g�̊J��
	CObject::Release();
}

//----------------------------------------
//�X�V
//----------------------------------------
void CBilding::Update()
{
	m_posOld = m_pos;

	Collision();
}

//----------------------------------------
//�`��
//----------------------------------------
void CBilding::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();		//�f�o�C�X�̃|�C���^

	D3DXMATRIX mtxRot, mtxTrans;												//�v�Z�p�}�g���b�N�X

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

	//�z�u�����������`�悷��
	m_pModel->Draw();
}

//----------------------------------------
//�����蔻��
//----------------------------------------
void CBilding::Collision()
{
	if (CGame::GetPlayer == nullptr)
	{//�v���C���[���g�p����Ă��Ȃ��Ƃ�
		return;						//����ȏ�ʂ��Ȃ�
	}

	if (CHelperFunction::CircleCollision(m_pos, 20.0f, CGame::GetPlayer()->GetPos(), 20.0f))
	{//�����蔻��̕Ԃ�l���^�Ȃ�
		m_pos = m_posOld;			//�ʒu���ߋ��̈ʒu�ɐݒ�
	}
}

//----------------------------------------
//���f���̐ݒ�
//----------------------------------------
void CBilding::SetModel(const char * pfile)
{
	//���f���̐���
	m_pModel = CModel::Create(pfile, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModel::TYPE_BILDING);
}

//----------------------------------------
//���f���̐ݒ�
//----------------------------------------
LPD3DXMESH CBilding::GetMesh()
{
	return m_pModel->GetMedh();
}

//----------------------------------------
//���f���̃}�g���b�N�X���擾
//----------------------------------------
D3DXMATRIX CBilding::GetmtxWorldModel()
{
	return m_pModel->GetMtxWorld();
}

//----------------------------------------
//�J���[�̐ݒ�
//----------------------------------------
void CBilding::SetColor(bool bcolor)
{
	m_pModel->SetChangeColor(bcolor);
}

//----------------------------------------
//�J���[�̐ݒ�
//----------------------------------------
D3DXVECTOR3 CBilding::GetModelpos()
{
	return m_pModel->GetPos();
}
