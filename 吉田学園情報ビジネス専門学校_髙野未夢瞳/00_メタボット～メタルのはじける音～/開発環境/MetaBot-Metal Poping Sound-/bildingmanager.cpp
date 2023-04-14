//--------------------------------------------------------------------------------------
//
// �����̊Ǘ�
// Author::TAKANO
//
//--------------------------------------------------------------------------------------

//--------------------------------------
//�C���N���[�h�t�@�C��
//--------------------------------------
#include "application.h"
#include "bildingmanager.h"
#include "bilding.h"
#include "helperfunction.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "object.h"
#include "camera.h"
#include <stdio.h>
#include <assert.h>

//--------------------------------------
//�萔��`
//--------------------------------------
const float SMALLEST_SQUARESIZE = 100.f;
const float HIGHT_POSITION = 0.0f;
const float WALL_HIGHT = 100.f;

//--------------------------------------
//�R���X�g���N�^
//--------------------------------------
CBildingManager::CBildingManager()
{

}

//--------------------------------------
//�f�X�g���N�^
//--------------------------------------
CBildingManager::~CBildingManager()
{
}

//--------------------------------------
//������
//--------------------------------------
HRESULT CBildingManager::Init()
{
	//���f���̓ǂݍ���
	Load();

	return S_OK;
}

//--------------------------------------
//�I��
//--------------------------------------
void CBildingManager::Uninit()
{
	if (m_pBilding != nullptr)
	{
		m_pBilding->Uninit();
		m_pBilding = nullptr;
	}
}

