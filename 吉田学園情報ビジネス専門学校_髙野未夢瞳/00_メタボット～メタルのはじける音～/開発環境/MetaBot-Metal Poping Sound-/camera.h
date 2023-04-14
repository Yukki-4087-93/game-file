//-----------------------------------------------------------------
//
// �J����
// Author::TAKANO
//
//-----------------------------------------------------------------
#ifndef _CAMERA_H_									//���̃}�N����`���Ȃ���Ȃ�������
#define _CAMERA_H_									//��d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include <d3dx9.h>

//----------------------------------------
//�}�N����`
//----------------------------------------
#define MAX_SPEED		(0.3f)						// �ړ��Ɏg�p����ő呬�x

//----------------------------------------
//�N���X��`
//----------------------------------------
class CCamera
{
public:
	CCamera();										// �R���X�g���N�^
	~CCamera();										// �f�X�g���N�^
	static CCamera* Create(D3DXVECTOR3 pos);		// ����
	void Init();									// ������
	void Uninit();									// �I��
	void Update();									// �X�V
	void Set();										// �J�����̔z�u
	D3DXVECTOR3 GetRot() { return m_rot; }			// �p�x
	D3DXVECTOR3 GetPosV() { return m_WorldPosV; }			// �p�x
	D3DXVECTOR3 GetPosR() { return m_WorldPosR; }			// �p�x
	D3DXMATRIX GetWorldmtx() { return m_mtxWorld; }			// �p�x
	void Sequence(int nFlame, float fMagnitude);		// �J������h�炷�֐�

private:
	int m_nCameraFlame;								// �J������h�炷�ۂɎg�p����J�E���g�ϐ�
	float m_fCameraMagnitude;						// �J������h�炷�ۂɎg�p����k�x�𐧌䂷��ϐ�
	D3DXVECTOR3 m_InitPosV;							// ���_
	D3DXVECTOR3 m_InitPosR;							// �����_
	D3DXVECTOR3 m_VecU;							// ����
	D3DXVECTOR3 m_WorldPosV;						// ���[�J�����W�n
	D3DXVECTOR3 m_WorldPosR;						// ���[�J�����W�n
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_rotDest;						// �p�x�̃t�H�t�H�t�H
	D3DXMATRIX m_mtxprojection;					// �}�g���b�N�X�̓��e
	D3DXMATRIX m_mtxWorld;						// �}�g���b�N�X���[���h
	D3DXMATRIX m_mtxView;							// �}�g���b�N�X�̎��_
	float m_fDistance;							// ����
};

#endif // !CAMERA_H_
