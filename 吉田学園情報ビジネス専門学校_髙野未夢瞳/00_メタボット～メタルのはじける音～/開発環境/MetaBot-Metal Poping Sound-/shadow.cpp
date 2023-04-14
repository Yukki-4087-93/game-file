////-----------------------------------------------------------------------------------------------------------
////
////�e
////Author;takano
////
////-----------------------------------------------------------------------------------------------------------
//
////--------------------------
////�C���N���[�h�t�@�C��
////--------------------------
//#include "application.h"
//#include "renderer.h"
//#include "shadow.h"
//
////--------------------------
////�萔��`
////--------------------------
//const int MAX_SHADOW = 128;								//�e�̍ő吔
//
//CShadow::CShadow()
//{
//}
//
//CShadow::~CShadow()
//{
//}
//
////-------------------------
////�e�̏���������
////-------------------------
//HRESULT CShadow::Init()
//{
//	CObject3D::Init();
//
//	return S_OK;
//}
//
////---------------------
////�e�̏I������
////---------------------
//void CShadow::Uninit()
//{
//	CObject3D::Uninit();
//}
//
////----------------
////�e�̍X�V����
////----------------
//void CShadow::Update()
//{
//	
//}
//
////--------------------------------
////�e�̕`�揈��
////--------------------------------
//void CShadow::Draw()
//{
//	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
//	D3DXMATRIX mtxRot, mtxTrans, mtxWorld;				//�v�Z�p���C�g���b�N�X
//
//	//A�u�����f�B���O�����Z�����ɐݒ�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, nullptr);
//
//	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
//	{
//		//���[���h�}�g���b�N�X�̏�����
//		D3DXMatrixIdentity(&mtxWorld);
//
//		//�����𔽉f
//		D3DXMatrixRotationYawPitchRoll(&mtxRot, s_aShadow[nCnt].rot.y, s_aShadow[nCnt].rot.x, s_aShadow[nCnt].rot.z);
//
//		D3DXMatrixMultiply(&s_aShadow[nCnt].mtxWorld, &s_aShadow[nCnt].mtxWorld, &mtxRot);
//
//		//�ʒu�𔽉f
//		D3DXMatrixTranslation(&mtxTrans, s_aShadow[nCnt].pos.x, s_aShadow[nCnt].pos.y, s_aShadow[nCnt].pos.z);
//
//		D3DXMatrixMultiply(&s_aShadow[nCnt].mtxWorld, &s_aShadow[nCnt].mtxWorld, &mtxTrans);
//
//
//		//���[���h�}�g���b�N�X�ɐݒ�
//		pDevice->SetTransform(D3DTS_WORLD, &s_aShadow[nCnt].mtxWorld);
//
//		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
//
//		//���_�t�H�[�}�b�g
//		pDevice->SetFVF(VERTEX_3D);
//
//		//�|���S���̕`��
//		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
//			nCnt * 4,							//�`�悷��ŏ��̒��_�C���f�b�N�X
//			2);										//�|���S����
//	}
//
//	//A�u�����f�B���O�����ɖ߂�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//
//	pDevice->SetTexture(0, NULL);
//}
//
////-------------------
////�e�̐ݒ菈��
////-------------------
//int CShadow::Set(D3DXVECTOR3 pos, float fRadius)
//{
//
//}