//--------------------------------------
//�X�V
//--------------------------------------
void CBildingManager::Update()
{
	for (int i = 0; i < MAX_OBJ; i++)
	{//�I�u�W�F�N�g�̑��ʕ��J�E���g����
		CObject *pObj = CObject::Getobject(i);		//�I�u�W�F�N�g�̎擾
		CObject::ObjType objType;					//�I�u�W�F�N�g�^�C�v��錾

		if (pObj == nullptr)
		{//�I�u�W�F�N�g���g�p����Ă��Ȃ������Ƃ�
			continue;						//for���ŏ��ɕԂ�
		}

		//�I�u�W�F�N�g�^�C�v�ϐ��ɃI�u�W�F�N�g�^�C�v������
		objType = pObj->GetObjectType();

		///*�I�u�W�F�N�g�^�C�v�������œ����蔻��̕Ԃ�l���^��������*/
		//if ((objType == CObject::OBJTYPE_BILDING_HELLOWARK ||
		//	objType == CObject::OBJTYPE_BILDING_LANDMARKTOWER ||
		//	objType == CObject::OBJTYPE_BILDING_THUMBSUP ||
		//	objType == CObject::OBJTYPE_BILDING_DTHUMBSUP ||
		//	objType == CObject::OBJTYPE_BILDING_TEMPLE ||
		//	objType == CObject::OBJTYPE_BILDING_APOSTLE) &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(SIZE_PLUS, 0.0f, SIZE_PLUS), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}

		if (objType == CObject::OBJTYPE_BILDING_HELLOWARK ||
			objType == CObject::OBJTYPE_BILDING_LANDMARKTOWER ||
			objType == CObject::OBJTYPE_BILDING_THUMBSUP ||
			objType == CObject::OBJTYPE_BILDING_DTHUMBSUP ||
			objType == CObject::OBJTYPE_BILDING_TEMPLE ||
			objType == CObject::OBJTYPE_BILDING_APOSTLE ||
			objType == CObject::OBJTYPE_SPOWN_BILDING ||
			objType == CObject::OBJTYPE_WALL_LONGLONG_WILD ||
			objType == CObject::OBJTYPE_WALL_LONGLONG_HIGHT ||
			objType == CObject::OBJTYPE_WALL_OUTSIDE_WIDE ||
			objType == CObject::OBJTYPE_WALL_OUTSIDE_HIGHT)
		{
			CBilding* pBuilding = (CBilding*)pObj;
			D3DXVECTOR3 posV, posR, vec;
			D3DXMATRIX mtxWorld;
			posV = CGame::GetCamera()->GetPosV() - pBuilding->GetModelpos();
			posR = CGame::GetCamera()->GetPosR() - pBuilding->GetModelpos();
			mtxWorld = pBuilding->GetmtxWorldModel();

			//�t�s��ɕϊ�
			D3DXMatrixInverse(&mtxWorld, nullptr, &mtxWorld);

			//
			D3DXVec3TransformCoord(&posR, &posR, &mtxWorld);

			//
			D3DXVec3TransformCoord(&posV, &posV, &mtxWorld);

			//posV����posR�̍����x�N�g���ɑ��
			vec = posV - posR;

			//�x�N�g�����P�ɂ��� �������Ɍ��ʂ�ۑ�������́A�������ɕϊ��������x�N�g��������
			D3DXVec3Normalize(&vec, &vec);
			BOOL bHit = true;
			FLOAT pfDistance = 0.0f;

			//�ǂƂ������Ƃ��̔���
			D3DXIntersect(pBuilding->GetMesh(), &posR, &vec, &bHit, nullptr, nullptr, nullptr, &pfDistance, nullptr, nullptr);

			if (pfDistance >= 0.0f)
			{
				//�J���[�̕ύX
				pBuilding->SetColor(bHit);
			}

		}

		//if (objType == OBJTYPE_SPOWN_BILDING &&
		//	CHelperFunction::CircleCollision(m_pos, m_Scale.y * SIZE_PLUS, pObj->Getpos(), SIZE_PLUS))
		//{//�I�u�W�F�N�g�^�C�v���o�����錚���������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}

		//if (objType == CObject::OBJTYPE_WALL_OUTSIDE_WIDE &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(10060.0f, 0.0f, 50.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}

		//if (objType == CObject::OBJTYPE_WALL_OUTSIDE_HIGHT &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(52.0f, 0.0f, 10060.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}

		//if (objType == CObject::OBJTYPE_WALL_WIDE &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(800.0f, 0.0f, 60.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		//}

		//if (objType == CObject::OBJTYPE_WALL_HIGHT &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(60.0f, 0.0f, 800.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		//}

		//if (objType == CObject::OBJTYPE_WALL_LONGLONG_WILD &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(2600.0f, 0.0f, 60.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�

		//}

		//if (objType == CObject::OBJTYPE_WALL_LONGLONG_HIGHT &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(60.0f, 0.0f, 2600.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}

		//if (objType == CObject::OBJTYPE_FENCE_WIDE &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(460.0f, 0.0f, 30.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}

		//if (objType == CObject::OBJTYPE_FENCE_HIGHT &&
		//	CHelperFunction::BoxCollision(m_pos, D3DXVECTOR3(m_Scale.x * SIZE_PLUS, 0.0f, m_Scale.z * SIZE_PLUS), pObj->Getpos(), D3DXVECTOR3(30.0f, 0.0f, 460.0f), m_posOld))
		//{//�I�u�W�F�N�g�^�C�v�������������蔻�菈�����^�Ȃ�
		//	m_pos = m_posOld;						//�ʒu���ߋ��̈ʒu�ɐݒ�
		//}
	}

#ifdef _DEBUG

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_F1))
	{
		if (m_pBilding != nullptr)
		{
			m_pBilding->Uninit();
			m_pBilding = nullptr;
		}
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_F2))
	{
		m_pBilding = CBilding::Create("Data/Model/Fence/Fence.x",
			CGame::GetPlayer()->GetPos(),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			CObject::OBJTYPE_FENCE_WIDE);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_F3))
	{
		m_pBilding = CBilding::Create("Data/Model/Fence/Fence.x",
			CGame::GetPlayer()->GetPos(),
			D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f),
			CObject::OBJTYPE_FENCE_HIGHT);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_F5))
	{
		m_pBilding = CBilding::Create("Data/Model/Building/Factory.x",
			CGame::GetPlayer()->GetPos(),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			CObject::OBJTYPE_SPOWN_BILDING);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_F6))
	{
		m_pBilding = CBilding::Create("Data/Model/Wall/WALL_LONGBELONG.x",
			CGame::GetPlayer()->GetPos(),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			CObject::OBJTYPE_WALL_LONGLONG_HIGHT);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_F7))
	{
		m_pBilding = CBilding::Create("Data/Model/Wall/WALL_LONGBELONG.x",
			CGame::GetPlayer()->GetPos(),
			D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f),
			CObject::OBJTYPE_WALL_LONGLONG_WILD);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_F8))
	{
		m_pBilding = CBilding::Create("Data/Model/Wall/WALL_NOMAL.x",
			CGame::GetPlayer()->GetPos(),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			CObject::OBJTYPE_WALL_HIGHT);
	}

	if (CApplication::GetKyeboard()->GetkeyboardTrigger(DIK_SPACE))
	{
		Save();
	}

#endif // _DEBUG
}

//--------------------------------------
//�`��
//--------------------------------------
void CBildingManager::Draw()
{
}

