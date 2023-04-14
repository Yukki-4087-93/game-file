//--------------------------------------------------------------------------------------
//
// ����
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _BILDING_H_
#define _BILDING_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object.h"
//#include "model.h"

class CModel;

//----------------------------------------
//�N���X��`
//�Q�[�����̌����Ɋւ���N���X
//----------------------------------------
class CBilding : public CObject
{
public:
	CBilding();																		//�R���X�g���N�^
	~CBilding();																	//�f�X�g���N�^
	static CBilding* Create(const char* pfile, D3DXVECTOR3 pos, D3DXVECTOR3 rot, ObjType type);	//����
	HRESULT Init() override;														//������
	void Uninit() override;															//�I��
	void Update() override;															//�X�V
	void Draw() override;															//�`��
	D3DXVECTOR3 GetPosOld() { return m_posOld; }									//�����̌Â��ʒu���̎擾
	void Collision();																//�����̓����蔻��𐧌䂷��֐�
	void SetModel(const char* pfile);												//�����̃��f����ύX����֐�
	CModel* GetModel() { return m_pModel; }
	LPD3DXMESH GetMesh();										//���b�V�����̎擾
	D3DXMATRIX GetmtxWorld() { return m_mtxWorld; }				//�}�g���b�N�X���[���h�̎擾
	D3DXMATRIX GetmtxWorldModel();									//�}�g���b�N�X���[���h�̎擾
	void SetColor(bool bcolor);
	D3DXVECTOR3 GetModelpos(); 								//�ʒu�̎擾

private:
	CModel* m_pModel;											//���f���̔z�u��
	D3DXVECTOR3 m_posOld;										//���_
	D3DXMATRIX m_mtxWorld;										//�}�g���b�N�X���[���h
	//DWORD m_nNumMat;											//�}�e���A�����̐�
	//LPD3DXBUFFER m_BuffMat;									//�}�e���A�����
	//LPD3DXMESH m_Mesh;										//���b�V�����
};

#endif // !_BILDING_H_