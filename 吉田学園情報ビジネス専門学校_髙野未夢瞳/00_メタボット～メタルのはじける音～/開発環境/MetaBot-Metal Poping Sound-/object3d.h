//--------------------------------------------------------------------------------------
//
// �I�u�W�F�N�g
// Author::TAKANO
//
//--------------------------------------------------------------------------------------
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//----------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------
#include "object.h"
#include "texture.h"

//----------------------------------------
//�N���X��`
//�I�u�W�F�N�g
//----------------------------------------
class CObject3D : public CObject
{
public:
	// ���_�f�[�^
	struct VERTEX_3D
	{
		D3DXVECTOR3 pos;														//���_���W
		D3DXVECTOR3 nor;														//�@���x�N�g��
		D3DCOLOR col;															//���_�J���[
		D3DXVECTOR2 tex;														//�e�N�X�`���̍��W
	};

public:
	CObject3D();																//�R���X�g���N�^
	~CObject3D();																//�f�X�g���N�^
	HRESULT Init()override;														//������
	static CObject3D * Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ObfHi, float ObfWd, CTexture::TEXTURE tex,bool bBillboard);		//�N���G�C�g
	void Update()override;														//�X�V
	void Draw()override;														//�`��
	void Uninit()override;														//�I��
	const D3DXVECTOR3& Getpos() const;											//�ʒu�̎擾
	void Addmove(D3DXVECTOR3 move);												//�ړ��ʂ̉��Z
	void SetTexture(CTexture::TEXTURE texture);									//�e�N�X�`���̐ݒ�
	void PattarnTexture(int nPattarn, int nSplit);								//�e�N�X�`���A�j���[�V�����̐ݒ�
	void SetColor(D3DXCOLOR col);												//�I�u�W�F�N�g�̃J���[�ݒ�
	void SetSize(float fHi, float fWd);											//�T�C�Y�ݒ�
	void SetBillboard(bool bswitch) { m_bBillboard = bswitch; }					//�r���{�[�h�̐ݒ�

protected:
	LPDIRECT3DVERTEXBUFFER9 m_Vertex;											//���_���擾�̎擾
	CTexture::TEXTURE m_texture;												//�e�N�X�`���̗񋓌^
	D3DXMATRIX m_mtxWorld;														//���[���h�}�g���b�N�X
	float m_fAngle;																//�A���O��
	float m_fLength;															//�����O�X
	float m_Change_Height;														//�ύX���鍂��
	float m_Change_Width;														//�ύX���镝
	float m_fPatternAnim;														//�A�j���[�V�����J�E���^�[
	int m_nCounterAnim;															//�A�j���[�V�����J�E���^�[
	bool m_bBillboard;															//�r���{�[�h���ۂ�

};

#endif // !_OBJECT3D_H_