//--------------------------------------
//���f���̓ǂݍ���
//--------------------------------------
void CBildingManager::Load()
{
	//�t�@�C���ɏ�������
	FILE *pFile;        //�t�@�C���|�C���^��錾

						//�t�@�C�����J��
	pFile = fopen(OPEN_FILE, "r");

	if (pFile != nullptr)
	{//�t�@�C�����J�����Ƃ�
	 //�t�@�C���ɐ��l�������o��

		for (int i = 0; i < MAX_OBJ; i++)
		{
			int nNumber = 0;
			D3DXVECTOR3 pos, rot;
			fscanf(pFile, "%d", &nNumber);
			fscanf(pFile, "%f,%f,%f", &pos.x, &pos.y, &pos.z);
			fscanf(pFile, "%f,%f,%f", &rot.x, &rot.y, &rot.z);

			switch (nNumber)
			{
			case 7:

				CBilding::Create("Data/Model/Building/Hello_Work_C.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_BILDING_HELLOWARK);

				break;

			case 8:

				CBilding::Create("Data/Model/Building/Landtower.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_BILDING_LANDMARKTOWER);

				break;

			case 9:

				CBilding::Create("Data/Model/Building/Thumbs_Up.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_BILDING_THUMBSUP);

				break;

			case 10:

				CBilding::Create("Data/Model/Building/DThumbs_Up.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_BILDING_DTHUMBSUP);

				break;

			case 11:

				CBilding::Create("Data/Model/Building/teratera.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_BILDING_TEMPLE);

				break;

			case 12:

				CBilding::Create("Data/Model/Building/shito.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_BILDING_APOSTLE);

				break;

			case 13:

				CBilding::Create("Data/Model/Building/Factory.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CObject::OBJTYPE_SPOWN_BILDING);

				break;

			case 14:

				CBilding::Create("Data/Model/Wall/WALL_NOMAL.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_WALL_WIDE);

				break;

			case 15:

				CBilding::Create("Data/Model/Wall/WALL_NOMAL.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_WALL_HIGHT);

				break;

			case 16:

				CBilding::Create("Data/Model/Wall/WALL_LONGBELONG.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_WALL_LONGLONG_WILD);

				break;

			case 17:

				CBilding::Create("Data/Model/Wall/WALL_LONGBELONG.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_WALL_LONGLONG_HIGHT);

				break;

			case 18:

				CBilding::Create("Data/Model/Wall/WALL_OUTSIDER.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_WALL_OUTSIDE_WIDE);

				break;

			case 19:

				CBilding::Create("Data/Model/Wall/WALL_OUTSIDER.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_WALL_OUTSIDE_HIGHT);

				break;

			case 20:

				CBilding::Create("Data/Model/Fence/Fence.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_FENCE_WIDE);

				break;

			case 21:

				CBilding::Create("Data/Model/Fence/Fence.x",
					D3DXVECTOR3(pos.x, pos.y, pos.z),
					D3DXVECTOR3(rot.x, rot.y, rot.z),
					CObject::OBJTYPE_FENCE_HIGHT);

				break;

			default:
				break;
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	else
	{//�t�@�C�����J���Ȃ������Ƃ�
		assert(false);				//�v���O�������~�߂�
	}
}

//--------------------------------------
//�ۑ�
//--------------------------------------
void CBildingManager::Save()
{
	//�t�@�C���ɏ�������
	FILE *pFile;        //�t�@�C���|�C���^��錾

						//�t�@�C�����J��
	pFile = fopen(OPEN_FILE, "w");

	if (pFile != nullptr)
	{//�t�@�C�����J�����Ƃ�
	 //�t�@�C���ɐ��l�������o��

		for (int i = 0; i < MAX_OBJ; i++)
		{
			CObject* pObj = CObject::Getobject(i);
			CObject::ObjType objType;					//�I�u�W�F�N�g�^�C�v��錾

			if (pObj == nullptr)
			{//�I�u�W�F�N�g���g�p����Ă��Ȃ������Ƃ�
				continue;						//for���ŏ��ɕԂ�
			}

			//�I�u�W�F�N�g�^�C�v�ϐ��ɃI�u�W�F�N�g�^�C�v������
			objType = pObj->GetObjectType();

			if (objType == CObject::OBJTYPE_BILDING_HELLOWARK ||
				objType == CObject::OBJTYPE_BILDING_LANDMARKTOWER ||
				objType == CObject::OBJTYPE_BILDING_THUMBSUP ||
				objType == CObject::OBJTYPE_BILDING_DTHUMBSUP ||
				objType == CObject::OBJTYPE_BILDING_TEMPLE ||
				objType == CObject::OBJTYPE_BILDING_APOSTLE ||
				objType == CObject::OBJTYPE_SPOWN_BILDING ||
				objType == CObject::OBJTYPE_WALL_WIDE ||
				objType == CObject::OBJTYPE_WALL_HIGHT ||
				objType == CObject::OBJTYPE_WALL_LONGLONG_WILD ||
				objType == CObject::OBJTYPE_WALL_LONGLONG_HIGHT ||
				objType == CObject::OBJTYPE_WALL_OUTSIDE_WIDE ||
				objType == CObject::OBJTYPE_WALL_OUTSIDE_HIGHT ||
				objType == CObject::OBJTYPE_FENCE_WIDE ||
				objType == CObject::OBJTYPE_FENCE_HIGHT)
			{
				fprintf(pFile, "%d\n", objType);
				fprintf(pFile, "%f,%f,%f \n", pObj->Getpos().x, pObj->Getpos().y, pObj->Getpos().z);
				fprintf(pFile, "%f,%f,%f \n\n", pObj->GetRot().x, pObj->GetRot().y, pObj->GetRot().z);
			}
		}

		//�t�@�C�������
		fclose(pFile);
	}

	else
	{//�t�@�C�����J���Ȃ������Ƃ�
		assert(false);				//�v���O�������~�߂�
	}
}
