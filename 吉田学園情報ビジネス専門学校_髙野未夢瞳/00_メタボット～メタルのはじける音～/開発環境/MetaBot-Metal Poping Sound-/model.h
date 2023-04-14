//-----------------------------------------------------------------------------------------------------------
//
//���b�V��
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _MODEL_H_													//���̃}�N����`���Ȃ���Ȃ�������
#define _MODEL_H_													//��d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------
//#include <d3dx9.h>
#include "object.h"

//-----------------------------------------------------------
//�N���X��`
//���f���֌W
//-----------------------------------------------------------
class CModel
{
public:

	enum MODEL_TYPE
	{
		TYPE_NONE = -1,
		TYPE_PLAYER = 0,
		TYPE_ENEMY,
		TYPE_BILDING,
		TYPE_MAX
	};

	CModel();															//�R���X�g���N�^
	~CModel();															//�f�X�g���N�^
	static CModel *Create(const char* pfile, const D3DXVECTOR3 & pos, const D3DXVECTOR3 & rot, MODEL_TYPE type);			//����
	HRESULT Init();										//������
	void Uninit();										//�I��
	void Update();										//�X�V
	void Draw();										//�`��
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�̐ݒ�
	D3DXVECTOR3 GetPos() { return m_pos; }								//�ʒu�̎擾
	D3DXVECTOR3 GetRot() { return m_rot; }								//�p�x�̎擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }						//�p�x�̐ݒ�
	void SetParent(CModel* pmodel) { m_pParent = pmodel; }				//�e�̏����擾����
	D3DXMATRIX GetMtxWorld() { return m_mtxWorld; }						//�}�g���b�N�X���[���h���擾����
	D3DXVECTOR3 GetStartPoint() { return m_StartPoint; }				//�����ʒu���擾����֐�
	D3DXVECTOR3 GetStartRotation() { return m_StartRotation; }			//�����ʒu���擾����֐�
	void SetModelType(MODEL_TYPE type) { m_ModelType = type; }			//���f���^�C�v�̐ݒ�
	MODEL_TYPE GetModelType() { return m_ModelType; }					//���f���^�C�v�̏����擾����
	D3DXVECTOR3 GetVtxMax() { return m_VtxMax; }
	D3DXVECTOR3 GetVtxMin() { return m_VtxMin; }
	LPD3DXMESH GetMedh() { return m_Mesh; }								//���b�V�����̎擾
	void SetModel(const char* pfile);									//���f���̔z�u
	void SetChangeColor(bool bcolor) { m_bChangeColor = bcolor; }		//�J���[��ݒ肷��֐�

private:
	MODEL_TYPE m_ModelType;
	LPD3DXMESH m_Mesh;													//���b�V��
	LPD3DXBUFFER m_BuffMat;												//�o�[�e�b�N�X
	DWORD m_nNumMat;													//�}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;												//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;													//���_
	D3DXVECTOR3 m_rot;													//����
	D3DXVECTOR3 m_VtxMax;												//�ő�
	D3DXVECTOR3 m_VtxMin;												//�ŏ�
	int m_nIdxModelParent;												//�e���f���̔ԍ�
	int m_nNubParts;													//���f���̔ԍ�
	CModel *m_pParent;													//�e���f���ւ̃|�C���^
	D3DXMATRIX m_mtxParent;												//�e�̃}�g���b�N�X
	D3DXVECTOR3 m_StartPoint;											//�����ʒu
	D3DXVECTOR3 m_StartRotation;										//�����p�x
	bool m_bChangeColor;												//�J���[��ύX���邩�ς���ϐ�
};

#endif // !_MODEL_H_
